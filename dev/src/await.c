/**
 * @file await.c
 * 
 * @date 2019-11-19
 * @author twatorowski 
 * 
 * @brief Asynchronous wait function
 */

#include "assert.h"
#include "config.h"
#include "err.h"
#include "dev/watchdog.h"
#include "stm32l476/nvic.h"
#include "stm32l476/rcc.h"
#include "stm32l476/timer.h"
#include "sys/atomic.h"
#include "sys/critical.h"
#include "sys/cb.h"
#include "sys/sem.h"
#include "util/elems.h"
#include "util/msblsb.h"

/* awaiters list indices */
static uint32_t head, tail, alloc;
/* operation callback */
static struct awaiter {
    /* number of milliseconds to wait */
    uint32_t ms;
    /* pointer to the callback function */
    cb_t callback;
    /* callback argument */
    void *arg;
} exec[8], list[16];

/* append callback to the awaiters list */
static int Await_AddAwaiter(uint16_t ms, cb_t cb, void *arg)
{
    /* local copy of the alloc index. this is the index under which the 
     * callback will be stored */
    uint32_t _alloc;

    /* allocate space for the callback */
    do {
        /* read current value of the alloc function */
        _alloc = Atomic_LDR32(&alloc);
        /* no space for next callback */
        if (_alloc - tail == elems(list))
            return EFATAL;
    /* try to store */
    } while (Atomic_STR32(&alloc, _alloc + 1) != EOK);

    /* store the callback */
    struct awaiter *a = &list[_alloc % elems(list)];
    /* fill in the information */
    a->callback = cb, a->arg = arg, a->ms = ms;

    /* 1st in line? */
    if (_alloc == head) {
        /* update the head pointer to the most actual */
        do {
            Atomic_LDR32(&head);
        /* this check will fail if the interrupt has occurred during read */
        } while (Atomic_STR32(&head, (volatile uint32_t)alloc) != EOK);
        /* kick the interrupt routine, it will do the rest! */
        NVIC_SETPENDING(STM32_INT_TIM3);
    }

    /* report status */
    return EOK;
}

/* timer3 isr */
void Await_TIM3Isr(void)
{
    /* clear flags */
    uint32_t sr = TIM3->SR;
    /* clear the interrupt flags */
    TIM3->SR = ~sr;
    /* execution is still not done */
    int running = 0;

    /* process all awaiters on the execution list */
    for (int i = 0; i < (int)elems(exec); i++) {
        /* get the valid pointer */
        struct awaiter *e = &exec[i];
        /* consume a millisecond */
        if ((sr & TIM_SR_UIF) && e->ms)
            e->ms--;
        /* we are still running the loop */
        if (e->ms)
            running = 1;
        /* call the callback, and then clear it's pointer */
        if (e->ms == 0 && e->callback) 
            e->callback(e->arg), e->callback = 0; 
        /* got the free entry? fetch the awaiter from the list */
        if (e->callback == 0 && tail != head) {
            /* get the first element from the list */
            struct awaiter *l = &list[tail % elems(list)];
            /* copy the entry */
            e->ms = l->ms, e->arg = l->arg, e->callback = l->callback;
            /* free up the pointer */
            tail++, running = 1;
        }
    }

    /* execution is not complete yet */
    if (!running) {
        /* disable the timer */
        STM32_BB(&TIM3->CR1, LSB(TIM_CR1_CEN)) = 0;
    /* still got some awaiters on the waiting list? */
    } else {
        /* keep the timer enabled */
        STM32_BB(&TIM3->CR1, LSB(TIM_CR1_CEN)) = 1;
    }
}

/* initialize the module */
int Await_Init(void)
{
    /* enter the critical section */
    Critical_Enter();
    /* enable timer */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

    /* set the prescaler value */
    TIM3->PSC = (CPUCLOCK_FREQ / 1000000) - 1;
    /* 1ms pulse */
    TIM3->ARR = 999;
    /* do not react to artificially generated update events */
    TIM3->CR1 = TIM_CR1_URS | TIM_CR1_OPM;
    /* apply the prescaler value */
    TIM3->EGR = TIM_EGR_UG;
    /* setup interrupts */
    TIM3->DIER = TIM_DIER_UIE;
    
    /* enable interrupts within the nvic */
    NVIC_ENABLEINT(STM32_INT_TIM3);
    NVIC_SETINTPRI(STM32_INT_TIM3, INT_PRI_AWAIT);

    /* enter the critical section */
    Critical_Exit();

    /* report status */
    return EOK;
}

/* schedule call after some time has passed */
void * Await_CallMeLater(int ms, cb_t cb, void *arg)
{
    /* sanity checks */
    assert(ms >= 0, "await: invalid ms value", ms);
    assert(Await_AddAwaiter(ms, cb, arg) == EOK, 
        "await: no space for caller", cb);
    /* report pointer */
    return 0;
}
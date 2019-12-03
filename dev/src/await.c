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
} awaiters[16];

/* append callback to the awaiters list */
static int Await_AddAwaiter(uint16_t ms, cb_t cb)
{
    /* local copy of the alloc index. this is the index under which the 
     * callback will be stored */
    uint32_t _alloc;

    /* allocate space for the callback */
    do {
        /* read current value of the alloc function */
        _alloc = Atomic_LDR32(&alloc);
        /* no space for next callback */
        if (_alloc - tail == elems(awaiters))
            return EFATAL;
    /* try to store */
    } while (Atomic_STR32(&alloc, _alloc + 1) != EOK);

    /* store the callback */
    struct awaiter *a = &awaiters[_alloc % elems(awaiters)];
    /* fill in the information */
    a->callback = cb, a->ms = ms;

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

    /* process all awaiters on the list */
    for (uint32_t i = tail; i < head; i++) {
        /* get the valid pointer */
        struct awaiter *a = &awaiters[i % elems(awaiters)];
        /* consume a millisecond on when timer overflows */
        if (sr & TIM_SR_UIF)
            a->ms--;
        /* call the callback, and then clear it's pointer */
        if (a->ms == 0 && a->callback) 
            a->callback(0), a->callback = 0;
        /* drop the entry as the callback was already executed */
        if (!a->callback && i == tail)
            tail++;
    }

    /* enable or disable the timer depending on whether we still have 
     * some awaiters queued. This is the only place (and it's not re-entrant) 
     * that messes with the timer internals so it is safe to implement this 
     * here */
    if (tail == head) {
        /* disable the timer */
        STM32_BB(&TIM3->CR1, LSB(TIM_CR1_CEN)) = 0;
    /* still got some awaiters on the waiting list? */
    } else {
        /* if the async await is used for the blocking functions then it would be 
         * nice to kick the dog once in a while! */
        Watchdog_Kick();
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
    TIM3->PSC = 4799;
    /* 1ms pulse */
    TIM3->ARR = 10;
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
void * Await_CallMeLater(int ms, cb_t cb)
{
    /* sanity checks */
    assert(ms >= 0, "await: invalid ms value", ms);
    assert(Await_AddAwaiter(ms, cb) == EOK, "await: no space for caller", 
        (uintptr_t)cb);
    /* report pointer */
    return 0;
}
/**
 * @file invoke.c
 * 
 * @date 2019-12-06
 * @author twatorowski 
 * 
 * @brief Abstract module that allows for invoking a callback on different 
 * context. The so called different context is simply an interrupt.
 * 
 * Yes, I know there is no such word as 'invokee' but I just made it up and you,
 * dear reader, have to live with it.
 */

#include "assert.h"
#include "config.h"
#include "err.h"
#include "stm32l476/nvic.h"
#include "sys/atomic.h"
#include "sys/cb.h"
#include "sys/critical.h"
#include "util/elems.h"

/* awaiters list indices */
static uint32_t head, tail, alloc;
/* invokers list element */
static struct invokee {
    /* callback */
    cb_t callback;
    /* callback argument */
    void *arg;
} invokees[16];

/* append callback to the invokees list */
static int Invoke_AddInvokee(cb_t cb, void *arg)
{
    /* local copy of the alloc index. this is the index under which the 
     * callback will be stored */
    uint32_t _alloc;

    /* allocate space for the callback */
    do {
        /* read current value of the alloc function */
        _alloc = Atomic_LDR32(&alloc);
        /* no space for next callback */
        if (_alloc - tail == elems(invokees))
            return EFATAL;
    /* try to store */
    } while (Atomic_STR32(&alloc, _alloc + 1) != EOK);

    /* store the callback */
    struct invokee *i = &invokees[_alloc % elems(invokees)];
    /* fill in the information */
    i->callback = cb, i->arg = arg;

    /* 1st in line? */
    if (_alloc == head) {
        /* update the head pointer to the most actual */
        do {
            Atomic_LDR32(&head);
        /* this check will fail if the interrupt has occurred during read */
        } while (Atomic_STR32(&head, (volatile uint32_t)alloc) != EOK);
        /* kick the interrupt routine, it will do the rest! */
        NVIC_SETPENDING(STM32_INT_FMC);
    }

    /* report status */
    return EOK;
}

/* invoke uses flexible memory controller isr */
void Invoke_FMCIsr(void)
{
    /* process all awaiters on the list */
    for (uint32_t i = tail; i < head; i++) {
        /* get the valid pointer */
        struct invokee *a = &invokees[i % elems(invokees)];
        /* extract the callback and it's argument */
        cb_t cb = a->callback; void *arg = a->arg;
        /* update the tail pointer before making the call so that we free up 
         * one entry */
        tail++;
        /* make the call */
        cb(arg);
    }
}

/* initialize module */
int Invoke_Init(void)
{
    /* enter the critical section */
    Critical_Enter();
    /* setup the interrupt */
    NVIC_SETINTPRI(STM32_INT_FMC, INT_PRI_INVOKE);
    /* enable */
    NVIC_ENABLEINT(STM32_INT_FMC);
    /* exit the critical section */
    Critical_Exit();

    /* report status */
    return EOK;
}

/* schedule call on differnt context */
void * Invoke_CallMeElsewhere(cb_t cb, void *arg)
{
    /* sanity checks */
    assert(Invoke_AddInvokee(cb, arg) == EOK, 
        "invoke: no space for caller", cb);
    /* report pointer */
    return 0;
}
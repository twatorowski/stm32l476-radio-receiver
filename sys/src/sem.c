/**
 * @file sem.c
 * 
 * @date 2019-10-10
 * @author twatorowski
 * 
 * @brief Semaphores with callback functionality
 */

#include "assert.h"
#include "err.h"
#include "arch/arch.h"
#include "sys/critical.h"
#include "sys/atomic.h"
#include "sys/cb.h"
#include "sys/sem.h"
#include "util/elems.h"

/* append callback to the list of callbacks and return the status: EOK if the 
 * lock for appended callback was acquired, EBUSY if the callback was appended 
 * but no lock was granted, EFATAL when callback was not added */
static int Sem_AppendCallback(sem_t *s, cb_t cb)
{
    /* local copy of the alloc variable, flag to tell whether the callback 
     * stored occupies the first place in the queue meaning that it will acquire 
     * the lock */
    uint32_t alloc, released;
    /* processing status */
    int rc = EBUSY;

    /* allocate space for the callback */
    do {
        /* read current value of the alloc function */
        alloc = Atomic_LDR32(&s->alloc);
        /* no space for next callback */
        if (alloc - s->tail == elems(s->cbs))
            return EFATAL;
    /* try to store */
    } while (Atomic_STR32(&s->alloc, alloc + 1) != EOK);

    /* set the callback */
    s->cbs[alloc % elems(s->cbs)] = cb;

    /* 1st in the line? */
    if (alloc == s->head) {
        /* update the head pointer to the most actual */
        do {
            Atomic_LDR32(&s->head);
        /* this check will fail if the interrupt has occurred during read */
        } while (Atomic_STR32(&s->head, s->alloc) != EOK);
        /* acquire callback execution lock */
        do {
            /* get lock */
            released = Atomic_LDR32(&s->released);
        /* try to mark as locked */
        } while (released == 1 && Atomic_STR32(&s->released, 0) != EOK);
        /* set status to indicate whether the callback shall be executed since 
         * it is the first thing in the callback array */
        rc = released == 1 ? EOK : EBUSY;
    }

    /* return the number of current entry */
    return rc;
}

/* lock semaphore */
int Sem_Lock(sem_t *s, cb_t cb)
{
    /* status */
    int rc = EOK;

    /* blocking version of the lock */
    if (cb == CB_SYNC) {
        /* loop as long as we are not able to acquire lock */
        do {
            while (Atomic_LDR32(&s->released) == 0);
        /* if the store did not succeed then we need to repeat the process */
        } while (Atomic_STR32(&s->released, 0) != EOK);
    /* async version with no callback */
    } else if (cb == CB_NONE) {
        /* loop as long as we are not able to store the lock acquired.*/
        do {
            /* semaphore is locked */
            if (Atomic_LDR32(&s->released) == 0)
                return EFATAL;
        /* if the store did not succeed then we need to repeat the process */
        } while (Atomic_STR32(&s->released, 0) != EOK);
    /* normal call with callbacks */
    } else {
        /* append callback */
        rc = Sem_AppendCallback(s, cb);
        /* sanity check */
        assert(rc != EFATAL, "no space for semaphore callback", (uintptr_t)s);
        /* callback was stored, and if the append function acquired the lock 
         * then all we need to do in order to execute all of the enlisted 
         * callbacks is to call the `release` function */
        if (rc == EOK)
            Sem_Release(s);
    }
    /* report status */
    return rc;
}

/* release semaphore */
int Sem_Release(sem_t *s)
{
    /* no more callbacks */
    if (s->tail == s->head) {
        /* release the semaphore */
        do {
            /* make sure we don't release the 'released' semaphore */
            assert(Atomic_LDR32(&s->released) == 0, 
                "semapohre already released", (uintptr_t)s);
        /* try to update the value */
        } while (Atomic_STR32(&s->released, 1) != EOK);
    /* still got some chained callbacks to be executed */
    } else {
        /* call the callback */
        s->cbs[s->tail++ % elems(s->cbs)](0);
    }

    /* report status */
    return EOK;
}

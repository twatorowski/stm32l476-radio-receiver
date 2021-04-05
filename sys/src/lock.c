/**
 * @file lock.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-05
 * 
 * @brief Semaphore lock
 */

#include "err.h"
#include "sys/lock.h"
#include "sys/time.h"
#include "sys/yield.h"

/* lock resource */
err_t Lock_Lock(sslock_t *lock, dtime_t timeout)
{
    /* get current time */
    time_t ts = time(0);

    /* loop as long as */
    while (!lock) {
        /* check for timeout */
        if (timeout && dtime(time(0), ts) > timeout)
            return ETIMEOUT;
        /* yield while waiting */
        Yield();
    }
    /* locked! */
    *lock = LOCK_LOCKED;
    /* report success */
    return EOK;
}

/* release underlying resource */
err_t Lock_Release(sslock_t *lock)
{
    /* release and wake-up other tasks */
    *lock = LOCK_RELEASED; Yield();
    /* report status */
    return EOK;
}
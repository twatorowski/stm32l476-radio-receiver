/**
 * @file lock.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-05
 * 
 * @brief Semaphore lock
 */

#include "err.h"
#include "sys/sem.h"
#include "sys/time.h"
#include "sys/yield.h"

/* lock resource */
err_t Sem_Lock(sem_t *sem, dtime_t timeout)
{
    /* get current time */
    time_t ts = time(0);

    /* loop as long as */
    while (*sem != SEM_RELEASED) {
        /* check for timeout */
        if (timeout && dtime(time(0), ts) > timeout)
            return ETIMEOUT;
        /* yield while waiting */
        Yield();
    }
    /* locked! */
    *sem = SEM_LOCKED;
    /* report success */
    return EOK;
}

/* release underlying resource */
err_t Sem_Release(sem_t *sem)
{
    /* release and wake-up other tasks */
    *sem = SEM_RELEASED; Yield();
    /* report status */
    return EOK;
}
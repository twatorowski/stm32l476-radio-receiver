/**
 * @file lock.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-05
 * 
 * @brief Semaphore lock
 */

#ifndef _SYS_SEM_H
#define _SYS_SEM_H

#include "err.h"
#include "sys/time.h"

/** semaphore lock typedef */
typedef enum sem { SEM_RELEASED, SEM_LOCKED } sem_t;

/**
 * @brief Lock the resource
 * 
 * @param sem lock to acquire
 * @param timeout locking timeout
 * 
 * @return err_t EOK or ETIMEOUT
 */
err_t Sem_Lock(sem_t *sem, dtime_t timeout);

/**
 * @brief elease underlying resource 
 * 
 * @param sem lock to be released
 * 
 * @return err_t status 
 */
err_t Sem_Release(sem_t *sem);


#endif /* _SYS_LOCK */

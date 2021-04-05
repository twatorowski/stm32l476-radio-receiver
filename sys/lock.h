/**
 * @file lock.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-05
 * 
 * @brief Semaphore lock
 */

#ifndef SYS_LOCK
#define SYS_LOCK

#include "err.h"
#include "sys/time.h"

/** semaphore lock typedef */
typedef enum lock { LOCK_RELEASED, LOCK_LOCKED } sslock_t;

/**
 * @brief Lock the resource
 * 
 * @param lock lock to acquire
 * @param timeout locking timeout
 * 
 * @return err_t EOK or ETIMEOUT
 */
err_t Lock_Lock(sslock_t *lock, dtime_t timeout);

/**
 * @brief elease underlying resource 
 * 
 * @param lock lock to be released
 * 
 * @return err_t status 
 */
err_t Lock_Release(sslock_t *lock);


#endif /* SYS_LOCK */

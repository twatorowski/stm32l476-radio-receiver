/**
 * @file sem.h
 * 
 * @date 2019-10-10
 * @author twatorowski
 * 
 * @brief Semaphores with callback functionality
 */

#ifndef SYS_SEM_H_
#define SYS_SEM_H_

#include <stdint.h>

#include "sys/cb.h"

/** @brief semaphore with callbacks */
typedef struct sem {
    /**< released flag. will be set to 1 when the semaphore is open */
    uint32_t released;
    /**< pointers for the callback array */
    uint32_t tail, head, alloc;
    /**< callback array */
    cb_t cbs[16];
} sem_t;


/**
 * @brief Wait for the resource to become available either by blocking or async 
 * or async with callback.
 * 
 * @param s semaphore that user whishes to acquire
 * @param cb pointer to a callback or @ref SYS_CB for 'sync' or 'try' mode of 
 * operation
 * 
 * @return int error code (@ref ERR_ERROR_CODES) returns lock status which is 
 * useful in case of 'try' mode
 */
int Sem_Lock(sem_t *s, cb_t cb);


/**
 * @brief Release the resource
 * 
 * @param s semaphore to be released
 * 
 * @return int error code (@ref ERR_ERROR_CODES)
 */
int Sem_Release(sem_t *s);

#endif /* SYS_SEM_H_ */

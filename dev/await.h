
/**
 * @file await.h
 * 
 * @date 2019-11-19
 * @author twatorowski 
 * 
 * @brief Async delay build around the TIM3s
 */

#ifndef DEV_AWAIT_H_
#define DEV_AWAIT_H_

#include "sys/cb.h"
#include "sys/sem.h"

/** @brief timer3 isr */
void Await_TIM3Isr(void);

/**
 * @brief Initialize the asynchronous wait routine
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int Await_Init(void);

/**
 * @brief  schedule the callback call after at least 'ms' milliseconds
 * 
 * @param ms number of milliseconds to await
 * @param cb callback to be called after the specified period of time
 * 
 * @return void * this module does not provide callback argument so it always 
 * returns null pointer
 */
void * Await_CallMeLater(int ms, cb_t cb);

#endif /* DEV_AWAIT_H_ */

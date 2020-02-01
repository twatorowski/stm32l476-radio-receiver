/**
 * @file invoke.h
 * 
 * @date 2019-12-06
 * @author twatorowski 
 * 
 * @brief Abstract module that allows for invoking a callback on different 
 * context. The so called different context is simply an interrupt.
 */

#ifndef DEV_INVOKE_H_
#define DEV_INVOKE_H_

#include "sys/cb.h"

/** @brief invoke uses flexible memory controller isr */
void Invoke_FMCIsr(void);


/**
 * @brief Initialize the invoke module
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int Invoke_Init(void);


/**
 * @brief Call the function on the different context asap
 * 
 * @param cb callback to be called
 * @param arg it's argument
 * 
 * @return void * null
 */
void * Invoke_CallMeElsewhere(cb_t cb, void *arg);


#endif /* DEV_INVOKE_H_ */

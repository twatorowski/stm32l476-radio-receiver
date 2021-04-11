/**
 * @file yield.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-03-27
 * 
 * @brief Yield - context switcher
 */

#ifndef SYS_YIELD
#define SYS_YIELD

#include <stddef.h>

#include "err.h"

/** @brief function type for task handler routine */
typedef void (* yield_hndl_t)(void *);


/** @brief Context switch service routine */
void Yield_PendSVHandler(void);


/**
 * @brief Starts the context switcher. Needs to be called before any context 
 * switch takes place
 * 
 * @return err_t error code
 */
err_t Yield_Init(void);


/**
 * @brief Create a task, but do not start it right away - it will be started 
 * after a call to Yield() is issued.
 * 
 * @param handler task handler routine
 * @param arg argument passed to that handler
 * @param stack stack for the task
 *
 * @return err_t error code is something goes wrong 
 */
err_t Yield_CreateTask(yield_hndl_t handler, void *arg, size_t stack_size);


/**
 * @brief Yields from current task, does a context switch and continues the 
 * execution of other tasks
 */
void Yield(void);

#endif /* SYS_YIELD */

/**
 * @file sleep.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-03-28
 * 
 * @brief Sleeping routine
 */

#ifndef SYS_SLEEP
#define SYS_SLEEP

#include "sys/time.h"

/**
 * @brief Pause the execution of current task for the time being 
 * 
 * @param period sleep period expressed in ms
 *
 */
void Sleep(time_t period);

#endif /* SYS_SLEEP */

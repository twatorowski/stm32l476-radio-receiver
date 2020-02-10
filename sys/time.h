/*
 * time.h
 *
 *	Created on: 11-06-2013
 *		Author: Tomek
 */

#ifndef SYS_TIME_H_
#define SYS_TIME_H_

#include <stdint.h>

#include "compiler.h"
#include "dev/systime.h"


/* default time type */
typedef uint32_t time_t;
/* default time difference type */
typedef int32_t dtime_t;

/**
 * @brief Get current system time timer value in ms;
 * 
 * @param t 
 * 
 * @return system time value 
 */
static inline ALWAYS_INLINE time_t time(time_t *t)
{
    /* get current system timer value */
    time_t ms = SysTime_GetTime() >> 1;
    /* store within the pointer value */
    if (t) 
        *t = ms;
    /* return the value */
    return ms;
}

/**
 * @brief Get the time difference between two timestamps: a - b
 * 
 * @param a 1st timestamp (must be greater than b to get the positive result)
 * @param b 2nd timestamp (must be lower than a to get the positive result)
 * 
 * @return difference in milliseconds 
 */
static inline ALWAYS_INLINE dtime_t dtime(time_t a, time_t b)
{
    return (dtime_t)(a - b);
}

#endif /* SYS_TIME_H_ */


/**
 * @file time.h
 * 
 * @date 2020-03-29
 * @author twatorowski 
 * 
 * @brief Basic system time routines
 */

#ifndef SYS_TIME_H
#define SYS_TIME_H

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
    time_t ms = SysTime_GetTime() / 10;
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

/**
 * @brief Get the time difference between two timestamps: a - b but ensure 
 * monotonicity: i.e if 'a' happened before 'b' (and so a-b < 0) return the 
 * biggest positive value that dtime_t can hold.
 * 
 * @param a 1st timestamp
 * @param b 2nd timestamp
 * 
 * @return difference in milliseconds of max value representable if a happened 
 * after b
 */
static inline ALWAYS_INLINE dtime_t dtime_m(time_t a, time_t b)
{
    /* get the time differential */
    dtime_t diff = dtime(a, b);
    /* never return negative numbers to ensure monotonicity */
    return diff < 0 ? INT32_MAX : diff;
}

#endif /* SYS_TIME_H */

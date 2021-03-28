/**
 * @file sleep.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-03-28
 * 
 * @brief Sleeping routine
 */

#include "sys/time.h"
#include "sys/yield.h"

/* pause the execution of current task for the time being */
int Sleep(time_t period)
{
    /* yield from current task for as long as requested */
    for (time_t ts = time(0); dtime(time(0), ts) < period; )
        Yield();
}
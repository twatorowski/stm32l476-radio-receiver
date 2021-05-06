/**
 * @file delay.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief Short delay
 */

#include "dev/systime.h"

/* simple delay function */
void Delay(uint32_t us)
{
    /* microsecond timestamps */
    uint16_t curr_us, prev_us = SysTime_GetUs();

    /* loop until timing is met */
    for (uint32_t elapsed = 0; elapsed < us; ) {
        /* get current timestamp */
        curr_us = SysTime_GetUs();
        /* update the elapsed counter */
        elapsed += (uint16_t)(curr_us - prev_us);
        prev_us = curr_us;
    }
}
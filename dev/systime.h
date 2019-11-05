/**
 * @file systime.h
 * 
 * @date 2019-11-05
 * @author twatorowski
 * 
 * @brief System Timer Module
 */

#ifndef DEV_SYSTIME_H_
#define DEV_SYSTIME_H_

#include <stdio.h>

/**
 * @brief Initialize System Timer Module
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int SysTime_Init(void);

/**
 * @brief Stalls the execution by the number of milliseconds
 * 
 * @param ms number of milliseconds to stall
 */
void SysTime_Delay(uint32_t ms);

/**
 * @brief Sets current system timer value 
 * 
 * @param t value to be put into system timer
 */
void SysTime_SetTime(uint32_t t);

#endif /* DEV_SYSTIME_H_ */

/**
 * @file systime.h
 * 
 * @date 2020-03-29
 * @author twatorowski 
 * 
 * @brief System Timer
 */

#ifndef DEV_SYSTIME_H
#define DEV_SYSTIME_H

#include <stdint.h>

/**
 * @brief Initialize the system timer
 * 
 * @return int status
 */
int SysTime_Init(void);

/**
 * @brief Get current system timer value
 * 
 * @return uint32_t system timer value
 */
uint32_t SysTime_GetTime(void);

#endif /* DEV_SYSTIME_H */

/**
 * @file timemeas.h
 * 
 * @date 2020-01-13
 * @author twatorowski 
 * 
 * @brief microsecond Time measurement module. Perfect tool for performance 
 * analysis
 */

#ifndef DEV_TIMEMEAS_H_
#define DEV_TIMEMEAS_H_

#include <stdint.h>

/**
 * @brief Initialize microsecond timer logic
 * 
 * @return int status (@ref ERR_ERROR_CODES) 
 */
int TimeMeas_Init(void);

/**
 * @brief Get current timer value. Timestamp is 16 bit wide, so a maximal diff 
 * of 65ms is possible 
 * 
 * @return uint16_t timestamp value
 */
uint16_t TimeMeas_GetTimeStamp(void);

#endif /* DEV_TIMEMEAS_H_ */

/**
 * @file watchdog.h
 * 
 * @date 2019-11-02
 * @author twatorowski
 * 
 * @brief WWDG Driver module
 */

#ifndef DEV_WATCHDOG_H_
#define DEV_WATCHDOG_H_

/**
 * @brief Initialize and start the watchdog
 * 
 * @return int initialization status error code @ref ERR_ERROR_CODES
 */
int Watchdog_Init(void);

/**
 * @brief Kick the watchdog counter
 */
void Watchdog_Kick(void);

#endif /* DEV_WATCHDOG_H_ */

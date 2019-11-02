/**
 * @file cpuclock.h
 * 
 * @date 2019-11-02
 * @author your name (you@domain.com)
 * 
 * @brief Setup the MCU's operating frequency
 */

#ifndef DEV_CPUCLOCK_H_
#define DEV_CPUCLOCK_H_

/**
 * @brief initialize cpu clock to 80MHz (HSE + PLL) and start the LSI. On the 
 * discovery board make sure that you have the solder jumpers set to correct 
 * values: Close the SB18, Open the SB22.
 * 
 * @return int initialization status error code @ref ERR_ERROR_CODES
 */
int CpuClock_Init(void);

#endif /* DEV_CPUCLOCK_H_ */

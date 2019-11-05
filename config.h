/**
 * @file config.h
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief Main configuration file
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>


/** @defgroup CONFIG Configuration */
/** @{ */

/** @name Development configuration */
/** @{ */
/** @brief Development flag. Used to generate the code with all of the printf 
 * debugging enabled */
#ifndef DEVELOPMENT
#define DEVELOPMENT						            1
#endif
/** @} */

/** @name System CPU Frequency */
/** @{ */
/** @brief system frequency in Hz */
#define CPU_FREQ							        80e6
/** @} */

/** @name System Event configuration */
/** @{ */
/** @brief maximal number of event callback subscribers (per event) */
#define EV_MAX_CB							        12
/** @} */

/** @name System Event configuration */
/** @{ */
/** @brief maximal number of semaphore lock event subscribers (per semaphore) */
#define SEM_MAX_CB							        16
/** @} */


/** @name AT Protcol configuration */
/** @{ */
/** @brief maximal length of response line. if the command generates responses 
 * (besides the general ending response OK or ERROR) then this is the max length 
 * of a single response */
#define AT_RES_MAX_LINE_LEN                         256
/** @brief at command line ending sequence */
#define AT_LINE_END                                 "\r\n"
/** @} */

/** @name LED configuration */
/** @{ */
/** @brief disable/enable led globally */
#define LED_ENABLE                                  1
/** @} */

/** @name Interrupt Priorities */
/** @{ */
/** @brief data received callback priority (0x00 - highest, 0xf0 lowest) */
#define INT_PRI_USART2_RX						    0x20
/** @brief data sent callback priority (0x00 - highest, 0xf0 lowest) */
#define INT_PRI_USART2_TX						    0xf0
/** @brief async delay priority */
#define INT_PRI_AWAIT                               0xf0
/** @brief external voltage monitor interrupt priority */
#define INT_PRI_VIN                                 0xf0
/** @brief dac fetching interrupt priority, keep at the same level as the 
 * microphone interrupt priority level (0x00 - highest, 0xf0 lowest) */
#define SAI2B_PRIORITY							    0x20
/** @brief decimator interrupt priority */
#define INT_PRI_DEC                                 0x20                           
/** @} */

/** @name USART2 configuration */
/** @{ */
/** @brief usart baudrate */
#define USART2_BAUD_RATE                            230400
/** @} */

/** @name IQ Decimators */
/** @{ */
/** @brief decimation rate */
#define DEC_DECIMATION_RATE                         32
/** @} */

#endif /* CONFIG_H_ */

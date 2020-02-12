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
/** @brief reference oscillator speed (hse or it's prescaled version) */
#define CPUCLOCK_REF_FREQ                           8000000
/** @brief system frequency in Hz */
#define CPUCLOCK_FREQ							    80000000
/** @} */

/** @name Debug configuration */
/** @{ */
/** @brief debugging is enabled?  */
#define DEBUG_ENABLED							    DEVELOPMENT
/** @brief number of interrupt active/interrupt pending 32-bit bitmask registers 
 * to be stored during the execution of default handler. In case of cortex-m4 
 * this should be equal to the number of implemented IABR/ISPR registers within 
 * the NVIC */
#define DEBUG_NUM_IABR_ISBR                         4
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
/** @brief decimator interrupt priority */
#define INT_PRI_DEC                                 0x20    
/** @brief exti multiplexer interrupt priority for exti[5-9] */
#define INT_PRI_EXI5_9                              0xf0
/** @brief exti multiplexer interrupt priority for exti[10-15] */
#define INT_PRI_EXI10_15                            0xf0
/** @brief invoke interrupt priority */
#define INT_PRI_INVOKE                              0x50
/** @brief USB priority */
#define INT_PRI_USB                                 0x50
/** @} */

/** @name USART2 configuration */
/** @{ */
/** @brief usart baudrate */
#define USART2_BAUD_RATE                            1500000
/** @} */

/** @name IQ Decimators */
/** @{ */
/** @brief decimation rate, must be a power of 2 */
#define DEC_DECIMATION_RATE                         64
/** maximal input word bit width */
#define DEC_MAX_INPUT_BITS                          14
/** @} */

/** @name CS43L22 configuration */
/** @{ */
/** @brief DAC's i2c address */
#define CS43L22_ADDR                                0x4A
/** @} */

/** @name RF paramaters  */
/** @{ */
/** @brief Sampling frequency */
#define RF_SAMPLING_FREQ                            2500000
/** @define number of bits per rf sample */
#define RF_SAMPLING_BITS                            12
/** @} */

/** @name USB module */
/** @{ */
/** @brief use the true serial number */
#define USB_SN_SIZE                                 58
/** @brief control endpoint max size (bidirectional) */
#define USB_CTRLEP_SIZE                             64
/** @brief interrupt endpoint transfer size (must be a power of 2) */
#define USB_VCP_INT_SIZE                            8
/** @brief transmission packet size (must be a power of 2) */
#define USB_VCP_TX_SIZE                             32
/** @brief reception packet size (must be a power of 2) */
#define USB_VCP_RX_SIZE                             32
/** @brief usb audio frame size */
#define USB_AU_SRC_SIZE                             64
/** @brief usb uses common fifo for reception so we need to set it's size to 
 * hold the largest packet possible */
#define USB_RX_FIFO_SIZE                            512
/** @} */



#endif /* CONFIG_H_ */

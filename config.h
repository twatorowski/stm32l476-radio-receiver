/**
 * @file config.h
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief Main configuration file
 */

#ifndef CONFIG
#define CONFIG

#include <stdint.h>


/** @name Development configuration */
/** @{ */
#ifndef DEVELOPMENT
/** @brief Development flag. Used to generate the code with all of the printf 
 * debugging enabled */
#define DEVELOPMENT                                 1
#endif
/** @} */


/** @name System Clock configuration */
/** @{ */
/** @brief mcu frequency */
#define CPUCLOCK_HZ                                 64000000
/** @brief ahb frequency */
#define AHBCLOCK_HZ                                 (CPUCLOCK_HZ / 1)
/** @brief apb1 bus frequency */
#define APB1CLOCK_HZ                                (CPUCLOCK_HZ / 1)
/** @brief apb2 bus frequency */
#define APB2CLOCK_HZ                                (CPUCLOCK_HZ / 1)
/** @} */


/** @name Debug configuration */
/** @{ */
/** @brief debugging is enabled?  */
#define DEBUG_ENABLED                               DEVELOPMENT
/** @brief maximal length of the debug line string  */
#define DEBUG_MAX_LINE_LEN                          128
/** @} */


/** @name Interrupt priorities */
/** @{ */
/** @brief context switcher */
#define INT_PRI_YIELD                               0xf0
/** @brief external interrupt line 0 */
#define INT_PRI_EXTIMUX_0                           0xe0
/** @brief external interrupt line 1 */
#define INT_PRI_EXTIMUX_1                           0xe0
/** @brief external interrupt line 2 */
#define INT_PRI_EXTIMUX_2                           0xe0
/** @brief external interrupt line 3 */
#define INT_PRI_EXTIMUX_3                           0xe0
/** @brief external interrupt line 4 */
#define INT_PRI_EXTIMUX_4                           0xe0
/** @brief external interrupt lines 9 - 5 */
#define INT_PRI_EXTIMUX_9_5                         0xe0
/** @brief external interrupt lines 15 - 10 */
#define INT_PRI_EXTIMUX_15_10                       0xe0
/** @} */



/** @name Yield configuration */
/** @{ */
/** @brief Maximal number of tasks */
#define OS_MAX_TASKS                                8
/** @brief Maximal number of tasks */
#define SYS_HEAP_SIZE                               (16 * 1024)
/** @} */

/** @name USART3 Configuration */
/** @{ */
/** @brief baudrate */
#define USART3_BAURDRATE                            115200
/** @} */


#endif /* CONFIG */

/**
 * @file err.h
 *
 * @date 23.06.2019
 * @author twatorowski
 *
 * @brief Error codes used across the application
 */

#ifndef ERR_H_
#define ERR_H_

/** @defgroup ERR_ERROR_CODES System Error Codes */
/** @{ */

/** @name Error Codes */
/** @{ */
/** @brief no error */
#define EOK                                     0
/** @brief fatal error */
#define EFATAL                                  -1
/** @brief resource busy */
#define EBUSY                                   -2
/** @brief not initialized */
#define ENOINIT                                 -3
/** @} */

/** @name AT Command Error Codes */
/** @{ */
#define EAT_UNKNOWN_CMD                         -10
/* main tracker was reset */
#define EAT_SYNTAX                              -11
/* execution error */
#define EAT_EXEC                                -12
/** @} */

/** @name I2C error codes */
/** @{ */
/** @brief addressing nack */
#define EI2C_ADDR_NACK                          -20
/** @brief transfer error */
#define EI2C_TRANSFER_ERROR                     -21
/** @} */

/** @name USART error codes */
/** @{ */
/** @} */

/** @name CIRCBUF error codes */
/** @{ */
/** @brief no space in buffer for alloc */
#define ECIRCBUF_NO_SPACE                       -30
/** @} */

/** @} */


#endif /* ERR_H_ */

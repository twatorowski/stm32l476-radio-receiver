/**
 * @file usart3.h
 * 
 * @date 2021-01-20
 * @author twatorowski 
 * 
 * @brief USART3 Driver
 */

#ifndef DEV_USART3
#define DEV_USART3

#include <stddef.h>

#include "err.h"
#include "sys/time.h"

/**
 * @brief Initialize USART2 driver.
 *
 * @return initialization status error code @ref ERR_ERROR_CODES
 */
err_t USART3_Init(void);

/**
 * @brief Send data over the USART2. Asynchronously or synchronously depending on the
 * @p cb callback pointer
 *
 * @param ptr pointer to the data to be sent. User is responsible for keeping the
 * data unchangeable during the send process
 * @param size size of the data to be sent in bytes
 * @param timeout timeout in milliseconds
 *
 * @return err_t negative number indicates errors, positive indicates number of 
 * bytes sent
 */
err_t USART3_Send(const void *ptr, size_t size, dtime_t timeout);

/**
 * @brief Receive data from the serial port
 * 
 * @param ptr pointer to where to store the data
 * @param size data size
 * @param tout timeout in milliseconds
 *
 * @return int number of bytes received (positive) 
 */
err_t USART3_Recv(void *ptr, size_t size, dtime_t timeout);

#endif /* DEV_USART3 */

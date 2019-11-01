/**
 * @file usart2.h
 *
 * @date 30.06.2019
 * @author twatorowski
 *
 * @brief USART2 Driver
 */

#ifndef DEV_USART2_H_
#define DEV_USART2_H_

#include "stddef.h"
#include "sys/cb.h"
#include "sys/sem.h"

/** @brief semaphores */
extern sem_t usart2tx_sem, usart2rx_sem;

/** @brief USART2 Interrupt service routine */
void USART2_USART2Isr(void);
/** @brief tx dma interrupt */
void USART2_DMA1C7Isr(void);
/** @brief rx dma interrupt */
void USART2_DMA1C6Isr(void);

/**
 * @brief Initialize USART2 driver.
 *
 * @return initialization status error code @ref ERR_ERROR_CODES
 */
int USART2_Init(void);

/**
 * @brief Send data over the USART2. Asynchronously or synchronously depending on the
 * @p cb callback pointer
 *
 * @param ptr pointer to the data to be sent. User is responsible for keeping the
 * data unchangeable during the send process
 * @param size size of the data to be sent in bytes
 * @param cb callback to be called after sending is done OR CB_NULL (as per @ref
 * SYS_CB) if synchronous operation is requested
 *
 * @return number of bytes sent
 */
int USART2_Send(const void *ptr, size_t size, cb_t cb);

/**
 * @brief Receive at most @p size of data.
 *
 * @param ptr memory to put the received data to
 * @param size maximal number of bytes to be received
 * @param cb callback to be called if the data is received. Callback argument will
 * contain the pointer to the number of bytes that were actually received. Callback
 * may be set for CB_NULL (as per @ref SYS_CB) for synchronous (blocking) operation.
 *
 * @return number of bytes received. Only valid for synchronous operation
 */
int USART2_Recv(void *ptr, size_t size, cb_t cb);

#endif /* DEV_USART2_H_ */

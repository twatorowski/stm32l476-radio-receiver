/**
 * @file usbvcp.h
 * 
 * @date 2019-12-07
 * @author twatorowski 
 * 
 * @brief Minimalistic Virtual Com Port implementation that works over the 
 * usbcore.c
 */

#ifndef DEV_USBVCP2_H_
#define DEV_USBVCP2_H_

#include <stddef.h>

#include "sys/cb.h"
#include "sys/sem.h"

/** @name VCP class requests */
/** @{ */
/** @brief set asynchronous line character formatting */
#define USB_VCP_REQ_SET_LINE_CODING				0x20
/** @brief get asynchronous line character formatting */
#define USB_VCP_REQ_GET_LINE_CODING				0x21
/** @brief This request generates RS-232/V.24 style control signals. */
#define USB_VCP_SET_CONTROL_LINE_STATE			0x22
/** @} */

// /** @brief callback argument */
// typedef struct usbvcp_cbarg {
//     /**< transfer error */
//     int error;
//     /**< transfer data pointer */
//     void *ptr;
//     /**< transfer size */
//     size_t size;
// } usbvcp_cbarg_t;

/** @beirf receive semaphore */
extern sem_t usbvcprx2_sem;
/** @brief transmit semaphore */
extern sem_t usbvcptx2_sem;

/**
 * @brief Initialize the USB Device module
 * 
 * @return int status (@ref ERR_ERROR_CODES) 
 */
int USBVCP2_Init(void);

/**
 * @brief Read data from the interface. You'll be called when the data is 
 * received or when USB reset occurs. Check the error code in the transfer 
 * callback.
 * 
 * @param ptr pointer to received data buffer
 * @param size max size of the data received
 * @param cb callback to be called when the data is received or CB_SYNC for 
 * synchronous operation
 * 
 * @return usbvcp_cbarg_t * reception status for sync calls or null for async 
 * calls
 */
usbvcp_cbarg_t * USBVCP2_Recv(void *ptr, size_t size, cb_t cb);

/**
 * @brief Write data to the interface. The underlying logic does all the data 
 * fragmentation to make the best use of the USB data carrying packets. Callback
 * will be called (or function will exit in case of sync calls) when data is 
 * transmitted or when USB Reset occurs.
 * 
 * @param ptr source data pointer
 * @param size size of data to be sent
 * @param cb callback to be called when the operation is done
 * 
 * @return usbvcp_cbarg_t * transmission status for sync calls or null for async 
 * calls
 */
usbvcp_cbarg_t * USBVCP2_Send(const void *ptr, size_t size, cb_t cb);

#endif /* DEV_USBVCP_H_ */

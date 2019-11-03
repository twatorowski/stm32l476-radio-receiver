/**
 * @file rxtx.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Reception and Transmission logic
 */

#ifndef AT_RXTX_H_
#define AT_RXTX_H_

#include <stddef.h>


/** @brief number of implemented interfaces */
#define ATRXTX_IFACENUM							1

/** @defgroup AT_RXTX_IFACE Interface ID */
/** @{ */
/** @name Interface IDs */
/** @{ */
/** @brief interfaces over which AT communication takes place */
#define ATRXTX_IFACE_USART2						0
/** @} */
/** @} */


/**
 * @brief Initialize the low-level reception and transmission part of the AT protocol
 *
 * @return initialization status error code @ref ERR_ERROR_CODES
 */
int ATRxTx_Init(void);

/**
 * @brief reception/transmission polling routine. To be put into the main AT polling
 * routine AT_Poll()
 */
void ATRxTx_Poll(void);

/**
 * @brief Sends response over given @p iface that is either a notification or a direct
 * response to a command.
 *
 * @param iface interface over which the response is to be sent.
 * @param is_notify 1 if the response is unsolicited, 0 if the response is a 
 * direct response to a command.
 * @param str pointer to the string containing the response
 * @param len length (in bytes) of the response
 *
 * @return response send status (@ref ERR_ERROR_CODES)
 */
int ATRxTx_SendResponse(int iface, int is_notify, const char *str, size_t len);


#endif /* AT_RXTX_H_ */

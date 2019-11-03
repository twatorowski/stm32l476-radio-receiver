/**
 * @file rxtx_usart2.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief 
 */

#ifndef AT_RXTX_USART2_H_
#define AT_RXTX_USART2_H_

#include <stddef.h>

/**
 * @brief Initialize low-level AT command Rx/Tx routines for the USART1 interface.
 *
 * @return initialization status error code @ref ERR_ERROR_CODES
 */
int ATRxTxUSART2_Init(void);

/**
 * @brief Driver polling function. To be called by the ATRxTx_Poll().
 */
void ATRxTxUSART2_Poll(void);

/**
 * @brief Sends response over given @p iface that is either a notification or a direct
 * response to a command.
 *
 * @param is_notify 1 if the response is unsolicited, 0 if the response is a direct
 * response to a command.
 * @param str pointer to the string containing the response
 * @param len length (in bytes) of the response
 *
 * @return response send status (@ref ERR_ERROR_CODES)
 */
int ATRxTxUSART2_SendResponse(int is_notify, const char *str, size_t len);

#endif /* AT_RXTX_USART1_H_ */

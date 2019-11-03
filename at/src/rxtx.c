/**
 * @file rxtx.c
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Reception and Transmission logic
 */

#include "err.h"
#include "at/rxtx.h"
#include "at/rxtx_usart2.h"

/* initialize receive and transmit wrapper */
int ATRxTx_Init(void)
{
	/* initialize the usart1 interface */
	ATRxTxUSART2_Init();

	/* report error */
	return EOK;
}

/* polling of the interfaces */
void ATRxTx_Poll(void)
{
	/* poll the uart */
	ATRxTxUSART2_Poll();
}

/* store line in internal buffer and send it */
int ATRxTx_SendResponse(int iface, int is_notify, const char *str, size_t len)
{
	/* switch over the implemented interfaces */
	if (iface == ATRXTX_IFACE_USART2) {
		return ATRxTxUSART2_SendResponse(is_notify, str, len);
	}

	/* unknown interface */
	return EFATAL;
}

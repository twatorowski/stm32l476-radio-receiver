/**
 * @file ntfy.c
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief 
 */

#include <stdint.h>
#include <stddef.h>
#include "err.h"
#include "at/rxtx.h"
#include "at/ntfy.h"
#include "sys/critical.h"
#include "util/elems.h"

/* submodules */
#include "at/ntfy/debug.h"


/* notification mask */
static uint32_t ntfy_mask[ATRXTX_IFACENUM] = {
	[ATRXTX_IFACE_USART2] = AT_NTFY_MASK_DEBUG,
};

/* notification mask or */
static uint32_t ntfy_mask_or = AT_NTFY_MASK_DEBUG;

/* test protocol notifications support */
int ATNtfy_Init(void)
{   
    /* overall status code */
    int rc = EOK;

    /* initialize all notification submodules */
    rc |= ATNtfyDebug_Init();

	/* report status */
	return EOK;
}

/* polling routines for notifications */
void ATNtfy_Poll(void)
{
    /* poll all notification submodules */
    /* debug */
    ATNtfyDebug_Poll();
}

/* set notification mask */
int ATNtfy_SetNotificaionMask(int iface, uint32_t mask)
{
	/* enter critical section */
	Critical_Enter();
	/* set notificaion mask */
	ntfy_mask[iface] = mask; ntfy_mask_or = 0;

	/* update ored mask */
	for (int i = 0; i < ATRXTX_IFACENUM; i++)
		ntfy_mask_or |= ntfy_mask[iface];
	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

/* get notification mask for given interface */
int ATNtfy_GetNotificationMask(int iface, uint32_t *mask)
{
	/* store current mask value */
	if (mask) *mask = ntfy_mask[iface];
	/* report status */
	return EOK;
}

/* get the orr'ed value of the notification mask for all of 
 * the interfaces */
int ATNtfy_GetNotificationORMask(uint32_t *mask)
{
	/* store current mask value */
	if (mask) *mask = ntfy_mask_or;
	/* report status */
	return EOK;
}

/* send notification */
int ATNtfy_SendNotification(int iface, const char *str, size_t len)
{
    /* send */
    return ATRxTx_SendResponse(iface, 1, str, len);
}

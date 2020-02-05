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
#include "at/ntf.h"
#include "sys/critical.h"
#include "util/elems.h"

/* submodules */
#include "at/ntf/debug.h"

/* notification mask */
static uint32_t ntf_mask[ATRXTX_IFACENUM] = {
	[ATRXTX_IFACE_USART2] = AT_NTF_MASK_DEBUG,
};

/* notification mask or */
static uint32_t ntf_mask_or = AT_NTF_MASK_DEBUG;

/* test protocol notifications support */
int ATNtf_Init(void)
{   
    /* overall status code */
    int rc = EOK;

    /* initialize all notification submodules */
    rc |= ATNtfDebug_Init();

	/* report status */
	return EOK;
}

/* polling routines for notifications */
void ATNtf_Poll(void)
{
    /* poll all notification submodules */
    /* debug */
    ATNtfDebug_Poll();
}

/* set notification mask */
int ATNtf_SetNotificaionMask(int iface, uint32_t mask)
{
	/* enter critical section */
	Critical_Enter();
	/* set notificaion mask */
	ntf_mask[iface] = mask; ntf_mask_or = 0;

	/* update ored mask */
	for (int i = 0; i < ATRXTX_IFACENUM; i++)
		ntf_mask_or |= ntf_mask[iface];
	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

/* get notification mask for given interface */
int ATNtf_GetNotificationMask(int iface, uint32_t *mask)
{
	/* store current mask value */
	if (mask) *mask = ntf_mask[iface];
	/* report status */
	return EOK;
}

/* get the orr'ed value of the notification mask for all of 
 * the interfaces */
int ATNtf_GetNotificationORMask(uint32_t *mask)
{
	/* store current mask value */
	if (mask) *mask = ntf_mask_or;
	/* report status */
	return EOK;
}

/* send notification */
int ATNtf_SendNotification(int iface, const char *str, size_t len)
{
    /* send */
    return ATRxTx_SendResponse(iface, 1, str, len);
}

/**
 * @file debug.c
 * 
 * @date 2019-09-13
 * @author twatorowski
 * 
 * @brief AT Notifications: Debug.
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "at/ntfy.h"
#include "at/rxtx.h"

/* initialize debug notifications submodule */
int ATNtfyDebug_Init(void)
{
    /* report status */
    return EOK;
}

/* poll debug notifications submodule */
void ATNtfyDebug_Poll(void)
{

}

/* send debug data over channels */
int ATNtfyDebug_PutDebugData(const char *str, size_t len)
{
	/* data sent? */
	int sent = 0;
    /* notification mask placeholder */
    uint32_t mask;

    /* get mask for all notifications */
    ATNtfy_GetNotificationORMask(&mask);
	/* this is to avoid stalling debugs when no interface has enabled
	 * debug logic */
	if (!(mask & AT_NTFY_MASK_DEBUG))
		return EOK;

	/* send response */
	for (int iface = 0; iface < ATRXTX_IFACENUM; iface++) {
        /* get notification mask for given interface */
        ATNtfy_GetNotificationMask(iface, &mask);
		/* notifications enabled for given interface? */
		if ((mask & AT_NTFY_MASK_DEBUG)) {
			/* send the actual data */
			sent |= ATRxTx_SendResponse(iface, 1, str, len) == EOK;
		}
	}

	/* report status */
	return sent ? EOK : EFATAL;
}
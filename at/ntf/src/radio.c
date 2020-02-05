/**
 * @file radio.c
 * 
 * @date 2020-02-05
 * @author twatorowski 
 * 
 * @brief AT Notifications: Radio.
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "at/ntfy.h"
#include "at/rxtx.h"

/* iqdata buffer */
static struct iqdata {
    /* samples buffer */
    float buf[128];
    /* pointers */
    uint32_t head, tail;
} iqdata;


/* initialize radio notifications submodule */
int ATNtfyRadio_Init(void)
{
    /* report status */
    return EOK;
}

/* poll radio notifications submodule */
void ATNtfyRadio_Poll(void)
{

}

/* store the iq data samples in at notifications buffer */
int ATRadio_PutIQsamples(const float *i, const float *q, int num)
{
    /* data stored? */
	int sent = 0;
    /* notification mask placeholder */
    uint32_t mask;

    /* get mask for all notifications */
    ATNtfy_GetNotificationORMask(&mask);
	/* this is to avoid stalling debugs when no interface has enabled
	 * debug logic */
	if (!(mask & AT_NTFY_MASK_RADIO_DATA))
		return EOK;

    /* report status */
	return sent ? EOK : EFATAL;
}
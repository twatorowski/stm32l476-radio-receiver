/**
 * @file vcp_rate.c
 * 
 * @date 2020-02-11
 * @author twatorowski 
 * 
 * @brief Test for VCP data rates
 */

#include "err.h"
#include "dev/usb.h"
#include "dev/usbvcp.h"
#include "sys/time.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

/* transmitted data */
static const char pattern[] = "1234567890";
/* tx test buffer */
static char buf[1023];
/* data counter */
static size_t size;
/* timer */
static time_t timer;

/* data sent callback */
static int TestVCPRate_Callback(void *ptr)
{
    /* cast callback argument */
    usbvcp_cbarg_t *ca = ptr;

    /* initial call */
    if (!ptr) {
        timer = time(0); size = 0;
    /* valid callback */
    } else {
        /* update size */
        size += ca->size;
        /* get the time difference */
        dtime_t dt = dtime(time(0), timer);
        /* time to show the results? */
        if (dt >= 1000) {
            /* print the rate */
            dprintf("rate = %d [B/s]", size * 1000 / dt);
            /* restart the measurement */
            size = 0; timer = time(0);
        }
    }

    /* send the data */
    USBVCP_Send(buf, sizeof(buf), TestVCPRate_Callback);

    /* report callback status */
    return EOK;
} 

/* initialize virtual com port test */
int TestVCPRate_Init(void)
{
    /* start the usb action */
    USB_Connect(1);
    /* initialize transmitter buffer */
    for (int i = 0; i < elems(buf); i++)
        buf[i] = pattern[i % (elems(pattern) - 1)];

    /* bombs away! */
    Sem_Lock(&usbvcptx_sem, TestVCPRate_Callback);
	/* report status */
	return EOK;
}
/**
 * @file vcp.c
 * 
 * @date 2020-02-10
 * @author twatorowski 
 * 
 * @brief Test for virtual COM port connection and data exchange
 */

#include "err.h"
#include "dev/usb.h"
#include "dev/usbvcp.h"
#include "sys/time.h"
#include "util/elems.h"
#include "util/minmax.h"


// #define DEBUG
#include "debug.h"

/* transmitted data */
static const char pattern[] = "1234567890";
static int pattern_len;
/* data buffer */
static char buf[max(USB_VCP_TX_SIZE, USB_VCP_RX_SIZE) + 1];
/* tx test buffer */
static char tx_buf[USB_VCP_TX_SIZE * 2];
/* buffer size & offset */
static size_t buf_size, buf_offs;
/* notification pointer */
static time_t timer;

/* tx done callback */
static int TestVCP_VCPTxCallback(void *ptr);
/* receive callback */
static int TestVCP_VCPRxCallback(void *ptr);

/* tx done callback */
static int TestVCP_VCPTxCallback(void *ptr)
{
	/* cast event argument */
    usbvcp_cbarg_t *ca = ptr;
    /* get the size of the transfer */
	size_t size = ca ? ca->size : 0;

	/* update size */
	buf_offs += size;
	/* end of transmission? */
	if (buf_offs >= buf_size) {
		/* restart recepion */
		Sem_Release(&usbvcptx_sem);
		TestVCP_VCPRxCallback(0);
	/* still something to send? */
	} else {
		/* restart transmission */
		USBVCP_Send(buf + buf_offs, buf_size - buf_offs, TestVCP_VCPTxCallback);
	}
    /* return status */
    return EOK;
}

/* receive callback */
static int TestVCP_VCPRxCallback(void *ptr)
{
	/* cast event argument */
    usbvcp_cbarg_t *ca = ptr;
    /* get the size of the transfer */
	size_t size = ca ? ca->size : 0;

	/* zero-terminate */
	buf[size] = 0, buf_size = size, buf_offs = 0;
	/* display */
	if (size) {
		/* display data */
		dprintf("sz = %d, data = %s\n", size, buf);
		/* start transmitting */
		if (Sem_Lock(&usbvcptx_sem, CB_NONE) == EOK)
			TestVCP_VCPTxCallback(0);
	/* nothing in buffer */
	} else {
		/* receive! */
		USBVCP_Recv(buf, sizeof(buf) - 1, TestVCP_VCPRxCallback);
	}
    /* return status */
    return EOK;
}

/* initialize virtual com port test */
int TestVCP_Init(void)
{
    /* initialize transmitter buffer */
    for (int i = 0; i < elems(tx_buf); i++)
        tx_buf[i] = pattern[i % (elems(pattern) - 1)];

    USB_Connect(1);
	/* start reception */
	// TestVCP_VCPRxCallback(0);
	/* report status */
	return EOK;
}

static int cb(void *ptr)
{
    /* cast callback argument */
    usbvcp_cbarg_t *ca = ptr;
    /* restore the buffer contents */
    if (ca)
        tx_buf[ca->size - 1] = pattern[(ca->size - 1) % (elems(pattern) - 1)];
    /* increment pattern length */
    if (++pattern_len > elems(tx_buf))
            pattern_len = 1;
    /* add the newline */
    tx_buf[pattern_len - 1] = '\n';

    /* send the data */
    USBVCP_Send(tx_buf, pattern_len, cb);

    /* report callback status */
    return EOK;
} 

/* polling */
void TestVCP_Poll(void)
{
	// /* check wakeup timer */
	// if (dtime(time(0), timer) < 300)
	// 	return;

	/* generate notification */
	if (Sem_Lock(&usbvcptx_sem, CB_NONE) == EOK) {
        /* kick the timer */
		timer = time(0);
        /* increment pattern length */
        if (++pattern_len > elems(tx_buf))
            pattern_len = 1;
        /* add the newline */
        tx_buf[pattern_len-1] = '\n';
        /* send the data */
		USBVCP_Send(tx_buf, pattern_len, cb);
	}
}

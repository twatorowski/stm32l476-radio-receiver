/**
 * @file vcp.c
 * 
 * @date 2020-02-10
 * @author twatorowski 
 * 
 * @brief Test for virtual COM port connection and data exchange
 */

#include <dev/usb.h>
#include <dev/usbvcp.h>
#include "err.h"
#include <sys/time.h>

#define DEBUG
#include "debug.h"

/* data buffer */
static char buf[32 + 1];
/* buffer size & offset */
static size_t buf_size, buf_offs;
/* notification pointer */
static time_t timer;

/* tx done callback */
static int TestVCP_VCPTxCallback(void *arg);
/* receive callback */
static int TestVCP_VCPRxCallback(void *arg);

/* tx done callback */
static int TestVCP_VCPTxCallback(void *arg)
{
	/* get size */
	size_t size = arg ? *(size_t *)arg : 0;

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
static int TestVCP_VCPRxCallback(void *arg)
{
	/* get size */
	size_t size = arg ? *(size_t *)arg : 0;

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
    USB_Connect(1);
	/* start reception */
	TestVCP_VCPRxCallback(0);
	/* report status */
	return EOK;
}

/* polling */
void TestVCP_Poll(void)
{
	/* check wakeup timer */
	if (dtime(time(0), timer) < 500)
		return;

	/* generate notification */
	if (Sem_Lock(&usbvcptx_sem, CB_NONE) == EOK) {
		timer = time(0);
		USBVCP_Send("notify", 6, TestVCP_VCPTxCallback);
	}
}

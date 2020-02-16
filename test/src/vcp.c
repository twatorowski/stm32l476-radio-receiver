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
#include "dev/usb_vcp.h"
#include "sys/time.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

/* transmitted data */
/* data buffer */
static char buf[max(USB_VCP_TX_SIZE, USB_VCP_RX_SIZE) + 1];
/* buffer size & offset */
static size_t buf_size, buf_offs;

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
		/* release the semaphore */
		Sem_Release(&usbvcptx_sem);
        /* start reception */
        Sem_Lock(&usbvcprx_sem, TestVCP_VCPRxCallback);
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
        /* release the receive semaphore */
        Sem_Release(&usbvcprx_sem);
		/* start transmitting */
		Sem_Lock(&usbvcptx_sem, TestVCP_VCPTxCallback);
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
    /* start the process */
    Sem_Lock(&usbvcprx_sem, TestVCP_VCPRxCallback);
	/* report status */
	return EOK;
}

/* polling */
void TestVCP_Poll(void)
{

}

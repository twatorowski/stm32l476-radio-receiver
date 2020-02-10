/*
 * usbvcp.c
 *
 *	Created on: 23.07.2017
 *		Author: Tomek
 */

#include <dev/usb.h>
#include <dev/usbcore.h>
#include <dev/usbdesc.h>
#include <dev/usbvcp.h>
#include "err.h"
#include <sys/sem.h>
#include <util/minmax.h>
#include "util/string.h"

//#define DEBUG
#include "debug.h"

/* semaphores */
sem_t usbvcprx_sem, usbvcptx_sem;

/* line encoding */
typedef struct {
	/* current baudrate */
	uint32_t bauds;
	/* stop bits */
	uint8_t stop_bits;
	/* parity type */
	uint8_t parity_type;
	/* data bits */
	uint8_t data_bits;
} __attribute__((packed)) le_t;
/* current line encoding: 115200bps, 1 stop bit, no parity, 8 bits */
static le_t le = {115200, 1, 0, 8};

/* callbacks */
static cb_t tx_cb, rx_cb;
/* buffer pointers */
static uint8_t *tx_ptr, *rx_ptr;
/* buffer size */
static size_t tx_size, tx_offs, rx_size, rx_offs;

/* temporary rx buffer */
static uint8_t rx_buf_[32];
/* temporary buffer size */
static size_t rx_buf_size, rx_buf_offs;

/* return data from buffer */
static size_t USBVCP_GetDataFromRxBuf(void *ptr, size_t size)
{
	/* number of bytes to copy */
	size_t bytes_to_copy = min(size, rx_buf_size - rx_buf_offs);
	/* copy data to caller buffer */
	memcpy(ptr, rx_buf_ + rx_buf_offs, bytes_to_copy);
	/* set initial pointer value */
	rx_buf_offs += bytes_to_copy;

	/* return number of bytes copied */
	return bytes_to_copy;
}

/* data received callback (received by the device from host) */
static int USBVCP_EpRxCallback(void *arg)
{
	/* get data size */
	size_t size = arg ? *(size_t *)arg : 0;
	/* callback */
	cb_t cb = rx_cb;
	/* called by usb stack */
	if (size)
		rx_buf_size = size, rx_buf_offs = 0;

	/* fetch data */
	rx_offs = USBVCP_GetDataFromRxBuf(rx_ptr, rx_size);
	/* clear the reception callback */
	rx_cb = CB_SYNC;
	/* sync call */
	if (cb == CB_SYNC) {
		cb = CB_NONE;
	/* async call was made? */
	} else if (cb != CB_NONE) {
		cb(&rx_offs);
	}

    /* report callback status */
    return EOK;
}

/* data sent callback (sent from device to host) */
static int USBVCP_EpTxCallback(void *arg)
{
	/* get data size */
	size_t size = arg ? *(size_t *)arg : 0;
	/* callback */
	cb_t cb = tx_cb;

	/* update offset */
	tx_offs += size;
	/* still got some data to send */
	if (tx_size > tx_offs) {
		/* restart transfer with the maximal data size possible */
		USB_StartINTransfer(USB_EP2, tx_ptr + tx_offs, min(32, tx_size - tx_offs),
				USBVCP_EpTxCallback);
	/* need to send zero length packet? */
	} else if (tx_offs % 32 == 0) {
		/* this ensures that we don't send more thatn one zlp */
		tx_offs = tx_size + 1;
		/* start transfer */
		USB_StartINTransfer(USB_EP2, 0, 0, USBVCP_EpTxCallback);
	/* all done! */
	} else {
		/* clear the transmission callback */
		tx_cb = CB_SYNC;
		/* sync call */
		if (cb == CB_SYNC) {
			cb = CB_NONE;
		/* async call was made? */
		} else if (cb != CB_NONE) {
			cb(&tx_size);
		}
	}

    /* report callback status */
    return EOK;
}

/* request callback: handle all special requests */
static int USBVCP_RequestCallback(void *arg)
{
	/* event argument */
	usbcore_req_evarg_t *a = arg;
	/* setup frame that cauesd this event */
	usb_setup_t *s = a->setup;

	/* some debug */
	dprintf("index = 0x%x, len = %d, r = 0x%x, r_type = 0x%x, val = 0x%x\n",
			s->index, s->length, s->request, s->request_type, s->value);

	/* switch on request type */
	switch (s->request) {
	/* set line encoding */
	case USB_VCP_REQ_SET_LINE_CODING : {
		/* still waiting for the data stage */
		if (a->ptr == 0) {
			/* set where to store data to */
			a->ptr = (void *)&le, a->size = sizeof(le);
		/* got data */
		} else	{
			/* TODO: apply line parameters */
		}
		/* set status */
		a->status = EOK;
	} break;
	/* get line encoding */
	case USB_VCP_REQ_GET_LINE_CODING : {
		/* set returned data */
		a->ptr = (void *)&le, a->size = sizeof(le);
		a->status = EOK;
	} break;
	/* set control line state */
	case USB_VCP_SET_CONTROL_LINE_STATE : {
		a->status = EOK;
	} break;
	}

    /* report callback status */
    return EOK;
}

/* usb reset callback */
static int USBVCP_ResetCallback(void *arg)
{
	/* prepare fifos */
	USB_SetTxFifoSize(USB_EP1, 0x20);
	USB_SetTxFifoSize(USB_EP2, 0x20);
	/* flush fifo */
	USB_FlushTxFifo(USB_EP1);
	USB_FlushTxFifo(USB_EP2);

	/* configure endpoints */
	USB_ConfigureINEndpoint(USB_EP1, USB_EPTYPE_INT, 0x08);
	USB_ConfigureINEndpoint(USB_EP2, USB_EPTYPE_BULK, 0x40);
	USB_ConfigureOUTEndpoint(USB_EP3, USB_EPTYPE_BULK, 0x40);

	/* sync call */
	if (tx_cb == CB_SYNC) {
		tx_cb = CB_NONE;
	/* async call was made? */
	} else if (tx_cb != CB_NONE) {
		tx_cb(0);
	}

	/* sync call */
	if (rx_cb == CB_SYNC) {
		rx_cb = CB_NONE;
	/* async call was made? */
	} else if (rx_cb != CB_NONE) {
		rx_cb(0);
	}

    /* report callback status */
    return EOK;
}

/* initialize virtual com port logic */
int USBVCP_Init(void)
{
	/* listen to usb reset events */
	Ev_RegisterCallback(&usb_rst_ev, USBVCP_ResetCallback);
	Ev_RegisterCallback(&usbcore_req_ev, USBVCP_RequestCallback);

	/* release semaphore */
	Sem_Release(&usbvcprx_sem);
	Sem_Release(&usbvcptx_sem);

	/* report status */
	return EOK;
}

/* read data */
int USBVCP_Recv(void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int rc = size, sync = cb == CB_SYNC;

	/* store callback information */
	rx_cb = cb;
	/* store data */
	rx_ptr = ptr, rx_size = size;

	/* fetch data that still resides in buffer */
	if (rx_buf_size != rx_buf_offs) {
		USBVCP_EpRxCallback(0);
	/* need to restart the data reception */
	} else {
		/* this shall start the transfer */
		USB_StartOUTTransfer(USB_EP3, rx_buf_, sizeof(rx_buf_), 
            USBVCP_EpRxCallback);
	}

	/* interrupt will alter callback address after transfer has finished */
	while (sync && rx_cb == CB_SYNC);
	/* report size */
	return rc;
}

/* write data */
int USBVCP_Send(const void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int rc = size, sync = cb == CB_SYNC;

	/* store callback information */
	tx_cb = cb;
	/* store data */
	tx_ptr = (uint8_t *)ptr, tx_size = size, tx_offs = 0;

	/* this shall start the transfer */
	USBVCP_EpTxCallback(0);

	/* interrupt will alter callback address after transfer has finished */
	while (sync && tx_cb == CB_SYNC);
	/* report size */
	return rc;
}

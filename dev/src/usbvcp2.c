/**
 * @file usbvcp2.c
 * 
 * @date 2019-12-07
 * @author twatorowski 
 * 
 * @brief Minimalistic Virtual Com Port implementation that works over the 
 * usbcore.c
 */

#include "compiler.h"
#include "err.h"
#include "dev/invoke.h"
#include "dev/usb.h"
#include "dev/usbcore.h"
#include "dev/usbdesc.h"
#include "dev/usbvcp.h"
#include "dev/usbvcp2.h"
#include "sys/sem.h"
#include "util/minmax.h"
#include "util/string.h"

#define DEBUG
#include "debug.h"

/* semaphores */
sem_t usbvcprx2_sem, usbvcptx2_sem;

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
} PACKED le_t;
/* current line encoding: 115200bps, 1 stop bit, no parity, 8 bits */
static le_t le = {115200, 1, 0, 8};

/* callbacks */
static cb_t tx_cb, rx_cb;
/* callback arguments */
static usbvcp_cbarg_t tx_cb_arg, rx_cb_arg;

/* temporary rx buffer */
static uint8_t rx_buf[USB_VCP_RX_SIZE];
/* temporary buffer size */
static size_t rx_buf_size, rx_buf_offs, tx_buf_offs;

/* transfer guarding semaphores */
static sem_t rx_guard_sem, tx_guard_sem;

/* reception callback */
static int USBVCP2_EpRxCallback(void *arg)
{
    /* cast event argument */
    usb_cbarg_t *ca = arg;
    /* get data size carried by the event */
	size_t size = ca ? ca->size : 0;
    /* get the error code */
    int error = ca ? ca->error : EOK;

    /* update the size */
    rx_buf_size += size;
    /* two main reasons for calling the callback: an error occured, got data 
     * buffered */
    if (error != EOK || rx_buf_size != rx_buf_offs) {
        /* this ensures that callback gets called only once per transfer 
         * request */
        if (Sem_Lock(&rx_guard_sem, CB_NONE) != EOK)
            return EOK;
        
        /* prepare the callback argument */
        rx_cb_arg.error = error;
        /* limit the number of bytes to copy */
        rx_cb_arg.size = min(rx_cb_arg.size, rx_buf_size - rx_buf_offs);
        /* copy data to the destination buffer */
        memcpy(rx_cb_arg.ptr, rx_buf + rx_buf_offs, rx_cb_arg.size);
        /* update the buffer offset */
        rx_buf_offs += rx_cb_arg.size;

        dprintf("sz = %d, rc = %d\n", rx_cb_arg.size, rx_cb_arg.error);

        /* call the callback */
        if (rx_cb == CB_SYNC) {
            rx_cb = CB_NONE;
        /* async call was made? */
        } else if (rx_cb != CB_NONE) {
            rx_cb(&rx_cb_arg);
        }

    /* nothing in buffers - restart the reception */
    } else {
        /* reset the buffer */
        rx_buf_offs = rx_buf_size = 0;
        /* this shall start the transfer */
        USB_StartOUTTransfer(USB_EP4, rx_buf, sizeof(rx_buf), 
            USBVCP2_EpRxCallback);
    }

    /* report status */
    return EOK;
}

/* data sent callback (sent from device to host) */
static int USBVCP2_EpTxCallback(void *arg)
{
    /* cast event argument */
    usb_cbarg_t *ca = arg;
    /* get the error code */
    int error = ca ? ca->error : EOK;

    /* two main reasons */
    if (error != EOK || tx_buf_offs > tx_cb_arg.size) {
        /* this ensures that callback gets called only once per transfer 
         * request */
        if (Sem_Lock(&tx_guard_sem, CB_NONE) != EOK)
            return EOK;
        
        /* store the error code */
        tx_cb_arg.error = error;
        /* store the transfer size */
        tx_cb_arg.size = min(tx_buf_offs, tx_cb_arg.size);

        /* sync call */
		if (tx_cb == CB_SYNC) {
			tx_cb = CB_NONE;
		/* async call was made? */
		} else if (tx_cb != CB_NONE) {
			tx_cb(&tx_cb_arg);
		}
    /* still got some data or zero-length packets to push over the bus */
    } else {
        /* update the buffer offset */
        size_t tx_offs = tx_buf_offs; tx_buf_offs += USB_VCP_TX_SIZE;
        /* restart transfer with the maximal data size possible */
		USB_StartINTransfer(USB_EP4, (uint8_t *)tx_cb_arg.ptr + tx_offs, 
            min(USB_VCP_TX_SIZE, tx_cb_arg.size - tx_offs), 
            USBVCP2_EpTxCallback);
    } 

    /* report callback status */
    return EOK;
}

/* request callback: handle all special requests */
static int USBVCP2_RequestCallback(void *arg)
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

    /* report status callback */
    return EOK;
}

/* usb reset callback */
static int USBVCP2_ResetCallback(void *arg)
{
	/* prepare fifos */
    /* interrupt transfers */
	USB_SetTxFifoSize(USB_EP3, USB_VCP_INT_SIZE / 4);
    /* Bulk IN (used for data transfers from device to host) */
	USB_SetTxFifoSize(USB_EP4, USB_VCP_TX_SIZE / 4);
	/* flush fifos */
	USB_FlushTxFifo(USB_EP3);
	USB_FlushTxFifo(USB_EP4);
	/* configure endpoints */
	USB_ConfigureINEndpoint(USB_EP3, USB_EPTYPE_INT, USB_VCP_INT_SIZE);
	USB_ConfigureINEndpoint(USB_EP4, USB_EPTYPE_BULK, USB_VCP_TX_SIZE);
	USB_ConfigureOUTEndpoint(USB_EP4, USB_EPTYPE_BULK, USB_VCP_RX_SIZE);

    /* the following calls are made to restart the process of reception or 
     * transmission in case of reset */
    /* prepare the callback event argument that indicates the reset took place */
    static const usb_cbarg_t ca = { .error = EUSB_RESET, .size = 0 };
    /* invoke both routines */
    Invoke_CallMeElsewhere(USBVCP2_EpTxCallback, (void *)&ca);
    Invoke_CallMeElsewhere(USBVCP2_EpRxCallback, (void *)&ca);

    /* report status callback */
    return EOK;
}

/* initialize virtual com port logic */
int USBVCP2_Init(void)
{
	/* listen to usb reset events */
	Ev_RegisterCallback(&usb_rst_ev, USBVCP2_ResetCallback);
	Ev_RegisterCallback(&usbcore_req_ev, USBVCP2_RequestCallback);

	/* release semaphore */
	Sem_Release(&usbvcprx2_sem);
	Sem_Release(&usbvcptx2_sem);

	/* report status */
	return EOK;
}

/* read data */
usbvcp_cbarg_t * USBVCP2_Recv(void *ptr, size_t size, cb_t cb)
{
	/* sync or async call? */
	int sync = cb == CB_SYNC;

	/* store callback information */
	rx_cb = cb;
    /* store pointer and size */
    rx_cb_arg.ptr = ptr; rx_cb_arg.size = size;

    /* release the transfer semaphore */
    Sem_Release(&rx_guard_sem);
    /* initiate transfer */
    Invoke_CallMeElsewhere(USBVCP2_EpRxCallback, 0);

	/* interrupt will alter callback address after transfer has finished */
	while (sync && rx_cb == CB_SYNC);
	/* report size */
	return sync ? &rx_cb_arg : 0;
}

/* write data */
usbvcp_cbarg_t * USBVCP2_Send(const void *ptr, size_t size, cb_t cb)
{
	/* sync or async call? */
	int sync = cb == CB_SYNC;

	/* store callback information */
	tx_cb = cb;
    /* store pointer and size */
    tx_cb_arg.ptr = (void *)ptr; tx_cb_arg.size = size;
    /* reset the transfer offset */
    tx_buf_offs = 0;

    /* release the transfer semaphore */
    Sem_Release(&tx_guard_sem);
    /* initiate transfer */
    Invoke_CallMeElsewhere(USBVCP2_EpTxCallback, 0);

	/* interrupt will alter callback address after transfer has finished */
	while (sync && tx_cb == CB_SYNC);
	/* report size */
	return sync ? &tx_cb_arg : 0;
}

/**
 * @file usb_au_src.c
 * 
 * @date 2020-02-11
 * @author twatorowski 
 * 
 * @brief USB Audio Source
 */

#include "err.h"
#include "dev/await.h"
#include "dev/invoke.h"
#include "dev/usb.h"
#include "dev/usbcore.h"
#include "sys/time.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

/* samples buffer */
static uint16_t buf[] = {
    0x0000, 0x30fb, 0x5a81, 0x7640, 0x7fff, 0x7640, 0x5a81, 0x30fb,
    0x0000, 0xcf05, 0xa57f, 0x89c0, 0x8001, 0x89c0, 0xa57f, 0xcf05,
};

static int cnt; 
static int si;
static sem_t sem = {.released = 1};
static int USBAuSrc_EpTxCallback(void *arg)
{
    if (si == 1) {
        USB_StartINTransfer(USB_EP1, buf, 32, USBAuSrc_EpTxCallback);
        // si = 0;
    } else {
        Sem_Release(&sem);
    }

    return EOK;
}

/* request callback: handle all special requests */
static int USBAuSrc_RequestCallback(void *arg)
{
	/* event argument */
	usbcore_req_evarg_t *a = arg;
	/* setup frame that cauesd this event */
	usb_setup_t *s = a->setup;

    /* extract type */
	uint8_t type = s->request_type & USB_SETUP_REQTYPE_TYPE;
    /* status of frame processing */
	int rc = EFATAL;

	/* some debug */
	dprintf("index = 0x%x, len = %d, r = 0x%x, r_type = 0x%x, val = 0x%x\n",
	    s->index, s->length, s->request, s->request_type, s->value);

    /* standard request */
	if (type == USB_SETUP_REQTYPE_TYPE_STANDARD) {
        /* process all 'set' frames. such frames have direction bit cleared */
		if (!(s->request_type & USB_SETUP_REQTYPE_DIR)) {
            /* frame opcode is contained in 'request' field */
			switch (s->request) {
            /* set interface */
			case USB_SETUP_REQ_SET_INTERFACE : {
                /* interface identifier */
                int iface_num = s->index;
                /* alternative setting */
                int iface_alt_num = s->value;

				dprintf("inum = %d, alt = %d\n", iface_num, iface_alt_num);
                if (iface_num == 1) {
                    si = iface_alt_num;
                    if (iface_alt_num && Sem_Lock(&sem, CB_NONE) == EOK) {
                        USBAuSrc_EpTxCallback(0);
                    }
                }
			} break;   
            }
        }
    }
    

	// /* switch on request type */
	// switch (s->request) {
	// /* set line encoding */
	// case USB_VCP_REQ_SET_LINE_CODING : {
	// 	/* still waiting for the data stage */
	// 	if (a->ptr == 0) {
	// 		/* set where to store data to */
	// 		a->ptr = (void *)&le, a->size = sizeof(le);
	// 	/* got data */
	// 	} else	{
	// 		/* TODO: apply line parameters */
	// 	}
	// 	/* set status */
	// 	a->status = EOK;
	// } break;
	// /* get line encoding */
	// case USB_VCP_REQ_GET_LINE_CODING : {
	// 	/* set returned data */
	// 	a->ptr = (void *)&le, a->size = sizeof(le);
	// 	a->status = EOK;
	// } break;
	// /* set control line state */
	// case USB_VCP_SET_CONTROL_LINE_STATE : {
	// 	a->status = EOK;
	// } break;
	// }

    /* report status callback */
    return EOK;
}
int i;
/* usb reset callback */
static int USBAuSrc_ResetCallback(void *arg)
{
	/* prepare fifos */
    /* interrupt transfers */
	USB_SetTxFifoSize(USB_EP1, USB_AU_SRC_SIZE);
	/* flush fifos */
	USB_FlushTxFifo(USB_EP1);
	/* configure endpoints */
	USB_ConfigureINEndpoint(USB_EP1, USB_EPTYPE_ISO, USB_AU_SRC_SIZE);

    // /* the following calls are made to restart the process of reception or 
    //  * transmission in case of reset */
    // /* prepare the callback event argument that indicates the reset took place */
    //static const usb_cbarg_t ca = { .error = EUSB_RESET, .size = 0 };
    // /* invoke both routines */
    //Invoke_CallMeElsewhere(USBAuSrc_EpTxCallback, (void *)&ca);

    // if (i++ == 0)
        // Await_CallMeLater(10000, USBAuSrc_EpTxCallback, 0);
    // dprintf("R!\n" ,0 );

    /* report status callback */
    return EOK;
}

/* initialize audio source */
int USBAuSrc_Init(void)
{
	/* listen to usb reset events */
	Ev_RegisterCallback(&usb_rst_ev, USBAuSrc_ResetCallback);
	Ev_RegisterCallback(&usbcore_req_ev, USBAuSrc_RequestCallback);

	/* report status */
	return EOK;
}
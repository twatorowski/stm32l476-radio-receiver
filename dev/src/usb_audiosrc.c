/**
 * @file usb_audiosrc.c
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
#include "dev/usb_audiosrc.h"
#include "sys/time.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

/* system event */
ev_t usb_audio_ev;

/* interface opened? */
static int mode;

/* data transfer complete callback */
static int USBAudioSrc_EpTxCallback(void *arg)
{   
    /* prepare the event argument */
    usb_audio_evarg_t ea = { .mode = mode, 
        .type = USB_AUDIO_SRC_EVARG_TYPE_TXDONE,
        .ptr = 0, .size = 0 };
    /* notify */
    Ev_Notify(&usb_audio_ev, &ea);
    
    /* report status */
    return EOK;
}

/* request callback: handle all special requests */
static int USBAudioSrc_RequestCallback(void *arg)
{
	/* event argument */
	usbcore_req_evarg_t *a = arg;
	/* setup frame that cauesd this event */
	usb_setup_t *s = a->setup;
    /* extract type */
	uint8_t type = s->request_type & USB_SETUP_REQTYPE_TYPE;

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
                /* show message */
				dprintf("inum = %d, alt = %d\n", iface_num, iface_alt_num);
                /* alternate setting 1: sampling mode */
                if (!mode && iface_alt_num) {
                    /* start sending audio */
                    USBAudioSrc_EpTxCallback(0);
                /* alternate setting 0: disabled mode */
                } else if (mode && !iface_alt_num) {
                    USB_DisableINEndpoint(USB_EP1);
                }
                /* update the 'opened' state */
                mode = iface_alt_num;
                /* set status code */
                a->status = EOK;
			} break;   
            }
        }
    }

    /* report status callback */
    return EOK;
}

/* incomplete isochronous callback */
static int USBAudioSrc_IncompleteIsoCallback(void *arg)
{
    /* disable endpoint */
    // USB_DisableINEndpoint(USB_EP1);
    USB_FlushTxFifo(USB_EP1);
    /* prepare the event argument */
    usb_audio_evarg_t ea = { .mode = mode, 
        .type = USB_AUDIO_SRC_EVARG_TYPE_ISOINC,
        .ptr = 0, .size = 0 };
    /* notify */
    Ev_Notify(&usb_audio_ev, &ea);

    /* report status */
    return EOK;
}

/* usb reset callback */
static int USBAudioSrc_ResetCallback(void *arg)
{
	/* prepare fifos */
    /* interrupt transfers */
	USB_SetTxFifoSize(USB_EP1, USB_AUDIO_SRC_MAX_TFER_SIZE / 4);
	/* flush fifos */
	USB_FlushTxFifo(USB_EP1);
	/* configure endpoints */
	USB_ConfigureINEndpoint(USB_EP1, USB_EPTYPE_ISO, 
        USB_AUDIO_SRC_MAX_TFER_SIZE);

    /* report status callback */
    return EOK;
}

/* usb callback */
static int USBAudioSrc_USBCallback(void *arg)
{
    /* cast event argument */
    usb_evarg_t *ea = arg;
    /* processing according to event type */
    switch (ea->type) {
    case USB_EVARG_TYPE_RESET : USBAudioSrc_ResetCallback(arg); break;
    case USB_EVARG_TYPE_ISOINC : USBAudioSrc_IncompleteIsoCallback(arg); break;
    }

    /* report status */
	return EOK;
}

/* initialize audio source */
int USBAudioSrc_Init(void)
{
	/* listen to usb reset events */
	Ev_RegisterCallback(&usb_ev, USBAudioSrc_USBCallback);
	Ev_RegisterCallback(&usbcore_req_ev, USBAudioSrc_RequestCallback);

	/* report status */
	return EOK;
}

void USBAudioSrc_Transfer(void *ptr, size_t size)
{
    /* send buffer contents */
    USB_StartINTransfer(USB_EP1, (void *)ptr, size, 
        USBAudioSrc_EpTxCallback);
}
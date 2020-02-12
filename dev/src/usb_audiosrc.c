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
#include "sys/time.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

#define MODE_OFF                    0
#define MODE_MONO                   1
#define MODE_STEREO                 2

/* example samples buffer */
static const uint32_t buf[] = {
    0x00000000, 0x085f2136, 0x10b5150f, 0x18f8b83c,
    0x2120fb82, 0x2924edab, 0x30fbc54c, 0x389cea71,
    0x3fffffff, 0x471cece6, 0x4debe4fd, 0x54657193,
    0x5a827999, 0x603c496b, 0x658c9a2c, 0x6a6d98a3,
    0x6ed9eba0, 0x72ccb9d9, 0x7641af3b, 0x793501a7,
    0x7ba3751c, 0x7d8a5f3e, 0x7ee7aa4a, 0x7fb9d757,
    0x7fffffff, 0x7fb9d757, 0x7ee7aa4a, 0x7d8a5f3e,
    0x7ba3751c, 0x793501a7, 0x7641af3b, 0x72ccb9d9,
    0x6ed9eba0, 0x6a6d98a3, 0x658c9a2c, 0x603c496b,
    0x5a827999, 0x54657193, 0x4debe4fd, 0x471cece6,
    0x3fffffff, 0x389cea71, 0x30fbc54c, 0x2924edab,
    0x2120fb82, 0x18f8b83c, 0x10b5150f, 0x085f2136,
    0x00000000, 0xf7a0deca, 0xef4aeaf1, 0xe70747c4,
    0xdedf047e, 0xd6db1255, 0xcf043ab4, 0xc763158f,
    0xc0000001, 0xb8e3131a, 0xb2141b03, 0xab9a8e6d,
    0xa57d8667, 0x9fc3b695, 0x9a7365d4, 0x9592675d,
    0x91261460, 0x8d334627, 0x89be50c5, 0x86cafe59,
    0x845c8ae4, 0x8275a0c2, 0x811855b6, 0x804628a9,
    0x80000001, 0x804628a9, 0x811855b6, 0x8275a0c2,
    0x845c8ae4, 0x86cafe59, 0x89be50c5, 0x8d334627,
    0x91261460, 0x9592675d, 0x9a7365d4, 0x9fc3b695,
    0xa57d8667, 0xab9a8e6d, 0xb2141b03, 0xb8e3131a,
    0xc0000001, 0xc763158f, 0xcf043ab4, 0xd6db1255,
    0xdedf047e, 0xe70747c4, 0xef4aeaf1, 0xf7a0deca,
};
/* interface opened? */
static int mode;

/* data transfer complete callback */
static int USBAudioSrc_EpTxCallback(void *arg)
{   
    /* transfer size */
    size_t size = USB_AUDIO_SRC_STEREO_SIZE;
    /* transmit half of the data in mono mode */
    if (mode == MODE_MONO)
        size = USB_AUDIO_SRC_MONO_SIZE;
    /* send buffer contents */
    USB_StartINTransfer(USB_EP1, (void *)buf, size, USBAudioSrc_EpTxCallback);
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

/* usb reset callback */
static int USBAudioSrc_ResetCallback(void *arg)
{
	/* prepare fifos */
    /* interrupt transfers */
	USB_SetTxFifoSize(USB_EP1, USB_AUDIO_SRC_STEREO_SIZE / 4);
	/* flush fifos */
	USB_FlushTxFifo(USB_EP1);
	/* configure endpoints */
	USB_ConfigureINEndpoint(USB_EP1, USB_EPTYPE_ISO, USB_AUDIO_SRC_STEREO_SIZE);

    /* report status callback */
    return EOK;
}

/* initialize audio source */
int USBAudioSrc_Init(void)
{
	/* listen to usb reset events */
	Ev_RegisterCallback(&usb_rst_ev, USBAudioSrc_ResetCallback);
	Ev_RegisterCallback(&usbcore_req_ev, USBAudioSrc_RequestCallback);

	/* report status */
	return EOK;
}
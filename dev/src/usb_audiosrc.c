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

/* current interface working mode */
static int mode;

/* usb sample type */
typedef struct { int32_t l, r; } usb_buf_elem_t;
/* data buffer */
static usb_buf_elem_t buf[USB_AUDIO_SRC_SAMPLES_PER_FRAME * 4];
/* linear memory space buffer */
static usb_buf_elem_t buf_lin[USB_AUDIO_SRC_MAX_TFER_SIZE / 
    sizeof(usb_buf_elem_t)];
/* head and tail pointers */
static uint32_t usb_head, usb_tail;

/* get samples from the buffer */
static int USBAudioSrc_GetSamples(usb_buf_elem_t *ptr, int num)
{
    /* space used within buffer, overall number frames to get, tail index */
    uint32_t space_used, frames_to_get, tail;
    /* samples to get before/after the circular buffer wraps */
    uint32_t frames_to_get_bwrap, frames_to_get_awrap;

    /* space used */
    space_used = usb_head - usb_tail;
    /* number of frames to get */
    frames_to_get = min(space_used, (unsigned)num);
    /* get the tail pointer */
    tail = usb_tail % elems(buf);
    /* limit the number of samples till wrapping occurs */
    frames_to_get_bwrap = min(frames_to_get, elems(buf) - tail);
    frames_to_get_awrap = frames_to_get - frames_to_get_bwrap;

    /* read data */
    for (int i = 0; i < (int)frames_to_get_bwrap; i++, ptr++)
        ptr->l = buf[tail + i].l, ptr->r = buf[tail + i].r;
    
    /* read data */
    for (int i = 0; i < (int)frames_to_get_awrap; i++, ptr++)
        ptr->l = buf[i].l, ptr->r = buf[i].r;
    
    /* update the tail pointer */
    usb_tail += frames_to_get;
    /* return the number of frames fetched from the buffer */
    return frames_to_get;
}

/* data transfer complete callback */
static int USBAudioSrc_DataCallback(void *arg)
{   
    /* space used in buffer */
    uint32_t space_used = usb_head - usb_tail;
    /* number of frames to fetch */
    uint32_t frames_to_get = USB_AUDIO_SRC_SAMPLES_PER_FRAME;

    /* buffer is getting full, use larger transfers */
    if (space_used > elems(buf) / 2)
        frames_to_get = elems(buf_lin);

    /* get samples to the buffer */
    int frames_fetched = USBAudioSrc_GetSamples(buf_lin, frames_to_get);
    /* send buffer contents */
    USB_StartINTransfer(USB_EP1, buf_lin, 
        frames_fetched * sizeof(usb_buf_elem_t), USBAudioSrc_DataCallback);
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
                    USBAudioSrc_DataCallback(0);
                /* alternate setting 0: disabled mode */
                } else if (mode && !iface_alt_num) {
                    USB_DisableINEndpoint(USB_EP1);
                }
                /* update the 'opened' state */
                mode = iface_alt_num;

                /* prepare event argument */
                usb_audio_evarg_t ea = { .mode = mode };
                /* generate an event */
                Ev_Notify(&usb_audio_ev, &ea);

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
    /* flush data */
    USB_FlushTxFifo(USB_EP1);
    /* restart audio process if possible */
    USBAudioSrc_DataCallback(0);

    /* report status */
    return EOK;
}

/* usb reset callback */
static int USBAudioSrc_ResetCallback(void *arg)
{
    /* reset mode */
    mode = USB_AUDIO_SRC_MODE_OFF;

    /* prepare event argument */
    usb_audio_evarg_t ea = { .mode = mode };
    /* generate an event */
    Ev_Notify(&usb_audio_ev, &ea);

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

/* put samples into the usb buffer */
int USBAudioSrc_PutSamples(const int32_t *l, const int32_t *r, int num)
{
    /* space left, overall number of frames to store, head element index */
    uint32_t space_left, frames_to_store, head;
    /* samples to store before/after the circular buffer wraps */
    uint32_t frames_to_store_bwrap, frames_to_store_awrap;

    /* space left */
    space_left = elems(buf) - (usb_head - usb_tail);
    /* buffer is full */
    frames_to_store = min(space_left, (unsigned)num);
    
    /* get the head pointer */
    head = usb_head % elems(buf);
    /* limit the number of samples till/after the wrapping occurs */
    frames_to_store_bwrap = min(frames_to_store, elems(buf) - head);
    frames_to_store_awrap = frames_to_store -frames_to_store_bwrap;
    
    /* store data before the buffer wraps */
    for (int i = 0; i < (int)frames_to_store_bwrap; i++)
        buf[head + i].l = *l++, buf[head + i].r = *r++;

    /* store data */
    for (int i = 0; i < (int)frames_to_store_awrap; i++)
        buf[i].l = *l++, buf[i].r = *r++;
        
    /* update the head pointer */
    usb_head += frames_to_store;
    /* return the number of frames stored */
    return frames_to_store;
}
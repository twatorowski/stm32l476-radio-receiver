/*
 * usbcore.c
 *
 *	Created on: 22.07.2017
 *		Author: Tomek
 */

#include <dev/usb.h>
#include <dev/usbcore.h>
#include "dev/usbdesc.h"
#include "err.h"
#include <util/minmax.h>
#include "util/string.h"

#define DEBUG
#include "debug.h"

/* core events */
ev_t usbcore_req_ev;

/* control endpoint setup frame buffer: max three back to back setup frames can be
 * received */
static usb_setup_t ctl_setup[3];
/* index of currently processed frame */
static uint32_t ctl_index;
/* control transfer data pointer */
static uint8_t *ctl_ptr;
/* overall control size, single transfer size */
static size_t ctl_size, ctl_offset;
/* buffer used for generating responses for 'get' commands */
static uint8_t buf[16];
/* device control block */
static struct {
	/* device state, device bus address */
	uint32_t state, address;
	/* selected configuration number, device status */
	uint32_t configuration, status;
	/* halted endpoints mask */
	uint32_t ep_halt_tx, ep_halt_rx;
	/* device interface alternate settings */
	uint32_t alternate_settings[10];
} dev;

/* callbacks */
/* setup frame received */
static int USBCore_SetupCallback(void *arg);
/* data in send callback  */
static int USBCore_DataINCallback(void *arg);
/* status out received callback */
static int USBCore_StatusOUTCallback(void *arg);

/* start next setup packet reception process */
static void USBCore_StartSETUPStage(void)
{
	/* clear pointer: it is supposed to stay zeroed during setup stage */
	ctl_ptr = 0, ctl_size = 0;
	/* prepare for next setup transfer */
	USB_StartSETUPTransfer(USB_EP0, ctl_setup, sizeof(ctl_setup),
			USBCore_SetupCallback);
}

/* status out received callback */
static int USBCore_StatusOUTCallback(void *arg)
{
	dprintf("STATUS OUT\n", 0);
	/* prepare for next setup transfer */
	USBCore_StartSETUPStage();

    /* report status */
    return EOK;
}

/* status in stage callback */
static int USBCore_StatusINCallback(void *arg)
{
	dprintf("STATUS IN\n", 0);
	/* prepare for next setup transfer */
	USBCore_StartSETUPStage();
    
    /* report status */
    return EOK;
}

/* start status out stage */
static void USBCore_StartStatusOUTStage(void)
{
	/* wait for zero length packet */
	USB_StartOUTTransfer(USB_EP0, 0, 0, USBCore_StatusOUTCallback);
}

/* data in send callback  */
static int USBCore_DataINCallback(void *arg)
{
	/* max frame size */
	size_t max_size = USB_CTRLEP_SIZE;

	/* this logic ensures that we send zero-length packet at the end of transfer that
	 * consists of n * max_size bytes (i.e. no short packets at the end) */
	if (ctl_size - ctl_offset >= max_size) {
		/* update pointers */
		ctl_offset += min(max_size, ctl_size - ctl_offset);
		/* send next frame */
		USB_StartINTransfer(USB_EP0, ctl_ptr + ctl_offset,
				min(max_size, ctl_size - ctl_offset), USBCore_DataINCallback);
	/* done sending data? */
	} else {
		/* wait for status */
		USBCore_StartStatusOUTStage();
	}

    /* report status */
    return EOK;
}

/* begin data in stage */
static void USBCore_StartDataINStage(void *ptr, size_t size)
{
	/* max frame size */
	size_t max_size = USB_CTRLEP_SIZE;
	/* store information */
	ctl_ptr = ptr, ctl_size = size, ctl_offset = 0;
	/* this shall result in transfer start */
	USB_StartINTransfer(USB_EP0, ctl_ptr, min(max_size, ctl_size),
			USBCore_DataINCallback);
    // TODO:
	/* we shall enable reception to listen to status out frames that end 
     * transfer */
	USB_StartOUTTransfer(USB_EP0, 0, 0, USBCore_StatusOUTCallback);
}

/* continue data out */
static int USBCore_DataOUTCallback(void *ptr)
{
	/* max frame size */
	size_t max_size = USB_CTRLEP_SIZE;
	/* extract data size from packet size */
	size_t size = *(size_t *)ptr;

	/* update offset */
	ctl_offset += size;
	/* more data to come? */
	if (size == max_size) {
		/* restart out transfer */
		USB_StartOUTTransfer(USB_EP0, ctl_ptr + ctl_offset,
				min(max_size, ctl_size - ctl_offset), USBCore_DataOUTCallback);
	/* short or zlp received? */
	} else {
		/* once again start processing of the setup frame, but this time with complete
		 * data. zeroed 'arg' indicates the processing of previously received setup
		 * frame */
		uint32_t arg = 0; USBCore_SetupCallback(&arg);
	}

    /* report processing status */
    return EOK;
}

/* start data out stage */
static void USBCore_StartDataOUTStage(void *ptr, size_t size)
{
	/* max frame size */
	size_t max_size = USB_CTRLEP_SIZE;
	/* store information */
	ctl_ptr = ptr, ctl_size = size, ctl_offset = 0;

	/* start transfer */
	USB_StartOUTTransfer(USB_EP0, ctl_ptr, min(max_size, ctl_size),
			USBCore_DataOUTCallback);
}

/* start status in stage */
static void USBCore_StartStatusINStage(void)
{
	/* send zero length packet */
	USB_StartINTransfer(USB_EP0, 0, 0, USBCore_StatusINCallback);
}

/* abort IN transfer */
static void USBCore_AbortStage(void)
{
	/* set stall condition on data in endpoint */
	USB_StallINEndpoint(USB_EP0);
	USB_StallOUTEndpoint(USB_EP0);
	/* re-enable listening for next setup packets */
	USBCore_StartSETUPStage();
}

/* process setup get descriptor */
static int USBCore_ProcessSetupGetDescriptor(usb_setup_t *s, void **ptr,
		size_t *size)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* addressed to device */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* what descriptor type is requested? */
		uint8_t desc_type = s->value >> 8;
		/* descriptor index */
		uint8_t desc_index = s->value;

		/* assume that everything is ok */
		rc = EOK;

		/* prepare data buffer */
		switch (desc_type) {
		/* device descriptor was requested */
		case USB_SETUP_DESCTYPE_DEVICE : {
			/* set data pointer and size */
			*ptr = (uint8_t *)usb_device_descriptor;
			*size = (uint8_t)usb_device_descriptor[0];
		} break;
		/* configuration descriptor was requested */
		case USB_SETUP_DESCTYPE_CONFIGURATION : {
			/* check if descriptor exists */
			if (desc_index >= usb_config_descriptors_num) {
				/* wrong index */
				break;
			}
			/* set data pointer and size */
			*ptr = (uint8_t *)usb_config_descriptors[desc_index];
			*size = usb_config_descriptors[desc_index][2] |
					usb_config_descriptors[desc_index][3] << 8;
		} break;
		/* string descriptor was requested */
		case USB_SETUP_DESCTYPE_STRING : {
			/* check if descriptor exists */
			if (desc_index >= usb_string_descriptors_num) {
				/* wrong index */
				break;
			}
			/* set data pointer and size */
			*ptr = (uint8_t *)usb_string_descriptors[desc_index];
			*size = (uint8_t)usb_string_descriptors[desc_index][0];
		} break;
		/* device qualifier descriptor */
		case USB_SETUP_DESCTYPE_QUALIFIER : {
			*ptr = (uint8_t *)usb_qualifier_descriptor;
			*size = usb_qualifier_descriptor[0];
		} break;
		/* unknown descriptor */
		default : {
			/* report an error */
			rc = EFATAL;
		} break;
		}
	/* addressed to interface */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_IFACE) {
		/* argument */
		usbcore_req_evarg_t arg = {s, EFATAL, 0, 0};
		/* all other modules */
		Ev_Notify(&usbcore_req_ev, &arg);
		/* copy status, pointer and size */
		rc = arg.status, *ptr = arg.ptr, *size = arg.size;
	}

	/* limit size, host should only get as many bytes as it requests, no matter
	 * if data will be truncated */
	*size = min(*size, s->length);
	/* report status */
	return rc;
}

/* process get configuration */
static int USBCore_ProcessSetupGetConfiguration(usb_setup_t *s, void **ptr,
		size_t *size)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* addressed to device */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* check frame */
		if (s->value == 0 && s->index == 0 && s->length == 1) {
			/* check our state */
			if (dev.state != USB_DEV_DEFAULT) {
				/* fill buffer */
				buf[0] = dev.configuration;
				/* prepare pointers */
				*ptr = buf, *size = 1;
				/* report success */
				rc = EOK;
			}
		}
	}

	/* report status */
	return rc;
}

/* process get status */
static int USBCore_ProcessSetupGetStatus(usb_setup_t *s, void **ptr,
		size_t *size)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* check frame: those fields must have those values */
	if (s->value != 0 || s->length != 2)
		return rc;

	/* addressed to device */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* check frame */
		if (s->index == 0) {
			/* check our state */
			if (dev.state != USB_DEV_DEFAULT) {
				/* prepare data in temporary buffer: two bits: self-powered,
				 * remote wake-up */
				buf[0] = dev.status, buf[1] = 0;
				/* prepare transfer */
				*ptr = buf, *size = 2;

				/* report success */
				rc = EOK;
			}
		}
	/* interface is recipient */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_IFACE) {
		/* interface number */
		uint8_t iface_num = s->index;
		/* request is supported only in configured state */
		if (dev.state == USB_DEV_CONFIGURED && iface_num < usb_interfaces_num) {
			/* prepare data in temporary buffer: both zeros */
			buf[0] = 0; buf[1] = 0;
			/* prepare transfer */
			*ptr = buf, *size = 2;
			/* report success */
			rc = EOK;
		}
	/* endpoint is recipient */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_EP) {
		/* get endpoint number, and endpoint direction (7-bit, when set then we
		 * are talking about IN (tx) endpoint */
		uint8_t ep_num = s->index & 0x7F, ep_dir = s->index & 0x80;
		/* endpoint 0 can be addressed in address state, all others can be
		 * addressed in configured state */
		if ((ep_num == USB_EP0 && dev.state != USB_DEV_DEFAULT) ||
			 (ep_num > USB_EP0 && ep_num < usb_endpoints_num &&
					 dev.state == USB_DEV_CONFIGURED)) {
			/* get proper endpoint mask */
			uint8_t ep_halt = ep_dir ? dev.ep_halt_tx : dev.ep_halt_rx;
			/* prepare data in temporary buffer: one bit - halt status */
			buf[0] = ep_halt & (1 << ep_num) ? 1 : 0;
			buf[1] = 0;
			/* prepare transfer */
			*ptr = buf, *size = 2;
			/* report success */
			rc = EOK;
		}
	}

	/* report status */
	return rc;
}

/* process get interface */
static int USBCore_ProcessSetupGetInterface(usb_setup_t *s, void **ptr,
		size_t *size)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;
	/* interface identifier */
	uint8_t iface_num = s->index;

	/* check frame: those fields must have those values */
	if (s->value != 0 || s->length != 1) {
		return rc;
	}

	/* interface is recipient */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_IFACE) {
		/* need to be in configured state */
		if (dev.state == USB_DEV_CONFIGURED && iface_num < usb_interfaces_num) {
			/* prepare data */
			buf[0] = dev.alternate_settings[iface_num];
			/* prepare transfer */
			*ptr = buf, *size = 1;
			/* status is ok */
			rc = EOK;
            
		}
	}

	/* report status */
	return rc;
}

/* process setup frame with data stage */
static void USBCore_ProcessSetupData(usb_setup_t *s)
{
	/* status of frame processing */
	int rc = EFATAL;
	/* extract type */
	uint8_t type = s->request_type & USB_SETUP_REQTYPE_TYPE;
	/* event for class specific requests */
	usbcore_req_evarg_t arg = {s, EFATAL, ctl_ptr, ctl_size};

	/* resulting data pointer */
	void *ptr = 0;
	/* resulting data size */
	size_t size = 0;

	/* standard request */
	if (type == USB_SETUP_REQTYPE_TYPE_STANDARD) {
		/* process all 'get' frames. such frames have direction bit set. device
		 * shall respond with data after parsing frame */
		if (s->request_type & USB_SETUP_REQTYPE_DIR) {

			/* frame opcode is contained in 'request' field */
			switch (s->request) {
			/* get descriptor request. this may be addressed only to device
			 * itself this frame is used to obtain device, configuration,
			 * interface, endpoint and interface descriptor */
			case USB_SETUP_REQ_GET_DESCRIPTOR : {
				/* process frame */
				rc = USBCore_ProcessSetupGetDescriptor(s, &ptr, &size);
			} break;
			/* get configuration */
			case USB_SETUP_REQ_GET_CONFIGURATION : {
				/* process frame */
				rc = USBCore_ProcessSetupGetConfiguration(s, &ptr, &size);
			} break;
			/* get status */
			case USB_SETUP_REQ_GET_STATUS : {
				/* process frame */
				rc = USBCore_ProcessSetupGetStatus(s, &ptr, &size);
			} break;
			/* get interface */
			case USB_SETUP_REQ_GET_INTERFACE : {
				/* process frame */
				rc = USBCore_ProcessSetupGetInterface(s, &ptr, &size);
			} break;
			}
		}
	} 

    /* prepare event argument to call the others */
    arg.status = rc, arg.ptr = ptr, arg.size = size;
    /* call event */
    Ev_Notify(&usbcore_req_ev, &arg);
    /* copy status & other stuff */
    rc = arg.status, ptr = arg.ptr, size = arg.size;

	/* prepare data stage according to transfer direction and result code */
	/* data is to be sent from device to host */
	if (s->request_type & USB_SETUP_REQTYPE_DIR) {
		/* frame processed successfully? */
		if (rc == EOK) {
			/* start data in stage */
			USBCore_StartDataINStage(ptr, size);
		/* an error has occurred */
		} else {
			/* send STALL status */
			USBCore_AbortStage();
		}
	/* data will be sent from host to device */
	} else {
		/* frame processed successfully? */
		if (rc == EOK) {
			/* ctl data pointer is zeroed? we are just after the setup stage */
			if (ctl_ptr == 0) {
				/* initiate OUT transfer */
				USBCore_StartDataOUTStage(ptr, size);
			/* pointer is non-zero, data is already transfered (data out completed) */
			} else {
				/* send status in frame */
				USBCore_StartStatusINStage();
			}
		/* an error has occurred */
		} else {
			/* abort transaction */
			USBCore_AbortStage();
		}
	}
}

/* process setup set address */
static int USBCore_ProcessSetupSetAddress(usb_setup_t *s)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* check device state */
	if (dev.state == USB_DEV_CONFIGURED) {
		/* invalid state */
		return rc;
	}

	/* only device can be addressed */
	if (recipient != USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* invalid state */
		return rc;
	}

	/* store address. address update will be performed after status
	 * stage (IN transfer) */
	dev.address = s->value;
	/* change dev state */
	dev.state = dev.address == 0 ? USB_DEV_DEFAULT : USB_DEV_ADDRESS;

	/* apply new address */
	USB_SetDeviceAddress(dev.address);
	/* show debug */
	dprintf("set device address = %02x\n", dev.address);

	/* all is ok */
	rc = EOK;
	/* report status */
	return rc;
}

/* process setup set configuration */
static int USBCore_ProcessSetupSetConfiguration(usb_setup_t *s)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* check device state */
	if (dev.state == USB_DEV_DEFAULT) {
		/* invalid state */
		return rc;
	}
	/* addressed to device */
	if (recipient != USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* invalid state */
		return rc;
	}
	/* extract configuration */
	dev.configuration = s->value;
	/* change dev state */
	dev.state = dev.configuration == 0 ? USB_DEV_ADDRESS :
			USB_DEV_CONFIGURED;
	/* all is ok */
	rc = EOK;
	/* report status */
	return rc;
}

/* process setup clear feature */
static int USBCore_ProcessSetupClearFeature(usb_setup_t *s)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* extract feature */
	uint16_t feature = s->value;
	/* extract endpoint or iface number */
	uint16_t num = s->index;


	/* device is addressed */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* device num must be 0 */
		if (num == 0) {
			/* TODO: device remote wakeup: not supported */
			if (feature == USB_SETUP_FEATURE_DEV_REMOTE_WKUP) {
			/* TODO: device test mode: not supported */
			} else if (feature == USB_SETUP_FEATURE_TEST_MODE) {
			}
		}
	/* interface is addressed */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_IFACE) {
		/* usb spec 2.0 does not define any features for interface */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_EP) {
		/* endpoint number, endpoint direction */
		uint8_t ep_num = num & 0x7F, ep_dir = num & 0x80;
		/* endpoint halt */
		if (ep_num >= USB_EP1 && ep_num < usb_endpoints_num &&
			feature == USB_SETUP_FEATURE_ENDPOINT_HALT) {
			/* select mask according to ep_dir */
			if (ep_dir) {
				dev.ep_halt_tx &= ~(1 << ep_num);
			} else {
				dev.ep_halt_rx &= ~(1 << ep_num);
			}
			/* all went ok */
			rc = EOK;
		}
	}


	/* report status */
	return rc;
}

/* process setup set feature */
static int USBCore_ProcessSetupSetFeature(usb_setup_t *s)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* extract feature */
	uint16_t feature = s->value;
	/* extract endpoint or iface number */
	uint16_t num = s->index;

	/* length must be zero */
	if (s->length != 0) {
		return rc;
	}

	/* device is addressed */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_DEVICE) {
		/* device num must be 0 */
		if (num == 0) {
			/* TODO: device remote wakeup: not supported */
			if (feature == USB_SETUP_FEATURE_DEV_REMOTE_WKUP) {
			/* TODO: device test mode: not supported */
			} else if (feature == USB_SETUP_FEATURE_TEST_MODE) {
			}
		}
	/* interface is addressed */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_IFACE) {
		/* usb spec 2.0 does not define any features for interface */
	} else if (recipient == USB_SETUP_REQTYPE_RECIPIENT_EP) {
		/* endpoint number, endpoint direction */
		uint8_t ep_num = num & 0x7F, ep_dir = num & 0x80;
		/* endpoint halt */
		if (ep_num >= USB_EP1 && ep_num < usb_endpoints_num &&
			feature == USB_SETUP_FEATURE_ENDPOINT_HALT) {
			/* select mask according to ep_dir */
			if (ep_dir) {
				dev.ep_halt_tx |= (1 << ep_num);
			} else {
				dev.ep_halt_rx |= (1 << ep_num);
			}
			/* all went ok */
			rc = EOK;
		}
	}

	/* report status */
	return rc;
}

/* process set interface */
static int USBCore_ProcessSetupSetInterface(usb_setup_t *s)
{
	/* operation status */
	int rc = EFATAL;
	/* extract recipient */
	uint8_t recipient = s->request_type & USB_SETUP_REQTYPE_RECIPIENT;

	/* interface identifier */
	uint8_t iface_num = s->index;
	/* alternative setting */
	uint8_t iface_alt_num = s->value;

	/* check frame: those fields must have those values */
	if (s->length != 0) {
		return rc;
	}

	/* interface is recipient */
	if (recipient == USB_SETUP_REQTYPE_RECIPIENT_IFACE) {
		/* need to be in configured state */
		if (dev.state == USB_DEV_CONFIGURED && iface_num < usb_interfaces_num) {
			/* prepare data */
			dev.alternate_settings[iface_num] = iface_alt_num;
			/* status is ok */
			rc = EOK;
		}
	}

	/* report status */
	return rc;
}

/* process setup frame with no data stage */
static void USBCore_ProcessSetupNoData(usb_setup_t *s)
{
	/* status of frame processing */
	int rc = EFATAL;
	/* extract type */
	uint8_t type = s->request_type & USB_SETUP_REQTYPE_TYPE;
    /* process frame */
    usbcore_req_evarg_t arg = {s, rc, 0, 0};

	/* standard request */
	if (type == USB_SETUP_REQTYPE_TYPE_STANDARD) {
		/* process all 'set' frames. such frames have direction bit cleared */
		if (!(s->request_type & USB_SETUP_REQTYPE_DIR)) {
			/* frame opcode is contained in 'request' field */
			switch (s->request) {
			/* set device address */
			case USB_SETUP_REQ_SET_ADDRESS : {
				/* process frame */
				rc = USBCore_ProcessSetupSetAddress(s);
			} break;
			/* set configuration */
			case USB_SETUP_REQ_SET_CONFIGURATION : {
				/* process frame */
				rc = USBCore_ProcessSetupSetConfiguration(s);
			} break;
			/* clear feature */
			case USB_SETUP_REQ_CLEAR_FEATURE : {
				/* process frame */
				rc = USBCore_ProcessSetupClearFeature(s);
			} break;
			/* set feature */
			case USB_SETUP_REQ_SET_FEATURE : {
				/* process frame */
				rc = USBCore_ProcessSetupSetFeature(s);
			} break;
			/* set interface */
			case USB_SETUP_REQ_SET_INTERFACE : {
				rc = USBCore_ProcessSetupSetInterface(s);
			} break;
			}
		}
	} 

    /* prepare event argument to be passed to other layers */
    arg.status = rc;
    /* call event */
    Ev_Notify(&usbcore_req_ev, &arg);
    /* copy status */
    rc = arg.status;

	/* set status */
	if (rc == EOK) {
		/* respond with status in frame */
		USBCore_StartStatusINStage();
	} else {
		/* stall endpoint, restart reception */
		USBCore_AbortStage();
	}
}

/* process setup frame */
static void USBCore_ProcessSetup(usb_setup_t *s)
{
	/* some debug */
	dprintf("type = 0x%x, req = 0x%x, val = 0x%x, idx = 0x%x, len = 0x%x\n",
			s->request_type, s->request, s->value, s->index,
			s->length);

	/* no data is to be transmitted in any way */
	if (s->length == 0) {
		/* process setup frame with no data stage */
		USBCore_ProcessSetupNoData(s);
	/* data stage is about to take place */
	} else {
		/* process setup frame with data stage */
		USBCore_ProcessSetupData(s);
	}
}

/* setup frame received */
static int USBCore_SetupCallback(void *arg)
{
	/* extract size */
	size_t size = *(size_t *)arg;
	/* according to specification only the last packet shall be processed, so get
	 * the last frame index. this callback may be called from data out completition
	 * (size will be 0 since no new setup frame is received and we ought to use the
	 * previous one) */
	if (size)
		ctl_index = (size / sizeof(usb_setup_t)) - 1;

	/* process frame */
	USBCore_ProcessSetup(&ctl_setup[ctl_index]);
    /* report status */
    return EOK;
}

/* usb reset callback */
static int USBCore_ResetCallback(void *arg)
{
	/* get frame size from device descriptor */
	size_t max_size = USB_CTRLEP_SIZE;

	/* prepare reception fifo */
	USB_SetRxFifoSize(USB_RX_FIFO_SIZE / 4);
	/* prepare transmission fifo */
	USB_SetTxFifoSize(USB_EP0, USB_CTRLEP_SIZE / 4);

	/* reset device state */
	memset(&dev, 0, sizeof(dev));

	/* configure out endpoint for receiving status frames and data out frames */
	USB_ConfigureOUTEndpoint(USB_EP0, USB_EPTYPE_CTL, max_size);
	/* configure in endpoint for receiving data in frames */
	USB_ConfigureINEndpoint(USB_EP0, USB_EPTYPE_CTL, max_size);

	/* release semaphore */
	USBCore_StartSETUPStage();

    /* report status */
    return EOK;
}

/* initialize usb core */
int USBCore_Init(void)
{
	/* listen to usb reset events */
	Ev_RegisterCallback(&usb_rst_ev, USBCore_ResetCallback);

	/* report status */
	return EOK;
}

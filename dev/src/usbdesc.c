/*
 * usbhid.c
 *
 *	Created on: 16-02-2014
 *	Author: Tomek
 */

#include <stdint.h>

#include "config.h"
#include "err.h"
#include "dev/usbdesc.h"
#include "util/elems.h"

/* USB Configuration Descriptor */
static const uint8_t usb_config0_descriptor[143] = {
    /* Configuration Descriptor */
    0x09,   		        /* bLength: Configuration Descriptor size */
    0x02,  			        /* bDescriptorType: Configuration */
    0x8F, 0x00, 	        /* wTotalLength: no of returned bytes */
    0x02,   		        /* bNumInterfaces: 4 interfaces TODO: */
    0x01,   		        /* bConfigurationValue: Configuration value */
    0x00,   		        /* iConfiguration: Index of string descriptor describing
                                * the configuration */
    0xC0,   		        /* bmAttributes: self powered */
    0x32,   		        /* MaxPower 100 mA */

    /* INTERFACE 0: AudioControl */
    /* USB Microphone Standard interface descriptor */
    0x09,      				/* bLength */
    0x04,        			/* bDescriptorType: interface desc. */
    0x00,                   /* bInterfaceNumber */
    0x00,                   /* bAlternateSetting */
    0x00,                   /* bNumEndpoints */
    0x01,               	/* bInterfaceClass */
    0x01,          			/* bInterfaceSubClass */
    0x00,             		/* bInterfaceProtocol */
    0x00,                   /* iInterface */

    /* USB Microphone Class-specific AudioControl Interface Descriptor */
    0x09,   				/* bLength */
    0x24,      				/* bDescriptorType: audio descriptor type */
    0x01,                 	/* bDescriptorSubtype: audio control header */
    0x00, 0x01,        		/* bcdADC */
    0x1E, 0x00,             /* wTotalLength */
    0x01,                   /* bInCollection */
    0x01,                   /* baInterfaceNr TODO: */

    /* USB Microphone Input Terminal Descriptor */
    0x0C,       			/* bLength */
    0x24,      				/* bDescriptorType: audio descriptor type */
    0x02,         			/* bDescriptorSubtype: control input terminal */
    0x01,                   /* bTerminalID */
    0x03, 0x06,             /* wTerminal: microphone */
    0x00,                   /* bAssocTerminal */
    0x02,                   /* bNrChannels: 2 (stereo) */
    0x03, 0x00,             /* wChannelConfig: left front, right front */
    0x00,                   /* iChannelNames */
    0x04,                   /* iTerminal */

    /* USB Microphone Output Terminal Descriptor */
    0x09,                   /* bLength */
    0x24,                   /* bDescriptorType: audio descriptor type */
    0x03,                   /* bDescriptorSubtype: control output terminal */
    0x02,                   /* bTerminalID */
    0x01, 0x01,             /* wTerminal: USB Streaming. */
    0x00,                   /* bAssocTerminal: none */
    0x01,                   /* bSourceID: from input terminal */
    0x00,                   /* iTerminal */


    /* INTERFACE 1: AudioStreaming ALT 0 (Disabled Mode) */
    /* USB Microphone Standard AS Interface Descriptor 
        * Zero-Bandwidth interface */
    0x09,                   /* bLength */
    0x04,                   /* bDescriptorType: interface desc. */
    0x01,                   /* bInterfaceNumber */
    0x00,                   /* bAlternateSetting: 0  */
    0x00,                   /* bNumEndpoints */
    0x01,                   /* bInterfaceClass : audio */
    0x02,                   /* bInterfaceSubclass: audio streaming */
    0x00,                   /* bInterfaceProtocol */
    0x00,                   /* iInterface */

    /* INTERFACE 1: AudioStreaming ALT 1 (Mono Mode) */
    /* USB Microphone Standard AS Interface Descriptor */
    0x09,                   /* bLength */
    0x04,                   /* bDescriptorType: interface desc. */
    0x01,                   /* bInterfaceNumber */
    0x01,                   /* bAlternateSetting: 1 */
    0x01,                   /* bNumEndpoints:  1 endpoint */
    0x01,                   /* bInterfaceClass : audio */
    0x02,                   /* bInterfaceSubclass: audio streaming */
    0x00,                   /* bInterfaceProtocol */
    0x00,                   /* iInterface */

    /*  USB Microphone Class-specific AS General Interface Descriptor */
    0x07,                   /* bLength */
    0x24,                   /* bDescriptorType: class spec interface desc. */
    0x01,                   /* bDescriptorSubtype: general descriptor */
    0x02,                   /* bTerminalLink: output terminal */
    0x00,                   /* bDelay:  Interface delay. */
    0x01, 0x00,             /* wFormatTag: PCM Format */

    /*  USB Microphone Type I Format Type Descriptor */
    0x0B,                   /* bLength */
    0x24,                   /* bDescriptorType: class spec interface desc. */
    0x02,                   /* bDescriptorSubtype: format type */
    0x01,                   /* bFormatType */
    0x01,                   /* bNrChannels: 1 */
    0x02,                   /* bSubFrameSize: Two bytes per audio subframe. */
    0x10,                   /* bBitResolution 16 bits per sample. */
    0x01,                   /* bSamFreqType: One frequency supported. */
    /* sampling frequency */
    (16000 & 0xFF), ((16000 >> 8) & 0xFF), ((16000 >> 16) & 0xFF), 

    /* ENDPOINT 1 IN */
    /*  USB Microphone Standard Endpoint Descriptor */
    0x09,                   /* bLength */
    0x05,                   /* bDescriptorType: endpoint desc. */
    0x81,                   /* bEndpointAddress: IN1 */
    0x0D,                   /* bmAttributes: Isochronous-synchronous */
    /* wMaxPacketSize: sps * 2 bytes / 1000 */
    (32 & 0xFF), ((32 >> 8) & 0xFF),
    0x01,                   /* bInterval: One packet per frame. */
    0x00,                   /* bRefresh */
    0x00,                   /* bSynchAddress */

    /* USB Microphone Class-specific Isoc. Audio Data Endpoint Descriptor */
    0x07,                   /* bLength */
    0x25,                   /* bDescriptorType: class spec. endpoint desc. */
    0x01,                   /* bDescriptorSubtype: general */
    0x00,                   /* bmAttributes: nothing */
    0x00,                   /* bLockDelayUnits */
    0x00, 0x00,             /* wLockDelay */


    /* INTERFACE 1: AudioStreaming ALT 2 (Stereo Mode) */
    /* USB Microphone Standard AS Interface Descriptor */
    0x09,                   /* bLength */
    0x04,                   /* bDescriptorType: interface desc. */
    0x01,                   /* bInterfaceNumber */
    0x02,                   /* bAlternateSetting: 2 */
    0x01,                   /* bNumEndpoints:  1 endpoint */
    0x01,                   /* bInterfaceClass : audio */
    0x02,                   /* bInterfaceSubclass: audio streaming */
    0x00,                   /* bInterfaceProtocol */
    0x00,                   /* iInterface */

    /*  USB Microphone Class-specific AS General Interface Descriptor */
    0x07,                   /* bLength */
    0x24,                   /* bDescriptorType: class spec interface desc. */
    0x01,                   /* bDescriptorSubtype: general descriptor */
    0x02,                   /* bTerminalLink: output terminal */
    0x00,                   /* bDelay:  Interface delay. */
    0x01, 0x00,             /* wFormatTag: PCM Format */

    /*  USB Microphone Type I Format Type Descriptor */
    0x0B,                   /* bLength */
    0x24,                   /* bDescriptorType: class spec interface desc. */
    0x02,                   /* bDescriptorSubtype: format type */
    0x01,                   /* bFormatType */
    0x02,                   /* bNrChannels: 2 */
    0x02,                   /* bSubFrameSize: Two bytes per audio subframe. */
    0x10,                   /* bBitResolution 16 bits per sample. */
    0x01,                   /* bSamFreqType: One frequency supported. */
    /* sampling frequency */
    (16000 & 0xFF), ((16000 >> 8) & 0xFF), ((16000 >> 16) & 0xFF),

    /* ENDPOINT 1 IN */
    /*  USB Microphone Standard Endpoint Descriptor */
    0x09,                   /* bLength */
    0x05,                   /* bDescriptorType: endpoint desc. */
    0x81,                   /* bEndpointAddress: IN1 */
    0x0D,                   /* bmAttributes: Isochronous-synchronous */
    /* wMaxPacketSize: sps * 2 bytes / 1000 */
    (64 & 0xFF), ((64 >> 8) & 0xFF),
    0x01,                   /* bInterval: One packet per frame. */
    0x00,                   /* bRefresh */
    0x00,                   /* bSynchAddress */

    /* USB Microphone Class-specific Isoc. Audio Data Endpoint Descriptor */
    0x07,                   /* bLength */
    0x25,                   /* bDescriptorType: class spec. endpoint desc. */
    0x01,                   /* bDescriptorSubtype: general */
    0x00,                   /* bmAttributes: nothing */
    0x00,                   /* bLockDelayUnits */
    0x00, 0x00,             /* wLockDelay */
};

/* language ID */
static const uint8_t usb_string0_descriptor[] = {
    0x04,					/* bLength */
    0x03,					/* bDescriptorType */
    0x09, 0x04,				/* LangID = 0x0409: U.S. English */
};

/* vendor string */
static const uint8_t usb_string1_descriptor[] = {
    0x1E,					/* bLength */
    0x03,					/* bDescriptorType */
    'M', 0, 'i', 0,
    'g', 0, 'h', 0,
    't', 0, 'y', 0,
    ' ', 0, 'D', 0,
    'e', 0, 'v', 0,
    'i', 0, 'c', 0,
    'e', 0, 's', 0,
};

/* product string */
static const uint8_t usb_string2_descriptor[] = {
    0x1E,					/* bLength */
    0x03,					/* bDescriptorType */
    'M', 0, 'i', 0,
    'g', 0, 'h', 0,
    't', 0, 'y', 0,
    ' ', 0, 'D', 0,
    'e', 0, 'v', 0,
    'i', 0, 'c', 0,
    'e', 0, 's', 0,
};

/* serial number string */
static uint8_t usb_string3_descriptor[2 + USB_SN_SIZE] = {
    2 + USB_SN_SIZE,				                /* bLength */
    0x03,											/* bDescriptorType */
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0,
};

/* function 1 string */
static const uint8_t usb_string4_descriptor[] = {
		0x10,					/* bLength */
		0x03,					/* bDescriptorType */
		'I', 0, 'Q', 0,
        ' ', 0, 'D', 0,
        'a', 0, 't', 0,
        'a', 0,
};

/* usb standard device descriptor */
const uint8_t usb_device_descriptor[] = {
    0x12,					/* bLength */
    0x01,					/* bDescriptorType */
    0x00, 0x02, 			/* bcdUSB */
    0x00,					/* bDeviceClass: Composite */
    0x00,					/* bDeviceSubClass: Composite */
    0x00,					/* bDeviceProtocol */
    USB_CTRLEP_SIZE,		/* bMaxPacketSize0 */
    0x83, 0x04,				/* idVendor (0x0483) */
    0x43, 0x57,				/* idProduct = (0x5740) TODO: */
    0x00, 0x02,				/* bcdDevice rel. 2.00 */
    0x01,					/* Index of string descriptor describing
                                * manufacturer */
    0x02,					/* Index of string descriptor describing
                                * product */
    0x03,					/* Index of string descriptor describing the
                                * device serial number */
    0x01					/* bNumConfigurations */
};

/* qualifier descriptor */
const uint8_t usb_qualifier_descriptor[] = {
    0x0A,					/* bLength: Configuration Descriptor size */
    0x06,					/* bDescriptorType: Qualifier */
    0x00, 0x02,				/* bcdUSB: USB Specification Release Number */
    0xef,					/* bDeviceClass */
    0x02,					/* bDeviceSubClass */
    0x01,					/* bDeviceProtocol */
    USB_CTRLEP_SIZE,		/* bMaxPacketSize40 */
    0x01,					/* bNumConfigurations */
    0x00					/* bReserved */
};

/* array of string descriptors */
const uint8_t * usb_config_descriptors[] = {
    usb_config0_descriptor,
};

/* array of string descriptors */
const uint8_t * usb_string_descriptors[] = {
    usb_string0_descriptor,
    usb_string1_descriptor,
    usb_string2_descriptor,
    usb_string3_descriptor,
    usb_string4_descriptor,
};

/* number of descriptors */
/* configuration descriptors number */
const int usb_config_descriptors_num = elems(usb_config_descriptors);
/* string descriptors number */
const int usb_string_descriptors_num = elems(usb_string_descriptors);
/* number of interfaces */
const int usb_interfaces_num = 2;
/* number of used endpoints */
const int usb_endpoints_num = 1;

/* Initialize all dynamically generated descriptors */
int USBDesc_Init(void)
{
/* need to build up a true serial number? */
#if USB_USE_TRUE_SN
	/* serial number string */
	char sn[UNIQUE_SNSTRING_SIZE];

	/* get string */
	if (Unique_GetUIDString(sn, sizeof(sn)) == EOK) {
		/* copy characters to the string descriptor placeholder */
		for (char *p = sn, *dst = (char *)&usb_string3_descriptor[2]; 
            *p; p++, dst += 2) {
			*dst = *p;
        }
	}
#endif
	/* report status */
	return EOK;
}


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
static const uint8_t usb_config0_descriptor[0x8D] = {
        /* Configuration Descriptor */
		0x09,   		/* bLength: Configuration Descriptor size */
		0x02,  			/* bDescriptorType: Configuration */
		0x8D, 0x00, 	/* wTotalLength: no of returned bytes */
		0x04,   		/* bNumInterfaces: 4 interfaces */
		0x01,   		/* bConfigurationValue: Configuration value */
		0x00,   		/* iConfiguration: Index of string descriptor describing
						   the configuration */
		0xC0,   		/* bmAttributes: self powered */
		0x32,   		/* MaxPower 100 mA */


		/* FIRST FUNCTION */

		/* Interface Association Descriptor */
		0x08,			/* bLength: Interface Descriptor size */
		0x0B,			/* bDescriptorType: IAD */
		0x00,			/* bFirstInterface */
		0x02,			/* bInterfaceCount */
		0x02,			/* bFunctionClass: CDC */
		0x02,			/* bFunctionSubClass */
		0x01,			/* bFunctionProtocol */
		0x00,			/* iFunction */

		/* Interface Descriptor */
		0x09,   		/* bLength: Interface Descriptor size */
		0x04, 	 		/* bDescriptorType: Interface descriptor type  */
		0x00,   		/* bInterfaceNumber: Number of Interface */
		0x00,   		/* bAlternateSetting: Alternate setting */
		0x01,   		/* bNumEndpoints: One endpoints used */
		0x02,   		/* bInterfaceClass: Communication Interface Class */
		0x02,   		/* bInterfaceSubClass: Abstract Control Model */
		0x01,   		/* bInterfaceProtocol: Common AT commands */
		0x00,   		/* iInterface: */

		/* Header Functional Descriptor */
		0x05,			/* bLength: Endpoint Descriptor size */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x00,			/* bDescriptorSubtype: Header Func Desc */
		0x10, 0x01,		/* bcdCDC: spec release number */

		/* Union Functional Descriptor */
		0x05,			/* bFunctionLength */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x06,			/* bDescriptorSubtype: Union func desc */
		0x00,			/* bMasterInterface: Communication class interface */
		0x01,			/* bSlaveInterface0: Data Class Interface */

		/* Call Management Functional Descriptor */
		0x05,			/* bFunctionLength */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x01,			/* bDescriptorSubtype: Call Management Func Desc */
		0x00,			/* bmCapabilities: D0+D1 */
		0x01,			/* bDataInterface: 1 */

		/* ACM Functional Descriptor */
		0x04,			/* bFunctionLength */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x02,			/* bDescriptorSubtype: Abstract Control Management
						   desc */
		0x02,			/* bmCapabilities */

		/* Endpoint 1 Descriptor */
		0x07,			/* bLength: Endpoint Descriptor size */
		0x05,			/* bDescriptorType: Endpoint */
		0x81,			/* bEndpointAddress: (IN1) */
		0x03,			/* bmAttributes: Interrupt */
		/* wMaxPacketSize: */
        USB_VCP_INT_SIZE & 0xff, USB_VCP_INT_SIZE >> 8,
		0xFF,			/* bInterval: */

		/* Data class interface descriptor */
		0x09,			/* bLength: Endpoint Descriptor size */
		0x04,			/* bDescriptorType: */
		0x01,			/* bInterfaceNumber: Number of Interface */
		0x00,			/* bAlternateSetting: Alternate setting */
		0x02,			/* bNumEndpoints: Two endpoints used */
		0x0A,			/* bInterfaceClass: Data Interface Class */
		0x00,			/* bInterfaceSubClass: */
		0x00,			/* bInterfaceProtocol: */
		0x00,			/* iInterface: */

		/* Endpoint 2 IN Descriptor */
		0x07,			/* bLength: Endpoint Descriptor size */
		0x05,			/* bDescriptorType: Endpoint */
		0x82,			/* bEndpointAddress: (IN2) */
		0x02,			/* bmAttributes: Bulk */
        /* wMaxPacketSize: */
        USB_VCP_TX_SIZE & 0xff, USB_VCP_TX_SIZE >> 8,
		0x00,			/* bInterval: ignore for Bulk transfer */

		/* Endpoint 2 OUT Descriptor */
		0x07,			/* bLength: Endpoint Descriptor size */
		0x05,			/* bDescriptorType: Endpoint */
		0x02,			/* bEndpointAddress: (OUT3) */
		0x02,			/* bmAttributes: Bulk */
        /* wMaxPacketSize: */
        USB_VCP_RX_SIZE & 0xff, USB_VCP_RX_SIZE >> 8,
		0x00,			/* bInterval: ignore for Bulk transfer */


		/* SECOND FUNCTION */

		/* Interface Association Descriptor */
		0x08,			/* bLength: Interface Descriptor size */
		0x0B,			/* bDescriptorType: IAD */
		0x02,			/* bFirstInterface */
		0x02,			/* bInterfaceCount */
		0x02,			/* bFunctionClass: CDC */
		0x02,			/* bFunctionSubClass */
		0x01,			/* bFunctionProtocol */
		0x00,			/* iFunction */

		/* Interface Descriptor */
		0x09,   		/* bLength: Interface Descriptor size */
		0x04, 	 		/* bDescriptorType: Interface descriptor type  */
		0x02,   		/* bInterfaceNumber: Number of Interface */
		0x00,   		/* bAlternateSetting: Alternate setting */
		0x01,   		/* bNumEndpoints: One endpoint used */
		0x02,   		/* bInterfaceClass: Communication Interface Class */
		0x02,   		/* bInterfaceSubClass: Abstract Control Model */
		0x01,   		/* bInterfaceProtocol: Common AT commands */
		0x00,   		/* iInterface: */

		/* Header Functional Descriptor */
		0x05,			/* bLength: Endpoint Descriptor size */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x00,			/* bDescriptorSubtype: Header Func Desc */
		0x10, 0x01,		/* bcdCDC: spec release number */

		/* Union Functional Descriptor */
		0x05,			/* bFunctionLength */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x06,			/* bDescriptorSubtype: Union func desc */
		0x02,			/* bMasterInterface: Communication class interface */
		0x03,			/* bSlaveInterface0: Data Class Interface */

		/* Call Management Functional Descriptor */
		0x05,			/* bFunctionLength */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x01,			/* bDescriptorSubtype: Call Management Func Desc */
		0x00,			/* bmCapabilities: D0+D1 */
		0x03,			/* bDataInterface: 3 */

		/* ACM Functional Descriptor */
		0x04,			/* bFunctionLength */
		0x24,			/* bDescriptorType: CS_INTERFACE */
		0x02,			/* bDescriptorSubtype: Abstract Control Management
						   desc */
		0x02,			/* bmCapabilities */

		/* Endpoint 3 IN Descriptor */
		0x07,			/* bLength: Endpoint Descriptor size */
		0x05,			/* bDescriptorType: Endpoint */
		0x83,			/* bEndpointAddress: (IN3) */
		0x03,			/* bmAttributes: Interrupt */
		/* wMaxPacketSize: */
        USB_VCP_INT_SIZE & 0xff, USB_VCP_INT_SIZE >> 8,
		0xFF,			/* bInterval: */

		/* Data class interface descriptor */
		0x09,			/* bLength: Endpoint Descriptor size */
		0x04,			/* bDescriptorType: */
		0x03,			/* bInterfaceNumber: Number of Interface */
		0x00,			/* bAlternateSetting: Alternate setting */
		0x02,			/* bNumEndpoints: Two endpoints used */
		0x0A,			/* bInterfaceClass: Data Interface Class */
		0x00,			/* bInterfaceSubClass: */
		0x00,			/* bInterfaceProtocol: */
		0x00,			/* iInterface: */

		/* Endpoint 4 IN Descriptor */
		0x07,			/* bLength: Endpoint Descriptor size */
		0x05,			/* bDescriptorType: Endpoint */
		0x84,			/* bEndpointAddress: (IN4) */
		0x02,			/* bmAttributes: Bulk */
        /* wMaxPacketSize: */
        USB_VCP_TX_SIZE & 0xff, USB_VCP_TX_SIZE >> 8,
		0x00,			/* bInterval: ignore for Bulk transfer */

		/* Endpoint 4 OUT Descriptor */
		0x07,			/* bLength: Endpoint Descriptor size */
		0x05,			/* bDescriptorType: Endpoint */
		0x04,			/* bEndpointAddress: (OUT4) */
		0x02,			/* bmAttributes: Bulk */
        /* wMaxPacketSize: */
        USB_VCP_RX_SIZE & 0xff, USB_VCP_RX_SIZE >> 8,
		0x00,			/* bInterval: ignore for Bulk transfer */
};

/* language ID */
static const uint8_t usb_string0_descriptor[] = {
    0x04,					/* bLength */
    0x03,					/* bDescriptorType */
    0x09, 0x04,				/* LangID = 0x0409: U.S. English */
};

/* vendor string */
static const uint8_t usb_string1_descriptor[] = {
    0x12,					/* bLength */
    0x03,					/* bDescriptorType */
    'S', 0, 't', 0,
    'e', 0, 't', 0,
    'h', 0, 'o', 0,
    'M', 0, 'e', 0,
};

/* product string */
static const uint8_t usb_string2_descriptor[] = {
    0x12,					/* bLength */
    0x03,					/* bDescriptorType */
    'S', 0, 't', 0,
    'e', 0, 't', 0,
    'h', 0, 'o', 0,
    'M', 0, 'e', 0,
};

/* serial number string */
static uint8_t usb_string3_descriptor[2 + USB_SN_SIZE] = {
    2 + USB_SN_SIZE,				                /* bLength */
    0x03,											/* bDescriptorType */
    '2', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '0', 0,
};

/* function 1 string */
static const uint8_t usb_string4_descritptor[] = {
		0x0C,					/* bLength */
		0x03,					/* bDescriptorType */
		'C', 0, 'O', 0,
		'M', 0, ' ', 0,
		'A', 0,
};

/* function 2 string */
static const uint8_t usb_string5_descritptor[] = {
		0x0C,					/* bLength */
		0x03,					/* bDescriptorType */
		'C', 0, 'O', 0,
		'M', 0, ' ', 0,
		'B', 0,
};

/* usb standard device descriptor */
const uint8_t usb_device_descriptor[] = {
    0x12,					/* bLength */
    0x01,					/* bDescriptorType */
    0x00, 0x02, 			/* bcdUSB */
    0xEF,					/* bDeviceClass: Composite */
    0x02,					/* bDeviceSubClass: Composite */
    0x01,					/* bDeviceProtocol */
    USB_CTRLEP_SIZE,		/* bMaxPacketSize0 */
    0x83, 0x04,				/* idVendor (0x0483) */
    0x40, 0x57,				/* idProduct = (0x5740) */
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
    usb_string4_descritptor,
    usb_string5_descritptor,
};

/* number of descriptors */
/* configuration descriptors number */
const int usb_config_descriptors_num = elems(usb_config_descriptors);
/* string descriptors number */
const int usb_string_descriptors_num = elems(usb_string_descriptors);
/* number of interfaces */
const int usb_interfaces_num = 4;
/* number of used endpoints */
const int usb_endpoints_num = 6;

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


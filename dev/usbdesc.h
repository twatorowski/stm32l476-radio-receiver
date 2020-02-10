/*
 * usbdesc.h
 *
 *	Created on: 16-02-2014
 *		Author: Tomek
 */

#ifndef DEV_USBDESC_H_
#define DEV_USBDESC_H_

#include <stdint.h>

/* device descriptor */
extern const uint8_t device_descriptor[];
/* configuration descriptors */
extern const uint8_t *config_descriptors[], config_descriptors_num;
/* string descriptors */
extern const uint8_t *string_descriptors[], string_descriptors_num;

/* device qualifier descriptor */
extern const uint8_t qualifier_descriptor[];

/* class specific descriptors */
extern const uint8_t hid_descriptor[];

/* number of interfaces */
extern const uint8_t interfaces_num;
/* number of used endpoints */
extern const uint8_t endpoints_num;


/* Initialize all dynamically generated descriptors */
int USBDesc_Init(void);

#endif /* USBDESC_H_ */

/**
 * @file usbdesc.h
 * 
 * @date 2020-02-10
 * @author twatorowski 
 * 
 * @brief USB Descriptors
 */

#ifndef DEV_USBDESC_H_
#define DEV_USBDESC_H_

#include <stdint.h>

/** @brief device descriptor */
extern const uint8_t usb_device_descriptor[];
/** @brief configuration descriptors */
extern const uint8_t *usb_config_descriptors[];
/** @brief number of configuration descriptors */
extern const int usb_config_descriptors_num;
/** @brief string descriptors */
extern const uint8_t *usb_string_descriptors[];
/** @brief number string descriptors */
extern const int usb_string_descriptors_num;

/** @brief device qualifier descriptor */
extern const uint8_t usb_qualifier_descriptor[];

/** @brief number of interfaces */
extern const int usb_interfaces_num;
/** @brief number of used endpoints */
extern const int usb_endpoints_num;

/**
 * @brief Initialize all dynamically generated descriptors
 * 
 * @return int status (@ref ERR_ERROR_CODES) 
 */
int USBDesc_Init(void);

#endif /* USBDESC_H_ */

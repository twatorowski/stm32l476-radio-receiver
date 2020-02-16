/**
 * @file usb.h
 * 
 * @date 2019-12-06
 * @author twatorowski 
 * 
 * @brief USB Device driver
 */

#ifndef DEV_USB_H_
#define DEV_USB_H_

#include <stdint.h>
#include <stddef.h>

#include "sys/ev.h"

/** @name enpoint numbers */
/** @{ */
/* enpoint 0 */
#define USB_EP0								0x00
/* enpoint 1 */
#define USB_EP1								0x01
/* enpoint 2 */
#define USB_EP2								0x02
/* enpoint 3 */
#define USB_EP3								0x03
/* enpoint 4 */
#define USB_EP4								0x04
/* enpoint 5 */
#define USB_EP5								0x05
/* enpoint 6 */
#define USB_EP6								0x06
/* enpoint 7 */
#define USB_EP7								0x07
/** @} */

/** @name endpoint types */
/** @{ */
/** @brief control endpoint */
#define USB_EPTYPE_CTL						0x00
/** @brief isochronous endpoint */
#define USB_EPTYPE_ISO						0x01
/** @brief bulk endpoint */
#define USB_EPTYPE_BULK						0x02
/** @brief interrupt endpoint */
#define USB_EPTYPE_INT						0x03
/** @} */

/** @name event types */
/** @{ */
/** @brief bus reset */
#define USB_EVARG_TYPE_RESET				0x00
/** @brief incomplete isochronous transfer occured  */
#define USB_EVARG_TYPE_ISOINC				0x01
/** @} */

/** @brief callback argument for StartXXXTransfer functions */
typedef struct usb_cbarg {
    /**< error code */
    int error;
    /**< transfer size */
    size_t size;
} usb_cbarg_t;

/** @brief event argument for usb_ev */
typedef struct usb_evarg {
    /**< event type */
    int type;
} usb_evarg_t;

/* usb events */
extern ev_t usb_ev;


/** @brief usb interrupt handler */
void USB_OTGFSIsr(void);

/**
 * @brief Initialize the USB Device module
 * 
 * @return int status (@ref ERR_ERROR_CODES) 
 */
int USB_Init(void);

/**
 * @brief Returns the microphone initialization status
 * 
 * @return int status (@ref ERR_ERROR_CODES) 
 */
int USB_GetInitStatus(void);

/**
 * @brief Attach/Remove the USB device. To be called when VUSB is 
 * applied/removed
 * 
 * @param enable 1 - enable USB Device, 0 - disable USB Device
 * 
 * @return int status (@ref ERR_ERROR_CODES) 
 */
int USB_Connect(int enable);

/**
 * @brief Sets the RX Fifo size which determines the maximal size of the frames 
 * being received. This shall be configured according to implemented device 
 * class requirements. Keep in mind that the hardware uses one RX fifo that is 
 * shared along all OUT endpoints so it should be set to handle biggest transfer 
 * possible.
 * 
 * @param size size expressed in 32-bit words.
 */
void USB_SetRxFifoSize(uint32_t size);

/**
 * @brief Sets the TX Fifo size. Every IN endpoint has it's own tx fifo (nothing 
 * is shared like in RX Fifo case).
 * 
 * @param ep_num endpoint number
 * @param size fifo size expressed in 32-bit words
 */
void USB_SetTxFifoSize(int ep_num, uint32_t size);

/**
 * @brief Flushes the TX Fifo associated with given endpoint.
 * 
 * @param ep_num endpoint number
 */
void USB_FlushTxFifo(int ep_num);

/**
 * @brief Start the IN transfer (from device to host). Send data pointed by 
 * 'ptr' of size 'size'. After the work is done callback 'cb' will be called
 * 
 * @param ep_num endpoint number
 * @param ptr data source pointer
 * @param size size of data 
 * @param cb callback to be called after the transfer is done
 * 
 * @return usb_cbarg_t * null as the CB_SYNC operation is not permitted
 */
usb_cbarg_t *  USB_StartINTransfer(int ep_num, void *ptr, size_t size, 
    cb_t cb);

/**
 * @brief Start OUT transfer (from host to the device) Data that host whishes 
 * to provide the device with will be stored under the 'ptr'. Max accepted data 
 * size is 'size'. After the data is received callback will be called
 * 
 * @param ep_num endpoint number
 * @param ptr pointer to where to store the data
 * @param size maximal acceptable size of data
 * @param cb callback to be called after the transfer is done
 * 
 * @return usb_cbarg_t * null as the CB_SYNC operation is not permitted
 */
usb_cbarg_t *  USB_StartOUTTransfer(int ep_num, void *ptr, size_t size, 
    cb_t cb);

/**
 * @brief Start SETUP transfer (from host to device). The size of buffer 
 * provided must be a multiple of 8. Use 24 as the host is allowed to send 3 
 * back-to-back setup packets
 * 
 * @param ep_num endpoint number
 * @param ptr pointer to where to store the data
 * @param size data size (must be a multiple of 8)
 * @param cb callback to be called after the transfer is done
 * 
 * @return usb_cbarg_t * null as the CB_SYNC operation is not permitted
 */
usb_cbarg_t *  USB_StartSETUPTransfer(int ep_num, void *ptr, size_t size, 
    cb_t cb);

/**
 * @brief Configure IN endpoint. To be called after USB reset event to 
 * re-initialize the endpoint.
 * 
 * @param ep_num endpoint number
 * @param type type of endpoint (see USB_EPTYPE_ defines)
 * @param mp_size maximal packet size
 */
void USB_ConfigureINEndpoint(int ep_num, uint32_t type, size_t mp_size);

/**
 * @brief Configure OUT endpoint. To be called after USB reset event to 
 * re-initialize the endpoint.
 * 
 * @param ep_num endpoint number
 * @param type type of endpoint (see USB_EPTYPE_ defines)
 * @param mp_size maximal packet size
 */
void USB_ConfigureOUTEndpoint(int ep_num, uint32_t type, size_t mp_size);

/**
 * @brief Set the device addres. To be called during enumeration when host 
 * assigns the address to the device.
 * 
 * @param addr address value
 */
void USB_SetDeviceAddress(uint8_t addr);

/**
 * @brief Stall OUT endpoint. Halt all the transfers.
 * 
 * @param ep_num endpoint number
 */
void USB_StallOUTEndpoint(int ep_num);

/**
 * @brief Stall IN endpoint. Halt all the transfers.
 * 
 * @param ep_num ednpoint number
 */
void USB_StallINEndpoint(int ep_num);

/**
 * @brief Disable IN endpoint.
 * 
 * @param ep_num endpoint number
 */
void USB_DisableINEndpoint(int ep_num);

/**
 * @brief Disable OUT endpoint.
 * 
 * @param ep_num endpoint number
 */
void USB_DisableOUTEndpoint(int ep_num);



#endif /* DEV_USB_H_ */

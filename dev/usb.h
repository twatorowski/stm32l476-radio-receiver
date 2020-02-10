/*
 * usb.h
 *
 *	Created on: Dec 25, 2016
 *		Author: Tomek
 */

#ifndef DEV_USB_H_
#define DEV_USB_H_

#include <stdint.h>
#include <stddef.h>
#include <sys/ev.h>

/* enpoint numbers */
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

/* endpoint types */
#define USB_EPTYPE_CTL						0x00
#define USB_EPTYPE_ISO						0x01
#define USB_EPTYPE_BULK						0x02
#define USB_EPTYPE_INT						0x03

/* system events: reset event */
extern ev_t usb_rst_ev;

/* initstat */
#define USB_INITSTAT_OK						0x00000001

/* my interrupt handler */
void USB_OTGFSIsr(void);
/* initialize usb support */
int USB_Init(void);
/* get initialization status */
int USB_GetInitStatus(void);

/* start usb action! */
int USB_Connect(int enable);

/* set rx fifo size */
void USB_SetRxFifoSize(uint32_t size);
/* set tx fifo size */
void USB_SetTxFifoSize(uint32_t ep_num, uint32_t size);
/* flush tx fifo */
void USB_FlushTxFifo(uint32_t ep_num);

/* start data transmission */
void USB_StartINTransfer(uint32_t ep_num, void *ptr, size_t size, cb_t cb);
/* start data reception */
void USB_StartOUTTransfer(uint32_t ep_num, void *ptr, size_t size, cb_t cb);
/* start setup transfer: size must be a multiple of 8 (setup frame size), use 24 for
 * best results since host may issue 3 back to back setup packets */
void USB_StartSETUPTransfer(uint32_t ep_num, void *ptr, size_t size, cb_t cb);

/* configure IN endpoint */
void USB_ConfigureINEndpoint(uint32_t ep_num, uint32_t type, size_t mp_size);
/* configure OUT endpoint */
void USB_ConfigureOUTEndpoint(uint32_t ep_num, uint32_t type, size_t mp_size);

/* set device address */
void USB_SetDeviceAddress(uint8_t addr);
/* stall out endpoint */
void USB_StallOUTEndpoint(uint32_t ep_num);
/* stall in endpoint */
void USB_StallINEndpoint(uint32_t ep_num);



#endif /* DEV_USB_H_ */

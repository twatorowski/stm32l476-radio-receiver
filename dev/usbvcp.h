/*
 * usbvcp.h
 *
 *	Created on: 24.07.2017
 *		Author: Tomek
 */

#ifndef DEV_USBVCP_H_
#define DEV_USBVCP_H_

#include <stddef.h>
#include <sys/cb.h>
#include <sys/sem.h>

/* semaphores */
extern sem_t usbvcprx_sem, usbvcptx_sem;

/* requests */
/* set asynchronous line character formatting */
#define USB_VCP_REQ_SET_LINE_CODING				0x20
/* get asynchronous line character formatting */
#define USB_VCP_REQ_GET_LINE_CODING				0x21
/* This request generates RS-232/V.24 style control signals. */
#define USB_VCP_SET_CONTROL_LINE_STATE			0x22

/* initialize virtual com port logic */
int USBVCP_Init(void);
/* read data */
int USBVCP_Recv(void *ptr, size_t size, cb_t cb);
/* write data */
int USBVCP_Send(const void *ptr, size_t size, cb_t cb);

#endif /* MY_USBVCP_H_ */

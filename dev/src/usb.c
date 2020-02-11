/**
 * @file usb.c
 * 
 * @date 2019-12-06
 * @author twatorowski 
 * 
 * @brief USB Physical driver
 */

#include "assert.h"
#include "err.h"
#include "dev/cpuclock.h"
#include "dev/systime.h"
#include "dev/usb.h"
#include "dev/usbdesc.h"
#include "stdint.h"
#include "stm32l476/rcc.h"
#include "stm32l476/gpio.h"
#include "stm32l476/flash.h"
#include "stm32l476/pwr.h"
#include "stm32l476/usb.h"
#include "stm32l476/nvic.h"
#include "sys/atomic.h"
#include "sys/critical.h"
#include "sys/ev.h"
#include "util/msblsb.h"
#include "util/minmax.h"
#include "util/string.h"

#define DEBUG
#include "debug.h"

/* system events: reset event */
ev_t usb_rst_ev;

/* in/out endpoint related stuff */
typedef struct {
	/* current transfer pointer */
	uint8_t *ptr;
	/* current transfer size */
	size_t size, offs;
	/* transfer callback */
	volatile cb_t callback;
} usb_epin_t;

/* in/out endpoint related stuff */
typedef struct {
	uint32_t setup;
	/* current transfer pointer */
	uint8_t *ptr;
	/* current transfer size */
	size_t size, offs;
	/* transfer callback */
	volatile cb_t callback;
} usb_epout_t;
/* in endpoints */
static usb_epin_t in[6];
/* out/control endpoints */
static usb_epout_t out[6];
/* initialization mask */
static int init;

/* read usb packet */
static size_t USB_ReadPacket(void *ptr, size_t size)
{
	/* data pointer */
	uint8_t *p = ptr; size_t b_left;
	/* read data from fifo */
	for (b_left = size; b_left >= 4; b_left -= 4, p += 4) {
		/* read register */
		uint32_t temp = USBFS_FIFO(0);
		/* alignment safe write */
		p[0] = temp >> 0, p[1] = temp >> 8;
		p[2] = temp >> 16, p[3] = temp >> 24;
	}

	/* last few bytes */
	if (b_left) {
		/* read last word */
		uint32_t temp = USBFS_FIFO(0);
		/* store last bytes */
		switch (b_left) {
		case 3 : *p++ = temp, temp >>= 8;
		case 2 : *p++ = temp, temp >>= 8;
		case 1 : *p++ = temp, temp >>= 8;
		}
	}
	/* return number of bytes read */
	return size;
}

/* write usb packet */
static size_t USB_WritePacket(int ep_num, const void *ptr, size_t size)
{
	/* data pointer */
	const uint8_t *p = ptr; size_t sz;
	/* limit next transfer size to the number of bytes available in fifo */
	size = min((USBFS_IE(ep_num)->DTXFSTS & USB_DTXFSTS_INEPTFSAV) * 4, size);

	/* read data from fifo */
	for (sz = size; sz >= 4; sz -= 4, p += 4)
		USBFS_FIFO(ep_num) = p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;

	uint32_t temp = 0;
	/* form 32 bit word from last bytes */
	switch (sz) {
	case 3 : temp |= p[2] << 16;
	case 2 : temp |= p[1] << 8;
	case 1 : USBFS_FIFO(ep_num) = p[0] | temp;
	}

	/* return number of bytes written */
	return size;
}

/* handle bus reset */
static void USB_OTGFSResetIsr(void)
{
	/* disable remote wake-up signaling */
	USBFS->DCTL &= ~USB_DCTL_RWUSIG;

	/* flush all tx fifos */
	USBFS->GRSTCTL = USB_GRSTCTL_TXFFLSH | 0x10 << LSB(USB_GRSTCTL_TXFNUM);
	/* wait for the fifo to become flushed */
	while (USBFS->GRSTCTL & USB_GRSTCTL_TXFFLSH);

	/* flush rx fifo */
	USBFS->GRSTCTL = USB_GRSTCTL_RXFFLSH;
	/* wait for the fifo to become flushed */
	while (USBFS->GRSTCTL & USB_GRSTCTL_RXFFLSH);

	/* mask out all the interrupts */
	USBFS->DIEPMSK = USBFS->DOEPMSK = USBFS->DAINTMSK = 0;

	/* clear endpoint interrupts */
	for (int i = 0; i < 4; i++) {
		/* disable in endpoint */
		if (USBFS_IE(i)->DIEPCTL & USB_DIEPCTL_EPENA)
			USBFS_IE(i)->DIEPCTL = USB_DIEPCTL_EPDIS | USB_DIEPCTL_SNAK;
		/* disable out endpoint */
		if (USBFS_OE(i)->DOEPCTL & USB_DOEPCTL_EPENA)
			USBFS_OE(i)->DOEPCTL = USB_DOEPCTL_EPDIS | USB_DOEPCTL_SNAK;
		/* clear interrupts */
		USBFS_IE(i)->DIEPINT = USBFS_OE(i)->DOEPINT = 0xff;
	}

	/* set out endpoint common interrupt mask: setup phase done,
	* transfer completed, endpoint disabled, OUT token received when endpoint
	* disabled */
	USBFS->DOEPMSK |= USB_DOEPMSK_STUPM | USB_DOEPMSK_XFRCM | USB_DOEPMSK_EPDM;
	/* timeout condition, transfer completed, endpoint disabled */
	USBFS->DIEPMSK |= USB_DIEPMSK_TOM | USB_DIEPMSK_XFRCM | USB_DIEPMSK_EPDM;

	/* set device address to 0 */
	USBFS->DCFG &= ~USB_DCFG_DAD;

	/* reset the endpoint situation */
	memset(in, 0, sizeof(in)); memset(out, 0, sizeof(out));
	/* start usb operation */
	Ev_Notify(&usb_rst_ev, 0);

	/* clear flag */
	USBFS->GINTSTS = USB_GINTSTS_USBRST;
}

/* handle enumaration done */
static void USB_OTGFSEnumIsr(void)
{
	/* configure turnaround time for full speed according to ahb frequency */
	USBFS->GUSBCFG = (USBFS->GUSBCFG & ~USB_GUSBCFG_TRDT) |
		  0x6 << LSB(USB_GUSBCFG_TRDT);
	/* clear global in nak */
	USBFS->DCTL |= USB_DCTL_CGINAK;
	/* clean flag */
	USBFS->GINTSTS = USB_GINTSTS_ENUMDNE;
}

/* handle rx fifo full */
static void USB_OTGFSRxlvlIsr(void)
{
	/* pop status register */
	uint32_t stat = USBFS->GRXSTSP;
	/* get length */
	uint32_t len = (stat & USB_GRXSTSP_BCNT) >> LSB(USB_GRXSTSP_BCNT);
	/* get the endpoint number */
	uint32_t ep_num = stat & USB_GRXSTSP_EPNUM;
	/* endpoint pointer */
	usb_epout_t *ep = &out[ep_num];

	/* decide what to do on packet status field */
	switch (stat & USB_GRXSTSP_PKTSTS) {
	/* setup frame received */
	case USB_GRXSTSP_PKTSTS_DEV_STP_RX :
	case USB_GRXSTSP_PKTSTS_DEV_OUT_RX : {
		/* read packet */
		ep->offs += USB_ReadPacket(ep->ptr + ep->offs, len);
	} break;
	}
}

/* output endpoint interrupt */
static void USB_OTGFSOutEpIsr(void)
{
	/* determine which endpoints raised the interrupt */
	uint32_t irq = (USBFS->DAINT & USBFS->DAINTMSK & USB_DAINTMSK_OEPM) >>
			LSB(USB_DAINTMSK_OEPM);
	/* endpoint number, current endpoint interrupt flags, 310a bit 15 in doepint,
	 * read below for details */
	uint32_t ep_num, ep_irq;
	/* out endpoint pointer */
	usb_epout_t *o = out; cb_t t;

	/* process */
	for (ep_num = 0; irq; ep_num++, irq >>= 1, o++) {
		/* endpoint did not raise the interrupt? */
		if (!(irq & 1))
			continue;

		/* read endpoint specific interrupt */
		ep_irq = USBFS_OE(ep_num)->DOEPINT & USBFS->DOEPMSK;

		/* transfer complete */
		if (ep_irq & USB_DOEPINT_XFRC) {
			/* clear flag */
			USBFS_OE(ep_num)->DOEPINT = USB_DOEPINT_XFRC;
			/* XXX: an important note here: this OTG_FS core exists in different
			 * revisions among the whole product range and there is a twist (an
			 * undocumented one, obviously... ;-( )to the processing of the 
             * messages to every each of them, the following routine is for 
             * ver. 310a */
			if (USBFS->GSNPSID == USB_OTG_CORE_ID_310A) {
				/* mystery bit set? */
				if (!(USBFS_OE(0)->DOEPINT & (1 << 15))) {
					/* not waiting for a setup frame? */
					if (!o->setup && o->callback) {
                        /* build up the event argument */
                        usb_cbarg_t arg = { .error = EOK, .size = o->offs };
                        /* call the callback */
                        t = o->callback, o->callback = 0, t(&arg);
                    }
				}
				/* make sure to set some other undocumented bits because... 
                 * why not */
				USBFS_OE(0)->DOEPINT |= (0x1 << 15) | (0x1 << 5);
			/* XXX: other core versions */
			} else {
				/* not waiting for a setup frame? */
				if (!o->setup && o->callback) {
                    /* build up the event argument */
                    usb_cbarg_t arg = { .error = EOK, .size = o->offs };
                    /* call the callback */
					t = o->callback, o->callback = 0, t(&arg);
                }
			}
		}

		/* setup transaction done? */
		if (ep_irq & USB_DOEPINT_STUP) {
            /* build up the event argument */
            usb_cbarg_t arg = { .error = EOK, .size = o->offs };
			/* call callback */
			o->callback(&arg); o->setup = 0;
			/* clear flag */
			USBFS_OE(ep_num)->DOEPINT = USB_DOEPINT_STUP;
		}
	}
}

/* input endpoint interrupt */
static void USB_OTGFSInEpIsr(void)
{
	/* determine which endpoints raised the interrupt */
	uint32_t irq = (USBFS->DAINT & USBFS->DAINTMSK & USB_DAINTMSK_IEPM) >>
			LSB(USB_DAINTMSK_IEPM);
	/* fifo empty interrupt mask */
	uint32_t fe = USBFS->DIEPEMPMSK, fe_bit = 0x0001;
	/* current endpoint index and interrupt flags, transfer size */
	uint32_t ep_num, ep_irq;
	/* in endpoint pointer */
	usb_epin_t *i = in; cb_t t;

	/* all other ep go here */
	for (ep_num = 0; irq; ep_num++, irq >>= 1, fe >>= 1, fe_bit <<= 1, i++) {
		/* endpoint did not raise the interrupt? */
		if (!(irq & 1))
			continue;
		/* read endpoint specific interrupt */
		ep_irq = USBFS_IE(ep_num)->DIEPINT & 
            (USBFS->DIEPMSK | USB_DIEPINT_TXFE);
		/* check if fifo empty is masked away */
		if (!(fe & 1))
			ep_irq &= ~USB_DIEPINT_TXFE;

		/* transfer complete? */
		if ((ep_irq & USB_DIEPINT_XFRC) && i->callback) {
            /* build up the event argument */
            usb_cbarg_t arg = { .error = EOK, .size = i->offs };
            /* call the callback */
			t = i->callback, i->callback = 0, t(&arg);
        }

		/* fifo empty? */
		if (ep_irq & USB_DIEPINT_TXFE) {
			/* store packet */
			i->offs += USB_WritePacket(ep_num, i->ptr + i->offs, 
                i->size - i->offs);
			/* update offset & mask out fifo empty interrupt */
			if (i->size <= i->offs)
				i->offs = i->size, USBFS->DIEPEMPMSK &= ~fe_bit;
		}

		/* clear flags */
		USBFS_IE(ep_num)->DIEPINT = ep_irq;
	}
}

/* my interrupt handler */
void USB_OTGFSIsr(void)
{
	/* get interrupt flags */
	uint32_t irq = USBFS->GINTSTS & USBFS->GINTMSK;

	/* display interrupt information */
	// dprintf("irq = %08x\n", irq);

	/* invalid interrupt? */
	if (!irq)
		return;

	/* OUT endpoint interrupt */
	if (irq & USB_GINTSTS_OEPINT)
		USB_OTGFSOutEpIsr();

	/* IN endpoint interrupt */
	if (irq & USB_GINTSTS_IEPINT)
		USB_OTGFSInEpIsr();

	/* wakeup interrupt */
	if (irq & USB_GINTSTS_WKUINT)
		USBFS->GINTSTS = USB_GINTSTS_WKUINT;

	/* usb suspend interrupt */
	if (irq & USB_GINTSTS_USBSUSP)
		USBFS->GINTSTS = USB_GINTSTS_USBSUSP;

	/* invalid mode interrupt? */
	if (irq & USB_GINTSTS_MMIS)
		USBFS->GINTSTS = USB_GINTSTS_MMIS;

	/* usb reset */
	if (irq & USB_GINTSTS_USBRST)
		USB_OTGFSResetIsr();

	/* usb enumeration done */
	if (irq & USB_GINTSTS_ENUMDNE)
		USB_OTGFSEnumIsr();

	/* got packet in rx fifo? */
	if (irq & USB_GINTSTS_RXFLVL)
		USB_OTGFSRxlvlIsr();
}

/* initialize usb support */
int USB_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable usb fs */
	RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN | RCC_AHB2ENR_GPIOAEN;
	/* enable usb power */
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;

	/* reset gpioa */
	GPIOA->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	/* select alternate function */
	GPIOA->AFRH |= 10 << (3*4) | 10 << (4*4);
	/* select output speed */
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12;
	/* apply alternate function */
	GPIOA->MODER |= GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1;

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_OTG_FS, INT_PRI_USB);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_OTG_FS);

	/* mark usb supply as valid */
	PWR->CR2 |= PWR_CR2_USV;

	/* disable the interrupts */
	USBFS->GAHBCFG &= ~USB_GAHBCFG_GINTMASK;
	/* Init the Core (common init.) */
	/* Select FS Embedded PHY */
	USBFS->GUSBCFG |= USB_GUSBCFG_PHYSEL;

	/* core reset */
	/* Wait for AHB master IDLE state. */
	while ((USBFS->GRSTCTL & USB_GRSTCTL_AHBIDL) == 0);
	/* Core Soft Reset */
	USBFS->GRSTCTL |= USB_GRSTCTL_CSRST;
	/* wait for reset fo finish */
	while ((USBFS->GRSTCTL & USB_GRSTCTL_CSRST) != 0);
	/* Deactivate the power down */
	USBFS->GCCFG = USB_GCCFG_PWRDWN;

	/* set current mode */
	/* reset mode setting */
	USBFS->GUSBCFG &= ~(USB_GUSBCFG_FHMOD | USB_GUSBCFG_FDMOD);
	/* enforce device mode */
	USBFS->GUSBCFG |= USB_GUSBCFG_FDMOD;
	/* wait for at least 50 ms */
	SysTime_Delay(50);

	/* reset out endpoints */
	for (int i = 0; i < 4; i++)
		USBFS->DIEPTXF[i] = 0;

	/* initialize device */
	/* Deactivate VBUS Sensing B */
	USBFS->GCCFG &= ~USB_GCCFG_VBDEN;
	/* B-peripheral session valid override enable */
	USBFS->GOTGCTL |= USB_GOTGCTL_BVALOEN;
	USBFS->GOTGCTL |= USB_GOTGCTL_BVALOVAL;
	/* Restart the Phy Clock */
	USBFS->PCGCCTL = 0;
	/* Device mode configuration */
	USBFS->DCFG |= 0; //TODO ???
	/* Set Full speed phy */
	USBFS->DCFG |= USB_DCFG_DSPD_0 | USB_DCFG_DSPD_1;

	/* flush the fifos */
	/* Tx fifo */
	USBFS->GRSTCTL = USB_GRSTCTL_TXFFLSH | 0x10 << LSB(USB_GRSTCTL_TXFNUM);
	/* wait for flush to complete */
	while ((USBFS->GRSTCTL & USB_GRSTCTL_TXFFLSH) != 0);
	/* flush receive fifo */
	USBFS->GRSTCTL = USB_GRSTCTL_RXFFLSH;
	/* wait for flush to complete */
	while ((USBFS->GRSTCTL & USB_GRSTCTL_RXFFLSH) != 0);

	/* Clear all pending Device Interrupts */
	/* .. for IN endpoints */
	USBFS->DIEPMSK = 0;
	/* .. for OUT enpoints */
	USBFS->DOEPMSK = 0;
	/* mask all interrupts */
	USBFS->DAINTMSK = 0;

	/* reset in endpoints */
	for (int i = 0; i < 4; i++) {
		/* reset configuration */
		USBFS_IE(i)->DIEPCTL = USB_DIEPCTL_EPDIS | USB_DIEPCTL_SNAK;
		/* reset size */
		USBFS_IE(i)->DIEPTSIZ = 0;
		/* clear interrupts */
		USBFS_IE(i)->DIEPINT  = 0xFF;
	}

	/* reset out endpoints */
	for (int i = 0; i < 4; i++) {
		/* reset configuration */
		USBFS_OE(i)->DOEPCTL = USB_DOEPCTL_EPDIS | USB_DOEPCTL_SNAK;
		/* reset size */
		USBFS_OE(i)->DOEPTSIZ = 0;
		/* clear interrupts */
		USBFS_OE(i)->DOEPINT  = 0xFF;
	}

	/* Disable all interrupts. */
	USBFS->GINTMSK = 0;
	/* Clear any pending interrupts */
	USBFS->GINTSTS = 0xBFFFFFFF;

	/* enable rx level interrupt */
	USBFS->GINTMSK |= USB_GINTMSK_RXFLVLM;
	/* Enable interrupts matching to the Device mode ONLY */
	USBFS->GINTMSK |= USB_GINTMSK_USBSUSPM | USB_GINTMSK_USBRST |
					  USB_GINTMSK_ENUMDNEM | USB_GINTMSK_IEPINT |
					  USB_GINTMSK_OEPINT   | USB_GINTMSK_IISOIXFRM |
					  USB_GINTMSK_WUIM;

	/* perform disconnect */
	USBFS->DCTL |= USB_DCTL_SDIS;
	/* wait for at least 3 ms */
	SysTime_Delay(3);

	/* stop phy clock */
	USBFS->PCGCCTL |= USB_PCGCCTL_STOPCLK;
	/* stop the host clock modules */
	USBFS->PCGCCTL |= USB_PCGCCTL_GATECLK;

	/* disable alternate function */
	GPIOA->MODER |= GPIO_MODER_MODER11 | GPIO_MODER_MODER12;

	/* update initialization flag */
	init = EOK;
	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

/* get initialization status */
int USB_GetInitStatus(void)
{
	/* report initialization status */
	return init;
}

/* start usb action! */
int USB_Connect(int enable)
{
	/* connect the device */
	if (enable) {
		/* enable alternate function */
		Atomic_AND32((void *)&GPIOA->MODER, 
            ~(GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0));
		/* start the host clock modules */
		USBFS->PCGCCTL &= ~(USB_PCGCCTL_GATECLK | USB_PCGCCTL_STOPCLK);

		/* this shall enable pull up resitor */
		USBFS->DCTL &= ~USB_DCTL_SDIS;
		/* wait for at least 3 ms */
		SysTime_Delay(3);
		/* enable interrupts globally */
		USBFS->GAHBCFG |= USB_GAHBCFG_GINTMASK;
	/* disconnect the device */
	} else {
		/* this shall enable pull up resitor */
		USBFS->DCTL |= USB_DCTL_SDIS;
		/* disable interrupts globally */
		USBFS->GAHBCFG &= ~USB_GAHBCFG_GINTMASK;
		/* stop phy clock */
		USBFS->PCGCCTL |= USB_PCGCCTL_STOPCLK;
		/* stop the host clock modules */
		USBFS->PCGCCTL |= USB_PCGCCTL_GATECLK;
		/* diable alternate function */
		Atomic_OR32((void *)&GPIOA->MODER, 
            GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	}

	/* report status */
	return EOK;
}

/* set rx fifo size in 32 bit words */
void USB_SetRxFifoSize(uint32_t size)
{
    /* minimal fifo length allowed */
    if (size < 16)
        size = 16;
	/* set rx fifo size */
	USBFS->GRXFSIZ = size;
}

/* set tx fifo size */
void USB_SetTxFifoSize(uint32_t ep_num, uint32_t size)
{
    /* fifo offset */
    uint32_t offset = USBFS->GRXFSIZ;

    /* minimal fifo length allowed */
    if (size < 16)
        size = 16;

    /* endpoint 0 */
    if (ep_num == 0) {
        USBFS->DIEPTXF0_HNPTXFSIZ = size << LSB(USB_DIEPTXF_INEPTXFD) | offset;
    /* other endpoints */
    } else {
        /* get offset from ep0 */
        offset += USBFS->DIEPTXF0_HNPTXFSIZ >> LSB(USB_DIEPTXF_INEPTXFD);
        /* get offset from other endpoints */
        for (uint32_t i = 1; i < ep_num; i++)
            offset += USBFS->DIEPTXF[i - 1] >> LSB(USB_DIEPTXF_INEPTXFD);
        /* store */
        USBFS->DIEPTXF[ep_num - 1] = size << LSB(USB_DIEPTXF_INEPTXFD) | offset;
    }
}

/* flush tx fifo */
void USB_FlushTxFifo(uint32_t ep_num)
{
	/* flush the fifos */
	/* Tx fifo */
	USBFS->GRSTCTL = USB_GRSTCTL_TXFFLSH | ep_num << LSB(USB_GRSTCTL_TXFNUM);
	/* wait for flush to complete */
	while ((USBFS->GRSTCTL & USB_GRSTCTL_TXFFLSH) != 0);
}

/* start data transmission */
usb_cbarg_t * USB_StartINTransfer(uint32_t ep_num, void *ptr, size_t size, 
    cb_t cb)
{
	/* endpoint pointer */
	usb_epin_t *ep = &in[ep_num];
	/* single packet max size, packet count */
	uint32_t max_size, pkt_cnt;

    /* sanity check */
    assert(cb != CB_SYNC, "usb: sync operation not permitted", ep_num);
	/* store pointer and size and operation finished callback */
	ep->ptr = ptr, ep->size = size, ep->offs = 0, ep->callback = cb;

	/* get single packet max. size */
	max_size = USBFS_IE(ep_num)->DIEPCTL & USB_DIEPCTL_MPSIZ;
	/* ep0 uses special coding for mpsiz field */
	if (ep_num == USB_EP0)
		max_size = 64 >> (max_size & 0x3);
	/* get packet count for this transfer (account for incomplete packets) */
	pkt_cnt = max(1, (size + max_size - 1) / max_size);

	/* clear size and packet count setting */
	USBFS_IE(ep_num)->DIEPTSIZ &= ~(USB_DIEPTSIZ_XFRSIZ | USB_DIEPTSIZ_PKTCNT);
	/* program transfer size */
	USBFS_IE(ep_num)->DIEPTSIZ |= pkt_cnt << LSB(USB_DIEPTSIZ_PKTCNT) | size;
	/* enable fifo tx empty interrupt for this endpoint */
	if (size)
		USBFS->DIEPEMPMSK |= 1 << ep_num;
	/* enable endpoint and clear nak condition: this shall result in tx fifo 
     * empty interrupt during which data will be stored in fifo */
	USBFS_IE(ep_num)->DIEPCTL = 
        (USBFS_IE(ep_num)->DIEPCTL & ~USB_DIEPCTL_EPDIS) |
		USB_DIEPCTL_CNAK | USB_DIEPCTL_EPENA;

    /* always returns 0, no sync operation possible */
    return 0;
}

/* start data reception */
usb_cbarg_t * USB_StartOUTTransfer(uint32_t ep_num, void *ptr, size_t size, 
    cb_t cb)
{
	/* endpoint pointer */
	usb_epout_t *ep = &out[ep_num];
	/* single packet max size, packet count */
	uint32_t max_size, pkt_cnt;

    /* sanity check */
    assert(cb != CB_SYNC, "usb: sync operation not permitted", ep_num);
	/* store pointer and size and operation finished callback */
	ep->ptr = ptr, ep->size = size, ep->offs = 0, ep->setup = 0;
    ep->callback = cb;

	/* get single packet max. size */
	max_size = USBFS_OE(ep_num)->DOEPCTL & USB_DOEPCTL_MPSIZ;
	/* ep0 uses special coding for mpsiz field */
	if (ep_num == USB_EP0)
		max_size = 64 >> (max_size & 0x3);
	/* get packet count for this transfer (account for incomplete packets) */
	pkt_cnt = max(1, (size + max_size - 1) / max_size);

	/* clear size and packet count setting */
	USBFS_OE(ep_num)->DOEPTSIZ &= ~(USB_DOEPTSIZ_XFRSIZ | USB_DOEPTSIZ_PKTCNT);
	/* program transfer size */
	USBFS_OE(ep_num)->DOEPTSIZ |= 
        pkt_cnt << LSB(USB_DOEPTSIZ_PKTCNT) | max_size;
	/* clear nak and enable endpoint for incoming data */
	USBFS_OE(ep_num)->DOEPCTL = 
        (USBFS_OE(ep_num)->DOEPCTL & ~USB_DOEPCTL_EPDIS) |
		USB_DOEPCTL_CNAK | USB_DOEPCTL_EPENA;
    
    /* always returns 0, no sync operation possible */
    return 0;
}

/* start setup transfer: size must be a multiple of 8 (setup frame size), use 
 * 24 for best results since host may issue 3 back to back setup packets */
usb_cbarg_t * USB_StartSETUPTransfer(uint32_t ep_num, void *ptr, size_t size, 
    cb_t cb)
{
	/* endpoint pointer */
	usb_epout_t *ep = &out[ep_num];

    /* sanity check */
    assert(cb != CB_SYNC, "usb: sync operation not permitted", ep_num);
	/* store pointer and size and operation finished callback */
	ep->ptr = ptr, ep->size = size, ep->offs = 0, ep->setup = 1;
    ep->callback = cb;

	/* prepare size register: accept 3 packets */
	USBFS_OE(ep_num)->DOEPTSIZ = 3 * 8 | 1 << LSB(USB_DOEPTSIZ0_PKTCNT) |
			3 << LSB(USB_DOEPTSIZ0_STUPCNT);
    /* always returns 0, no sync operation possible */
    return 0;
}

/* configure IN endpoint and activate it */
void USB_ConfigureINEndpoint(uint32_t ep_num, uint32_t type, size_t mp_size)
{
	/* read register */
	uint32_t temp = USBFS_IE(ep_num)->DIEPCTL & ~(USB_DIEPCTL_EPTYP |
			USB_DIEPCTL_MPSIZ | USB_DIEPCTL_TXFNUM);
	/* ep0 uses special encoding for max packet size */
	if (ep_num == USB_EP0)
		mp_size = (mp_size == 8) ? 0x3 : (mp_size == 16) ? 0x2 :
				  (mp_size == 32) ? 0x1 : 0x0;
	/* write back */
	USBFS_IE(ep_num)->DIEPCTL = temp | 
        type << LSB(USB_DIEPCTL_EPTYP) |
		mp_size << LSB(USB_DIEPCTL_MPSIZ) | 
        ep_num << LSB(USB_DIEPCTL_TXFNUM) |
		USB_DIEPCTL_USBAEP | USB_DIEPCTL_SD0PID_SEVNFRM;

	/* enable interrupt generation */
	USBFS->DAINTMSK |= 1 << (ep_num + LSB(USB_DAINTMSK_IEPM));
}

/* configure OUT endpoint and activate it */
void USB_ConfigureOUTEndpoint(uint32_t ep_num, uint32_t type, size_t mp_size)
{
	/* read register */
	uint32_t temp = USBFS_OE(ep_num)->DOEPCTL & ~(USB_DOEPCTL_EPTYP |
			USB_DOEPCTL_MPSIZ);
	/* ep0 uses special encoding for max packet size */
	if (ep_num == USB_EP0)
		mp_size = (mp_size == 8) ? 0x3 : (mp_size == 16) ? 0x2 :
				  (mp_size == 32) ? 0x1 : 0x0;
	/* write back */
	USBFS_OE(ep_num)->DOEPCTL = temp | type << LSB(USB_DOEPCTL_EPTYP) |
			mp_size << LSB(USB_DOEPCTL_MPSIZ) | USB_DIEPCTL_USBAEP |
			USB_DOEPCTL_SD0PID_SEVNFRM;

	/* enable interrupt generation */
	USBFS->DAINTMSK |= 1 << (ep_num + LSB(USB_DAINTMSK_OEPM));
}

/* set device address */
void USB_SetDeviceAddress(uint8_t addr)
{
	/* modify address field */
	USBFS->DCFG = (USBFS->DCFG & ~USB_DCFG_DAD) | addr << LSB(USB_DCFG_DAD);
}

/* stall out endpoint */
void USB_StallOUTEndpoint(uint32_t ep_num)
{
	/* stall endpoint */
	USBFS_OE(ep_num)->DOEPCTL |= USB_DOEPCTL_STALL;
}

/* stall in endpoint */
void USB_StallINEndpoint(uint32_t ep_num)
{
	/* stall endpoint */
	USBFS_IE(ep_num)->DIEPCTL |= USB_DIEPCTL_STALL;
}

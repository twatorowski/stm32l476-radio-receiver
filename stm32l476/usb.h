/**
 * @file usb.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: USB
 */

#ifndef STM32L476_USB_H_
#define STM32L476_USB_H_

#include "stm32l476/stm32l476.h"

/* registers bases */
#define USBFS_BASE							(0x50000000)

/* core registers */
#define USBFS								((usb_t *)USBFS_BASE)

/* in-endpoints - full speed */
#define USBFS_IE(x)							((usb_ie_t *)(USBFS_BASE + 0x900 + \
												0x20 * (x)))
/* out endpoints - full speed */
#define USBFS_OE(x)							((usb_oe_t *)(USBFS_BASE + 0xB00 + \
												0x20 * (x)))
/* host channels - full speed */
#define USBFS_HC(x)							((usb_hc_t *)(USBFS_BASE + 0xB00 + \
												0x20 * (x)))
/* usb fifo specific push/pop register */
#define USBFS_FIFO(x)						*((reg32_t *)(USBFS_BASE + 0x1000 + \
												0x1000 * (x)))

#define USB_OTG_CORE_ID_310A		  0x4F54310A
#define USB_OTG_CORE_ID_320A		  0x4F54320A

/* core registers */
typedef struct {
	/* core registers */
	reg32_t GOTGCTL;
	reg32_t GOTGINT;
	reg32_t GAHBCFG;
	reg32_t GUSBCFG;
	reg32_t GRSTCTL;
	reg32_t GINTSTS;
	reg32_t GINTMSK;
	reg32_t GRXSTSR;
	reg32_t GRXSTSP;
	reg32_t GRXFSIZ;
	reg32_t DIEPTXF0_HNPTXFSIZ;
	reg32_t HNPTXSTS;
	reg32_t _RESERVED0[2];
	reg32_t GCCFG;
	reg32_t CID;
	reg32_t GSNPSID;
	reg32_t GHWCFG1;
	reg32_t GHWCFG2;
	reg32_t GHWCFG3;
	reg32_t _RESERVED2[1];
	reg32_t GLPMCFG;
	reg32_t GPWRDN;
	reg32_t GDFIFOCFG;
	reg32_t GADPCTL;
	reg32_t _RESERVED3[39];
	reg32_t HPTXFSIZ;
	reg32_t DIEPTXF[16];
	reg32_t _RESERVED4[175];

	/* host registers */
	reg32_t HCFG;
	reg32_t HFIR;
	reg32_t HFNUM;
	reg32_t _RESERVED5[1];
	reg32_t HPTXSTS;
	reg32_t HAINT;
	reg32_t HAINTMSK;
	reg32_t _RESERVED6[249];

	/* device mode registers */
	reg32_t DCFG;
	reg32_t DCTL;
	reg32_t DSTS;
	reg32_t _RESERVED7;
	reg32_t DIEPMSK;
	reg32_t DOEPMSK;
	reg32_t DAINT;
	reg32_t DAINTMSK;
	reg32_t _RESERVED8[2];
	reg32_t DVBUSDIS;
	reg32_t DVBUSPULSE;
	reg32_t _RESERVED9[1];
	reg32_t DIEPEMPMSK;
	reg32_t DEACHINT;
	reg32_t DEACHMSK;
	reg32_t _RESERVED10[1];
	reg32_t DINEP1MSK;
	reg32_t _RESERVED11[15];
	reg32_t DOUTEP1MSK;
	reg32_t _RESERVED12[350];

	/* power and clock gating */
	reg32_t PCGCCTL;
} __attribute__ ((packed, aligned(4))) usb_t;

/*	Bit definition for USB_GOTGCTL register  */
#define USB_GOTGCTL_SRQSCS					0x00000001U
#define USB_GOTGCTL_SRQ						0x00000002U
#define USB_GOTGCTL_VBVALOEN				0x00000004U
#define USB_GOTGCTL_VBVALOVAL				0x00000008U
#define USB_GOTGCTL_AVALOEN					0x00000010U
#define USB_GOTGCTL_AVALOVAL				0x00000020U
#define USB_GOTGCTL_BVALOEN					0x00000040U
#define USB_GOTGCTL_BVALOVAL				0x00000080U
#define USB_GOTGCTL_HNGSCS					0x00000100U
#define USB_GOTGCTL_HNPRQ					0x00000200U
#define USB_GOTGCTL_HSHNPEN					0x00000400U
#define USB_GOTGCTL_DHNPEN					0x00000800U
#define USB_GOTGCTL_EHEN					0x00001000U
#define USB_GOTGCTL_CIDSTS					0x00010000U
#define USB_GOTGCTL_DBCT					0x00020000U
#define USB_GOTGCTL_ASVLD					0x00040000U
#define USB_GOTGCTL_BSESVLD					0x00080000U
#define USB_GOTGCTL_OTGVER					0x00100000U

/*	Bit definition for USB_GOTGINT register  */
#define USB_GOTGINT_SEDET					0x00000004U
#define USB_GOTGINT_SRSSCHG					0x00000100U
#define USB_GOTGINT_HNSSCHG					0x00000200U
#define USB_GOTGINT_HNGDET					0x00020000U
#define USB_GOTGINT_ADTOCHG					0x00040000U
#define USB_GOTGINT_DBCDNE					0x00080000U
#define USB_GOTGINT_IDCHNG					0x00100000U

/*	Bit definition for USB_GAHBCFG register  */
#define USB_GAHBCFG_GINTMASK				0x00000001U
#define USB_GAHBCFG_TXFELVL					0x00000080U
#define USB_GAHBCFG_PTXFELVL				0x00000100U

/*	Bit definition for USB_GUSBCFG register  */
#define USB_GUSBCFG_TOCAL					0x00000007U
#define USB_GUSBCFG_TOCAL_0					0x00000001U
#define USB_GUSBCFG_TOCAL_1					0x00000002U
#define USB_GUSBCFG_TOCAL_2					0x00000004U
#define USB_GUSBCFG_PHYSEL					0x00000040U
#define USB_GUSBCFG_SRPCAP					0x00000100U
#define USB_GUSBCFG_HNPCAP					0x00000200U
#define USB_GUSBCFG_TRDT					0x00003C00U
#define USB_GUSBCFG_TRDT_0					0x00000400U
#define USB_GUSBCFG_TRDT_1					0x00000800U
#define USB_GUSBCFG_TRDT_2					0x00001000U
#define USB_GUSBCFG_FHMOD					0x20000000U
#define USB_GUSBCFG_FDMOD					0x40000000U

/*	Bit definition for USB_GRSTCTL register  */
#define USB_GRSTCTL_CSRST					0x00000001U
#define USB_GRSTCTL_FCRST					0x00000004U
#define USB_GRSTCTL_RXFFLSH					0x00000010U
#define USB_GRSTCTL_TXFFLSH					0x00000020U
#define USB_GRSTCTL_TXFNUM					0x000007C0U
#define USB_GRSTCTL_TXFNUM_0				0x00000040U
#define USB_GRSTCTL_TXFNUM_1				0x00000080U
#define USB_GRSTCTL_TXFNUM_2				0x00000100U
#define USB_GRSTCTL_TXFNUM_3				0x00000200U
#define USB_GRSTCTL_TXFNUM_4				0x00000400U
#define USB_GRSTCTL_AHBIDL					0x80000000U

/*	Bit definition for USB_GINTSTS register  */
#define USB_GINTSTS_CMOD					0x00000001U
#define USB_GINTSTS_MMIS					0x00000002U
#define USB_GINTSTS_OTGINT					0x00000004U
#define USB_GINTSTS_SOF						0x00000008U
#define USB_GINTSTS_RXFLVL					0x00000010U
#define USB_GINTSTS_NPTXFE					0x00000020U
#define USB_GINTSTS_GINAKEFF				0x00000040U
#define USB_GINTSTS_BOUTNAKEFF				0x00000080U
#define USB_GINTSTS_ESUSP					0x00000400U
#define USB_GINTSTS_USBSUSP					0x00000800U
#define USB_GINTSTS_USBRST					0x00001000U
#define USB_GINTSTS_ENUMDNE					0x00002000U
#define USB_GINTSTS_ISOODRP					0x00004000U
#define USB_GINTSTS_EOPF					0x00008000U
#define USB_GINTSTS_IEPINT					0x00040000U
#define USB_GINTSTS_OEPINT					0x00080000U
#define USB_GINTSTS_IISOIXFR				0x00100000U
#define USB_GINTSTS_IPXFR_INCOMPISOOUT		0x00200000U
#define USB_GINTSTS_RSTDET					0x00800000U
#define USB_GINTSTS_HPRTINT					0x01000000U
#define USB_GINTSTS_HCINT					0x02000000U
#define USB_GINTSTS_PTXFE					0x04000000U
#define USB_GINTSTS_LPMINT					0x08000000U
#define USB_GINTSTS_CIDSCHG					0x10000000U
#define USB_GINTSTS_DISCINT					0x20000000U
#define USB_GINTSTS_SRQINT					0x40000000U
#define USB_GINTSTS_WKUINT					0x80000000U

/*	Bit definition for USB_OTG_GINTMSK register  */
#define USB_GINTMSK_MMISM					0x00000002U
#define USB_GINTMSK_OTGINT					0x00000004U
#define USB_GINTMSK_SOFM					0x00000008U
#define USB_GINTMSK_RXFLVLM					0x00000010U
#define USB_GINTMSK_NPTXFEM					0x00000020U
#define USB_GINTMSK_GINAKEFFM				0x00000040U
#define USB_GINTMSK_GONAKEFFM				0x00000080U
#define USB_GINTMSK_ESUSPM					0x00000400U
#define USB_GINTMSK_USBSUSPM				0x00000800U
#define USB_GINTMSK_USBRST					0x00001000U
#define USB_GINTMSK_ENUMDNEM				0x00002000U
#define USB_GINTMSK_ISOODRPM				0x00004000U
#define USB_GINTMSK_EOPFM					0x00008000U
#define USB_GINTMSK_EPMISM					0x00020000U
#define USB_GINTMSK_IEPINT					0x00040000U
#define USB_GINTMSK_OEPINT					0x00080000U
#define USB_GINTMSK_IISOIXFRM				0x00100000U
#define USB_GINTMSK_IPXFRM_IISOOXFRM		0x00200000U
#define USB_GINTMSK_RSTDEM					0x00800000U
#define USB_GINTMSK_PRTIM					0x01000000U
#define USB_GINTMSK_HCIM					0x02000000U
#define USB_GINTMSK_PTXFEM					0x04000000U
#define USB_GINTMSK_LPMINTM					0x08000000U
#define USB_GINTMSK_CIDSCHGM				0x10000000U
#define USB_GINTMSK_DISCINT					0x20000000U
#define USB_GINTMSK_SRQIM					0x40000000U
#define USB_GINTMSK_WUIM					0x80000000U

/*	Bit definition for USB_GRXSTSR register  */
#define USB_GRXSTSR_EPNUM					0x0000000FU
#define USB_GRXSTSR_BCNT					0x00007FF0U
#define USB_GRXSTSR_DPID					0x00018000U
#define USB_GRXSTSR_PKTSTS					0x001E0000U
#define USB_GRXSTSR_PKTSTS_DEV_GOUTNAK		0x00020000U
#define USB_GRXSTSR_PKTSTS_DEV_OUT_RX		0x00040000U
#define USB_GRXSTSR_PKTSTS_DEV_OUT_TC		0x00060000U
#define USB_GRXSTSR_PKTSTS_DEV_STP_TC		0x00080000U
#define USB_GRXSTSR_PKTSTS_DEV_STP_RX		0x000C0000U
#define USB_GRXSTSR_FRNUM					0x01E00000U
#define USB_GRXSTSR_FRNUM_0					0x00200000U
#define USB_GRXSTSR_FRNUM_1					0x00400000U
#define USB_GRXSTSR_FRNUM_2					0x00800000U
#define USB_GRXSTSR_FRNUM_3					0x01000000U

/*	Bit definition for USB_GRXSTSP register  */
#define USB_GRXSTSP_EPNUM					0x0000000FU
#define USB_GRXSTSP_BCNT					0x00007FF0U
#define USB_GRXSTSP_DPID					0x00018000U
#define USB_GRXSTSP_PKTSTS					0x001E0000U
#define USB_GRXSTSP_PKTSTS_DEV_GOUTNAK		0x00020000U
#define USB_GRXSTSP_PKTSTS_DEV_OUT_RX		0x00040000U
#define USB_GRXSTSP_PKTSTS_DEV_OUT_TC		0x00060000U
#define USB_GRXSTSP_PKTSTS_DEV_STP_TC		0x00080000U
#define USB_GRXSTSP_PKTSTS_DEV_STP_RX		0x000C0000U
#define USB_GRXSTSP_FRNUM					0x01E00000U
#define USB_GRXSTSP_FRNUM_0					0x00200000U
#define USB_GRXSTSP_FRNUM_1					0x00400000U
#define USB_GRXSTSP_FRNUM_2					0x00800000U
#define USB_GRXSTSP_FRNUM_3					0x01000000U

/*	Bit definition for USB_GRXFSIZ register  */
#define USB_GRXFSIZ_RXFD					0x0000FFFFU

/* usb core versions */
#define USB_GSNPSID_OTG_CORE_ID_310A		0x4F54310AU
#define USB_GSNPSID_OTG_CORE_ID_320A		0x4F54320AU

/*	Bit definition for USB_DIEPTXF register  */
#define USB_DIEPTXF_INEPTXSA				0x0000FFFFU
#define USB_DIEPTXF_INEPTXFD				0xFFFF0000U

/*	Bit definition for USB_GCCFG register  */
#define USB_GCCFG_DCDET						0x00000001U
#define USB_GCCFG_PDET						0x00000002U
#define USB_GCCFG_SDET						0x00000004U
#define USB_GCCFG_PS2DET					0x00000008U
#define USB_GCCFG_PWRDWN					0x00010000U
#define USB_GCCFG_BCDEN						0x00020000U
#define USB_GCCFG_DCDEN						0x00040000U
#define USB_GCCFG_PDEN						0x00080000U
#define USB_GCCFG_SDEN						0x00100000U
#define USB_GCCFG_VBDEN						0x00200000U

/*	Bit definition for USB_CID register  */
#define USB_CID_PRODUCT_ID					0xFFFFFFFFU

/*	Bit definition for USB_GLPMCFG register  */
#define USB_GLPMCFG_LPMEN					0x00000001U
#define USB_GLPMCFG_LPMACK					0x00000002U
#define USB_GLPMCFG_BESL					0x0000003CU
#define USB_GLPMCFG_REMWAKE					0x00000040U
#define USB_GLPMCFG_L1SSEN					0x00000080U
#define USB_GLPMCFG_BESLTHRS				0x00000F00U
#define USB_GLPMCFG_L1DSEN					0x00001000U
#define USB_GLPMCFG_LPMRSP					0x00006000U
#define USB_GLPMCFG_SLPSTS					0x00008000U
#define USB_GLPMCFG_L1RSMOK					0x00010000U
#define USB_GLPMCFG_LPMCHIDX				0x001E0000U
#define USB_GLPMCFG_LPMRCNT					0x00E00000U
#define USB_GLPMCFG_SNDLPM					0x01000000U
#define USB_GLPMCFG_LPMRCNTSTS				0x0E000000U
#define USB_GLPMCFG_ENBESL					0x10000000U

/*	Bit definition for USB_GPWRDN register	*/
#define USB_GPWRDN_ADPMEN					0x00000001U
#define USB_GPWRDN_ADPIF					0x00800000U

/*	Bit definition for USB_HPTXFSIZ register  */
#define USB_HPTXFSIZ_PTXSA					0x0000FFFFU
#define USB_HPTXFSIZ_PTXFD					0xFFFF0000U

/*	Bit definition for USB_HCFG register  */
#define USB_HCFG_FSLSPCS					0x00000003U
#define USB_HCFG_FSLSPCS_0					0x00000001U
#define USB_HCFG_FSLSPCS_1					0x00000002U
#define USB_HCFG_FSLSS						0x00000004U

/*	Bit definition for USB_HFIR register  */
#define USB_HFIR_FRIVL						0x0000FFFFU
#define USB_HFIR_RLDCTRL					0x00010000U

/*	Bit definition for USB_HFNUM register  */
#define USB_HFNUM_FRNUM						0x0000FFFFU
#define USB_HFNUM_FTREM						0xFFFF0000U

/*	Bit definition for USB_HPTXSTS register  */
#define USB_HPTXSTS_PTXFSAVL				0x0000FFFFU
#define USB_HPTXSTS_PTXQSAV					0x00FF0000U
#define USB_HPTXSTS_PTXQSAV_0				0x00010000U
#define USB_HPTXSTS_PTXQSAV_1				0x00020000U
#define USB_HPTXSTS_PTXQSAV_2				0x00040000U
#define USB_HPTXSTS_PTXQSAV_3				0x00080000U
#define USB_HPTXSTS_PTXQSAV_4				0x00100000U
#define USB_HPTXSTS_PTXQSAV_5				0x00200000U
#define USB_HPTXSTS_PTXQSAV_6				0x00400000U
#define USB_HPTXSTS_PTXQSAV_7				0x00800000U
#define USB_HPTXSTS_PTXQTOP					0xFF000000U
#define USB_HPTXSTS_PTXQTOP_0				0x01000000U
#define USB_HPTXSTS_PTXQTOP_1				0x02000000U
#define USB_HPTXSTS_PTXQTOP_2				0x04000000U
#define USB_HPTXSTS_PTXQTOP_3				0x08000000U
#define USB_HPTXSTS_PTXQTOP_4				0x10000000U
#define USB_HPTXSTS_PTXQTOP_5				0x20000000U
#define USB_HPTXSTS_PTXQTOP_6				0x40000000U
#define USB_HPTXSTS_PTXQTOP_7				0x80000000U

/*	Bit definition for USB_HAINT register  */
#define USB_HAINT_HAINT						0x0000FFFFU

/*	Bit definition for USB_HAINTMSK register  */
#define USB_HAINTMSK_HAINTM					0x0000FFFFU

/*	Bit definition for USB_DCFG register  */
#define USB_DCFG_DSPD						0x00000003U
#define USB_DCFG_DSPD_0						0x00000001U
#define USB_DCFG_DSPD_1						0x00000002U
#define USB_DCFG_NZLSOHSK					0x00000004U
#define USB_DCFG_DAD						0x000007F0U
#define USB_DCFG_DAD_0						0x00000010U
#define USB_DCFG_DAD_1						0x00000020U
#define USB_DCFG_DAD_2						0x00000040U
#define USB_DCFG_DAD_3						0x00000080U
#define USB_DCFG_DAD_4						0x00000100U
#define USB_DCFG_DAD_5						0x00000200U
#define USB_DCFG_DAD_6						0x00000400U
#define USB_DCFG_PFIVL						0x00001800U
#define USB_DCFG_PFIVL_0					0x00000800U
#define USB_DCFG_PFIVL_1					0x00001000U

/*	Bit definition for USB_DCTL register  */
#define USB_DCTL_RWUSIG						0x00000001U
#define USB_DCTL_SDIS						0x00000002U
#define USB_DCTL_GINSTS						0x00000004U
#define USB_DCTL_GONSTS						0x00000008U
#define USB_DCTL_TCTL						0x00000070U
#define USB_DCTL_TCTL_0						0x00000010U
#define USB_DCTL_TCTL_1						0x00000020U
#define USB_DCTL_TCTL_2						0x00000040U
#define USB_DCTL_SGINAK						0x00000080U
#define USB_DCTL_CGINAK						0x00000100U
#define USB_DCTL_SGONAK						0x00000200U
#define USB_DCTL_CGONAK						0x00000400U
#define USB_DCTL_POPRGDNE					0x00000800U
#define USB_DCTL_DSBESLRJCT					0x00004000U

/*	Bit definition for USB_DSTS register  */
#define USB_DSTS_SUSPSTS					0x00000001U
#define USB_DSTS_ENUMSPD					0x00000006U
#define USB_DSTS_ENUMSPD_0					0x00000002U
#define USB_DSTS_ENUMSPD_1					0x00000004U
#define USB_DSTS_EERR						0x00000008U
#define USB_DSTS_FNSOF						0x003FFF00U
#define USB_DSTS_DEVLNSTS					0x0C000000U
#define USB_DSTS_DEVLNSTS_0					0x04000000U
#define USB_DSTS_DEVLNSTS_1					0x08000000U

/*	Bit definition for USB_DIEPMSK register  */
#define USB_DIEPMSK_XFRCM					0x00000001U
#define USB_DIEPMSK_EPDM					0x00000002U
#define USB_DIEPMSK_TOM						0x00000008U
#define USB_DIEPMSK_ITTXFEMSK				0x00000010U
#define USB_DIEPMSK_INEPNMM					0x00000020U
#define USB_DIEPMSK_INEPNEM					0x00000040U
#define USB_DIEPMSK_TXFURM					0x00000100U
#define USB_DIEPMSK_NAKM					0x00000200U

/*	Bit definition for USB_DOEPMSK register  */
#define USB_DOEPMSK_XFRCM					0x00000001U
#define USB_DOEPMSK_EPDM					0x00000002U
#define USB_DOEPMSK_STUPM					0x00000008U
#define USB_DOEPMSK_OTEPDM					0x00000010U

/*	Bit definition for USB_DAINT register  */
#define USB_DAINT_IEPINT					0x0000FFFFU
#define USB_DAINT_OEPINT					0xFFFF0000U
#define USB_DAINT_IEPM_0					0x00000001U
#define USB_DAINT_IEPM_1					0x00000002U
#define USB_DAINT_IEPM_2					0x00000004U
#define USB_DAINT_IEPM_3					0x00000008U
#define USB_DAINT_IEPM_4					0x00000010U
#define USB_DAINT_IEPM_5					0x00000020U
#define USB_DAINT_IEPM_6					0x00000040U
#define USB_DAINT_IEPM_7					0x00000080U
#define USB_DAINT_IEPM_8					0x00000100U
#define USB_DAINT_IEPM_9					0x00000200U
#define USB_DAINT_IEPM_10					0x00000400U
#define USB_DAINT_IEPM_11					0x00000800U
#define USB_DAINT_IEPM_12					0x00001000U
#define USB_DAINT_IEPM_13					0x00002000U
#define USB_DAINT_IEPM_14					0x00004000U
#define USB_DAINT_IEPM_15					0x00008000U
#define USB_DAINT_OEPM_0					0x00010000U
#define USB_DAINT_OEPM_1					0x00020000U
#define USB_DAINT_OEPM_2					0x00040000U
#define USB_DAINT_OEPM_3					0x00080000U
#define USB_DAINT_OEPM_4					0x00100000U
#define USB_DAINT_OEPM_5					0x00200000U
#define USB_DAINT_OEPM_6					0x00400000U
#define USB_DAINT_OEPM_7					0x00800000U
#define USB_DAINT_OEPM_8					0x01000000U
#define USB_DAINT_OEPM_9					0x02000000U
#define USB_DAINT_OEPM_10					0x04000000U
#define USB_DAINT_OEPM_11					0x08000000U
#define USB_DAINT_OEPM_12					0x10000000U
#define USB_DAINT_OEPM_13					0x20000000U
#define USB_DAINT_OEPM_14					0x40000000U
#define USB_DAINT_OEPM_15					0x80000000U

/*	Bit definition for USB_DAINTMSK register  */
#define USB_DAINTMSK_IEPM					0x0000FFFFU
#define USB_DAINTMSK_OEPM					0xFFFF0000U
#define USB_DAINTMSK_IEPM_0					0x00000001U
#define USB_DAINTMSK_IEPM_1					0x00000002U
#define USB_DAINTMSK_IEPM_2					0x00000004U
#define USB_DAINTMSK_IEPM_3					0x00000008U
#define USB_DAINTMSK_IEPM_4					0x00000010U
#define USB_DAINTMSK_IEPM_5					0x00000020U
#define USB_DAINTMSK_IEPM_6					0x00000040U
#define USB_DAINTMSK_IEPM_7					0x00000080U
#define USB_DAINTMSK_IEPM_8					0x00000100U
#define USB_DAINTMSK_IEPM_9					0x00000200U
#define USB_DAINTMSK_IEPM_10				0x00000400U
#define USB_DAINTMSK_IEPM_11				0x00000800U
#define USB_DAINTMSK_IEPM_12				0x00001000U
#define USB_DAINTMSK_IEPM_13				0x00002000U
#define USB_DAINTMSK_IEPM_14				0x00004000U
#define USB_DAINTMSK_IEPM_15				0x00008000U
#define USB_DAINTMSK_OEPM_0					0x00010000U
#define USB_DAINTMSK_OEPM_1					0x00020000U
#define USB_DAINTMSK_OEPM_2					0x00040000U
#define USB_DAINTMSK_OEPM_3					0x00080000U
#define USB_DAINTMSK_OEPM_4					0x00100000U
#define USB_DAINTMSK_OEPM_5					0x00200000U
#define USB_DAINTMSK_OEPM_6					0x00400000U
#define USB_DAINTMSK_OEPM_7					0x00800000U
#define USB_DAINTMSK_OEPM_8					0x01000000U
#define USB_DAINTMSK_OEPM_9					0x02000000U
#define USB_DAINTMSK_OEPM_10				0x04000000U
#define USB_DAINTMSK_OEPM_11				0x08000000U
#define USB_DAINTMSK_OEPM_12				0x10000000U
#define USB_DAINTMSK_OEPM_13				0x20000000U
#define USB_DAINTMSK_OEPM_14				0x40000000U
#define USB_DAINTMSK_OEPM_15				0x80000000U

/*	Bit definition for USB_DVBUSDIS register  */
#define USB_DVBUSDIS_VBUSDT					0x0000FFFFU

/*	Bit definition for USB_DVBUSPULSE register	*/
#define USB_DVBUSPULSE_DVBUSP				0x00000FFFU

/*	Bit definition for USB_DIEPEMPMSK register	*/
#define USB_DIEPEMPMSK_INEPTXFEM			0x0000FFFFU
#define USB_DIEPEMPMSK_INEPTXFEM_0			0x00000001U
#define USB_DIEPEMPMSK_INEPTXFEM_1			0x00000002U
#define USB_DIEPEMPMSK_INEPTXFEM_2			0x00000004U
#define USB_DIEPEMPMSK_INEPTXFEM_3			0x00000008U
#define USB_DIEPEMPMSK_INEPTXFEM_4			0x00000010U
#define USB_DIEPEMPMSK_INEPTXFEM_5			0x00000020U
#define USB_DIEPEMPMSK_INEPTXFEM_6			0x00000040U
#define USB_DIEPEMPMSK_INEPTXFEM_7			0x00000080U
#define USB_DIEPEMPMSK_INEPTXFEM_8			0x00000100U
#define USB_DIEPEMPMSK_INEPTXFEM_9			0x00000200U
#define USB_DIEPEMPMSK_INEPTXFEM_10			0x00000400U
#define USB_DIEPEMPMSK_INEPTXFEM_11			0x00000800U
#define USB_DIEPEMPMSK_INEPTXFEM_12			0x00001000U
#define USB_DIEPEMPMSK_INEPTXFEM_13			0x00002000U
#define USB_DIEPEMPMSK_INEPTXFEM_14			0x00004000U
#define USB_DIEPEMPMSK_INEPTXFEM_15			0x00008000U

/*	Bit definition for USB_DEACHINT register  */
#define USB_DEACHINT_IEP1INT				0x00000002U
#define USB_DEACHINT_OEP1INT				0x00020000U

/*	Bit definition for USB_DEACHINTMSK register  */
#define USB_DEACHINTMSK_IEP1INTM			0x00000002U
#define USB_DEACHINTMSK_OEP1INTM			0x00020000U

/*	Bit definition for PCGCCTL register  */
#define USB_PCGCCTL_STOPCLK					0x00000001U
#define USB_PCGCCTL_GATECLK					0x00000002U
#define USB_PCGCCTL_PHYSUSP					0x00000010U
#define USB_PCGCCTL_ENL1GTG					0x00000020U
#define USB_PCGCCTL_PHYSLEEP				0x00000040U
#define USB_PCGCCTL_SUSP					0x00000080U

/* in-endpoint specific registers */
typedef struct {
	reg32_t DIEPCTL;
	reg32_t _RESERVED0[1];
	reg32_t DIEPINT;
	reg32_t _RESERVED1[1];
	reg32_t DIEPTSIZ;
	reg32_t DIEPDMA;
	reg32_t DTXFSTS;
	reg32_t _RESERVED2[1];
} __attribute__ ((packed, aligned(4))) usb_ie_t;

/*	Bit definition for USB_DIEPCTL0 register  */
#define USB_DIEPCTL0_MPSIZ					0x00000003U
#define USB_DIEPCTL0_USBAEP					0x00008000U
#define USB_DIEPCTL0_NAKSTS					0x00020000U
#define USB_DIEPCTL0_EPTYP					0x000C0000U
#define USB_DIEPCTL0_EPTYP_0				0x00040000U
#define USB_DIEPCTL0_EPTYP_1				0x00080000U
#define USB_DIEPCTL0_STALL					0x00200000U
#define USB_DIEPCTL0_TXFNUM					0x03C00000U
#define USB_DIEPCTL0_TXFNUM_0				0x00400000U
#define USB_DIEPCTL0_TXFNUM_1				0x00800000U
#define USB_DIEPCTL0_TXFNUM_2				0x01000000U
#define USB_DIEPCTL0_TXFNUM_3				0x02000000U
#define USB_DIEPCTL0_CNAK					0x04000000U
#define USB_DIEPCTL0_SNAK					0x08000000U
#define USB_DIEPCTL0_EPDIS					0x40000000U
#define USB_DIEPCTL0_EPENA					0x80000000U

/*	Bit definition for USB_DIEPCTL register  */
#define USB_DIEPCTL_MPSIZ					0x000007FFU
#define USB_DIEPCTL_USBAEP					0x00008000U
#define USB_DIEPCTL_EONUM_DPID				0x00010000U
#define USB_DIEPCTL_NAKSTS					0x00020000U
#define USB_DIEPCTL_EPTYP					0x000C0000U
#define USB_DIEPCTL_EPTYP_0					0x00040000U
#define USB_DIEPCTL_EPTYP_1					0x00080000U
#define USB_DIEPCTL_STALL					0x00200000U
#define USB_DIEPCTL_TXFNUM					0x03C00000U
#define USB_DIEPCTL_TXFNUM_0				0x00400000U
#define USB_DIEPCTL_TXFNUM_1				0x00800000U
#define USB_DIEPCTL_TXFNUM_2				0x01000000U
#define USB_DIEPCTL_TXFNUM_3				0x02000000U
#define USB_DIEPCTL_CNAK					0x04000000U
#define USB_DIEPCTL_SNAK					0x08000000U
#define USB_DIEPCTL_SD0PID_SEVNFRM			0x10000000U
#define USB_DIEPCTL_SODDFRM					0x20000000U
#define USB_DIEPCTL_EPDIS					0x40000000U
#define USB_DIEPCTL_EPENA					0x80000000U

/*	Bit definition for USB_DIEPINT register  */
#define USB_DIEPINT_XFRC					0x00000001U
#define USB_DIEPINT_EPDISD					0x00000002U
#define USB_DIEPINT_TOC						0x00000008U
#define USB_DIEPINT_ITTXFE					0x00000010U
#define USB_DIEPINT_INEPNE					0x00000040U
#define USB_DIEPINT_TXFE					0x00000080U

/*	Bit definition for USB_DIEPTSIZ0 register  */
#define USB_DIEPTSIZ0_XFRSIZ				0x0000007FU
#define USB_DIEPTSIZ0_PKTCNT				0x00180000U

/*	Bit definition for USB_DIEPTSIZ register  */
#define USB_DIEPTSIZ_XFRSIZ					0x0007FFFFU
#define USB_DIEPTSIZ_PKTCNT					0x1FF80000U
#define USB_DIEPTSIZ_MULCNT					0x60000000U

/*	Bit definition for USB_DIEPDMA register  */
#define USB_DIEPDMA_DMAADDR					0xFFFFFFFFU

/*	Bit definition for USB_DTXFSTS register  */
#define USB_DTXFSTS_INEPTFSAV				0x0000FFFFU

/* out endpoint specific registers */
typedef struct {
	reg32_t DOEPCTL;
	reg32_t _RESERVED0[1];
	reg32_t DOEPINT;
	reg32_t _RESERVED1[1];
	reg32_t DOEPTSIZ;
	reg32_t DOEPDMA;
	reg32_t _RESERVED2[2];
} __attribute__ ((packed, aligned(4))) usb_oe_t;

/*	Bit definition for USB_DOEPCTL0 register  */
#define USB_DOEPCTL0_MPSIZ						0x00000003U
#define USB_DOEPCTL0_USBAEP						0x00008000U
#define USB_DOEPCTL0_NAKSTS						0x00020000U
#define USB_DOEPCTL0_SD0PID_SEVNFRM				0x10000000U
#define USB_DOEPCTL0_SODDFRM					0x20000000U
#define USB_DOEPCTL0_EPTYP						0x000C0000U
#define USB_DOEPCTL0_EPTYP_0					0x00040000U
#define USB_DOEPCTL0_EPTYP_1					0x00080000U
#define USB_DOEPCTL0_SNPM						0x00100000U
#define USB_DOEPCTL0_STALL						0x00200000U
#define USB_DOEPCTL0_CNAK						0x04000000U
#define USB_DOEPCTL0_SNAK						0x08000000U
#define USB_DOEPCTL0_EPDIS						0x40000000U
#define USB_DOEPCTL0_EPENA						0x80000000U

/*	Bit definition for USB_DOEPCTL register  */
#define USB_DOEPCTL_MPSIZ						0x000007FFU
#define USB_DOEPCTL_USBAEP						0x00008000U
#define USB_DOEPCTL_EONUM						0x00010000U
#define USB_DOEPCTL_NAKSTS						0x00020000U
#define USB_DOEPCTL_EPTYP						0x000C0000U
#define USB_DOEPCTL_EPTYP_0						0x00040000U
#define USB_DOEPCTL_EPTYP_1						0x00080000U
#define USB_DOEPCTL_SNPM						0x00100000U
#define USB_DOEPCTL_STALL						0x00200000U
#define USB_DOEPCTL_CNAK						0x04000000U
#define USB_DOEPCTL_SNAK						0x08000000U
#define USB_DOEPCTL_SD0PID_SEVNFRM				0x10000000U
#define USB_DOEPCTL_SD1PID_SODDFRM				0x20000000U
#define USB_DOEPCTL_EPDIS						0x40000000U
#define USB_DOEPCTL_EPENA						0x80000000U

/*	Bit definition for USB_DOEPINT register  */
#define USB_DOEPINT_XFRC						0x00000001U
#define USB_DOEPINT_EPDISD						0x00000002U
#define USB_DOEPINT_STUP						0x00000008U
#define USB_DOEPINT_OTEPDIS						0x00000010U
#define USB_DOEPINT_OTEPSPR						0x00000020U
#define USB_DOEPINT_B2BSTUP						0x00000040U
#define USB_DOEPINT_NYET						0x00004000U

/*	Bit definition for USB_DOEPTSIZ0 register  */
#define USB_DOEPTSIZ0_XFRSIZ					0x0000007FU
#define USB_DOEPTSIZ0_PKTCNT					0x00080000U
#define USB_DOEPTSIZ0_STUPCNT					0x60000000U
#define USB_DOEPTSIZ0_STUPCNT_0					0x20000000U
#define USB_DOEPTSIZ0_STUPCNT_1					0x40000000U

/*	Bit definition for USB_DOEPTSIZ register  */
#define USB_DOEPTSIZ_XFRSIZ						0x0007FFFFU
#define USB_DOEPTSIZ_PKTCNT						0x1FF80000U
#define USB_DOEPTSIZ_RXDPID_STUPCNT				0x60000000U
#define USB_DOEPTSIZ_RXDPID_STUPCNT_0			0x20000000U
#define USB_DOEPTSIZ_RXDPID_STUPCNT_1			0x40000000U

/*	Bit definition for USB_DOEPDMA register  */
#define USB_DOEPDMA_DMAADDR						0xFFFFFFFFU

/* host channel specific registeres */
typedef struct {
	reg32_t HCCHAR;
	reg32_t _RESERVED0;
	reg32_t HCINT;
	reg32_t HCINTMSK;
	reg32_t HCTSIZ;
	reg32_t _RESERVED1[3];
} __attribute__ ((packed, aligned(4))) usb_hc_t;

/*	Bit definition for USB_HCCHAR register	*/
#define USB_HCCHAR_MPSIZ						0x000007FFU
#define USB_HCCHAR_EPNUM						0x00007800U
#define USB_HCCHAR_EPNUM_0						0x00000800U
#define USB_HCCHAR_EPNUM_1						0x00001000U
#define USB_HCCHAR_EPNUM_2						0x00002000U
#define USB_HCCHAR_EPNUM_3						0x00004000U
#define USB_HCCHAR_EPDIR						0x00008000U
#define USB_HCCHAR_LSDEV						0x00020000U
#define USB_HCCHAR_EPTYP						0x000C0000U
#define USB_HCCHAR_EPTYP_0						0x00040000U
#define USB_HCCHAR_EPTYP_1						0x00080000U
#define USB_HCCHAR_MCNT							0x00300000U
#define USB_HCCHAR_MCNT_0						0x00100000U
#define USB_HCCHAR_MCNT_1						0x00200000U
#define USB_HCCHAR_DAD							0x1FC00000U
#define USB_HCCHAR_DAD_0						0x00400000U
#define USB_HCCHAR_DAD_1						0x00800000U
#define USB_HCCHAR_DAD_2						0x01000000U
#define USB_HCCHAR_DAD_3						0x02000000U
#define USB_HCCHAR_DAD_4						0x04000000U
#define USB_HCCHAR_DAD_5						0x08000000U
#define USB_HCCHAR_DAD_6						0x10000000U
#define USB_HCCHAR_ODDFRM						0x20000000U
#define USB_HCCHAR_CHDIS						0x40000000U
#define USB_HCCHAR_CHENA						0x80000000U

/*	Bit definition for USB_HCINT register  */
#define USB_HCINT_XFRC							0x00000001U
#define USB_HCINT_CHH							0x00000002U
#define USB_HCINT_AHBERR						0x00000004U
#define USB_HCINT_STALL							0x00000008U
#define USB_HCINT_NAK							0x00000010U
#define USB_HCINT_ACK							0x00000020U
#define USB_HCINT_TXERR							0x00000080U
#define USB_HCINT_BBERR							0x00000100U
#define USB_HCINT_FRMOR							0x00000200U
#define USB_HCINT_DTERR							0x00000400U

/*	Bit definition for USB_HCINTMSK register */
#define USB_HCINTMSK_XFRCM						0x00000001U
#define USB_HCINTMSK_CHHM						0x00000002U
#define USB_HCINTMSK_AHBERR						0x00000004U
#define USB_HCINTMSK_STALLM						0x00000008U
#define USB_HCINTMSK_NAKM						0x00000010U
#define USB_HCINTMSK_ACKM						0x00000020U
#define USB_HCINTMSK_NYET						0x00000040U
#define USB_HCINTMSK_TXERRM						0x00000080U
#define USB_HCINTMSK_BBERRM						0x00000100U
#define USB_HCINTMSK_FRMORM						0x00000200U
#define USB_HCINTMSK_DTERRM						0x00000400U

/*	Bit definition for USB_HCTSIZ register	*/
#define USB_HCTSIZ_XFRSIZ						0x0007FFFFU
#define USB_HCTSIZ_PKTCNT						0x1FF80000U
#define USB_HCTSIZ_DPID							0x60000000U
#define USB_HCTSIZ_DPID_0						0x20000000U
#define USB_HCTSIZ_DPID_1						0x40000000U

#endif /* STM32L476_USB_H_ */

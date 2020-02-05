/**
 * @file opamp.h
 * 
 * @date 2020-02-04
 * @author twatorowski 
 * 
 * @brief STM32 Defines: OPAMP
 */

#ifndef STM32L476_OPAMP_H_
#define STM32L476_OPAMP_H_

#include "stm32l476/stm32l476.h"

/* register base address */
#define OPAMP1_BASE             			(0x40007800)
#define OPAMP2_BASE             			(0x40007810)

/* register base */
#define OPAMP1								((opamp_t *)OPAMP1_BASE)
#define OPAMP2								((opamp_t *)OPAMP2_BASE)

/* registers */
typedef struct {
	reg32_t CSR;
	reg32_t OTR;
	reg32_t LPOTR;
} __attribute__((packed, aligned(4))) opamp_t;

/*  Bit definition for OPAMPx_CSR register  */
#define OPAMP_CSR_OPAEN            			(0x00000001)
#define OPAMP_CSR_OPALPM              		(0x00000002)
#define OPAMP_CSR_OPAMODE             		(0x0000000C)
#define OPAMP_CSR_OPAMODE_0           		(0x00000004)
#define OPAMP_CSR_OPAMODE_1           		(0x00000008)
#define OPAMP_CSR_PGGAIN             		(0x00000030)
#define OPAMP_CSR_PGGAIN_0           		(0x00000010)
#define OPAMP_CSR_PGGAIN_1           		(0x00000020)
#define OPAMP_CSR_VMSEL               		(0x00000300)
#define OPAMP_CSR_VMSEL_0             		(0x00000100)
#define OPAMP_CSR_VMSEL_1             		(0x00000200)
#define OPAMP_CSR_VPSEL               		(0x00000400)
#define OPAMP_CSR_CALON               		(0x00001000)
#define OPAMP_CSR_CALSEL              		(0x00002000)
#define OPAMP_CSR_USERTRIM            		(0x00004000)
#define OPAMP_CSR_CALOUT              		(0x00008000)
#define OPAMP_CSR_OPARANGE					(0x80000000)

/*  Bit definition for OPAMP_OTR register  */
#define OPAMP_OTR_TRIMOFFSETN            	(0x0000001F)
#define OPAMP_OTR_TRIMOFFSETP            	(0x00001F00)

/*  Bit definition for OPAMP_LPOTR register  */
#define OPAMP_LPOTR_TRIMLPOFFSETN        	(0x0000001F)
#define OPAMP_LPOTR_TRIMLPOFFSETP        	(0x00001F00)

#endif /* STM32L476_OPAMP_H_ */
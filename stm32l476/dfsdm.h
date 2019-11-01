/**
 * @file dfsdm.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: DFSDM
 */

#ifndef STM32L476_DFSDM_H_
#define STM32L476_DFSDM_H_

#include "stm32l476/stm32l476.h"

/* dac register base */
#define DFSDM_BASE							(0x40016000)
#define DFSDM_CH0_BASE						(DFSDM_BASE + 0x00)
#define DFSDM_CH1_BASE						(DFSDM_BASE + 0x20)
#define DFSDM_CH2_BASE						(DFSDM_BASE + 0x40)
#define DFSDM_CH3_BASE						(DFSDM_BASE + 0x60)
#define DFSDM_CH4_BASE						(DFSDM_BASE + 0x80)
#define DFSDM_CH5_BASE						(DFSDM_BASE + 0xA0)
#define DFSDM_CH6_BASE						(DFSDM_BASE + 0xC0)
#define DFSDM_CH7_BASE						(DFSDM_BASE + 0xE0)
#define DFSDM_FLT0_BASE					(DFSDM_BASE + 0x100)
#define DFSDM_FLT1_BASE					(DFSDM_BASE + 0x180)
#define DFSDM_FLT2_BASE					(DFSDM_BASE + 0x200)
#define DFSDM_FLT3_BASE					(DFSDM_BASE + 0x280)

/* channel registers base address */
#define DFSDMC0								((dfsdm_chan_t *)DFSDM_CH0_BASE)
#define DFSDMC1								((dfsdm_chan_t *)DFSDM_CH1_BASE)
#define DFSDMC2								((dfsdm_chan_t *)DFSDM_CH2_BASE)
#define DFSDMC3								((dfsdm_chan_t *)DFSDM_CH3_BASE)
#define DFSDMC4								((dfsdm_chan_t *)DFSDM_CH4_BASE)
#define DFSDMC5								((dfsdm_chan_t *)DFSDM_CH5_BASE)
#define DFSDMC6								((dfsdm_chan_t *)DFSDM_CH6_BASE)
#define DFSDMC7								((dfsdm_chan_t *)DFSDM_CH7_BASE)
/* filter */
#define DFSDMF0								((dfsdm_flt_t *)DFSDM_FLT0_BASE)
#define DFSDMF1								((dfsdm_flt_t *)DFSDM_FLT1_BASE)
#define DFSDMF2								((dfsdm_flt_t *)DFSDM_FLT2_BASE)
#define DFSDMF3								((dfsdm_flt_t *)DFSDM_FLT3_BASE)

/* DFSDM module registers */
typedef struct {
	reg32_t CR1;
	reg32_t CR2;
	reg32_t ISR;
	reg32_t ICR;
	reg32_t JCHGR;
	reg32_t FCR;
	reg32_t JDATAR;
	reg32_t RDATAR;
	reg32_t AWHTR;
	reg32_t AWLTR;
	reg32_t AWSR;
	reg32_t AWCFR;
	reg32_t EXMAX;
	reg32_t EXMIN;
	reg32_t CNVTIMR;
} __attribute__((packed, aligned(4))) dfsdm_flt_t;

/*	Bit definition for DFSDM_CR1 register */
#define DFSDM_CR1_AWFSEL					(0x40000000)
#define DFSDM_CR1_FAST						(0x20000000)
#define DFSDM_CR1_RCH						(0x07000000)
#define DFSDM_CR1_RDMAEN					(0x00200000)
#define DFSDM_CR1_RSYNC						(0x00080000)
#define DFSDM_CR1_RCONT						(0x00040000)
#define DFSDM_CR1_RSWSTART					(0x00020000)
#define DFSDM_CR1_JEXTEN					(0x00006000)
#define DFSDM_CR1_JEXTEN_1					(0x00004000)
#define DFSDM_CR1_JEXTEN_0					(0x00002000)
#define DFSDM_CR1_JEXTSEL					(0x00000700)
#define DFSDM_CR1_JEXTSEL_2					(0x00000400)
#define DFSDM_CR1_JEXTSEL_1					(0x00000200)
#define DFSDM_CR1_JEXTSEL_0					(0x00000100)
#define DFSDM_CR1_JDMAEN					(0x00000020)
#define DFSDM_CR1_JSCAN						(0x00000010)
#define DFSDM_CR1_JSYNC						(0x00000008)
#define DFSDM_CR1_JSWSTART					(0x00000002)
#define DFSDM_CR1_DFEN						(0x00000001)

/*	Bit definition for DFSDM_CR2 register */
#define DFSDM_CR2_AWDCH						(0x00FF0000)
#define DFSDM_CR2_EXCH						(0x0000FF00)
#define DFSDM_CR2_CKABIE					(0x00000040)
#define DFSDM_CR2_SCDIE						(0x00000020)
#define DFSDM_CR2_AWDIE						(0x00000010)
#define DFSDM_CR2_ROVRIE					(0x00000008)
#define DFSDM_CR2_JOVRIE					(0x00000004)
#define DFSDM_CR2_REOCIE					(0x00000002)
#define DFSDM_CR2_JEOCIE					(0x00000001)

/*	Bit definition for DFSDM_ISR register */
#define DFSDM_ISR_SCDF						(0xFF000000)
#define DFSDM_ISR_CKABF						(0x00FF0000)
#define DFSDM_ISR_RCIP						(0x00004000)
#define DFSDM_ISR_JCIP						(0x00002000)
#define DFSDM_ISR_AWDF						(0x00000010)
#define DFSDM_ISR_ROVRF						(0x00000008)
#define DFSDM_ISR_JOVRF						(0x00000004)
#define DFSDM_ISR_REOCF						(0x00000002)
#define DFSDM_ISR_JEOCF						(0x00000001)

/*	Bit definition for DFSDM_ICR register */
#define DFSDM_ICR_CLRSCSDF					(0xFF000000)
#define DFSDM_ICR_CLRCKABF					(0x00FF0000)
#define DFSDM_ICR_CLRROVRF					(0x00000008)
#define DFSDM_ICR_CLRJOVRF					(0x00000004)

/*	Bit definition for DFSDM_JCHGR register */
#define DFSDM_JCHGR_JCHG					(0x000000FF)

/*	Bit definition for DFSDM_FCR register */
#define DFSDM_FCR_FORD						(0xE0000000)
#define DFSDM_FCR_FORD_2					(0x80000000)
#define DFSDM_FCR_FORD_1					(0x40000000)
#define DFSDM_FCR_FORD_0					(0x20000000)
#define DFSDM_FCR_FOSR						(0x03FF0000)
#define DFSDM_FCR_IOSR						(0x000000FF)

/*	Bit definition for DFSDM_JDATAR register */
#define DFSDM_JDATAR_JDATA					(0xFFFFFF00)
#define DFSDM_JDATAR_JDATACH				(0x00000007)

/*	Bit definition for DFSDM_RDATAR register */
#define DFSDM_RDATAR_RDATA					(0xFFFFFF00)
#define DFSDM_RDATAR_RPEND					(0x00000010)
#define DFSDM_RDATAR_RDATACH				(0x00000007)

/*	Bit definition for DFSDM_AWHTR register */
#define DFSDM_AWHTR_AWHT					(0xFFFFFF00)
#define DFSDM_AWHTR_BKAWH					(0x0000000F)

/*	Bit definition for DFSDM_AWLTR register */
#define DFSDM_AWLTR_AWLT					(0xFFFFFF00)
#define DFSDM_AWLTR_BKAWL					(0x0000000F)

/*	Bit definition for DFSDM_AWSR register */
#define DFSDM_AWSR_AWHTF					(0x0000FF00)
#define DFSDM_AWSR_AWLTF					(0x000000FF)

/*	Bit definition for DFSDM_AWCFR) register */
#define DFSDM_AWCFR_CLRAWHTF				(0x0000FF00)
#define DFSDM_AWCFR_CLRAWLTF				(0x000000FF)

/*	Bit definition for DFSDM_EXMAX register */
#define DFSDM_EXMAX_EXMAX					(0xFFFFFF00)
#define DFSDM_EXMAX_EXMAXCH					(0x00000007)

/*	Bit definition for DFSDM_EXMIN register */
#define DFSDM_EXMIN_EXMIN					(0xFFFFFF00)
#define DFSDM_EXMIN_EXMINCH					(0x00000007)

/*	Bit definition for DFSDM_EXMIN register */
#define DFSDM_CNVTIMR_CNVCNT				(0xFFFFFFF0)


/* DFSDM channel configuration registers */
typedef struct {
	reg32_t CHCFGR1;
	reg32_t CHCFGR2;
	reg32_t AWSCDR;
	reg32_t CHWDATAR;
	reg32_t CHDATINR;
} dfsdm_chan_t;

/*	Bit definition for DFSDM_CHCFGR1 register  */
#define DFSDM_CHCFGR1_DFSDMEN				(0x80000000)
#define DFSDM_CHCFGR1_CKOUTSRC				(0x40000000)
#define DFSDM_CHCFGR1_CKOUTDIV				(0x00FF0000)
#define DFSDM_CHCFGR1_DATPACK				(0x0000C000)
#define DFSDM_CHCFGR1_DATPACK_1				(0x00008000)
#define DFSDM_CHCFGR1_DATPACK_0				(0x00004000)
#define DFSDM_CHCFGR1_DATMPX				(0x00003000)
#define DFSDM_CHCFGR1_DATMPX_1				(0x00002000)
#define DFSDM_CHCFGR1_DATMPX_0				(0x00001000)
#define DFSDM_CHCFGR1_CHINSEL				(0x00000100)
#define DFSDM_CHCFGR1_CHEN					(0x00000080)
#define DFSDM_CHCFGR1_CKABEN				(0x00000040)
#define DFSDM_CHCFGR1_SCDEN					(0x00000020)
#define DFSDM_CHCFGR1_SPICKSEL				(0x0000000C)
#define DFSDM_CHCFGR1_SPICKSEL_1			(0x00000008)
#define DFSDM_CHCFGR1_SPICKSEL_0			(0x00000004)
#define DFSDM_CHCFGR1_SITP					(0x00000003)
#define DFSDM_CHCFGR1_SITP_1				(0x00000002)
#define DFSDM_CHCFGR1_SITP_0				(0x00000001)

/*	Bit definition for DFSDM_CHCFGR2 register  */
#define DFSDM_CHCFGR2_OFFSET				(0xFFFFFF00)
#define DFSDM_CHCFGR2_DTRBS					(0x000000F8)

/*	Bit definition for DFSDM_AWSCDR register */
#define DFSDM_AWSCDR_AWFORD					(0x00C00000)
#define DFSDM_AWSCDR_AWFORD_1				(0x00800000)
#define DFSDM_AWSCDR_AWFORD_0				(0x00400000)
#define DFSDM_AWSCDR_AWFOSR					(0x001F0000)
#define DFSDM_AWSCDR_BKSCD					(0x0000F000)
#define DFSDM_AWSCDR_SCDT					(0x000000FF)

/*	Bit definition for DFSDM_CHWDATR register */
#define DFSDM_CHWDATR_WDATA					(0x0000FFFF)

/*	Bit definition for DFSDM_CHDATINR register */
#define DFSDM_CHDATINR_INDAT0				(0x0000FFFF)
#define DFSDM_CHDATINR_INDAT1				(0xFFFF0000)


#endif /* STM32L476_DFSDM_H_ */

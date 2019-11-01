/**
 * @file dac.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: DAC
 */

#ifndef STM32L476_DAC_H_
#define STM32L476_DAC_H_

#include "stm32l476/stm32l476.h"

/* dac register base */
#define DAC_BASE							(0x40007400)
/* dac registers base address */
#define DAC									((dac_t *)DAC_BASE)

/* dar registers */
typedef struct {
	reg32_t CR;
	reg32_t SWTRIGR;
	reg32_t DHR12R1;
	reg32_t DHR12L1;
	reg32_t DHR8R1;
	reg32_t DHR12R2;
	reg32_t DHR12L2;
	reg32_t DHR8R2;
	reg32_t DHR12RD;
	reg32_t DHR12LD;
	reg32_t DHR8RD;
	reg32_t DOR1;
	reg32_t DOR2;
	reg32_t SR;
	reg32_t CCR;
	reg32_t MCR;
	reg32_t SHSR1;
	reg32_t SHSR2;
	reg32_t SHHR;
	reg32_t SHRR;
} __attribute__((packed, aligned(4))) dac_t;

/*	Bit definition for DAC_CR register	*/
#define DAC_CR_EN1							(0x00000001)
#define DAC_CR_TEN1							(0x00000004)
#define DAC_CR_TSEL1						(0x00000038)
#define DAC_CR_TSEL1_0						(0x00000008)
#define DAC_CR_TSEL1_1						(0x00000010)
#define DAC_CR_TSEL1_2						(0x00000020)
#define DAC_CR_WAVE1						(0x000000C0)
#define DAC_CR_WAVE1_0						(0x00000040)
#define DAC_CR_WAVE1_1						(0x00000080)
#define DAC_CR_MAMP1						(0x00000F00)
#define DAC_CR_MAMP1_0						(0x00000100)
#define DAC_CR_MAMP1_1						(0x00000200)
#define DAC_CR_MAMP1_2						(0x00000400)
#define DAC_CR_MAMP1_3						(0x00000800)
#define DAC_CR_DMAEN1						(0x00001000)
#define DAC_CR_DMAUDRIE1					(0x00002000)
#define DAC_CR_CEN1							(0x00004000)
#define DAC_CR_EN2							(0x00010000)
#define DAC_CR_TEN2							(0x00040000)
#define DAC_CR_TSEL2						(0x00380000)
#define DAC_CR_TSEL2_0						(0x00080000)
#define DAC_CR_TSEL2_1						(0x00100000)
#define DAC_CR_TSEL2_2						(0x00200000)
#define DAC_CR_WAVE2						(0x00C00000)
#define DAC_CR_WAVE2_0						(0x00400000)
#define DAC_CR_WAVE2_1						(0x00800000)
#define DAC_CR_MAMP2						(0x0F000000)
#define DAC_CR_MAMP2_0						(0x01000000)
#define DAC_CR_MAMP2_1						(0x02000000)
#define DAC_CR_MAMP2_2						(0x04000000)
#define DAC_CR_MAMP2_3						(0x08000000)
#define DAC_CR_DMAEN2						(0x10000000)
#define DAC_CR_DMAUDRIE2					(0x20000000)
#define DAC_CR_CEN2							(0x40000000)

/*	Bit definition for DAC_SWTRIGR register  */
#define DAC_SWTRIGR_SWTRIG1					(0x00000001)
#define DAC_SWTRIGR_SWTRIG2					(0x00000002)

/*	Bit definition for DAC_DHR12R1 register  */
#define DAC_DHR12R1_DACC1DHR				(0x00000FFF)

/*	Bit definition for DAC_DHR12L1 register  */
#define DAC_DHR12L1_DACC1DHR				(0x0000FFF0)

/*	Bit definition for DAC_DHR8R1 register	*/
#define DAC_DHR8R1_DACC1DHR					(0x000000FF)

/*	Bit definition for DAC_DHR12R2 register  */
#define DAC_DHR12R2_DACC2DHR				(0x00000FFF)

/*	Bit definition for DAC_DHR12L2 register  */
#define DAC_DHR12L2_DACC2DHR				(0x0000FFF0)

/*	Bit definition for DAC_DHR8R2 register	*/
#define DAC_DHR8R2_DACC2DHR					(0x000000FF)

/*	Bit definition for DAC_DHR12RD register  */
#define DAC_DHR12RD_DACC1DHR				(0x00000FFF)
#define DAC_DHR12RD_DACC2DHR				(0x0FFF0000)

/*	Bit definition for DAC_DHR12LD register  */
#define DAC_DHR12LD_DACC1DHR				(0x0000FFF0)
#define DAC_DHR12LD_DACC2DHR				(0xFFF00000)

/*	Bit definition for DAC_DHR8RD register	*/
#define DAC_DHR8RD_DACC1DHR					(0x000000FF)
#define DAC_DHR8RD_DACC2DHR					(0x0000FF00)

/*	Bit definition for DAC_DOR1 register  */
#define DAC_DOR1_DACC1DOR					(0x00000FFF)

/*	Bit definition for DAC_DOR2 register  */
#define DAC_DOR2_DACC2DOR					(0x00000FFF)

/*	Bit definition for DAC_SR register	*/
#define DAC_SR_DMAUDR1						(0x00002000)
#define DAC_SR_CAL_FLAG1					(0x00004000)
#define DAC_SR_BWST1						(0x20008000)

#define DAC_SR_DMAUDR2						(0x20000000)
#define DAC_SR_CAL_FLAG2					(0x40000000)
#define DAC_SR_BWST2						(0x80000000)

/*	Bit definition for DAC_CCR register  */
#define DAC_CCR_OTRIM1						(0x0000001F)
#define DAC_CCR_OTRIM2						(0x001F0000)

/*	Bit definition for DAC_MCR register  */
#define DAC_MCR_MODE1						(0x00000007)
#define DAC_MCR_MODE1_0						(0x00000001)
#define DAC_MCR_MODE1_1						(0x00000002)
#define DAC_MCR_MODE1_2						(0x00000004)
#define DAC_MCR_MODE2						(0x00070000)
#define DAC_MCR_MODE2_0						(0x00010000)
#define DAC_MCR_MODE2_1						(0x00020000)
#define DAC_MCR_MODE2_2						(0x00040000)

/*	Bit definition for DAC_SHSR1 register  */
#define DAC_SHSR1_TSAMPLE1					(0x000003FF)

/*	Bit definition for DAC_SHSR2 register  */
#define DAC_SHSR2_TSAMPLE2					(0x000003FF)

/*	Bit definition for DAC_SHHR register  */
#define DAC_SHHR_THOLD1						(0x000003FF)
#define DAC_SHHR_THOLD2						(0x03FF0000)

/*	Bit definition for DAC_SHRR register  */
#define DAC_SHRR_TREFRESH1					(0x000000FF)
#define DAC_SHRR_TREFRESH2					(0x00FF0000)

#endif /* STM32L476_DAC_H_ */

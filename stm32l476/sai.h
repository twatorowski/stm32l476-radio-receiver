/**
 * @file sai.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: SAI
 */

#ifndef STM32L476_SAI_H_
#define STM32L476_SAI_H_

#include "stm32l476/stm32l476.h"

/* sai1 register base */
#define SAI1_BASE							(0x40015400)
#define SAI1A_BASE							(SAI1_BASE + 0x04)
#define SAI1B_BASE							(SAI1_BASE + 0x24)
/* sai2 register base */
#define SAI2_BASE							(0x40015800)
#define SAI2A_BASE							(SAI2_BASE + 0x04)
#define SAI2B_BASE							(SAI2_BASE + 0x24)

/* register banks */
#define SAI1								((sai_t *)SAI1_BASE)
#define SAI1A								((sai_block_t *)SAI1A_BASE)
#define SAI1B								((sai_block_t *)SAI1B_BASE)
#define SAI2								((sai_t *)SAI2_BASE)
#define SAI2A								((sai_block_t *)SAI2A_BASE)
#define SAI2B								((sai_block_t *)SAI2B_BASE)

/* sai global registers */
typedef struct {
	reg32_t GCR;
} __attribute__((packed, aligned(4))) sai_t;

/*	Bit definition for SAI_GCR register  */
#define SAI_GCR_SYNCIN						(0x00000003)
#define SAI_GCR_SYNCIN_0					(0x00000001)
#define SAI_GCR_SYNCIN_1					(0x00000002)
#define SAI_GCR_SYNCOUT						(0x00000030)
#define SAI_GCR_SYNCOUT_0					(0x00000010)
#define SAI_GCR_SYNCOUT_1					(0x00000020)

/* sai block registers */
typedef struct {
	reg32_t CR1;
	reg32_t CR2;
	reg32_t FRCR;
	reg32_t SLOTR;
	reg32_t IMR;
	reg32_t SR;
	reg32_t CLRFR;
	reg32_t DR;
} __attribute__((packed, aligned(4))) sai_block_t;

/*	Bit definition for SAI_CR1 register  */
#define SAI_CR1_MODE						(0x00000003)
#define SAI_CR1_MODE_0						(0x00000001)
#define SAI_CR1_MODE_1						(0x00000002)
#define SAI_CR1_PRTCFG						(0x0000000C)
#define SAI_CR1_PRTCFG_0					(0x00000004)
#define SAI_CR1_PRTCFG_1					(0x00000008)
#define SAI_CR1_DS							(0x000000E0)
#define SAI_CR1_DS_0						(0x00000020)
#define SAI_CR1_DS_1						(0x00000040)
#define SAI_CR1_DS_2						(0x00000080)
#define SAI_CR1_LSBFIRST					(0x00000100)
#define SAI_CR1_CKSTR						(0x00000200)
#define SAI_CR1_SYNCEN						(0x00000C00)
#define SAI_CR1_SYNCEN_0					(0x00000400)
#define SAI_CR1_SYNCEN_1					(0x00000800)
#define SAI_CR1_MONO						(0x00001000)
#define SAI_CR1_OUTDRIV						(0x00002000)
#define SAI_CR1_SAIEN						(0x00010000)
#define SAI_CR1_DMAEN						(0x00020000)
#define SAI_CR1_NODIV						(0x00080000)
#define SAI_CR1_MCKDIV						(0x00F00000)
#define SAI_CR1_MCKDIV_0					(0x00100000)
#define SAI_CR1_MCKDIV_1					(0x00200000)
#define SAI_CR1_MCKDIV_2					(0x00400000)
#define SAI_CR1_MCKDIV_3					(0x00800000)

/*	Bit definition for SAI_CR2 register  */
#define SAI_CR2_FTH							(0x00000007)
#define SAI_CR2_FTH_0						(0x00000001)
#define SAI_CR2_FTH_1						(0x00000002)
#define SAI_CR2_FTH_2						(0x00000004)
#define SAI_CR2_FFLUSH						(0x00000008)
#define SAI_CR2_TRIS						(0x00000010)
#define SAI_CR2_MUTE						(0x00000020)
#define SAI_CR2_MUTEVAL						(0x00000040)
#define SAI_CR2_MUTECNT						(0x00001F80)
#define SAI_CR2_MUTECNT_0					(0x00000080)
#define SAI_CR2_MUTECNT_1					(0x00000100)
#define SAI_CR2_MUTECNT_2					(0x00000200)
#define SAI_CR2_MUTECNT_3					(0x00000400)
#define SAI_CR2_MUTECNT_4					(0x00000800)
#define SAI_CR2_MUTECNT_5					(0x00001000)
#define SAI_CR2_CPL							(0x00002000)
#define SAI_CR2_COMP						(0x0000C000)
#define SAI_CR2_COMP_0						(0x00004000)
#define SAI_CR2_COMP_1						(0x00008000)

/*	Bit definition for SAI_FRCR register  */
#define SAI_FRCR_FRL						(0x000000FF)
#define SAI_FRCR_FRL_0						(0x00000001)
#define SAI_FRCR_FRL_1						(0x00000002)
#define SAI_FRCR_FRL_2						(0x00000004)
#define SAI_FRCR_FRL_3						(0x00000008)
#define SAI_FRCR_FRL_4						(0x00000010)
#define SAI_FRCR_FRL_5						(0x00000020)
#define SAI_FRCR_FRL_6						(0x00000040)
#define SAI_FRCR_FRL_7						(0x00000080)
#define SAI_FRCR_FSALL						(0x00007F00)
#define SAI_FRCR_FSALL_0					(0x00000100)
#define SAI_FRCR_FSALL_1					(0x00000200)
#define SAI_FRCR_FSALL_2					(0x00000400)
#define SAI_FRCR_FSALL_3					(0x00000800)
#define SAI_FRCR_FSALL_4					(0x00001000)
#define SAI_FRCR_FSALL_5					(0x00002000)
#define SAI_FRCR_FSALL_6					(0x00004000)
#define SAI_FRCR_FSDEF						(0x00010000)
#define SAI_FRCR_FSPOL						(0x00020000)
#define SAI_FRCR_FSOFF						(0x00040000)

/*	Bit definition for SAI_SLOTR register  */
#define SAI_SLOTR_FBOFF						(0x0000001F)
#define SAI_SLOTR_FBOFF_0					(0x00000001)
#define SAI_SLOTR_FBOFF_1					(0x00000002)
#define SAI_SLOTR_FBOFF_2					(0x00000004)
#define SAI_SLOTR_FBOFF_3					(0x00000008)
#define SAI_SLOTR_FBOFF_4					(0x00000010)
#define SAI_SLOTR_SLOTSZ					(0x000000C0)
#define SAI_SLOTR_SLOTSZ_0					(0x00000040)
#define SAI_SLOTR_SLOTSZ_1					(0x00000080)
#define SAI_SLOTR_NBSLOT					(0x00000F00)
#define SAI_SLOTR_NBSLOT_0					(0x00000100)
#define SAI_SLOTR_NBSLOT_1					(0x00000200)
#define SAI_SLOTR_NBSLOT_2					(0x00000400)
#define SAI_SLOTR_NBSLOT_3					(0x00000800)

#define SAI_SLOTR_SLOTEN					(0xFFFF0000)
#define SAI_SLOTR_SLOTEN_0					(0x00010000)
#define SAI_SLOTR_SLOTEN_1					(0x00020000)
#define SAI_SLOTR_SLOTEN_2					(0x00040000)
#define SAI_SLOTR_SLOTEN_3					(0x00080000)
#define SAI_SLOTR_SLOTEN_4					(0x00100000)
#define SAI_SLOTR_SLOTEN_5					(0x00200000)
#define SAI_SLOTR_SLOTEN_6					(0x00400000)
#define SAI_SLOTR_SLOTEN_7					(0x00800000)
#define SAI_SLOTR_SLOTEN_8					(0x01000000)
#define SAI_SLOTR_SLOTEN_9					(0x02000000)
#define SAI_SLOTR_SLOTEN_10					(0x04000000)
#define SAI_SLOTR_SLOTEN_11					(0x08000000)
#define SAI_SLOTR_SLOTEN_12					(0x10000000)
#define SAI_SLOTR_SLOTEN_13					(0x20000000)
#define SAI_SLOTR_SLOTEN_14					(0x40000000)
#define SAI_SLOTR_SLOTEN_15					(0x80000000)

/*	Bit definition for SAI_IMR register  */
#define SAI_IMR_OVRUDRIE					(0x00000001)
#define SAI_IMR_MUTEDETIE					(0x00000002)
#define SAI_IMR_WCKCFGIE					(0x00000004)
#define SAI_IMR_FREQIE						(0x00000008)
#define SAI_IMR_CNRDYIE						(0x00000010)
#define SAI_IMR_AFSDETIE					(0x00000020)
#define SAI_IMR_LFSDETIE					(0x00000040)

/*	Bit definition for SAI_SR register	*/
#define SAI_SR_OVRUDR						(0x00000001)
#define SAI_SR_MUTEDET						(0x00000002)
#define SAI_SR_WCKCFG						(0x00000004)
#define SAI_SR_FREQ							(0x00000008)
#define SAI_SR_CNRDY						(0x00000010)
#define SAI_SR_AFSDET						(0x00000020)
#define SAI_SR_LFSDET						(0x00000040)
#define SAI_SR_FLVL							(0x00070000)
#define SAI_SR_FLVL_0						(0x00010000)
#define SAI_SR_FLVL_1						(0x00020000)
#define SAI_SR_FLVL_2						(0x00040000)

/*	Bit definition for SAI_CLRFR register  */
#define SAI_CLRFR_COVRUDR					(0x00000001)
#define SAI_CLRFR_CMUTEDET					(0x00000002)
#define SAI_CLRFR_CWCKCFG					(0x00000004)
#define SAI_CLRFR_CFREQ						(0x00000008)
#define SAI_CLRFR_CCNRDY					(0x00000010)
#define SAI_CLRFR_CAFSDET					(0x00000020)
#define SAI_CLRFR_CLFSDET					(0x00000040)

/*	Bit definition for SAI_DR register	*/
#define SAI_DR_DATA							(0xFFFFFFFF)


#endif /* STM32L476_SAI_H_ */

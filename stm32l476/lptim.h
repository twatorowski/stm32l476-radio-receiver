/**
 * @file lptim.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: LPTIM
 */

#ifndef STM32L476_LPTIM_H_
#define STM32L476_LPTIM_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define LPTIM1_BASE							(0x40007C00)
#define LPTIM2_BASE							(0x40009400)
/* registers */
#define LPTIM1								((lptim_t *) LPTIM1_BASE)
#define LPTIM2								((lptim_t *) LPTIM2_BASE)

/* registers */
typedef struct {
	reg32_t ISR;
	reg32_t ICR;
	reg32_t IER;
	reg32_t CFGR;
	reg32_t CR;
	reg32_t CMP;
	reg32_t ARR;
	reg32_t CNT;
	reg32_t OR;
} __attribute__((packed, aligned(4))) lptim_t;

/*	Bit definition for LPTIM_ISR register  */
#define LPTIM_ISR_CMPM						(0x00000001)
#define LPTIM_ISR_ARRM						(0x00000002)
#define LPTIM_ISR_EXTTRIG					(0x00000004)
#define LPTIM_ISR_CMPOK						(0x00000008)
#define LPTIM_ISR_ARROK						(0x00000010)
#define LPTIM_ISR_UP						(0x00000020)
#define LPTIM_ISR_DOWN						(0x00000040)

/*	Bit definition for LPTIM_ICR register  */
#define LPTIM_ICR_CMPMCF					(0x00000001)
#define LPTIM_ICR_ARRMCF					(0x00000002)
#define LPTIM_ICR_EXTTRIGCF					(0x00000004)
#define LPTIM_ICR_CMPOKCF					(0x00000008)
#define LPTIM_ICR_ARROKCF					(0x00000010)
#define LPTIM_ICR_UPCF						(0x00000020)
#define LPTIM_ICR_DOWNCF					(0x00000040)

/*	Bit definition for LPTIM_IER register */
#define LPTIM_IER_CMPMIE					(0x00000001)
#define LPTIM_IER_ARRMIE					(0x00000002)
#define LPTIM_IER_EXTTRIGIE					(0x00000004)
#define LPTIM_IER_CMPOKIE					(0x00000008)
#define LPTIM_IER_ARROKIE					(0x00000010)
#define LPTIM_IER_UPIE						(0x00000020)
#define LPTIM_IER_DOWNIE					(0x00000040)

/*	Bit definition for LPTIM_CFGR register */
#define LPTIM_CFGR_CKSEL					(0x00000001)
#define LPTIM_CFGR_CKPOL					(0x00000006)
#define LPTIM_CFGR_CKPOL_0					(0x00000002)
#define LPTIM_CFGR_CKPOL_1					(0x00000004)
#define LPTIM_CFGR_CKFLT					(0x00000018)
#define LPTIM_CFGR_CKFLT_0					(0x00000008)
#define LPTIM_CFGR_CKFLT_1					(0x00000010)
#define LPTIM_CFGR_TRGFLT					(0x000000C0)
#define LPTIM_CFGR_TRGFLT_0					(0x00000040)
#define LPTIM_CFGR_TRGFLT_1					(0x00000080)
#define LPTIM_CFGR_PRESC					(0x00000E00)
#define LPTIM_CFGR_PRESC_0					(0x00000200)
#define LPTIM_CFGR_PRESC_1					(0x00000400)
#define LPTIM_CFGR_PRESC_2					(0x00000800)
#define LPTIM_CFGR_TRIGSEL					(0x0000E000)
#define LPTIM_CFGR_TRIGSEL_0				(0x00002000)
#define LPTIM_CFGR_TRIGSEL_1				(0x00004000)
#define LPTIM_CFGR_TRIGSEL_2				(0x00008000)
#define LPTIM_CFGR_TRIGEN					(0x00060000)
#define LPTIM_CFGR_TRIGEN_0					(0x00020000)
#define LPTIM_CFGR_TRIGEN_1					(0x00040000)
#define LPTIM_CFGR_TIMOUT					(0x00080000)
#define LPTIM_CFGR_WAVE						(0x00100000)
#define LPTIM_CFGR_WAVPOL					(0x00200000)
#define LPTIM_CFGR_PRELOAD					(0x00400000)
#define LPTIM_CFGR_COUNTMODE				(0x00800000)
#define LPTIM_CFGR_ENC						(0x01000000)

/*	Bit definition for LPTIM_CR register  */
#define LPTIM_CR_ENABLE						(0x00000001)
#define LPTIM_CR_SNGSTRT					(0x00000002)
#define LPTIM_CR_CNTSTRT					(0x00000004)

/*	Bit definition for LPTIM_CMP register  */
#define LPTIM_CMP_CMP						(0x0000FFFF)

/*	Bit definition for LPTIM_ARR register  */
#define LPTIM_ARR_ARR						(0x0000FFFF)

/*	Bit definition for LPTIM_CNT register  */
#define LPTIM_CNT_CNT						(0x0000FFFF)

/*	Bit definition for LPTIM_OR register  */
#define LPTIM_OR_OR							(0x00000003)
#define LPTIM_OR_OR_0						(0x00000001)
#define LPTIM_OR_OR_1						(0x00000002)

#endif /* STM32L476_LPTIM_H_ */

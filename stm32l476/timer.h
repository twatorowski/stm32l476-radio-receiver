/**
 * @file timer.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: TIMER
 */

#ifndef STM32L476_TIMER_H_
#define STM32L476_TIMER_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define TIM1_BASE						0x40012C00
#define TIM2_BASE						0x40000000
#define TIM3_BASE						0x40000400
#define TIM4_BASE						0x40000800
#define TIM5_BASE						0x40000C00
#define TIM6_BASE						0x40001000
#define TIM7_BASE						0x40001400
#define TIM8_BASE						0x40013400
#define TIM15_BASE						0x40014000
#define TIM16_BASE						0x40014400
#define TIM17_BASE						0x40014800

/* timers */
#define TIM1							((tim_t *)TIM1_BASE)
#define TIM2							((tim_t *)TIM2_BASE)
#define TIM3							((tim_t *)TIM3_BASE)
#define TIM4							((tim_t *)TIM4_BASE)
#define TIM5							((tim_t *)TIM5_BASE)
#define TIM6							((tim_t *)TIM6_BASE)
#define TIM7							((tim_t *)TIM7_BASE)
#define TIM8							((tim_t *)TIM8_BASE)
#define TIM15							((tim_t *)TIM15_BASE)
#define TIM16							((tim_t *)TIM16_BASE)
#define TIM17							((tim_t *)TIM17_BASE)

/* timer */
typedef struct {
	reg32_t CR1;
	reg32_t CR2;
	reg32_t SMCR;
	reg32_t DIER;
	reg32_t SR;
	reg32_t EGR;
	reg32_t CCMR1;
	reg32_t CCMR2;
	reg32_t CCER;
	reg32_t CNT;
	reg32_t PSC;
	reg32_t ARR;
	reg32_t RCR;
	reg32_t CCR1;
	reg32_t CCR2;
	reg32_t CCR3;
	reg32_t CCR4;
	reg32_t BDTR;
	reg32_t DCR;
	reg32_t DMAR;
	reg32_t OR1;
	reg32_t CCMR3;
	reg32_t CCR5;
	reg32_t CCR6;
	reg32_t OR2;
	reg32_t OR3;
} __attribute__((packed, aligned(4))) tim_t;

/*	Bit definition for TIM_CR1 register  */
#define TIM_CR1_CEN						(0x00000001)
#define TIM_CR1_UDIS					(0x00000002)
#define TIM_CR1_URS						(0x00000004)
#define TIM_CR1_OPM						(0x00000008)
#define TIM_CR1_DIR						(0x00000010)
#define TIM_CR1_CMS						(0x00000060)
#define TIM_CR1_CMS_0					(0x00000020)
#define TIM_CR1_CMS_1					(0x00000040)
#define TIM_CR1_ARPE					(0x00000080)
#define TIM_CR1_CKD						(0x00000300)
#define TIM_CR1_CKD_0					(0x00000100)
#define TIM_CR1_CKD_1					(0x00000200)
#define TIM_CR1_UIFREMAP				(0x00000800)

/*	Bit definition for TIM_CR2 register  */
#define TIM_CR2_CCPC					(0x00000001)
#define TIM_CR2_CCUS					(0x00000004)
#define TIM_CR2_CCDS					(0x00000008)
#define TIM_CR2_MMS						(0x00000070)
#define TIM_CR2_MMS_0					(0x00000010)
#define TIM_CR2_MMS_1					(0x00000020)
#define TIM_CR2_MMS_2					(0x00000040)
#define TIM_CR2_MMS_RESET				(0x00000000)
#define TIM_CR2_MMS_ENABLE				(0x00000010)
#define TIM_CR2_MMS_UPDATE				(0x00000020)
#define TIM_CR2_MMS_CMPPULSE			(0x00000030)
#define TIM_CR2_MMS_CMPOC1REF			(0x00000040)
#define TIM_CR2_MMS_CMPOC2REF			(0x00000050)
#define TIM_CR2_MMS_CMPOC3REF			(0x00000060)
#define TIM_CR2_MMS_CMPOC4REF			(0x00000070)
#define TIM_CR2_TI1S					(0x00000080)
#define TIM_CR2_OIS1					(0x00000100)
#define TIM_CR2_OIS1N					(0x00000200)
#define TIM_CR2_OIS2					(0x00000400)
#define TIM_CR2_OIS2N					(0x00000800)
#define TIM_CR2_OIS3					(0x00001000)
#define TIM_CR2_OIS3N					(0x00002000)
#define TIM_CR2_OIS4					(0x00004000)
#define TIM_CR2_OIS5					(0x00010000)
#define TIM_CR2_OIS6					(0x00040000)
#define TIM_CR2_MMS2					(0x00F00000)
#define TIM_CR2_MMS2_0					(0x00100000)
#define TIM_CR2_MMS2_1					(0x00200000)
#define TIM_CR2_MMS2_2					(0x00400000)
#define TIM_CR2_MMS2_3					(0x00800000)

/*	Bit definition for TIM_SMCR register  */
#define TIM_SMCR_SMS					(0x00010007)
#define TIM_SMCR_SMS_0					(0x00000001)
#define TIM_SMCR_SMS_1					(0x00000002)
#define TIM_SMCR_SMS_2					(0x00000004)
#define TIM_SMCR_SMS_3					(0x00010000)
#define TIM_SMCR_OCCS					(0x00000008)
#define TIM_SMCR_TS						(0x00000070)
#define TIM_SMCR_TS_0					(0x00000010)
#define TIM_SMCR_TS_1					(0x00000020)
#define TIM_SMCR_TS_2					(0x00000040)
#define TIM_SMCR_MSM					(0x00000080)
#define TIM_SMCR_ETF					(0x00000F00)
#define TIM_SMCR_ETF_0					(0x00000100)
#define TIM_SMCR_ETF_1					(0x00000200)
#define TIM_SMCR_ETF_2					(0x00000400)
#define TIM_SMCR_ETF_3					(0x00000800)
#define TIM_SMCR_ETPS					(0x00003000)
#define TIM_SMCR_ETPS_0					(0x00001000)
#define TIM_SMCR_ETPS_1					(0x00002000)
#define TIM_SMCR_ECE					(0x00004000)
#define TIM_SMCR_ETP					(0x00008000)

/*	Bit definition for TIM_DIER register  */
#define TIM_DIER_UIE					(0x00000001)
#define TIM_DIER_CC1IE					(0x00000002)
#define TIM_DIER_CC2IE					(0x00000004)
#define TIM_DIER_CC3IE					(0x00000008)
#define TIM_DIER_CC4IE					(0x00000010)
#define TIM_DIER_COMIE					(0x00000020)
#define TIM_DIER_TIE					(0x00000040)
#define TIM_DIER_BIE					(0x00000080)
#define TIM_DIER_UDE					(0x00000100)
#define TIM_DIER_CC1DE					(0x00000200)
#define TIM_DIER_CC2DE					(0x00000400)
#define TIM_DIER_CC3DE					(0x00000800)
#define TIM_DIER_CC4DE					(0x00001000)
#define TIM_DIER_COMDE					(0x00002000)
#define TIM_DIER_TDE					(0x00004000)

/*	Bit definition for TIM_SR register	*/
#define TIM_SR_UIF						(0x00000001)
#define TIM_SR_CC1IF					(0x00000002)
#define TIM_SR_CC2IF					(0x00000004)
#define TIM_SR_CC3IF					(0x00000008)
#define TIM_SR_CC4IF					(0x00000010)
#define TIM_SR_COMIF					(0x00000020)
#define TIM_SR_TIF						(0x00000040)
#define TIM_SR_BIF						(0x00000080)
#define TIM_SR_B2IF						(0x00000100)
#define TIM_SR_CC1OF					(0x00000200)
#define TIM_SR_CC2OF					(0x00000400)
#define TIM_SR_CC3OF					(0x00000800)
#define TIM_SR_CC4OF					(0x00001000)
#define TIM_SR_SBIF						(0x00002000)
#define TIM_SR_CC5IF					(0x00010000)
#define TIM_SR_CC6IF					(0x00020000)

/*	Bit definition for TIM_EGR register  */
#define TIM_EGR_UG						(0x00000001)
#define TIM_EGR_CC1G					(0x00000002)
#define TIM_EGR_CC2G					(0x00000004)
#define TIM_EGR_CC3G					(0x00000008)
#define TIM_EGR_CC4G					(0x00000010)
#define TIM_EGR_COMG					(0x00000020)
#define TIM_EGR_TG						(0x00000040)
#define TIM_EGR_BG						(0x00000080)
#define TIM_EGR_B2G						(0x00000100)

/*	Bit definition for TIM_CCMR1 register  */
#define TIM_CCMR1_CC1S					(0x00000003)
#define TIM_CCMR1_CC1S_0				(0x00000001)
#define TIM_CCMR1_CC1S_1				(0x00000002)
#define TIM_CCMR1_OC1FE					(0x00000004)
#define TIM_CCMR1_OC1PE					(0x00000008)
#define TIM_CCMR1_OC1M					(0x00010070)
#define TIM_CCMR1_OC1M_0				(0x00000010)
#define TIM_CCMR1_OC1M_1				(0x00000020)
#define TIM_CCMR1_OC1M_2				(0x00000040)
#define TIM_CCMR1_OC1M_3				(0x00010000)
#define TIM_CCMR1_OC1CE					(0x00000080)
#define TIM_CCMR1_CC2S					(0x00000300)
#define TIM_CCMR1_CC2S_0				(0x00000100)
#define TIM_CCMR1_CC2S_1				(0x00000200)
#define TIM_CCMR1_OC2FE					(0x00000400)
#define TIM_CCMR1_OC2PE					(0x00000800)
#define TIM_CCMR1_OC2M					(0x01007000)
#define TIM_CCMR1_OC2M_0				(0x00001000)
#define TIM_CCMR1_OC2M_1				(0x00002000)
#define TIM_CCMR1_OC2M_2				(0x00004000)
#define TIM_CCMR1_OC2M_3				(0x01000000)
#define TIM_CCMR1_OC2CE					(0x00008000)
#define TIM_CCMR1_IC1PSC				(0x0000000C)
#define TIM_CCMR1_IC1PSC_0				(0x00000004)
#define TIM_CCMR1_IC1PSC_1				(0x00000008)
#define TIM_CCMR1_IC1F					(0x000000F0)
#define TIM_CCMR1_IC1F_0				(0x00000010)
#define TIM_CCMR1_IC1F_1				(0x00000020)
#define TIM_CCMR1_IC1F_2				(0x00000040)
#define TIM_CCMR1_IC1F_3				(0x00000080)
#define TIM_CCMR1_IC2PSC				(0x00000C00)
#define TIM_CCMR1_IC2PSC_0				(0x00000400)
#define TIM_CCMR1_IC2PSC_1				(0x00000800)
#define TIM_CCMR1_IC2F					(0x0000F000)
#define TIM_CCMR1_IC2F_0				(0x00001000)
#define TIM_CCMR1_IC2F_1				(0x00002000)
#define TIM_CCMR1_IC2F_2				(0x00004000)
#define TIM_CCMR1_IC2F_3				(0x00008000)

/*	Bit definition for TIM_CCMR2 register  */
#define TIM_CCMR2_CC3S					(0x00000003)
#define TIM_CCMR2_CC3S_0				(0x00000001)
#define TIM_CCMR2_CC3S_1				(0x00000002)
#define TIM_CCMR2_OC3FE					(0x00000004)
#define TIM_CCMR2_OC3PE					(0x00000008)
#define TIM_CCMR2_OC3M					(0x00010070)
#define TIM_CCMR2_OC3M_0				(0x00000010)
#define TIM_CCMR2_OC3M_1				(0x00000020)
#define TIM_CCMR2_OC3M_2				(0x00000040)
#define TIM_CCMR2_OC3M_3				(0x00010000)
#define TIM_CCMR2_OC3CE					(0x00000080)
#define TIM_CCMR2_CC4S					(0x00000300)
#define TIM_CCMR2_CC4S_0				(0x00000100)
#define TIM_CCMR2_CC4S_1				(0x00000200)
#define TIM_CCMR2_OC4FE					(0x00000400)
#define TIM_CCMR2_OC4PE					(0x00000800)
#define TIM_CCMR2_OC4M					(0x01007000)
#define TIM_CCMR2_OC4M_0				(0x00001000)
#define TIM_CCMR2_OC4M_1				(0x00002000)
#define TIM_CCMR2_OC4M_2				(0x00004000)
#define TIM_CCMR2_OC4M_3				(0x01000000)
#define TIM_CCMR2_OC4CE					(0x00008000)
#define TIM_CCMR2_IC3PSC				(0x0000000C)
#define TIM_CCMR2_IC3PSC_0				(0x00000004)
#define TIM_CCMR2_IC3PSC_1				(0x00000008)
#define TIM_CCMR2_IC3F					(0x000000F0)
#define TIM_CCMR2_IC3F_0				(0x00000010)
#define TIM_CCMR2_IC3F_1				(0x00000020)
#define TIM_CCMR2_IC3F_2				(0x00000040)
#define TIM_CCMR2_IC3F_3				(0x00000080)
#define TIM_CCMR2_IC4PSC				(0x00000C00)
#define TIM_CCMR2_IC4PSC_0				(0x00000400)
#define TIM_CCMR2_IC4PSC_1				(0x00000800)
#define TIM_CCMR2_IC4F					(0x0000F000)
#define TIM_CCMR2_IC4F_0				(0x00001000)
#define TIM_CCMR2_IC4F_1				(0x00002000)
#define TIM_CCMR2_IC4F_2				(0x00004000)
#define TIM_CCMR2_IC4F_3				(0x00008000)

/*	Bit definition for TIM_CCMR3 register  */
#define TIM_CCMR3_OC5FE					(0x00000004)
#define TIM_CCMR3_OC5PE					(0x00000008)
#define TIM_CCMR3_OC5M					(0x00010070)
#define TIM_CCMR3_OC5M_0				(0x00000010)
#define TIM_CCMR3_OC5M_1				(0x00000020)
#define TIM_CCMR3_OC5M_2				(0x00000040)
#define TIM_CCMR3_OC5M_3				(0x00010000)
#define TIM_CCMR3_OC5CE					(0x00000080)
#define TIM_CCMR3_OC6FE					(0x00000400)
#define TIM_CCMR3_OC6PE					(0x00000800)
#define TIM_CCMR3_OC6M					(0x01007000)
#define TIM_CCMR3_OC6M_0				(0x00001000)
#define TIM_CCMR3_OC6M_1				(0x00002000)
#define TIM_CCMR3_OC6M_2				(0x00004000)
#define TIM_CCMR3_OC6M_3				(0x01000000)
#define TIM_CCMR3_OC6CE					(0x00008000)

/*	Bit definition for TIM_CCER register  */
#define TIM_CCER_CC1E					(0x00000001)
#define TIM_CCER_CC1P					(0x00000002)
#define TIM_CCER_CC1NE					(0x00000004)
#define TIM_CCER_CC1NP					(0x00000008)
#define TIM_CCER_CC2E					(0x00000010)
#define TIM_CCER_CC2P					(0x00000020)
#define TIM_CCER_CC2NE					(0x00000040)
#define TIM_CCER_CC2NP					(0x00000080)
#define TIM_CCER_CC3E					(0x00000100)
#define TIM_CCER_CC3P					(0x00000200)
#define TIM_CCER_CC3NE					(0x00000400)
#define TIM_CCER_CC3NP					(0x00000800)
#define TIM_CCER_CC4E					(0x00001000)
#define TIM_CCER_CC4P					(0x00002000)
#define TIM_CCER_CC4NP					(0x00008000)
#define TIM_CCER_CC5E					(0x00010000)
#define TIM_CCER_CC5P					(0x00020000)
#define TIM_CCER_CC6E					(0x00100000)
#define TIM_CCER_CC6P					(0x00200000)

/*	Bit definition for TIM_CNT register  */
#define TIM_CNT_CNT						(0xFFFFFFFF)
#define TIM_CNT_UIFCPY					(0x80000000)

/*	Bit definition for TIM_PSC register  */
#define TIM_PSC_PSC						(0x0000FFFF)

/*	Bit definition for TIM_ARR register  */
#define TIM_ARR_ARR						(0xFFFFFFFF)

/*	Bit definition for TIM_RCR register  */
#define TIM_RCR_REP						(0x0000FFFF)

/*	Bit definition for TIM_CCR1 register  */
#define TIM_CCR1_CCR1					(0x0000FFFF)

/*	Bit definition for TIM_CCR2 register  */
#define TIM_CCR2_CCR2					(0x0000FFFF)

/*	Bit definition for TIM_CCR3 register  */
#define TIM_CCR3_CCR3					(0x0000FFFF)

/*	Bit definition for TIM_CCR4 register  */
#define TIM_CCR4_CCR4					(0x0000FFFF)

/*	Bit definition for TIM_CCR5 register  */
#define TIM_CCR5_CCR5					(0xFFFFFFFF)
#define TIM_CCR5_GC5C1					(0x20000000)
#define TIM_CCR5_GC5C2					(0x40000000)
#define TIM_CCR5_GC5C3					(0x80000000)

/*	Bit definition for TIM_CCR6 register  */
#define TIM_CCR6_CCR6					(0x0000FFFF)

/*	Bit definition for TIM_BDTR register  */
#define TIM_BDTR_DTG					(0x000000FF)
#define TIM_BDTR_DTG_0					(0x00000001)
#define TIM_BDTR_DTG_1					(0x00000002)
#define TIM_BDTR_DTG_2					(0x00000004)
#define TIM_BDTR_DTG_3					(0x00000008)
#define TIM_BDTR_DTG_4					(0x00000010)
#define TIM_BDTR_DTG_5					(0x00000020)
#define TIM_BDTR_DTG_6					(0x00000040)
#define TIM_BDTR_DTG_7					(0x00000080)
#define TIM_BDTR_LOCK					(0x00000300)
#define TIM_BDTR_LOCK_0					(0x00000100)
#define TIM_BDTR_LOCK_1					(0x00000200)
#define TIM_BDTR_OSSI					(0x00000400)
#define TIM_BDTR_OSSR					(0x00000800)
#define TIM_BDTR_BKE					(0x00001000)
#define TIM_BDTR_BKP					(0x00002000)
#define TIM_BDTR_AOE					(0x00004000)
#define TIM_BDTR_MOE					(0x00008000)
#define TIM_BDTR_BKF					(0x000F0000)
#define TIM_BDTR_BK2F					(0x00F00000)
#define TIM_BDTR_BK2E					(0x01000000)
#define TIM_BDTR_BK2P					(0x02000000)

/*	Bit definition for TIM_DCR register  */
#define TIM_DCR_DBA						(0x0000001F)
#define TIM_DCR_DBA_0					(0x00000001)
#define TIM_DCR_DBA_1					(0x00000002)
#define TIM_DCR_DBA_2					(0x00000004)
#define TIM_DCR_DBA_3					(0x00000008)
#define TIM_DCR_DBA_4					(0x00000010)
#define TIM_DCR_DBL						(0x00001F00)
#define TIM_DCR_DBL_0					(0x00000100)
#define TIM_DCR_DBL_1					(0x00000200)
#define TIM_DCR_DBL_2					(0x00000400)
#define TIM_DCR_DBL_3					(0x00000800)
#define TIM_DCR_DBL_4					(0x00001000)

/*	Bit definition for TIM_DMAR register  */
#define TIM_DMAR_DMAB					(0x0000FFFF)

/*	Bit definition for TIM1_OR1 register  */
#define TIM1_OR1_ETR_ADC1_RMP			(0x00000003)
#define TIM1_OR1_ETR_ADC1_RMP_0		(0x00000001)
#define TIM1_OR1_ETR_ADC1_RMP_1		(0x00000002)
#define TIM1_OR1_ETR_ADC3_RMP			(0x0000000C)
#define TIM1_OR1_ETR_ADC3_RMP_0		(0x00000004)
#define TIM1_OR1_ETR_ADC3_RMP_1		(0x00000008)
#define TIM1_OR1_TI1_RMP				(0x00000010)

/*	Bit definition for TIM1_OR2 register  */
#define TIM1_OR2_BKINE					(0x00000001)
#define TIM1_OR2_BKCMP1E				(0x00000002)
#define TIM1_OR2_BKCMP2E				(0x00000004)
#define TIM1_OR2_BKDFBK0E				(0x00000100)
#define TIM1_OR2_BKINP					(0x00000200)
#define TIM1_OR2_BKCMP1P				(0x00000400)
#define TIM1_OR2_BKCMP2P				(0x00000800)
#define TIM1_OR2_ETRSEL					(0x0001C000)
#define TIM1_OR2_ETRSEL_0				(0x00004000)
#define TIM1_OR2_ETRSEL_1				(0x00008000)
#define TIM1_OR2_ETRSEL_2				(0x00010000)

/*	Bit definition for TIM1_OR3 register  */
#define TIM1_OR3_BK2INE					(0x00000001)
#define TIM1_OR3_BK2CMP1E				(0x00000002)
#define TIM1_OR3_BK2CMP2E				(0x00000004)
#define TIM1_OR3_BK2DFBK1E				(0x00000100)
#define TIM1_OR3_BK2INP					(0x00000200)
#define TIM1_OR3_BK2CMP1P				(0x00000400)
#define TIM1_OR3_BK2CMP2P				(0x00000800)

/*	Bit definition for TIM8_OR1 register  */
#define TIM8_OR1_ETR_ADC2_RMP			(0x00000003)
#define TIM8_OR1_ETR_ADC2_RMP_0		(0x00000001)
#define TIM8_OR1_ETR_ADC2_RMP_1		(0x00000002)
#define TIM8_OR1_ETR_ADC3_RMP			(0x0000000C)
#define TIM8_OR1_ETR_ADC3_RMP_0		(0x00000004)
#define TIM8_OR1_ETR_ADC3_RMP_1		(0x00000008)

#define TIM8_OR1_TI1_RMP				(0x00000010)

/*	Bit definition for TIM8_OR2 register  */
#define TIM8_OR2_BKINE					(0x00000001)
#define TIM8_OR2_BKCMP1E				(0x00000002)
#define TIM8_OR2_BKCMP2E				(0x00000004)
#define TIM8_OR2_BKDFBK2E				(0x00000100)
#define TIM8_OR2_BKINP					(0x00000200)
#define TIM8_OR2_BKCMP1P				(0x00000400)
#define TIM8_OR2_BKCMP2P				(0x00000800)
#define TIM8_OR2_ETRSEL					(0x0001C000)
#define TIM8_OR2_ETRSEL_0				(0x00004000)
#define TIM8_OR2_ETRSEL_1				(0x00008000)
#define TIM8_OR2_ETRSEL_2				(0x00010000)

/*	Bit definition for TIM8_OR3 register  */
#define TIM8_OR3_BK2INE					(0x00000001)
#define TIM8_OR3_BK2CMP1E				(0x00000002)
#define TIM8_OR3_BK2CMP2E				(0x00000004)
#define TIM8_OR3_BK2DFBK3E				(0x00000100)
#define TIM8_OR3_BK2INP					(0x00000200)
#define TIM8_OR3_BK2CMP1P				(0x00000400)
#define TIM8_OR3_BK2CMP2P				(0x00000800)

/*	Bit definition for TIM2_OR1 register  */
#define TIM2_OR1_ITR1_RMP				(0x00000001)
#define TIM2_OR1_ETR1_RMP				(0x00000002)
#define TIM2_OR1_TI4_RMP				(0x0000000C)
#define TIM2_OR1_TI4_RMP_0				(0x00000004)
#define TIM2_OR1_TI4_RMP_1				(0x00000008)

/*	Bit definition for TIM2_OR2 register  */
#define TIM2_OR2_ETRSEL					(0x0001C000)
#define TIM2_OR2_ETRSEL_0				(0x00004000)
#define TIM2_OR2_ETRSEL_1				(0x00008000)
#define TIM2_OR2_ETRSEL_2				(0x00010000)

/*	Bit definition for TIM3_OR1 register  */
#define TIM3_OR1_TI1_RMP				(0x00000003)
#define TIM3_OR1_TI1_RMP_0				(0x00000001)
#define TIM3_OR1_TI1_RMP_1				(0x00000002)

/*	Bit definition for TIM3_OR2 register  */
#define TIM3_OR2_ETRSEL					(0x0001C000)
#define TIM3_OR2_ETRSEL_0				(0x00004000)
#define TIM3_OR2_ETRSEL_1				(0x00008000)
#define TIM3_OR2_ETRSEL_2				(0x00010000)

/*	Bit definition for TIM15_OR1 register  */
#define TIM15_OR1_TI1_RMP				(0x00000001)
#define TIM15_OR1_ENCODER_MODE			(0x00000006)
#define TIM15_OR1_ENCODER_MODE_0		(0x00000002)
#define TIM15_OR1_ENCODER_MODE_1		(0x00000004)

/*	Bit definition for TIM15_OR2 register  */
#define TIM15_OR2_BKINE					(0x00000001)
#define TIM15_OR2_BKCMP1E				(0x00000002)
#define TIM15_OR2_BKCMP2E				(0x00000004)
#define TIM15_OR2_BKDFBK0E				(0x00000100)
#define TIM15_OR2_BKINP					(0x00000200)
#define TIM15_OR2_BKCMP1P				(0x00000400)
#define TIM15_OR2_BKCMP2P				(0x00000800)

/*	Bit definition for TIM16_OR1 register  */
#define TIM16_OR1_TI1_RMP				(0x00000003)
#define TIM16_OR1_TI1_RMP_0				(0x00000001)
#define TIM16_OR1_TI1_RMP_1				(0x00000002)

/*	Bit definition for TIM16_OR2 register  */
#define TIM16_OR2_BKINE					(0x00000001)
#define TIM16_OR2_BKCMP1E				(0x00000002)
#define TIM16_OR2_BKCMP2E				(0x00000004)
#define TIM16_OR2_BKDFBK1E				(0x00000100)
#define TIM16_OR2_BKINP					(0x00000200)
#define TIM16_OR2_BKCMP1P				(0x00000400)
#define TIM16_OR2_BKCMP2P				(0x00000800)

/*	Bit definition for TIM17_OR1 register  */
#define TIM17_OR1_TI1_RMP				(0x00000003)
#define TIM17_OR1_TI1_RMP_0				(0x00000001)
#define TIM17_OR1_TI1_RMP_1				(0x00000002)

/*	Bit definition for TIM17_OR2 register  */
#define TIM17_OR2_BKINE					(0x00000001)
#define TIM17_OR2_BKCMP1E				(0x00000002)
#define TIM17_OR2_BKCMP2E				(0x00000004)
#define TIM17_OR2_BKDFBK2E				(0x00000100)
#define TIM17_OR2_BKINP					(0x00000200)
#define TIM17_OR2_BKCMP1P				(0x00000400)
#define TIM17_OR2_BKCMP2P				(0x00000800)

#endif /* STM32L476_TIMER_H_ */

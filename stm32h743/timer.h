/**
 * @file timer.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: TIMER
 */


#ifndef STM32H743_TIMER_H
#define STM32H743_TIMER_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define TIM1_BASE                                           0x40010000U
#define TIM8_BASE                                           0x40010400U
#define TIM2_BASE                                           0x40000000U
#define TIM3_BASE                                           0x40000400U
#define TIM4_BASE                                           0x40000800U
#define TIM5_BASE                                           0x40000c00U
#define TIM12_BASE                                          0x40001800U
#define TIM13_BASE                                          0x40001c00U
#define TIM14_BASE                                          0x40002000U
#define TIM6_BASE                                           0x40001000U
#define TIM7_BASE                                           0x40001400U

/* instances */
#define TIM1                                                ((tim_t *)TIM1_BASE)
#define TIM8                                                ((tim_t *)TIM8_BASE)
#define TIM2                                                ((tim_t *)TIM2_BASE)
#define TIM3                                                ((tim_t *)TIM3_BASE)
#define TIM4                                                ((tim_t *)TIM4_BASE)
#define TIM5                                                ((tim_t *)TIM5_BASE)
#define TIM12                                               ((tim_t *)TIM12_BASE)
#define TIM13                                               ((tim_t *)TIM13_BASE)
#define TIM14                                               ((tim_t *)TIM14_BASE)
#define TIM6                                                ((tim_t *)TIM6_BASE)
#define TIM7                                                ((tim_t *)TIM7_BASE)

/* register bank */
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
    reg8_t RESERVED2[4];
    reg32_t CCMR3;
    reg32_t CCR5;
    reg32_t CRR6;
    reg32_t AF1;
    reg32_t AF2;
    reg32_t TISEL;
} tim_t;

/******************* bit definitions for CR1 register *******************/
#define TIM_CR1_CEN                                         0x00000001
#define TIM_CR1_UDIS                                        0x00000002
#define TIM_CR1_URS                                         0x00000004
#define TIM_CR1_OPM                                         0x00000008
#define TIM_CR1_DIR                                         0x00000010
#define TIM_CR1_CMS                                         0x00000060
#define TIM_CR1_ARPE                                        0x00000080
#define TIM_CR1_CKD                                         0x00000300
#define TIM_CR1_UIFREMAP                                    0x00000800

/******************* bit definitions for CR2 register *******************/
#define TIM_CR2_MMS2                                        0x00f00000
#define TIM_CR2_OIS6                                        0x00040000
#define TIM_CR2_OIS5                                        0x00010000
#define TIM_CR2_OIS4                                        0x00004000
#define TIM_CR2_OIS3N                                       0x00002000
#define TIM_CR2_OIS3                                        0x00001000
#define TIM_CR2_OIS2N                                       0x00000800
#define TIM_CR2_OIS2                                        0x00000400
#define TIM_CR2_OIS1N                                       0x00000200
#define TIM_CR2_OIS1                                        0x00000100
#define TIM_CR2_TI1S                                        0x00000080
#define TIM_CR2_MMS                                         0x00000070
#define TIM_CR2_CCDS                                        0x00000008
#define TIM_CR2_CCUS                                        0x00000004
#define TIM_CR2_CCPC                                        0x00000001

/****************** bit definitions for SMCR register *******************/
#define TIM_SMCR_SMS                                        0x00000007
#define TIM_SMCR_TS                                         0x00000070
#define TIM_SMCR_MSM                                        0x00000080
#define TIM_SMCR_ETF                                        0x00000f00
#define TIM_SMCR_ETPS                                       0x00003000
#define TIM_SMCR_ECE                                        0x00004000
#define TIM_SMCR_ETP                                        0x00008000
#define TIM_SMCR_SMS_3                                      0x00010000
#define TIM_SMCR_TS_4_3                                     0x00300000

/****************** bit definitions for DIER register *******************/
#define TIM_DIER_TDE                                        0x00004000
#define TIM_DIER_COMDE                                      0x00002000
#define TIM_DIER_CC4DE                                      0x00001000
#define TIM_DIER_CC3DE                                      0x00000800
#define TIM_DIER_CC2DE                                      0x00000400
#define TIM_DIER_CC1DE                                      0x00000200
#define TIM_DIER_UDE                                        0x00000100
#define TIM_DIER_TIE                                        0x00000040
#define TIM_DIER_CC4IE                                      0x00000010
#define TIM_DIER_CC3IE                                      0x00000008
#define TIM_DIER_CC2IE                                      0x00000004
#define TIM_DIER_CC1IE                                      0x00000002
#define TIM_DIER_UIE                                        0x00000001
#define TIM_DIER_BIE                                        0x00000080
#define TIM_DIER_COMIE                                      0x00000020

/******************* bit definitions for SR register ********************/
#define TIM_SR_CC6IF                                        0x00020000
#define TIM_SR_CC5IF                                        0x00010000
#define TIM_SR_SBIF                                         0x00002000
#define TIM_SR_CC4OF                                        0x00001000
#define TIM_SR_CC3OF                                        0x00000800
#define TIM_SR_CC2OF                                        0x00000400
#define TIM_SR_CC1OF                                        0x00000200
#define TIM_SR_B2IF                                         0x00000100
#define TIM_SR_BIF                                          0x00000080
#define TIM_SR_TIF                                          0x00000040
#define TIM_SR_COMIF                                        0x00000020
#define TIM_SR_CC4IF                                        0x00000010
#define TIM_SR_CC3IF                                        0x00000008
#define TIM_SR_CC2IF                                        0x00000004
#define TIM_SR_CC1IF                                        0x00000002
#define TIM_SR_UIF                                          0x00000001

/******************* bit definitions for EGR register *******************/
#define TIM_EGR_UG                                          0x00000001
#define TIM_EGR_CC1G                                        0x00000002
#define TIM_EGR_CC2G                                        0x00000004
#define TIM_EGR_CC3G                                        0x00000008
#define TIM_EGR_CC4G                                        0x00000010
#define TIM_EGR_COMG                                        0x00000020
#define TIM_EGR_TG                                          0x00000040
#define TIM_EGR_BG                                          0x00000080
#define TIM_EGR_B2G                                         0x00000100

/************** bit definitions for CCMR1_Output register ***************/
#define TIM_CCMR1_OUTPUT_CC1S                               0x00000003
#define TIM_CCMR1_OUTPUT_OC1FE                              0x00000004
#define TIM_CCMR1_OUTPUT_OC1PE                              0x00000008
#define TIM_CCMR1_OUTPUT_OC1M                               0x00000070
#define TIM_CCMR1_OUTPUT_OC1CE                              0x00000080
#define TIM_CCMR1_OUTPUT_CC2S                               0x00000300
#define TIM_CCMR1_OUTPUT_OC2FE                              0x00000400
#define TIM_CCMR1_OUTPUT_OC2PE                              0x00000800
#define TIM_CCMR1_OUTPUT_OC2M                               0x00007000
#define TIM_CCMR1_OUTPUT_OC2CE                              0x00008000
#define TIM_CCMR1_OUTPUT_OC1M_3                             0x00010000
#define TIM_CCMR1_OUTPUT_OC2M_3                             0x01000000

/*************** bit definitions for CCMR1_Input register ***************/
#define TIM_CCMR1_INPUT_IC2F                                0x0000f000
#define TIM_CCMR1_INPUT_IC2PCS                              0x00000c00
#define TIM_CCMR1_INPUT_CC2S                                0x00000300
#define TIM_CCMR1_INPUT_IC1F                                0x000000f0
#define TIM_CCMR1_INPUT_ICPCS                               0x0000000c
#define TIM_CCMR1_INPUT_CC1S                                0x00000003

/************** bit definitions for CCMR2_Output register ***************/
#define TIM_CCMR2_OUTPUT_CC3S                               0x00000003
#define TIM_CCMR2_OUTPUT_OC3FE                              0x00000004
#define TIM_CCMR2_OUTPUT_OC3PE                              0x00000008
#define TIM_CCMR2_OUTPUT_OC3M                               0x00000070
#define TIM_CCMR2_OUTPUT_OC3CE                              0x00000080
#define TIM_CCMR2_OUTPUT_CC4S                               0x00000300
#define TIM_CCMR2_OUTPUT_OC4FE                              0x00000400
#define TIM_CCMR2_OUTPUT_OC4PE                              0x00000800
#define TIM_CCMR2_OUTPUT_OC4M                               0x00007000
#define TIM_CCMR2_OUTPUT_OC4CE                              0x00008000
#define TIM_CCMR2_OUTPUT_OC3M_3                             0x00010000
#define TIM_CCMR2_OUTPUT_OC4M_4                             0x01000000

/*************** bit definitions for CCMR2_Input register ***************/
#define TIM_CCMR2_INPUT_IC4F                                0x0000f000
#define TIM_CCMR2_INPUT_IC4PSC                              0x00000c00
#define TIM_CCMR2_INPUT_CC4S                                0x00000300
#define TIM_CCMR2_INPUT_IC3F                                0x000000f0
#define TIM_CCMR2_INPUT_IC3PSC                              0x0000000c
#define TIM_CCMR2_INPUT_CC3S                                0x00000003

/****************** bit definitions for CCER register *******************/
#define TIM_CCER_CC1E                                       0x00000001
#define TIM_CCER_CC1P                                       0x00000002
#define TIM_CCER_CC1NE                                      0x00000004
#define TIM_CCER_CC1NP                                      0x00000008
#define TIM_CCER_CC2E                                       0x00000010
#define TIM_CCER_CC2P                                       0x00000020
#define TIM_CCER_CC2NE                                      0x00000040
#define TIM_CCER_CC2NP                                      0x00000080
#define TIM_CCER_CC3E                                       0x00000100
#define TIM_CCER_CC3P                                       0x00000200
#define TIM_CCER_CC3NE                                      0x00000400
#define TIM_CCER_CC3NP                                      0x00000800
#define TIM_CCER_CC4E                                       0x00001000
#define TIM_CCER_CC4P                                       0x00002000
#define TIM_CCER_CC4NP                                      0x00008000
#define TIM_CCER_CC5E                                       0x00010000
#define TIM_CCER_CC5P                                       0x00020000
#define TIM_CCER_CC6E                                       0x00100000
#define TIM_CCER_CC6P                                       0x00200000

/******************* bit definitions for CNT register *******************/
#define TIM_CNT_CNT                                         0x0000ffff
#define TIM_CNT_UIFCPY                                      0x80000000

/******************* bit definitions for PSC register *******************/
#define TIM_PSC_PSC                                         0x0000ffff

/******************* bit definitions for ARR register *******************/
#define TIM_ARR_ARR                                         0x0000ffff

/******************* bit definitions for RCR register *******************/
#define TIM_RCR_REP                                         0x000000ff

/****************** bit definitions for CCR1 register *******************/
#define TIM_CCR1_CCR1                                       0x0000ffff

/****************** bit definitions for CCR2 register *******************/
#define TIM_CCR2_CCR2                                       0x0000ffff

/****************** bit definitions for CCR3 register *******************/
#define TIM_CCR3_CCR3                                       0x0000ffff

/****************** bit definitions for CCR4 register *******************/
#define TIM_CCR4_CCR4                                       0x0000ffff

/****************** bit definitions for BDTR register *******************/
#define TIM_BDTR_DTG                                        0x000000ff
#define TIM_BDTR_LOCK                                       0x00000300
#define TIM_BDTR_OSSI                                       0x00000400
#define TIM_BDTR_OSSR                                       0x00000800
#define TIM_BDTR_BKE                                        0x00001000
#define TIM_BDTR_BKP                                        0x00002000
#define TIM_BDTR_AOE                                        0x00004000
#define TIM_BDTR_MOE                                        0x00008000
#define TIM_BDTR_BKF                                        0x000f0000
#define TIM_BDTR_BK2F                                       0x00f00000
#define TIM_BDTR_BK2E                                       0x01000000
#define TIM_BDTR_BK2P                                       0x02000000

/******************* bit definitions for DCR register *******************/
#define TIM_DCR_DBL                                         0x00001f00
#define TIM_DCR_DBA                                         0x0000001f

/****************** bit definitions for DMAR register *******************/
#define TIM_DMAR_DMAB                                       0x0000ffff

/************** bit definitions for CCMR3_Output register ***************/
#define TIM_CCMR3_OUTPUT_OC5FE                              0x00000004
#define TIM_CCMR3_OUTPUT_OC5PE                              0x00000008
#define TIM_CCMR3_OUTPUT_OC5M                               0x00000070
#define TIM_CCMR3_OUTPUT_OC5CE                              0x00000080
#define TIM_CCMR3_OUTPUT_OC6FE                              0x00000400
#define TIM_CCMR3_OUTPUT_OC6PE                              0x00000800
#define TIM_CCMR3_OUTPUT_OC6M                               0x00007000
#define TIM_CCMR3_OUTPUT_OC6CE                              0x00008000
#define TIM_CCMR3_OUTPUT_OC5M3                              0x00010000
#define TIM_CCMR3_OUTPUT_OC6M3                              0x01000000

/****************** bit definitions for CCR5 register *******************/
#define TIM_CCR5_CCR5                                       0x0000ffff
#define TIM_CCR5_GC5C1                                      0x20000000
#define TIM_CCR5_GC5C2                                      0x40000000
#define TIM_CCR5_GC5C3                                      0x80000000

/****************** bit definitions for CRR6 register *******************/
#define TIM_CRR6_CCR6                                       0x0000ffff

/******************* bit definitions for AF1 register *******************/
#define TIM_AF1_BKINE                                       0x00000001
#define TIM_AF1_BKCMP1E                                     0x00000002
#define TIM_AF1_BKCMP2E                                     0x00000004
#define TIM_AF1_BKDF1BK0E                                   0x00000100
#define TIM_AF1_BKINP                                       0x00000200
#define TIM_AF1_BKCMP1P                                     0x00000400
#define TIM_AF1_BKCMP2P                                     0x00000800
#define TIM_AF1_ETRSEL                                      0x0003c000

/******************* bit definitions for AF2 register *******************/
#define TIM_AF2_BK2INE                                      0x00000001
#define TIM_AF2_BK2CMP1E                                    0x00000002
#define TIM_AF2_BK2CMP2E                                    0x00000004
#define TIM_AF2_BK2DF1BK1E                                  0x00000100
#define TIM_AF2_BK2INP                                      0x00000200
#define TIM_AF2_BK2CMP1P                                    0x00000400
#define TIM_AF2_BK2CMP2P                                    0x00000800

/****************** bit definitions for TISEL register ******************/
#define TIM_TISEL_TI1SEL                                    0x0000000f
#define TIM_TISEL_TI2SEL                                    0x00000f00
#define TIM_TISEL_TI3SEL                                    0x000f0000
#define TIM_TISEL_TI4SEL                                    0x0f000000

#endif /* STM32H743_TIMER_H */
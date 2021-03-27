/**
 * @file syscfg.h
 * 
 * @date 2021-01-22
 * @author twatorowski 
 * 
 * @brief STM32H743: SYSCFG
 */

#ifndef STM32H743_SYSCFG_H
#define STM32H743_SYSCFG_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define SYSCFG_BASE                                         0x58000400U

/* instances */
#define SYSCFG                                              ((syscfg_t *)SYSCFG_BASE)

/* register bank */
typedef struct {
    reg8_t RESERVED0[4];
    reg32_t PMCR;
    reg32_t EXTICR1;
    reg32_t EXTICR2;
    reg32_t EXTICR3;
    reg32_t EXTICR4;
    reg8_t RESERVED1[8];
    reg32_t CCCSR;
    reg32_t CCVR;
    reg32_t CCCR;
    reg32_t PWRCR;
    reg8_t RESERVED2[244];
    reg32_t PKGR;
    reg8_t RESERVED3[472];
    reg32_t UR0;
    reg8_t RESERVED4[4];
    reg32_t UR2;
    reg32_t UR3;
    reg32_t UR4;
    reg32_t UR5;
    reg32_t UR6;
    reg32_t UR7;
    reg32_t UR8;
    reg32_t UR9;
    reg32_t UR10;
    reg32_t UR11;
    reg32_t UR12;
    reg32_t UR13;
    reg32_t UR14;
    reg32_t UR15;
    reg32_t UR16;
    reg32_t UR17;
} syscfg_t;

/****************** bit definitions for PMCR register *******************/
#define SYSCFG_PMCR_I2C1FMP                                 0x00000001
#define SYSCFG_PMCR_I2C2FMP                                 0x00000002
#define SYSCFG_PMCR_I2C3FMP                                 0x00000004
#define SYSCFG_PMCR_I2C4FMP                                 0x00000008
#define SYSCFG_PMCR_PB6FMP                                  0x00000010
#define SYSCFG_PMCR_PB7FMP                                  0x00000020
#define SYSCFG_PMCR_PB8FMP                                  0x00000040
#define SYSCFG_PMCR_PB9FMP                                  0x00000080
#define SYSCFG_PMCR_BOOSTE                                  0x00000100
#define SYSCFG_PMCR_BOOSTVDDSEL                             0x00000200
#define SYSCFG_PMCR_EPIS                                    0x00e00000
#define SYSCFG_PMCR_PA0SO                                   0x01000000
#define SYSCFG_PMCR_PA1SO                                   0x02000000
#define SYSCFG_PMCR_PC2SO                                   0x04000000
#define SYSCFG_PMCR_PC3SO                                   0x08000000

/***************** bit definitions for EXTICR1 register *****************/
#define SYSCFG_EXTICR1_EXTI3                                0x0000f000
#define SYSCFG_EXTICR1_EXTI2                                0x00000f00
#define SYSCFG_EXTICR1_EXTI1                                0x000000f0
#define SYSCFG_EXTICR1_EXTI0                                0x0000000f

/***************** bit definitions for EXTICR2 register *****************/
#define SYSCFG_EXTICR2_EXTI7                                0x0000f000
#define SYSCFG_EXTICR2_EXTI6                                0x00000f00
#define SYSCFG_EXTICR2_EXTI5                                0x000000f0
#define SYSCFG_EXTICR2_EXTI4                                0x0000000f

/***************** bit definitions for EXTICR3 register *****************/
#define SYSCFG_EXTICR3_EXTI11                               0x0000f000
#define SYSCFG_EXTICR3_EXTI10                               0x00000f00
#define SYSCFG_EXTICR3_EXTI9                                0x000000f0
#define SYSCFG_EXTICR3_EXTI8                                0x0000000f

/***************** bit definitions for EXTICR4 register *****************/
#define SYSCFG_EXTICR4_EXTI15                               0x0000f000
#define SYSCFG_EXTICR4_EXTI14                               0x00000f00
#define SYSCFG_EXTICR4_EXTI13                               0x000000f0
#define SYSCFG_EXTICR4_EXTI12                               0x0000000f

/****************** bit definitions for CCCSR register ******************/
#define SYSCFG_CCCSR_EN                                     0x00000001
#define SYSCFG_CCCSR_CS                                     0x00000002
#define SYSCFG_CCCSR_READY                                  0x00000100
#define SYSCFG_CCCSR_HSLV                                   0x00010000

/****************** bit definitions for CCVR register *******************/
#define SYSCFG_CCVR_NCV                                     0x0000000f
#define SYSCFG_CCVR_PCV                                     0x000000f0

/****************** bit definitions for CCCR register *******************/
#define SYSCFG_CCCR_NCC                                     0x0000000f
#define SYSCFG_CCCR_PCC                                     0x000000f0

/****************** bit definitions for PWRCR register ******************/
#define SYSCFG_PWRCR_ODEN                                   0x0000000f

/****************** bit definitions for PKGR register *******************/
#define SYSCFG_PKGR_PKG                                     0x0000000f

/******************* bit definitions for UR0 register *******************/
#define SYSCFG_UR0_BKS                                      0x00000001
#define SYSCFG_UR0_RDP                                      0x00ff0000

/******************* bit definitions for UR2 register *******************/
#define SYSCFG_UR2_BORH                                     0x00000003
#define SYSCFG_UR2_BOOT_ADD0                                0xffff0000

/******************* bit definitions for UR3 register *******************/
#define SYSCFG_UR3_BOOT_ADD1                                0xffff0000

/******************* bit definitions for UR4 register *******************/
#define SYSCFG_UR4_MEPAD_1                                  0x00010000

/******************* bit definitions for UR5 register *******************/
#define SYSCFG_UR5_MESAD_1                                  0x00000001
#define SYSCFG_UR5_WRPN_1                                   0x00ff0000

/******************* bit definitions for UR6 register *******************/
#define SYSCFG_UR6_PA_BEG_1                                 0x00000fff
#define SYSCFG_UR6_PA_END_1                                 0x0fff0000

/******************* bit definitions for UR7 register *******************/
#define SYSCFG_UR7_SA_BEG_1                                 0x00000fff
#define SYSCFG_UR7_SA_END_1                                 0x0fff0000

/******************* bit definitions for UR8 register *******************/
#define SYSCFG_UR8_MEPAD_2                                  0x00000001
#define SYSCFG_UR8_MESAD_2                                  0x00010000

/******************* bit definitions for UR9 register *******************/
#define SYSCFG_UR9_WRPN_2                                   0x000000ff
#define SYSCFG_UR9_PA_BEG_2                                 0x0fff0000

/****************** bit definitions for UR10 register *******************/
#define SYSCFG_UR10_PA_END_2                                0x00000fff
#define SYSCFG_UR10_SA_BEG_2                                0x0fff0000

/****************** bit definitions for UR11 register *******************/
#define SYSCFG_UR11_SA_END_2                                0x00000fff
#define SYSCFG_UR11_IWDG1M                                  0x00010000

/****************** bit definitions for UR12 register *******************/
#define SYSCFG_UR12_SECURE                                  0x00010000

/****************** bit definitions for UR13 register *******************/
#define SYSCFG_UR13_SDRS                                    0x00000003
#define SYSCFG_UR13_D1SBRST                                 0x00010000

/****************** bit definitions for UR14 register *******************/
#define SYSCFG_UR14_D1STPRST                                0x00000001

/****************** bit definitions for UR15 register *******************/
#define SYSCFG_UR15_FZIWDGSTB                               0x00010000

/****************** bit definitions for UR16 register *******************/
#define SYSCFG_UR16_FZIWDGSTP                               0x00000001
#define SYSCFG_UR16_PKP                                     0x00010000

/****************** bit definitions for UR17 register *******************/
#define SYSCFG_UR17_IO_HSLV                                 0x00000001

#endif /* STM32H743_SYSCFG_H */

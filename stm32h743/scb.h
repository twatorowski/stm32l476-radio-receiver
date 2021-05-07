/**
 * @file scb.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: SCB
 */

#ifndef STM32H743_SCB_H
#define STM32H743_SCB_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define SCB_SCS_BASE                                        0xe000e000U
#define SCB_BASE                                            0xe000ed00U

/* instances */
#define SCB_SCS                                             ((scb_scs_t *)SCB_SCS_BASE)
#define SCB                                                 ((scb_t *)SCB_BASE)

/* register block */
typedef struct {
    reg32_t CPUID;
    reg32_t ICSR;
    reg32_t VTOR;
    reg32_t AIRCR;
    reg32_t SCR;
    reg32_t CCR;
    reg8_t SHPR[12];
    reg32_t SHCSR;
    reg32_t CFSR;
    reg32_t HFSR;
    reg32_t DFSR;
    reg32_t MMFAR;
    reg32_t BFAR;
    reg32_t AFSR;
    reg32_t PFR[2];
    reg32_t DFR;
    reg32_t ADR;
    reg32_t MMFR[4];
    reg32_t ISAR[5];
    reg32_t RESERVED0[1];
    reg32_t CLIDR;                  
    reg32_t CTR;                    
    reg32_t CCSIDR;                 
    reg32_t CSSELR;                 
    reg32_t CPACR;                  
    reg32_t RESERVED3[93];
    reg32_t STIR;                   
    reg32_t RESERVED4[15];
    reg32_t MVFR0;                  
    reg32_t MVFR1;                  
    reg32_t MVFR2;                  
    reg32_t RESERVED5[1];
    reg32_t ICIALLU;                
    reg32_t RESERVED6[1];
    reg32_t ICIMVAU;                
    reg32_t DCIMVAC;                
    reg32_t DCISW;                  
    reg32_t DCCMVAU;                
    reg32_t DCCMVAC;                
    reg32_t DCCSW;                  
    reg32_t DCCIMVAC;               
    reg32_t DCCISW;                 
    reg32_t RESERVED7[6];
    reg32_t ITCMCR;                 
    reg32_t DTCMCR;                 
    reg32_t AHBPCR;                 
    reg32_t CACR;                   
    reg32_t AHBSCR;                 
    reg32_t RESERVED8[1];
    reg32_t ABFSR;                  
} scb_t;

/****************** bit definitions for CPUID register ******************/
#define SCB_CPUID_IMPLEMENTER                               (0xFFUL << 24U)
#define SCB_CPUID_VARIANT                                   (0xFUL << 20U)
#define SCB_CPUID_ARCHITECTURE                              (0xFUL << 16U)
#define SCB_CPUID_PARTNO                                    (0xFFFUL << 4U)
#define SCB_CPUID_REVISION                                  (0xFUL )

/****************** bit definitions for ICSR register *******************/
#define SCB_ICSR_NMIPENDSET                                 (1UL << 31U)
#define SCB_ICSR_PENDSVSET                                  (1UL << 28U)
#define SCB_ICSR_PENDSVCLR                                  (1UL << 27U)
#define SCB_ICSR_PENDSTSET                                  (1UL << 26U)
#define SCB_ICSR_PENDSTCLR                                  (1UL << 25U)
#define SCB_ICSR_ISRPREEMPT                                 (1UL << 23U)
#define SCB_ICSR_ISRPENDING                                 (1UL << 22U)
#define SCB_ICSR_VECTPENDING                                (0x1FFUL << 12U)
#define SCB_ICSR_RETTOBASE                                  (1UL << 11U)
#define SCB_ICSR_VECTACTIVE                                 (0x1FFUL )

/****************** bit definitions for VTOR register *******************/
#define SCB_VTOR_TBLOFF                                     (0x1FFFFFFUL << 7U)

/****************** bit definitions for AIRCR register ******************/
#define SCB_AIRCR_VECTKEY                                   (0x05FAUL << 16U)
#define SCB_AIRCR_VECTKEYSTAT                               (0xFFFFUL << 16U)
#define SCB_AIRCR_ENDIANESS                                 (1UL << 15U)
#define SCB_AIRCR_PRIGROUP                                  (7UL << 8U)
#define SCB_AIRCR_SYSRESETREQ                               (1UL << 2U)
#define SCB_AIRCR_VECTCLRACTIVE                             (1UL << 1U)
#define SCB_AIRCR_VECTRESET                                 (1UL )

/******************* bit definitions for SCR register *******************/
#define SCB_SCR_SEVONPEND                                   (1UL << 4U)
#define SCB_SCR_SLEEPDEEP                                   (1UL << 2U)
#define SCB_SCR_SLEEPONEXIT                                 (1UL << 1U)

/******************* bit definitions for CCR register *******************/
#define SCB_CCR_BP                                          (1UL << 18U)
#define SCB_CCR_IC                                          (1UL << 17U)
#define SCB_CCR_DC                                          (1UL << 16U)
#define SCB_CCR_STKALIGN                                    (1UL << 9U)
#define SCB_CCR_BFHFNMIGN                                   (1UL << 8U)
#define SCB_CCR_DIV_0_TRP                                   (1UL << 4U)
#define SCB_CCR_UNALIGN_TRP                                 (1UL << 3U)
#define SCB_CCR_USERSETMPEND                                (1UL << 1U)
#define SCB_CCR_NONBASETHRDENA                              (1UL )

/****************** bit definitions for SHCSR register ******************/
#define SCB_SHCSR_USGFAULTENA                               (1UL << 18U)
#define SCB_SHCSR_BUSFAULTENA                               (1UL << 17U)
#define SCB_SHCSR_MEMFAULTENA                               (1UL << 16U)
#define SCB_SHCSR_SVCALLPENDED                              (1UL << 15U)
#define SCB_SHCSR_BUSFAULTPENDED                            (1UL << 14U)
#define SCB_SHCSR_MEMFAULTPENDED                            (1UL << 13U)
#define SCB_SHCSR_USGFAULTPENDED                            (1UL << 12U)
#define SCB_SHCSR_SYSTICKACT                                (1UL << 11U)
#define SCB_SHCSR_PENDSVACT                                 (1UL << 10U)
#define SCB_SHCSR_MONITORACT                                (1UL << 8U)
#define SCB_SHCSR_SVCALLACT                                 (1UL << 7U)
#define SCB_SHCSR_USGFAULTACT                               (1UL << 3U)
#define SCB_SHCSR_BUSFAULTACT                               (1UL << 1U)
#define SCB_SHCSR_MEMFAULTACT                               (1UL )

/****************** bit definitions for CFSR register ******************/
#define SCB_CFSR_USGFAULTSR                                 (0xFFFFUL << 16U)
#define SCB_CFSR_BUSFAULTSR                                 (0xFFUL << 8U)
#define SCB_CFSR_MEMFAULTSR                                 (0xFFUL )
#define SCB_CFSR_MMARVALID                                  (1UL << (0U + 7U))
#define SCB_CFSR_MLSPERR                                    (1UL << (0U + 5U))
#define SCB_CFSR_MSTKERR                                    (1UL << (0U + 4U))
#define SCB_CFSR_MUNSTKERR                                  (1UL << (0U + 3U))
#define SCB_CFSR_DACCVIOL                                   (1UL << (0U + 1U))
#define SCB_CFSR_IACCVIOL                                   (1UL )
#define SCB_CFSR_BFARVALID                                  (1UL << (8U + 7U))
#define SCB_CFSR_LSPERR                                     (1UL << (8U + 5U))
#define SCB_CFSR_STKERR                                     (1UL << (8U + 4U))
#define SCB_CFSR_UNSTKERR                                   (1UL << (8U + 3U))
#define SCB_CFSR_IMPRECISERR                                (1UL << (8U + 2U))
#define SCB_CFSR_PRECISERR                                  (1UL << (8U + 1U))
#define SCB_CFSR_IBUSERR                                    (1UL << (8U + 0U))
#define SCB_CFSR_DIVBYZERO                                  (1UL << (16U + 9U))
#define SCB_CFSR_UNALIGNED                                  (1UL << (16U + 8U))
#define SCB_CFSR_NOCP                                       (1UL << (16U + 3U))
#define SCB_CFSR_INVPC                                      (1UL << (16U + 2U))
#define SCB_CFSR_INVSTATE                                   (1UL << (16U + 1U))
#define SCB_CFSR_UNDEFINSTR                                 (1UL << (16U + 0U))

/****************** bit definitions for HFSR register ******************/
#define SCB_HFSR_DEBUGEVT                                   (1UL << 31U)
#define SCB_HFSR_FORCED                                     (1UL << 30U)
#define SCB_HFSR_VECTTBL                                    (1UL << 1U)

/****************** bit definitions for DFSR register ******************/
#define SCB_DFSR_EXTERNAL                                   (1UL << 4U)
#define SCB_DFSR_VCATCH                                     (1UL << 3U)
#define SCB_DFSR_DWTTRAP                                    (1UL << 2U)
#define SCB_DFSR_BKPT                                       (1UL << 1U)
#define SCB_DFSR_HALTED                                     (1UL )

/****************** bit definitions for CLIDR register ******************/
#define SCB_CLIDR_LOUU                                      (7UL << 27U)
#define SCB_CLIDR_LOC                                       (7UL << 24U)

/****************** bit definitions for CTR register ******************/
#define SCB_CTR_FORMAT                                      (7UL << 29U)
#define SCB_CTR_CWG                                         (0xFUL << 24U)
#define SCB_CTR_ERG                                         (0xFUL << 20U)
#define SCB_CTR_DMINLINE                                    (0xFUL << 16U)
#define SCB_CTR_IMINLINE                                    (0xFUL )

/****************** bit definitions for CCSIDR register ******************/
#define SCB_CCSIDR_WT                                       (1UL << 31U)
#define SCB_CCSIDR_WB                                       (1UL << 30U)
#define SCB_CCSIDR_RA                                       (1UL << 29U)
#define SCB_CCSIDR_WA                                       (1UL << 28U)
#define SCB_CCSIDR_NUMSETS                                  (0x7FFFUL << 13U)
#define SCB_CCSIDR_ASSOCIATIVITY                            (0x3FFUL << 3U)
#define SCB_CCSIDR_LINESIZE                                 (7UL )

/****************** bit definitions for CSSELR register ******************/
#define SCB_CSSELR_LEVEL                                    (7UL << 1U)
#define SCB_CSSELR_IND                                      (1UL )

/****************** bit definitions for STIR register ******************/
#define SCB_STIR_INTID                                      (0x1FFUL )

/****************** bit definitions for DCISW register ******************/
#define SCB_DCISW_WAY                                       (3UL << 30U)
#define SCB_DCISW_SET                                       (0x1FFUL << 5U)

/****************** bit definitions for DCCSW register ******************/
#define SCB_DCCSW_WAY                                       (3UL << 30U)
#define SCB_DCCSW_SET                                       (0x1FFUL << 5U)

/****************** bit definitions for DCCISW register ******************/
#define SCB_DCCISW_WAY                                      (3UL << 30U)
#define SCB_DCCISW_SET                                      (0x1FFUL << 5U)

/****************** bit definitions for ITCMCR register ******************/
#define SCB_ITCMCR_SZ                                       (0xFUL << 3U)
#define SCB_ITCMCR_RETEN                                    (1UL << 2U)
#define SCB_ITCMCR_RMW                                      (1UL << 1U)
#define SCB_ITCMCR_EN                                       (1UL )

/****************** bit definitions for DTCMCR register ******************/
#define SCB_DTCMCR_SZ                                       (0xFUL << 3U)
#define SCB_DTCMCR_RETEN                                    (1UL << 2U)
#define SCB_DTCMCR_RMW                                      (1UL << 1U)
#define SCB_DTCMCR_EN                                       (1UL )

/****************** bit definitions for AHBPCR register ******************/
#define SCB_AHBPCR_SZ                                       (7UL << 1U)
#define SCB_AHBPCR_EN                                       (1UL )

/****************** bit definitions for CACR register ******************/
#define SCB_CACR_FORCEWT                                    (1UL << 2U)
#define SCB_CACR_ECCEN                                      (1UL << 1U)
#define SCB_CACR_SIWT                                       (1UL )

/****************** bit definitions for AHBSCR register ******************/
#define SCB_AHBSCR_INITCOUNT                                (0x1FUL << SCB_AHBPCR_INITCOUNT_Pos)
#define SCB_AHBSCR_TPRI                                     (0x1FFUL << SCB_AHBPCR_TPRI_Pos)
#define SCB_AHBSCR_CTL                                      (3UL )

/****************** bit definitions for ABFSR register ******************/
#define SCB_ABFSR_AXIMTYPE                                  (3UL << 8U)
#define SCB_ABFSR_EPPB                                      (1UL << 4U)
#define SCB_ABFSR_AXIM                                      (1UL << 3U)
#define SCB_ABFSR_AHBP                                      (1UL << 2U)
#define SCB_ABFSR_DTCM                                      (1UL << 1U)
#define SCB_ABFSR_ITCM                                      (1UL )

/* register block */
typedef struct {
    reg32_t RESERVED0[1];
    reg32_t ICTR;
    reg32_t ACTRL;
} scb_scs_t;

/****************** bit definitions for BFAR register ******************/
#define SCB_ICTR_INTLINESNUM                                (0xFUL )

/****************** bit definitions for ACTRL register ******************/
#define SCB_ACTLR_DISDYNADD                                 (1UL << 26U)
#define SCB_ACTLR_DISISSCH1                                 (0x1FUL << 21U)
#define SCB_ACTLR_DISDI                                     (0x1FUL << 16U)
#define SCB_ACTLR_DISCRITAXIRUR                             (1UL << 15U)
#define SCB_ACTLR_DISBTACALLOC                              (1UL << 14U)
#define SCB_ACTLR_DISBTACREAD                               (1UL << 13U)
#define SCB_ACTLR_DISITMATBFLUSH                            (1UL << 12U)
#define SCB_ACTLR_DISRAMODE                                 (1UL << 11U)
#define SCB_ACTLR_FPEXCODIS                                 (1UL << 10U)
#define SCB_ACTLR_DISFOLD                                   (1UL << 2U)
#define SCB_ACTLR_DISMCYCINT                                (1UL)

/* set exception priority */
#define SCB_SETEXCPRI(e, p)                     \
    (SCB->SHPR[(e) - 3] = (p))

/* get exception priority */
#define SCB_GETEXCPRI(e)                        \
    (SCB->SHPR[(e) - 3])


#endif /* _STM32H743_SCB2_H */

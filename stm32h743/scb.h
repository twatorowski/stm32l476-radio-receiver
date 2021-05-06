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
#define SCB_ACTRL_BASE                                      0xe000e008U
#define SCB_BASE                                            0xe000ed00U

/* instances */
#define SCB_ACTRL                                           ((scb_actrl_t *)SCB_ACTRL_BASE)
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
    reg32_t RESERVED0[5];
    reg32_t CPACR;
} scb_t;

/****************** bit definitions for CPUID register ******************/
#define SCB_CPUID_REVISION                                  0x0000000f
#define SCB_CPUID_PARTNO                                    0x0000fff0
#define SCB_CPUID_CONSTANT                                  0x000f0000
#define SCB_CPUID_VARIANT                                   0x00f00000
#define SCB_CPUID_IMPLEMENTER                               0xff000000

/****************** bit definitions for ICSR register *******************/
#define SCB_ICSR_VECTACTIVE                                 0x000001ff
#define SCB_ICSR_RETTOBASE                                  0x00000800
#define SCB_ICSR_VECTPENDING                                0x0007f000
#define SCB_ICSR_ISRPENDING                                 0x00400000
#define SCB_ICSR_PENDSTCLR                                  0x02000000
#define SCB_ICSR_PENDSTSET                                  0x04000000
#define SCB_ICSR_PENDSVCLR                                  0x08000000
#define SCB_ICSR_PENDSVSET                                  0x10000000
#define SCB_ICSR_NMIPENDSET                                 0x80000000

/****************** bit definitions for VTOR register *******************/
#define SCB_VTOR_TBLOFF                                     0x3ffffe00

/****************** bit definitions for AIRCR register ******************/
#define SCB_AIRCR_VECTRESET                                 0x00000001
#define SCB_AIRCR_VECTCLRACTIVE                             0x00000002
#define SCB_AIRCR_SYSRESETREQ                               0x00000004
#define SCB_AIRCR_PRIGROUP                                  0x00000700
#define SCB_AIRCR_ENDIANESS                                 0x00008000
#define SCB_AIRCR_VECTKEYSTAT                               0xffff0000

/******************* bit definitions for SCR register *******************/
#define SCB_SCR_SLEEPONEXIT                                 0x00000002
#define SCB_SCR_SLEEPDEEP                                   0x00000004
#define SCB_SCR_SEVEONPEND                                  0x00000010

/******************* bit definitions for CCR register *******************/
#define SCB_CCR_NONBASETHRDENA                              0x00000001
#define SCB_CCR_USERSETMPEND                                0x00000002
#define SCB_CCR_UNALIGN__TRP                                0x00000008
#define SCB_CCR_DIV_0_TRP                                   0x00000010
#define SCB_CCR_BFHFNMIGN                                   0x00000100
#define SCB_CCR_STKALIGN                                    0x00000200
#define SCB_CCR_DC                                          0x00010000
#define SCB_CCR_IC                                          0x00020000
#define SCB_CCR_BP                                          0x00040000

/****************** bit definitions for SHPR1 register ******************/
#define SCB_SHPR1_PRI_4                                     0x000000ff
#define SCB_SHPR1_PRI_5                                     0x0000ff00
#define SCB_SHPR1_PRI_6                                     0x00ff0000

/****************** bit definitions for SHPR2 register ******************/
#define SCB_SHPR2_PRI_11                                    0xff000000

/****************** bit definitions for SHPR3 register ******************/
#define SCB_SHPR3_PRI_14                                    0x00ff0000
#define SCB_SHPR3_PRI_15                                    0xff000000

/****************** bit definitions for SHCRS register ******************/
#define SCB_SHCRS_MEMFAULTACT                               0x00000001
#define SCB_SHCRS_BUSFAULTACT                               0x00000002
#define SCB_SHCRS_USGFAULTACT                               0x00000008
#define SCB_SHCRS_SVCALLACT                                 0x00000080
#define SCB_SHCRS_MONITORACT                                0x00000100
#define SCB_SHCRS_PENDSVACT                                 0x00000400
#define SCB_SHCRS_SYSTICKACT                                0x00000800
#define SCB_SHCRS_USGFAULTPENDED                            0x00001000
#define SCB_SHCRS_MEMFAULTPENDED                            0x00002000
#define SCB_SHCRS_BUSFAULTPENDED                            0x00004000
#define SCB_SHCRS_SVCALLPENDED                              0x00008000
#define SCB_SHCRS_MEMFAULTENA                               0x00010000
#define SCB_SHCRS_BUSFAULTENA                               0x00020000
#define SCB_SHCRS_USGFAULTENA                               0x00040000

/********** bit definitions for CFSR_UFSR_BFSR_MMFSR register ***********/
#define SCB_CFSR_IACCVIOL                                   0x00000001
#define SCB_CFSR_DACCVIOL                                   0x00000002
#define SCB_CFSR_MUNSTKERR                                  0x00000008
#define SCB_CFSR_MSTKERR                                    0x00000010
#define SCB_CFSR_MLSPERR                                    0x00000020
#define SCB_CFSR_MMARVALID                                  0x00000080
#define SCB_CFSR_IBUSERR                                    0x00000100
#define SCB_CFSR_PRECISERR                                  0x00000200
#define SCB_CFSR_IMPRECISERR                                0x00000400
#define SCB_CFSR_UNSTKERR                                   0x00000800
#define SCB_CFSR_STKERR                                     0x00001000
#define SCB_CFSR_LSPERR                                     0x00002000
#define SCB_CFSR_BFARVALID                                  0x00008000
#define SCB_CFSR_UNDEFINSTR                                 0x00010000
#define SCB_CFSR_INVSTATE                                   0x00020000
#define SCB_CFSR_INVPC                                      0x00040000
#define SCB_CFSR_NOCP                                       0x00080000
#define SCB_CFSR_UNALIGNED                                  0x01000000
#define SCB_CFSR_DIVBYZERO                                  0x02000000

/****************** bit definitions for HFSR register *******************/
#define SCB_HFSR_VECTTBL                                    0x00000002
#define SCB_HFSR_FORCED                                     0x40000000
#define SCB_HFSR_DEBUG_VT                                   0x80000000

/****************** bit definitions for MMFAR register ******************/
#define SCB_MMFAR_ADDRESS                                   0xffffffff

/****************** bit definitions for BFAR register *******************/
#define SCB_BFAR_ADDRESS                                    0xffffffff

/* register block */
typedef struct {
    reg32_t ACTRL;
}scb_actrl_t;

/****************** bit definitions for ACTRL register ******************/
#define SCB_ACTRL_DISFOLD                                   0x00000004
#define SCB_ACTRL_FPEXCODIS                                 0x00000400
#define SCB_ACTRL_DISRAMODE                                 0x00000800
#define SCB_ACTRL_DISITMATBFLUSH                            0x00001000

/* set exception priority */
#define SCB_SETEXCPRI(e, p)                     \
    (SCB->SHPR[(e) - 4] = (p))

/* get exception priority */
#define SCB_GETEXCPRI(e)                        \
    (SCB->SHPR[(e) - 4])

#endif /* STM32H743_SCB_H */

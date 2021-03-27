/**
 * @file nvic.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: NVIC
 */


#ifndef STM32H743_NVIC_H
#define STM32H743_NVIC_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define NVIC_BASE                                           0xe000e100U
#define NVIC_STIR_BASE                                      0xe000ef00U

/* instances */
#define NVIC                                                ((nvic_t *)NVIC_BASE)     
#define NVIC_STIR                                           ((nvic_stir_t *)NVIC_STIR_BASE)

/* register bank */
typedef struct {
    reg32_t ISER[8];               
    reg32_t RESERVED0[24];
    reg32_t ICER[8];               
    reg32_t RSERVED1[24];
    reg32_t ISPR[8];               
    reg32_t RESERVED2[24];
    reg32_t ICPR[8];
    reg32_t RESERVED3[24];
    reg32_t IABR[8];
    reg32_t RESERVED4[56];
    reg8_t  IP[240];
} nvic_t;

/****************** bit definitions for ISER0 register ******************/
#define NVIC_ISER_SETENA                                    0xffffffff

/****************** bit definitions for ICER0 register ******************/
#define NVIC_ICER_CLRENA                                    0xffffffff

/****************** bit definitions for ISPR0 register ******************/
#define NVIC_ISPR_SETPEND                                   0xffffffff

/****************** bit definitions for ICPR0 register ******************/
#define NVIC_ICPR_CLRPEND                                   0xffffffff

/****************** bit definitions for IABR0 register ******************/
#define NVIC_IABR_ACTIVE                                    0xffffffff

/****************** bit definitions for IPR0 register *******************/
#define NVIC_IPR_IPR_N0                                     0x000000ff
#define NVIC_IPR_IPR_N1                                     0x0000ff00
#define NVIC_IPR_IPR_N2                                     0x00ff0000
#define NVIC_IPR_IPR_N3                                     0xff000000

/* register bank */
typedef struct {
    reg32_t STIR;
} nvic_stir_t;

/****************** bit definitions for STIR register *******************/
#define NVIC_STIR_INTID                                     0x000001ff

/* enable interrupt */
#define NVIC_ENABLEINT(i)                    \
    (NVIC->ISER[(i) / 32] = 1 << ((i) % 32))

/* disable interrupt */
#define NVIC_DISABLEINT(i)                    \
    (NVIC->ICER[(i) / 32] = 1 << ((i) % 32))

/* set pending interrupt */
#define NVIC_SETPENDING(i)                    \
    (NVIC->ISPR[(i) / 32] = 1 << ((i) % 32))

/* clear pending interrupt */
#define NVIC_CLEARPENDING(i)                \
    (NVIC->ICPR[(i) / 32] = 1 << ((i) % 32))

/* set interrupt priority */
#define NVIC_SETINTPRI(i, p)                \
    (NVIC->IP[i] = (p))

/* get interrupt priority */
#define NVIC_GETINTPRI(i)                    \
    (NVIC->IP[i])

#endif /* STM32H743_NVIC_H */

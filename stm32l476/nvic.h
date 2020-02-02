/**
 * @file nvic.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: NVIC
 */

#ifndef STM32L476_NVIC_H_
#define STM32L476_NVIC_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define NVIC_BASE							0xE000E100
/* nvic & scb */
#define NVIC								((nvic_t *) NVIC_BASE)

/* nvic registers */
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
	reg8_t	IP[240];
	reg32_t RESERVED5[644];
	reg32_t STIR;
} __attribute__((packed, aligned(4))) nvic_t;

/* enable interrupt */
#define NVIC_ENABLEINT(i)					\
	(NVIC->ISER[(i) / 32] = 1 << ((i) % 32))

/* disable interrupt */
#define NVIC_DISABLEINT(i)					\
	(NVIC->ICER[(i) / 32] = 1 << ((i) % 32))

/* set pending interrupt */
#define NVIC_SETPENDING(i)					\
	(NVIC->ISPR[(i) / 32] = 1 << ((i) % 32))

/* clear pending interrupt */
#define NVIC_CLEARPENDING(i)				\
	(NVIC->ICPR[(i) / 32] = 1 << ((i) % 32))

/* set interrupt priority */
#define NVIC_SETINTPRI(i, p)				\
	(NVIC->IP[i] = (p))

/* get interrupt priority */
#define NVIC_GETINTPRI(i)				    \
	(NVIC->IP[i])

#endif /* STM32L476_NVIC_H_ */

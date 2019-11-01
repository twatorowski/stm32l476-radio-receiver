/**
 * @file systick.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: SYSTICK
 */

#ifndef STM32L476_SYSTICK_H_
#define STM32L476_SYSTICK_H_

#include "stm32l476/stm32l476.h"

/* reg base */
#define SYSTICK_BASE						0xE000E010
/* systick */
#define SYSTICK								((systick_t *)SYSTICK_BASE)

/* register */
typedef struct {
	reg32_t CSR;
	reg32_t RVR;
	reg32_t CVR;
	reg32_t CAL;
} __attribute__((packed, aligned(4))) systick_t;

/* ctrl register */
#define SYSTICK_CSR_ENABLE					(0x00000001)
#define SYSTICK_CSR_TICKINT					(0x00000002)
#define SYSTICK_CSR_CLKSOURCE				(0x00000004)
#define SYSTICK_CSR_COUNTFLAG				(0x00010000)

/* cal register */
#define SYSTICK_CALIB_TENMS					(0x00FFFFFF)
#define SYSTICK_CALIB_SKEW					(0x40000000)
#define SYSTICK_CALIB_NOREF					(0x80000000)

#endif /* STM32L476_SYSTICK_H_ */

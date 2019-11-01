/**
 * @file wwdg.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: WWDG
 */
#ifndef STM32L476_WWDG_H_
#define STM32L476_WWDG_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define WWDG_BASE							(0x40002C00)
/* watchdog */
#define WWDG								((wwdg_t *)WWDG_BASE)

/* watchdog registers */
typedef struct {
	reg32_t CR;
	reg32_t CFR;
	reg32_t SR;
} __attribute__((packed, aligned(4))) wwdg_t;

/* Control register */
#define WWDG_CR_T							(0x7F)
#define WWDG_CR_T0							(0x01)
#define WWDG_CR_T1							(0x02)
#define WWDG_CR_T2							(0x04)
#define WWDG_CR_T3							(0x08)
#define WWDG_CR_T4							(0x10)
#define WWDG_CR_T5							(0x20)
#define WWDG_CR_T6							(0x40)
#define WWDG_CR_WDGA						(0x80)

/* Configuration register */
#define WWDG_CFR_W							(0x007F)
#define WWDG_CFR_W0							(0x0001)
#define WWDG_CFR_W1							(0x0002)
#define WWDG_CFR_W2							(0x0004)
#define WWDG_CFR_W3							(0x0008)
#define WWDG_CFR_W4							(0x0010)
#define WWDG_CFR_W5							(0x0020)
#define WWDG_CFR_W6							(0x0040)
#define WWDG_CFR_WDGTB						(0x0180)
#define WWDG_CFR_WDGTB0						(0x0080)
#define WWDG_CFR_WDGTB1						(0x0100)
#define WWDG_CFR_EWI						(0x0200)

/* Status register */
#define WWDG_SR_EWIF						(0x01)


#endif /* STM32L476_WWDG_H_ */

/**
 * @file iwdg.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: IWDG
 */

#ifndef STM32L476_IWDG_H_
#define STM32L476_IWDG_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define IWDG_BASE							(0x48000000)

/* iwdg */
#define IWDG								((iwdg_t *) IWDG_BASE)

/* gpio registers */
typedef struct {
	reg32_t KR;
	reg32_t PR;
	reg32_t RLR;
	reg32_t SR;
	reg32_t WINR;
} __attribute__((packed, aligned(4))) iwdg_t;

/*	Bit definition for IWDG_KR register  */
#define IWDG_KR_KEY							(0x0000FFFF)
#define IWDG_KR_KEY_RELOAD					(0x0000AAAA)
#define IWDG_KR_KEY_ACCESS					(0x00005555)
#define IWDG_KR_KEY_START					(0x0000CCCC)

/*	Bit definition for IWDG_PR register  */
#define IWDG_PR_PR							(0x00000007)
#define IWDG_PR_PR_0						(0x00000001)
#define IWDG_PR_PR_1						(0x00000002)
#define IWDG_PR_PR_2						(0x00000004)

/*	Bit definition for IWDG_RLR register  */
#define IWDG_RLR_RL							(0x00000FFF)

/*	Bit definition for IWDG_SR register  */
#define IWDG_SR_PVU							(0x00000001)
#define IWDG_SR_RVU							(0x00000002)
#define IWDG_SR_WVU							(0x00000004)

/*	Bit definition for IWDG_KR register  */
#define IWDG_WINR_WIN						(0x00000FFF)

#endif /* STM32L476_IWDG_H_ */

/*
 * lcd.h
 *
 *  Created on: 30-07-2016
 *      Author: Tomek
 */

#ifndef STM32L476_LCD_H_
#define STM32L476_LCD_H_

#include <stm32l476/stm32l476.h>

/* register base address */
#define LCD_BASE             				(0x40002400)

/* register base */
#define LCD									((lcd_t *)LCD_BASE)

/* registers */
typedef struct {
	reg32_t CR;
	reg32_t FCR;
	reg32_t SR;
	reg32_t CLR;
	reg32_t RESERVED;
	reg32_t RAM[16];
} lcd_t;

/*  Bit definition for LCD_CR register  */
#define LCD_CR_LCDEN               			(0x00000001)
#define LCD_CR_VSEL                			(0x00000002)
#define LCD_CR_DUTY                			(0x0000001C)
#define LCD_CR_DUTY_0              			(0x00000004)
#define LCD_CR_DUTY_1              			(0x00000008)
#define LCD_CR_DUTY_2              			(0x00000010)
#define LCD_CR_BIAS                			(0x00000060)
#define LCD_CR_BIAS_0              			(0x00000020)
#define LCD_CR_BIAS_1              			(0x00000040)
#define LCD_CR_MUX_SEG             			(0x00000080)
#define LCD_CR_BUFEN               			(0x00000100)

/*  Bit definition for LCD_FCR register  */
#define LCD_FCR_HD                 			(0x00000001)
#define LCD_FCR_SOFIE              			(0x00000002)
#define LCD_FCR_UDDIE              			(0x00000008)
#define LCD_FCR_PON                			(0x00000070)
#define LCD_FCR_PON_0              			(0x00000010)
#define LCD_FCR_PON_1              			(0x00000020)
#define LCD_FCR_PON_2              			(0x00000040)
#define LCD_FCR_DEAD               			(0x00000380)
#define LCD_FCR_DEAD_0             			(0x00000080)
#define LCD_FCR_DEAD_1             			(0x00000100)
#define LCD_FCR_DEAD_2             			(0x00000200)
#define LCD_FCR_CC                 			(0x00001C00)
#define LCD_FCR_CC_0               			(0x00000400)
#define LCD_FCR_CC_1               			(0x00000800)
#define LCD_FCR_CC_2               			(0x00001000)
#define LCD_FCR_BLINKF             			(0x0000E000)
#define LCD_FCR_BLINKF_0           			(0x00002000)
#define LCD_FCR_BLINKF_1           			(0x00004000)
#define LCD_FCR_BLINKF_2           			(0x00008000)
#define LCD_FCR_BLINK              			(0x00030000)
#define LCD_FCR_BLINK_0            			(0x00010000)
#define LCD_FCR_BLINK_1            			(0x00020000)
#define LCD_FCR_DIV                			(0x003C0000)
#define LCD_FCR_PS                 			(0x03C00000)

/*  Bit definition for LCD_SR register  */
#define LCD_SR_ENS                 			(0x00000001)
#define LCD_SR_SOF                 			(0x00000002)
#define LCD_SR_UDR                 			(0x00000004)
#define LCD_SR_UDD                 			(0x00000008)
#define LCD_SR_RDY                 			(0x00000010)
#define LCD_SR_FCRSR               			(0x00000020)

/*  Bit definition for LCD_CLR register  */
#define LCD_CLR_SOFC               			(0x00000002)
#define LCD_CLR_UDDC               			(0x00000008)

/*  Bit definition for LCD_RAM register  */
#define LCD_RAM_SEGMENT_DATA       			(0xFFFFFFFF)

#endif /* STM32L476_LCD_H_ */

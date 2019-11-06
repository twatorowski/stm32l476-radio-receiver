/**
 * @file display.c
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief LCD Multi-segment display driver. Drives the stm32l4-discover on-board 
 * display. Uses LSE clock.
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "stm32l476/rcc.h"
#include "stm32l476/gpio.h"
#include "stm32l476/lcd.h"
#include "sys/critical.h"

/* digits: 0 - 9 */
static const uint16_t digs[] = {
	 0x5F00, 0x4200, 0xF500, 0xE700, 0xEA00,
	 0xAF00, 0xBF00, 0x4600, 0xFF00, 0xEF00
};

/* letters: A - Z */
static const uint16_t lets[] = {
	0xFE00, 0x6714, 0x1D00, 0x4714, 0x9D00, 0x9C00, 0x3F00, 0xFA00, 0x0014,
	0x5300, 0x9841, 0x1900, 0x5A48, 0x5A09, 0x5F00, 0xFC00, 0x5F01, 0xFC01,
	0xAF00, 0x0414, 0x5b00, 0x18C0, 0x5A81, 0x00C9, 0x0058, 0x05C0
};

/* segment look up table */
static const uint8_t lut[] = {
	/* bit numbers for segments in order:
	 * e-m-b-g, d-c-a-f, p-col-k-q, n-dp-j-h */
	 4, 23, 22,  3,  6, 13, 12,  5,
	15, 29, 28, 14, 31, 33, 32, 30,
	35, 25, 24, 34, 17,  8,  9, 26,
};
/* character masks */
static const uint32_t masks[] = {
	0x00C00018, 0x00000000, 0x00003060, 0x00000000,
	0x3000C000, 0x00000000, 0xC0000000, 0x00000003,
	0x03000000, 0x0000000C, 0x04020300, 0x00000000,
};

/* display digit on a given position */
static void Display_SetDisplay(int pos, uint16_t v)
{
	/* prepare ram registers */
	uint32_t r0, r1, m0 = 0, m1 = 0;
	/* initial lut offset */
	const uint8_t *l = lut + (pos * 4);

	/* masks for whole character  */
	m0 = masks[pos * 2 + 0], m1 = masks[pos * 2 + 1];
	/* process all four nibbles */
	for (int com = 0; com < 4; com++) {
		/* reset variables */
		r0 = 0, r1 = 0;
		/* get segments that are about to get lit */
		if (v & 0x1000) r0 |= 1 << l[0], r1 |= 1 << (l[0] - 32);
		if (v & 0x2000) r0 |= 1 << l[1], r1 |= 1 << (l[1] - 32);
		if (v & 0x4000) r0 |= 1 << l[2], r1 |= 1 << (l[2] - 32);
		if (v & 0x8000) r0 |= 1 << l[3], r1 |= 1 << (l[3] - 32);

		/* update ram */
		LCD->RAM[com * 2 + 0] = (LCD->RAM[com * 2 + 0] & ~m0) | r0;
		LCD->RAM[com * 2 + 1] = (LCD->RAM[com * 2 + 1] & ~m1) | r1;
		/* shift nibble */
		v = v << 4;
	}
}

/* initialize display */
int Display_Init(void)
{
	/* enter critical section */
	Critical_Enter();
	/* enable gpios */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN |
			RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIODEN;
	/* enable lcd */
	RCC->APB1ENR1 |= RCC_APB1ENR1_LCDEN;

	/* reset lcd */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_LCDRST;
	/* disable reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_LCDRST;

	/* reset port a */
	GPIOA->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7 |
			GPIO_MODER_MODER8 | GPIO_MODER_MODER9 | GPIO_MODER_MODER10 |
			GPIO_MODER_MODER15);
	/* select alternate function */
	GPIOA->AFRL |= 11 << (6 * 4) | 11 << (7 * 4);
	/* select alternate function */
	GPIOA->AFRH |= 11 << (0 * 4) | 11 << (1 * 4) | 11 << (2 * 4) |
			11 << (7 * 4);
	/* set as peripheral driven */
	GPIOA->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1 |
			GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1 |
			GPIO_MODER_MODER15_1;

	/* reset port b */
	GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 |
			GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER9 |
			GPIO_MODER_MODER12 | GPIO_MODER_MODER13 | GPIO_MODER_MODER14 |
			GPIO_MODER_MODER15);
	/* select alternate function */
	GPIOB->AFRL |= 11 << (0 * 4) | 11 << (1 * 4) | 11 << (4 * 4) |
			11 << (5 * 4);
	/* select alternate function */
	GPIOB->AFRH |= 11 << (1 * 4) | 11 << (4 * 4) | 11 << (5 * 4) |
			11 << (6 * 4) | 11 << (7 * 4);
	/* set as peripheral driven */
	GPIOB->MODER |= GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1 |
			GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1 | GPIO_MODER_MODER9_1 |
			GPIO_MODER_MODER12_1 | GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1 |
			GPIO_MODER_MODER15_1;

	/* reset port c */
	GPIOC->MODER &= ~(GPIO_MODER_MODER3 | GPIO_MODER_MODER4 |
			GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7 |
			GPIO_MODER_MODER8);
	/* select alternate function */
	GPIOC->AFRL |= 11 << (3 * 4) | 11 << (4 * 4) | 11 << (5 * 4) |
			11 << (6 * 4) | 11 << (7 * 4);
	/* select alternate function */
	GPIOC->AFRH |= 11 << (0 * 4);
	/* set as peripheral driven */
	GPIOC->MODER |= GPIO_MODER_MODER3_1 | GPIO_MODER_MODER4_1 |
			GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1 |
			GPIO_MODER_MODER8_1;

	/* reset port d */
	GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9 |
			GPIO_MODER_MODER10 | GPIO_MODER_MODER11 | GPIO_MODER_MODER12 |
			GPIO_MODER_MODER13 | GPIO_MODER_MODER14 | GPIO_MODER_MODER15);
	/* select alternate function */
	GPIOD->AFRH |= 11 << (0 * 4) | 11 << (1 * 4) | 11 << (2 * 4) |
			11 << (3 * 4) | 11 << (4 * 4) | 11 << (5 * 4) | 11 << (6 * 4) |
			11 << (7 * 4);
	/* set as peripheral driven */
	GPIOD->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1 |
			GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1 |
			GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1 | GPIO_MODER_MODER15_1;

	/* setup control register */
	LCD->CR = LCD_CR_DUTY_2 | LCD_CR_BIAS_1;
	/* set up frame register: pulse on = 1/4, no dead time, contrast = 5,
	 * blink = flcd / 32, divider = 31, prescaler = 1 */
	LCD->FCR = LCD_FCR_PON_2 | LCD_FCR_CC_2 | LCD_FCR_CC_0 | LCD_FCR_BLINKF_1 |
			LCD_FCR_DIV;
	/* enable */
	LCD->CR |= LCD_CR_LCDEN;

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* display a character */
void Display_SetCharacter(int pos, char c)
{
    /* unsupported characters will be displayed as spaces */
	uint16_t val = 0x0000;
	/* digits */
	if (c >= '0' && c <= '9') {
		val = digs[c - '0'];
	/* letters */
	} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		/* make there uppercase */
		c &= ~0x20;
		/* get value */
		val = lets[c - 'A'];
	}

    /* set character at given position */
	Display_SetDisplay(pos, val);
}

/* update display */
void Display_Update(void)
{
	/* clear flag */
	LCD->CLR = LCD_CLR_UDDC;
	/* transfer ram contents to display */
	LCD->SR = LCD_SR_UDR;
	/* wait for previous transfer to be completed */
	while (!(LCD->SR & LCD_SR_UDD));
}
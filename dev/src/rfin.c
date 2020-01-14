/**
 * @file rfin.c
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief RF Input driver module
 */

#include "assert.h"
#include "compiler.h"
#include "err.h"
#include "stm32l476/rcc.h"
#include "stm32l476/gpio.h"
#include "sys/critical.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"

/* radio frequency input pin */
int RFIn_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable gpioa */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	/* enable opamp clock */
	RCC->APB1ENR1 |= RCC_APB1ENR1_OPAMPEN;

	/* reset op-amp */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_OPAMPRST;
	/* release reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_OPAMPRST;

	/* set pa0 as analog input and pa3 as analog output */
	GPIOA->MODER |= GPIO_MODER_MODER0;
	/* enable analog switch */
	GPIOA->ASCR |= GPIO_ASCR_ASC0;

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}


/**
 * @file extimux.c
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief EXII Interrupts multiplexer. Since EXTI interrupts are grouped (at 
 * least the high-number extis) this piece of code is responsible for undoing 
 * the grouping.
 */

#include "config.h"
#include "err.h"
#include "stm32l476/rcc.h"
#include "stm32l476/exti.h"
#include "stm32l476/nvic.h"
#include "stm32l476/syscfg.h"
#include "sys/critical.h"

/* routines */
#include "dev/joystick.h"

/* exti interrupt mux for lines 5 to 9 */
void ExtiMux_Exti5_9Isr(void)
{
	/* get pending register */
	uint32_t pr = EXTI->PR1;

	/* key press interrupt */
	if (pr & EXTI_PR1_PIF5)
		Joystick_Exti1_3_5Isr();
}

/* exti interrupt mux for lines 10 to 15 */
void ExtiMux_Exti10_15Isr(void)
{
//	/* get pending register */
//	uint32_t pr = EXTI->PR1;
}

/* initialize exti mux */
int ExtiMux_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable syscfg */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI5_9, INT_PRI_EXI5_9);
	/* enable */
	NVIC_ENABLEINT(STM32_INT_EXTI5_9);

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI10_15, INT_PRI_EXI10_15);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_EXTI10_15);

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}
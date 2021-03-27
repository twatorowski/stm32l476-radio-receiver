/**
 * @file systime.c
 * 
 * @date 2021-01-26
 * @author twatorowski 
 * 
 * @brief System timer
 */

#include "config.h"
#include "err.h"
#include "sys/critical.h"
#include "stm32h743/rcc.h"
#include "stm32h743/timer.h"

/* reset time base */
int SysTime_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable tim2 clock */
	RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
    /* wait for the timer to be started */
    while ((RCC->APB1LENR & RCC_APB1LENR_TIM2EN) == 0);

	/* set prescaler to obtain 100us pulse */
	TIM2->PSC = ((APB1CLOCK_HZ) / 10000) - 1;
	/* set autoreload value */
	TIM2->ARR = 0xffffffff;
	/* reset value */
	TIM2->CNT = 0;
	/* set update event */
	TIM2->EGR = TIM_EGR_UG;
	/* enable timer */
	TIM2->CR1 = TIM_CR1_CEN;

	/* exit critical section */
	Critical_Exit();

	/* not much could go wrong here */
	return EOK;
}

/* get time */
uint32_t SysTime_GetTime(void)
{
    /* return the timer value in 100us ticks */
    return TIM2->CNT;
}

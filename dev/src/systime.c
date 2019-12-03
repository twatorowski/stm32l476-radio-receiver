/**
 * @file systime.c
 * 
 * @date 2019-11-05
 * @author twatorowski
 * 
 * @brief System Timer Module
 */

#include "config.h"
#include "err.h"
#include "dev/watchdog.h"
#include "stm32l476/rcc.h"
#include "stm32l476/timer.h"
#include "sys/critical.h"
#include "sys/time.h"

/* reset time base */
int SysTime_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable tim5 clock */
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;

	/* set prescaler (500us) */
	TIM5->PSC = (CPUCLOCK_FREQ / 2000) - 1;
	/* set autoreload value */
	TIM5->ARR = 0xffffffff;
	/* reset value */
	TIM5->CNT = 0;
	/* set update event */
	TIM5->EGR = TIM_EGR_UG;
	/* enable timer */
	TIM5->CR1 = TIM_CR1_CEN;

	/* exit critical section */
	Critical_Exit();

	/* not much could go wrong here */
	return EOK;
}

/* delay in ms */
void SysTime_Delay(uint32_t ms)
{
	/* get current time */
	uint32_t x = TIM5->CNT;
	/* blocking wait */
	while (TIM5->CNT - x < ms * 2)
		Watchdog_Kick();
}

/* set current time */
void SysTime_SetTime(uint32_t t)
{
	/* apply new setting */
	TIM5->CNT = t * 2;
}
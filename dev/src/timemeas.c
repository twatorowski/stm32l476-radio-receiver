/**
 * @file timemeas.c
 * 
 * @date 2020-01-13
 * @author twatorowski 
 * 
 * @brief microsecond Time measurement module. Perfect tool for performance 
 * analysis
 */

#include "assert.h"
#include "config.h"
#include "err.h"
#include "stm32l476/rcc.h"
#include "stm32l476/timer.h"
#include "sys/critical.h"

/* time measurement timer initialization */
int TimeMeas_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable timer 8 */
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

    /* can we even clock one microsecond? */
    assert((int)CPUCLOCK_FREQ / 1000000 * 1000000 == CPUCLOCK_FREQ, 
        "cpu clock frequency must be divisible by 1000000", CPUCLOCK_FREQ);

	/* reset prescaler: 1us per tick */
	TIM8->PSC = (CPUCLOCK_FREQ / 1000000) - 1;
	/* max val */
	TIM8->ARR = 0xffff;
	/* update timer */
	TIM8->EGR = TIM_EGR_UG;
	/* enable counter */
	TIM8->CR1 = TIM_CR1_CEN;

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* get timestamp */
uint16_t TimeMeas_GetTimeStamp(void)
{
    /* report the timer value */
    return TIM8->CNT;
}
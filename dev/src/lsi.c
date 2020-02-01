/**
 * @file lsi.c
 * 
 * @date 2020-02-01
 * @author twatorowski 
 * 
 * @brief Low Speed Oscillator driver
 */

#include "err.h"
#include "stm32l476/rcc.h"
#include "stm32l476/pwr.h"
#include "sys/critical.h"

/* initialize low speed oscillator */
int LSI_Init(void)
{
    /* enter critical section */
	Critical_Enter();

    /* enable the pwr */
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    
    /* start lsi clock */
	RCC->CSR |= RCC_CSR_LSION;
	/* wait till it becomes stable */
	while ((RCC->CSR & RCC_CSR_LSIRDY) == 0);

    /* select lsi as RTCCLK/LCDCLK */
	/* disable register protection */
	PWR->CR1 |= PWR_CR1_DBP;
	/* select clock */
	RCC->BDCR |= RCC_BDCR_RTCSEL_1;
    
	/* enter critical section */
	Critical_Exit();

    /* report status */
    return EOK;
}


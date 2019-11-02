/**
 * @file cpuclock.c
 * 
 * @date 2019-11-02
 * @author twatorowski
 * 
 * @brief Setup the MCU's operating frequency
 */

#include "err.h"
#include "stm32l476/rcc.h"
#include "stm32l476/pwr.h"
#include "stm32l476/flash.h"
#include "sys/critical.h"
#include "util/msblsb.h"

/* initialize cpu clock to 80MHz */
int CpuClock_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* configure latency: 4ws */
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS | FLASH_ACR_PRFTEN;

	/* enable crystal oscillator */
	RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
	/* wait till its enabled */
	while (!(RCC->CR & RCC_CR_HSERDY));

	/* configure pll, REF = HSE (8MHz) / 1 (M) = 8MHz, VCO = REF * N =
	 * 8MHz * 20 = 160MHz, OUT = VCO / R = 160MHz / 2 = 80MHz */
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE | 40 << LSB(RCC_PLLCFGR_PLLN) | 
        0 << LSB(RCC_PLLCFGR_PLLM) | RCC_PLLCFGR_PLLREN;
	/* enable pll */
	RCC->CR |= RCC_CR_PLLON;
	/* wait till its enabled */
	while (!(RCC->CR & RCC_CR_PLLRDY));

	/* select pll as a system clock */
	RCC->CFGR = RCC_CFGR_SW_PLL;
	/* wait till its selected */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	/* start lsi clock */
	RCC->CSR |= RCC_CSR_LSION;
	/* wait till it becomes stable */
	while ((RCC->CSR & RCC_CSR_LSIRDY) == 0);

	/* select lsi as RTCCLK/LCDCLK */
	/* disable register protection */
	PWR->CR1 |= PWR_CR1_DBP;
	/* select clock */
	RCC->BDCR |= RCC_BDCR_RTCSEL_1;

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}
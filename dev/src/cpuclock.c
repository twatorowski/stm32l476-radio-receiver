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

    /* configure msi oscillator for 48MHz operation */
	RCC->CR = (RCC->CR & ~RCC_CR_MSIRANGE) | RCC_CR_MSIRANGE_11;
	/* select msi range configuration */
	RCC->CR |= RCC_CR_MSIRGSEL;

    /* select the msi as the 48MHz source TODO: */
    RCC->CCIPR |= RCC_CCIPR_CLK48SEL;

	/* enable crystal oscillator */
	RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
	/* wait till its enabled */
	while (!(RCC->CR & RCC_CR_HSERDY));

	/* configure pll, REF = HSE (8MHz) / 2 (M) = 4MHz, VCO = REF * N =
	 * 4MHz * 36 = 144MHz, OUT = VCO / R = 144MHz / 2 = 72MHz */
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE | 36 << LSB(RCC_PLLCFGR_PLLN) | 
        (2 - 1) << LSB(RCC_PLLCFGR_PLLM) | 0 << LSB(RCC_PLLCFGR_PLLR) | 
        RCC_PLLCFGR_PLLREN;
	/* enable pll */
	RCC->CR |= RCC_CR_PLLON;
	/* wait till its enabled */
	while (!(RCC->CR & RCC_CR_PLLRDY));

	/* select pll as a system clock */
	RCC->CFGR = RCC_CFGR_SW_PLL;
	/* wait till its selected */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);


	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}
/**
 * @file analog.c
 * 
 * @date 2019-11-05
 * @author twatorowski
 * 
 * @brief ADC sampler driver module
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "dev/analog.h"
#include "stm32l476/rcc.h"
#include "stm32l476/nvic.h"
#include "stm32l476/dma.h"
#include "stm32l476/adc.h"
#include "stm32l476/timer.h"
#include "sys/critical.h"
#include "sys/ev.h"

/* event */
ev_t analog_ev;

/* adc dma1 interrupt */
void Analog_DMA1C1Isr(void)
{
	/* build up event argument */
	analog_evarg_t ea = { ANALOG_TYPE_HT };
	/* get interrupt flags */
	uint32_t isr = DMA1->ISR & (DMA_ISR_TCIF1 | DMA_ISR_HTIF1);
	/* clear interrupt */
	DMA1->IFCR = isr;

	/* full transfer occured? */
	if (isr & DMA_ISR_TCIF1)
		ea.type = ANALOG_TYPE_FT;

	/* notify others */
	Ev_Notify(&analog_ev, &ea);
}
/* initialize adc */
int Analog_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	/* enable adc */
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	/* enable timer */
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	/* reset adc */
	RCC->AHB2RSTR |= RCC_AHB2RSTR_ADCRST;
	/* disable reset */
	RCC->AHB2RSTR &= ~RCC_AHB2RSTR_ADCRST;

	/* reset timer */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM2RST;
	/* disable reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM2RST;

	/* configure timer */
	/* reset prescaler */
	TIM2->PSC = 0;
	/* select output event generation on every update event */
	TIM2->CR2 = TIM_CR2_MMS_UPDATE;
	/* disable update generation on setting the ug bit */
	TIM2->CR1 = TIM_CR1_URS;
	/* apply prescaler setting */
	TIM2->EGR = TIM_EGR_UG;

	/* select dma channel */
	DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C1S) | DMA1_CSELR_C1S_ADC1;
	/* select mode: 16b transfers, circular buffer, generate interrupts */
	DMA1C1->CCR = DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 |
			DMA_CCR_CIRC | DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_MINC;
	/* select source register */
	DMA1C1->CPAR = (uint32_t)&ADC1->DR;

	/* set interrupt priority */
	NVIC_SETINTPRI(STM32_INT_DMA1C1, 0x10);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_DMA1C1);

	/* select adc clock to come from ahb bus (sync clock, no jitter) */
	ADC->CCR = ADC_CCR_CKMODE_0;

	/* disable deep power down */
	ADC1->CR &= ~ADC_CR_DEEPPWD;
	/* enable voltage reference */
	ADC1->CR |= ADC_CR_ADVREGEN;
	/* wait till its settled */
	while ((ADC1->CR & ADC_CR_ADVREGEN) == 0);

	/* start calibration */
	ADC1->CR |= ADC_CR_ADCAL;
	/* loop until it is finished */
	while (ADC1->CR & ADC_CR_ADCAL);

	/* set sampling: pa3 - ch5 - 2.5 adc cycles */
	ADC1->SMPR1 = (ADC1->SMPR1 & ~ADC_SMPR1_SMP5) | ADC_SMPR1_SMP5_2CLK5;
	/* set configuration: overrun stop disabled, rising edge external trigger
	 * detection, select tim2 trgo as external trigger, enable dma in circular
	 * mode */
	ADC1->CFGR = ADC_CFGR_OVRMOD | ADC_CFGR_EXTSEL_TIM2_TRGO | ADC_CFGR_DMAEN |
			ADC_CFGR_EXTEN_RE | ADC_CFGR_DMACFG;
	/* enable oversampling */
	ADC1->CFGR2 = ADC_CFGR2_TROVS | ADC_CFGR2_ROVSE;

	/* clear ready flag */
	ADC1->ISR = ADC_ISR_ADRDY;
	/* enable adc */
	ADC1->CR |= ADC_CR_ADEN;
	/* wait till adc becomes ready */
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* configure sampling */
void Analog_StartSampling(int channel, int pres, int16_t *ptr, int num)
{
	/* enter critical section */
	Critical_Enter();

	/* stop adc */
	ADC1->CR |= ADC_CR_ADSTP;
	/* wait till it is completely stopped */
	while (ADC1->CR & ADC_CR_ADSTART);
	/* update channel selection */
	ADC1->SQR1 = channel << 6;

	/* disable timer */
	TIM2->CR1 &= ~TIM_CR1_CEN;
	/* write new prescaling setting */
	TIM2->ARR = (pres + 1) / 2 - 1;
	/* apply setting */
	TIM2->EGR = TIM_EGR_UG;
	/* enable timer */
	TIM2->CR1 |= TIM_CR1_CEN;

	/* start dma */
	DMA1C1->CCR &= ~DMA_CCR_EN;
	/* set destination buffer address */
	DMA1C1->CMAR = (uint32_t)ptr;
	/* set buffer size (expressed in number of samples */
	DMA1C1->CNDTR = num;
	/* start dma */
	DMA1C1->CCR |= DMA_CCR_EN;

	/* resume adc operation */
	ADC1->CR |= ADC_CR_ADSTART;

	/* exit critical section */
	Critical_Exit();
}

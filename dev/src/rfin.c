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
#include "dev/rfin.h"
#include "stm32l476/rcc.h"
#include "stm32l476/nvic.h"
#include "stm32l476/dma.h"
#include "stm32l476/adc.h"
#include "stm32l476/timer.h"
#include "stm32l476/gpio.h"
#include "sys/critical.h"
#include "sys/ev.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"

/* system event */
ev_t rfin_ev;
/* data pointer, */
static int16_t *samples;
/* data buffer size in number of samples */
static int samples_num;

/* adc dma1 interrupt */
void RFIn_DMA1C1Isr(void)
{
    // /* event argument */
	rfin_evarg_t ea = { .type = RFIN_TYPE_HT, .num = samples_num / 2, 
        .samples = samples };
	/* get interrupt flags */
	uint32_t isr = DMA1->ISR & (DMA_ISR_TCIF1 | DMA_ISR_HTIF1);
	/* clear interrupt */
	DMA1->IFCR = isr;

	/* full transfer occured? */
	if (isr & DMA_ISR_TCIF1) {
		ea.type = RFIN_TYPE_FT; ea.samples = &samples[samples_num / 2];
    }

	/* notify others */
	Ev_Notify(&rfin_ev, &ea);
}

/* radio frequency input pin */
int RFIn_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	/* enable gpioa and adc */
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN | RCC_AHB2ENR_GPIOAEN;
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

	/* set pa0 as analog input */
	GPIOA->MODER |= GPIO_MODER_MODER0;
	/* enable analog switch */
	GPIOA->ASCR |= GPIO_ASCR_ASC0;

    /* rf sampling frequency must divide the adc clock frequency */
    assert((int)CPUCLOCK_FREQ / RF_SAMPLING_FREQ * RF_SAMPLING_FREQ 
        == CPUCLOCK_FREQ, "rf sampling frequency does not divide the clock "
        "frequency", 0);
    /* adc needs at least 15 clock cycles per sample */
    assert(CPUCLOCK_FREQ / RF_SAMPLING_FREQ >= 15, "sampling rate too fast",
        RF_SAMPLING_FREQ);

    /* configure timer */
	/* reset prescaler */
	TIM2->PSC = 0;
    /* configure the reload value to generate the sampling clock */
    TIM2->ARR = (CPUCLOCK_FREQ / RF_SAMPLING_FREQ) - 1;
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
	NVIC_SETINTPRI(STM32_INT_DMA1C1, INT_PRI_RFIN);
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

	/* set sampling: pa0 - ch5 - 2.5 adc cycles, which gives 15 clock cycles for 
     * the sample */
	ADC1->SMPR1 = (ADC1->SMPR1 & ~ADC_SMPR1_SMP5) | ADC_SMPR1_SMP5_6CLK5;
	/* set configuration: overrun stop disabled, rising edge external trigger
	 * detection, select tim2 trgo as external trigger, enable dma in circular
	 * mode */
	ADC1->CFGR = ADC_CFGR_OVRMOD | ADC_CFGR_EXTSEL_TIM2_TRGO | ADC_CFGR_DMAEN |
			ADC_CFGR_EXTEN_RE | ADC_CFGR_DMACFG;

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
void RFIn_StartSampling(int16_t *ptr, int num)
{
    /* pa0 = analog channel 5 */
    const int channel = 5;

    /* must be divisible by two */
    assert(num % 2 == 0, "uneven number of samples", num);

	/* enter critical section */
	Critical_Enter();

	/* stop adc */
	ADC1->CR |= ADC_CR_ADSTP;
	/* wait till it is completely stopped */
	while (ADC1->CR & ADC_CR_ADSTART);
	/* update channel selection */
	ADC1->SQR1 = channel << 6;

    /* disable timer for the time of connfiguration */
	TIM2->CR1 &= ~TIM_CR1_CEN;

	/* start dma */
	DMA1C1->CCR &= ~DMA_CCR_EN;
	/* set destination buffer address */
	DMA1C1->CMAR = (uint32_t)(samples = ptr);
	/* set buffer size (expressed in number of samples) */
	DMA1C1->CNDTR = (samples_num = num);
	/* start dma */
	DMA1C1->CCR |= DMA_CCR_EN;

    /* resume adc operation */
	ADC1->CR |= ADC_CR_ADSTART;
    /* enable timer */
	TIM2->CR1 |= TIM_CR1_CEN;

	/* exit critical section */
	Critical_Exit();
}


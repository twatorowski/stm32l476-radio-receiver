/**
 * @file sai1a.c
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief Serial Audio Interface Driver Module. Uses channel 1A to send 24-bit 
 * audio data using left-justified mode. Clocked from PLLSAI1 running @ 16MHz.
 * Outputs ausio samples @ 31.25ksps. Mono.
 */

#include "err.h"
#include "dev/i2c1.h"
#include "dev/systime.h"
#include "stm32l476/rcc.h"
#include "stm32l476/gpio.h"
#include "stm32l476/sai.h"
#include "stm32l476/dma.h"
#include "stm32l476/nvic.h"
#include "sys/critical.h"
#include "util/fp.h"
#include "util/elems.h"
#include "util/msblsb.h"

#define DEBUG
#include "debug.h"

/* sai1a access semaphore */
sem_t sai1a_sem;

/* initialize sai1a interface that feeds the DAC with data */
int SAI1A_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	/* enable gpio */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	/* enable sai1 clock */
	RCC->APB2ENR |= RCC_APB2ENR_SAI1EN;

	/* reset sai1 */
	RCC->APB2RSTR |= RCC_APB2RSTR_SAI1RST;
	/* release reset */
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SAI1RST;

	/* configure pins */
	GPIOE->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5
			| GPIO_MODER_MODER6);
	/* set alternate functions */
	GPIOE->AFRL |= (13 << (2*4)) | (13 << (4*4)) | (13 << (5*4)) |
			(13 << (6*4));
	/* set output speed */
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_0 | GPIO_OSPEEDER_OSPEEDR4_0 |
			GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR6_0;
	/* set as peripheral driven */
	GPIOE->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER4_1 |
			GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1;

	/* set appropriate channel */
	DMA2->CSELR = (DMA2->CSELR & ~DMA_CSELR_C1S) | DMA2_CSELR_C1S_SAI1_A;

	/* configure dma channel */
	DMA2C1->CCR = DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_CIRC | DMA_CCR_MSIZE_1 |
			DMA_CCR_PSIZE_1 | DMA_CCR_MINC;
	/* set peripheral address */
	DMA2C1->CPAR = (uint32_t)&SAI1A->DR;

	/* configure sai: 24 bit data, 16MHz / 2 / 256 = 31.25kHz sampling rate,
	 * mono mode */
	SAI1A->CR1 = SAI_CR1_DS_2 | SAI_CR1_DS_1 | SAI_CR1_DMAEN | SAI_CR1_MCKDIV_1
			| SAI_CR1_MONO;
	/* 1/4 fifo treshold */
	SAI1A->CR2 = SAI_CR2_FTH_0;
	/* configure slots (use two of the slots) */
	SAI1A->SLOTR = SAI_SLOTR_SLOTEN_0 | SAI_SLOTR_SLOTEN_1 | 
        (2 - 1) << LSB(SAI_SLOTR_NBSLOT);
	/* sync on rising edge */
	SAI1A->FRCR = SAI_FRCR_FSPOL | SAI_FRCR_FSDEF | 31 << LSB(SAI_FRCR_FSALL) | 
        63 << LSB(SAI_FRCR_FRL);
	/* enable clock output */
	SAI1A->CR1 |= SAI_CR1_OUTDRIV;

    /* release the semaphore */
    Sem_Release(&sai1a_sem);
	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* start streaming data */
void SAI1A_StartStreaming(float sampling_rate, const int32_t *ptr, int num)
{
    /* sai master clock frequency must be equal to = sampling_rate * mck_div *
     * frame_length = sampling_rate * 4 * 256 = sampling_rate * 1024. We need to 
     * generate that from the sai1 pll that is clocked from the REF clock by 
     * adjusting the multiplier. the divider is constant and equal to 7 */
    float mclk_freq = sampling_rate * 4 * 256;
    /* compute the multiplier */
    int mult = fp_round(mclk_freq * 7 / CPUCLOCK_REF_FREQ);

	/* enter critical section */
	Critical_Enter();

    /* generate SAI1 clock */
	RCC->PLLSAI1CFGR = mult << LSB(RCC_PLLSAI1CFGR_PLLSAI1N) | 
        RCC_PLLSAI1CFGR_PLLSAI1PEN;
	/* enable pll */
	RCC->CR |= RCC_CR_PLLSAI1ON;
	/* wait till it is stable */
	while (!(RCC->CR & RCC_CR_PLLSAI1RDY));

	/* set memory address */
	DMA2C1->CMAR = (uint32_t)ptr;
	/* set buffer size */
	DMA2C1->CNDTR = num;
	/* enable dma */
	DMA2C1->CCR |= DMA_CCR_EN;

	/* start sending data */
	SAI1A->CR1 |= SAI_CR1_SAIEN;

	/* exit critical section */
	Critical_Exit();
}

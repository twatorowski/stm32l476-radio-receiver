/**
 * @file dec.c
 * 
 * @date 2020-01-19
 * @author twatorowski 
 * 
 * @brief Decimators for the I/Q channels
 */

#include "assert.h"
#include "err.h"
#include "dev/dec.h"
/*TODO:*/
#include "dev/watchdog.h"
#include "dsp/float_fixp.h"
#include "stm32l476/rcc.h"
#include "stm32l476/dfsdm.h"
#include "stm32l476/dma.h"
#include "stm32l476/nvic.h"
#include "sys/critical.h"
#include "sys/cb.h"
#include "sys/sem.h"
#include "util/elems.h"
#include "util/msblsb.h"

#define DEBUG
#include "debug.h"

/* decimator semaphore */
sem_t dec_sem;

/* callback */
static volatile cb_t callback;
/* callback argument */
static dec_cbarg_t callback_arg;
/* buffer pointer */
static union {int32_t *i32; float *fl; } samples_i, samples_q;
/* number of processed samples */
static int samples_num;

/* decimation dma interrupt */
void OPTIMIZE("O0") Dec_DMA1C4Isr(void)
{
    /* synchronize both channels */
    while ((DMA1->ISR & (DMA_ISR_TCIF4 | DMA_ISR_TCIF5)) != 
        (DMA_ISR_TCIF4 | DMA_ISR_TCIF5));
    /* clear flags */
    DMA1->IFCR = DMA_ISR_TCIF4 | DMA_ISR_TCIF5;

    /* disable the interrupt */
	NVIC_DISABLEINT(STM32_INT_DMA1C4);

    /* convert fixed point notation to floating point */
    FloatFixp_Fixp32ToFloat(samples_i.i32, samples_num, 31, samples_i.fl);
    FloatFixp_Fixp32ToFloat(samples_q.i32, samples_num, 31, samples_q.fl);

    /* set-up the callback argument */
    callback_arg.num = samples_num;
    /* store data pointers */
    callback_arg.i = samples_i.fl, callback_arg.q = samples_q.fl;

	/* sync call */
	if (callback == CB_SYNC) {
		callback = CB_NONE;
	/* async call was made? */
	} else if (callback != CB_NONE) {
		callback(&callback_arg);
	}
}

/* initialize decimator for in-phase channel */
int Dec_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable clock for dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMA2EN;
	/* enable demod */
	RCC->APB2ENR |= RCC_APB2ENR_DFSDMEN;

	/* use dma2c7 for pushing data into I decimator */
	DMA2C7->CCR = DMA_CCR_MEM2MEM | DMA_CCR_DIR | DMA_CCR_MINC |
			DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
	/* set destination register */
	DMA2C7->CPAR = (uint32_t)&DFSDMC0->CHDATINR;

    /* use dma2c2 for pushing data into Q decimator */
	DMA2C2->CCR = DMA_CCR_MEM2MEM | DMA_CCR_DIR | DMA_CCR_MINC |
			DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
	/* set destination register */
	DMA2C2->CPAR = (uint32_t)&DFSDMC1->CHDATINR;

	/* use dma1c4 for fetching the I data from the decimator */
	DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C4S) | DMA1_CSELR_C4S_DFSDM0;
	/* configure dma fetching data out of I decimator */
	DMA1C4->CCR = DMA_CCR_TCIE | DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 | 
        DMA_CCR_MINC;
	/* set source register */
	DMA1C4->CPAR = (uint32_t)&DFSDMF0->RDATAR;

    /* use dma1c5 for fetching the Q data from the decimator */
    DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C5S) | DMA1_CSELR_C5S_DFSDM1;
	/* configure dma fetching data out of Q decimator */
	DMA1C5->CCR = DMA_CCR_TCIE | DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 |
			DMA_CCR_MINC;
	/* set source register */
	DMA1C5->CPAR = (uint32_t)&DFSDMF1->RDATAR;

	/* set interrupt priority */
	NVIC_SETINTPRI(STM32_INT_DMA1C4, INT_PRI_DEC);

    /* this is prepared for only one decimation rate */
    assert(DEC_DECIMATION_RATE == 50, "unsupported decimation factor",
        DEC_DECIMATION_RATE);

	/* enable interface */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_DFSDMEN;

	/* 0th channel: I data input */
	/* configure for single data input */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_DATMPX_1;
	/* configure offset and bit shift  */
	DFSDMC0->CHCFGR2 |= 8 << LSB(DFSDM_CHCFGR2_DTRBS);
	/* enable channel */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_CHEN;

    /* 1st channel: Q data input */
	/* configure for single data input */
	DFSDMC1->CHCFGR1 |= DFSDM_CHCFGR1_DATMPX_1;
	/* configure offset and bit shift  */
	DFSDMC1->CHCFGR2 |= 8 << LSB(DFSDM_CHCFGR2_DTRBS);
	/* enable channel */
	DFSDMC1->CHCFGR1 |= DFSDM_CHCFGR1_CHEN;

	/* 0th Filter: mapped to channel 0 (I samples), decimation by 50, sinc^4
	 * filter, bit growth = N*log2(R) = 3 * log2(50) ~= 18, output data width =
	 * input data width + bit growth = 14b + 18b = 32b, but since the output
	 * register can only handle 24 bit data we need to shift by 6 (done in
	 * input channel configuration) */
	/* disable block */
	DFSDMF0->CR1 &= ~DFSDM_CR1_DFEN;
	/* enable fast conversion, enable dma requests  */
	DFSDMF0->CR1 = DFSDM_CR1_FAST | DFSDM_CR1_RDMAEN;
	/* sinc^3 filter, decimation by 50, no integration */
	DFSDMF0->FCR = DFSDM_FCR_FORD_1 | DFSDM_FCR_FORD_0 |
        (DEC_DECIMATION_RATE - 1) << LSB(DFSDM_FCR_FOSR) | 
        0 << LSB(DFSDM_FCR_IOSR);
	/* select regular channel 0, continuous conversion */
	DFSDMF0->CR1 |= DFSDM_CR1_RCONT | 0 << LSB(DFSDM_CR1_RCH);
	/* enable filtering */
	DFSDMF0->CR1 |= DFSDM_CR1_DFEN;

	/* 1st Filter: mapped to channel 1 (Q samples), decimation by 50, sinc^3
	 * filter, bit growth = N*log2(R) = 3 * log2(50) ~= 18, output data width =
	 * input data width + bit growth = 14b + 18b = 32b, but since the output
	 * register can only handle 24 bit data we need to shift by 8 (done in
	 * input channel configuration) */
	/* disable block */
	DFSDMF1->CR1 &= ~DFSDM_CR1_DFEN;
	/* enable fast conversion, enable dma requests  */
	DFSDMF1->CR1 = DFSDM_CR1_FAST | DFSDM_CR1_RDMAEN;
	/* sinc^3 filter, decimation by 50, no integration */
	DFSDMF1->FCR = DFSDM_FCR_FORD_1 | DFSDM_FCR_FORD_0  | 
        (DEC_DECIMATION_RATE - 1) << LSB(DFSDM_FCR_FOSR) |
        0 << LSB(DFSDM_FCR_IOSR);
	/* select regular channel 0, continuous conversion */
	DFSDMF1->CR1 |= DFSDM_CR1_RCONT | 1 << LSB(DFSDM_CR1_RCH);
	/* enable filtering */
	DFSDMF1->CR1 |= DFSDM_CR1_DFEN;

	/* start filter operation */
	DFSDMF0->CR1 |= DFSDM_CR1_RSWSTART;
    DFSDMF1->CR1 |= DFSDM_CR1_RSWSTART;
    ASM volatile("nop\n");
    ASM volatile("nop\n");
    ASM volatile("nop\n");
    ASM volatile("nop\n");
	/* initialize filter, this needs to be done because filter is not willing to
	 * output any data before it's integrators and combs are filled (decimation
	 * factor * filter order samples are needed) */
    /* TODO: */
	for (int i = 0; i < DEC_DECIMATION_RATE *50; i++) {
		DFSDMC1->CHDATINR = 0; DFSDMC0->CHDATINR = 0; 
    }

    /* sanity check */
    assert(sizeof(int32_t) == sizeof(float), 
        "int32_t must have the same size as the float for this code to work", 0);

	/* exit critical section */
	Critical_Exit();

    /* release the device */
    Sem_Release(&dec_sem);

	/* report status */
	return EOK;
}

/* perform filtration and decimation */
dec_cbarg_t * Dec_Decimate(const int16_t *i, const int16_t *q, int num, 
    float *i_out,  float *q_out, cb_t cb)
{
    /* call is synchronous? */
    int sync = cb == CB_SYNC;

	/* store callback */
	callback = cb;
	/* store output buffer size and pointer */
	samples_num = num / DEC_DECIMATION_RATE;
    /* store the output buffer pointers */
    samples_i.fl = i_out, samples_q.fl = q_out;

    /* sanity check TODO: */
    assert((uintptr_t)i % 4 == 0 && (uintptr_t)q % 4 == 0, 
        "input data address is not aligned", 0);
    /* sanity check for the number of samples */
    assert(samples_num * DEC_DECIMATION_RATE == num, 
        "number of samples is not divisible by the decimation factor", 
        num);

	/* prepare output dma for I samples */
	DMA1C4->CCR &= ~DMA_CCR_EN;
	/* set data destination pointer */
	DMA1C4->CMAR = (uint32_t)(i_out);
	/* set number of samples */
	DMA1C4->CNDTR = samples_num;
	/* enaable dma */
	DMA1C4->CCR |= DMA_CCR_EN;
    
    /* prepare output dma for Q samples */
	DMA1C5->CCR &= ~DMA_CCR_EN;
	/* set data destination pointer */
	DMA1C5->CMAR = (uint32_t)(q_out);
	/* set number of samples */
	DMA1C5->CNDTR = samples_num;
	/* eanable dma */
	DMA1C5->CCR |= DMA_CCR_EN;

	/* prepare input dma for I samples */
	DMA2C7->CCR &= ~DMA_CCR_EN;
	/* set source pointer */
	DMA2C7->CMAR = (uint32_t)(i);
	/* set the number of samples */
	DMA2C7->CNDTR = num;
	/* enable dma */
	DMA2C7->CCR |= DMA_CCR_EN;

    /* prepare input dma for Q samples */
	DMA2C2->CCR &= ~DMA_CCR_EN;
	/* set source pointer */
	DMA2C2->CMAR = (uint32_t)(q);
	/* set the number of samples */
	DMA2C2->CNDTR = num;
	/* enable dma */
	DMA2C2->CCR |= DMA_CCR_EN;

    /* enable the interrupt */
	NVIC_ENABLEINT(STM32_INT_DMA1C4);

	/* sync call was made? */
	while (sync && callback == CB_SYNC);
    /* this function returns nothing */
    return sync ? &callback_arg : 0;
}
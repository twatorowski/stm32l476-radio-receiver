/**
 * @file deci.c
 * 
 * @date 2019-11-04
 * @author twatorowski
 * 
 * @brief Decimator for the In-Phase channel. Applies low-pass filtering using 
 * CIC filter and then decimates by factor of 32.
 */

#include "err.h"
#include "dev/watchdog.h"
#include "stm32l476/rcc.h"
#include "stm32l476/dfsdm.h"
#include "stm32l476/dma.h"
#include "stm32l476/nvic.h"
#include "sys/critical.h"
#include "sys/cb.h"
#include "util/elems.h"
#include "util/msblsb.h"

#define DEBUG
#include "debug.h"

/* callback */
static cb_t callback;
/* pointer to the decimated output */
static int32_t *buf;
/* number of processed samples */
static size_t buf_smpls;

/* decimation dma interrupt */
void DecI_DMA1C4Isr(void)
{
	/* clear interrupt */
	DMA1->IFCR = DMA_IFCR_CTCIF4;

	/* perform bit shifting */
	do {
		/* data comes out as shifted by 8 bits */
		*buf = *buf >> 8, buf++;
		*buf = *buf >> 8, buf++;
		*buf = *buf >> 8, buf++;
		*buf = *buf >> 8, buf++;
		/* decrease the number of samples */
		buf_smpls -= 4;
	/* still something to process? */
	} while (buf_smpls);

	/* sync call */
	if (callback == CB_SYNC) {
		callback = CB_NONE;
	/* async call was made? */
	} else if (callback != CB_NONE) {
		callback(0);
	}
}

/* initialize decimator for in-phase channel */
int DecI_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable clock for dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMA2EN;
	/* enable demod */
	RCC->APB2ENR |= RCC_APB2ENR_DFSDMEN;

	/* use dma2c6 for pushing data into I decimator */
	DMA2C6->CCR = DMA_CCR_MEM2MEM | DMA_CCR_DIR | DMA_CCR_MINC |
			DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1;
	/* set destination register */
	DMA2C6->CPAR = (uint32_t)&DFSDMC0->CHDATINR;

	/* select dma channel */
	DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C4S) | DMA1_CSELR_C4S_DFSDM0;
	/* configure dma fetching data out of I decimator */
	DMA1C4->CCR = DMA_CCR_TCIE | DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 | 
        DMA_CCR_MINC;
	/* set source register */
	DMA1C4->CPAR = (uint32_t)&DFSDMF0->RDATAR;

	/* set interrupt priority */
	NVIC_SETINTPRI(STM32_INT_DMA1C4, INT_PRI_DEC);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_DMA1C4);

	/* enable interface */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_DFSDMEN;

	/* 0th channel: I data input */
	/* configure for parallel data input */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_DATMPX_1 | DFSDM_CHCFGR1_DATPACK_0;
	/* configure offset and bit shift  */
	DFSDMC0->CHCFGR2 |= 6 << LSB(DFSDM_CHCFGR2_DTRBS);
	/* enable channel */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_CHEN;

	/* 0th Filter: mapped to channel 0 (I samples), decimation by 32, sinc^4
	 * filter, bit growth = N*log2(R) = 4 * log2(32) = 20, output data width =
	 * input data width + bit growth = 12b + 20b = 32b, but since the output
	 * register can only handle 24 bit data we need to shift by 8 (done in
	 * input channel configuration) */
	/* disable block */
	DFSDMF0->CR1 &= ~DFSDM_CR1_DFEN;
	/* enable fast conversion, enable dma requests  */
	DFSDMF0->CR1 = DFSDM_CR1_FAST | DFSDM_CR1_RDMAEN;
	/* sinc^4 filter, decimation by 32, no integration */
	DFSDMF0->FCR = DFSDM_FCR_FORD_2 | 
        (DEC_DECIMATION_RATE - 1) << LSB(DFSDM_FCR_FOSR) | 
        0 << LSB(DFSDM_FCR_IOSR);
	/* select regular channel 0, continuous conversion */
	DFSDMF0->CR1 |= DFSDM_CR1_RCONT | 0 << LSB(DFSDM_CR1_RCH);
	/* enable filtering */
	DFSDMF0->CR1 |= DFSDM_CR1_DFEN;

	/* start filter operation */
	DFSDMF0->CR1 |= DFSDM_CR1_RSWSTART;
	/* initialize filter, this needs to be done because filter is not willing to
	 * output any data before it's integrators and combs are filled (decimation
	 * factor * filter order samples are needed) */
	for (int i = 0; i < 32 * 4; i++)
		DFSDMC0->CHDATINR = 0;

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

/* perform filtration and decimation */
void * DecI_Decimate(int16_t *in, int32_t *out, int num, cb_t cb)
{
	/* store callback */
	callback = cb;
	/* store output buffer size and pointer TODO: constant decimation factor */
	buf_smpls = num / DEC_DECIMATION_RATE, buf = out;

	/* prepare output dma for I samples */
	DMA1C4->CCR &= ~DMA_CCR_EN;
	/* set data destination pointer */
	DMA1C4->CMAR = (uint32_t) (buf);
	/* set number of samples */
	DMA1C4->CNDTR = buf_smpls;
	/* enaable dma */
	DMA1C4->CCR |= DMA_CCR_EN;

	/* prepare input dma for I samples */
	DMA2C6->CCR &= ~DMA_CCR_EN;
	/* set source pointer */
	DMA2C6->CMAR = (uint32_t)(in);
	/* set the number of samples */
	DMA2C6->CNDTR = num / (sizeof(out[0]) / sizeof(in[0]));
	/* enable dma */
	DMA2C6->CCR |= DMA_CCR_EN;

	/* sync call was made? */
	while (callback == CB_SYNC);
    /* this function returns nothing */
    return 0;
}

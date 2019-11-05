/**
 * @file decq.c
 * 
 * @date 2019-11-04
 * @author twatorowski
 * 
 * @brief Decimator for the Quadrature channel. Applies low-pass filtering using 
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
/* buffer pointer */
static int32_t *buf;
/* buffer number samples */
static size_t buf_smpls;

/* decimation dma interrupt */
void DecQ_DMA1C5Isr(void)
{
	/* clear interrupt */
	DMA1->IFCR = DMA_IFCR_CTCIF5;

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

/* initialize decimator for quadrature channel */
int DecQ_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable clock for dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMA2EN;
	/* enable demod */
	RCC->APB2ENR |= RCC_APB2ENR_DFSDMEN;

	/* use dma2c7 for pushing data into Q decimator */
	DMA2C7->CCR = DMA_CCR_MEM2MEM | DMA_CCR_DIR | DMA_CCR_MINC |
			DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1;
	/* set destination register */
	DMA2C7->CPAR = (uint32_t)&DFSDMC1->CHDATINR;

	/* select dma channel */
	DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C5S) | DMA1_CSELR_C5S_DFSDM1;
	/* configure dma fetching data out of Q decimator */
	DMA1C5->CCR = DMA_CCR_TCIE | DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 |
			DMA_CCR_MINC;
	/* set source register */
	DMA1C5->CPAR = (uint32_t)&DFSDMF1->RDATAR;

	/* set interrupt priority */
	NVIC_SETINTPRI(STM32_INT_DMA1C5, INT_PRI_DEC);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_DMA1C5);

	/* enable interface */
	DFSDMC0->CHCFGR1 |= DFSDM_CHCFGR1_DFSDMEN;

	/* 1st channel: Q data input */
	/* configure for parallel data input */
	DFSDMC1->CHCFGR1 |= DFSDM_CHCFGR1_DATMPX_1 | DFSDM_CHCFGR1_DATPACK_0;
	/* configure offset and bit shift  */
	DFSDMC1->CHCFGR2 |= LSB(DFSDM_CHCFGR2_DTRBS);
	/* enable channel */
	DFSDMC1->CHCFGR1 |= DFSDM_CHCFGR1_CHEN;

	/* 1st Filter: mapped to channel 1 (Q samples), decimation by 32, sinc^4
	 * filter, bit growth = N*log2(R) = 4 * log2(32) = 20, output data width =
	 * input data width + bit growth = 12b + 20b = 32b, but since the output
	 * register can only handle 24 bit data we need to shift by 8 (done in
	 * input channel configuration) */
	/* disable block */
	DFSDMF1->CR1 &= ~DFSDM_CR1_DFEN;
	/* enable fast conversion, enable dma requests  */
	DFSDMF1->CR1 = DFSDM_CR1_FAST | DFSDM_CR1_RDMAEN;
	/* sinc^4 filter, decimation by 32, no integration */
	DFSDMF1->FCR = DFSDM_FCR_FORD_2 | 
        (DEC_DECIMATION_RATE - 1) << LSB(DFSDM_FCR_FOSR) |
        0 << LSB(DFSDM_FCR_IOSR);
	/* select regular channel 0, continuous conversion */
	DFSDMF1->CR1 |= DFSDM_CR1_RCONT | 1 << LSB(DFSDM_CR1_RCH);
	/* enable filtering */
	DFSDMF1->CR1 |= DFSDM_CR1_DFEN;

	/* start filter operation */
	DFSDMF1->CR1 |= DFSDM_CR1_RSWSTART;
	/* initialize filter, this needs to be done because filter is not willing to
	 * output any data before it's integrators and combs are filled (decimation
	 * factor * filter order samples are needed) */
	for (int i = 0; i < 32 * 4; i++)
		DFSDMC1->CHDATINR = 0;

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

/* perform filtration and decimation */
void * DecQ_Decimate(int16_t *in, int32_t *out, int num, cb_t cb)
{
	/* store callback */
	callback = cb;
	/* store output buffer size and pointer TODO: constant decimation factor  */
	buf_smpls = num / DEC_DECIMATION_RATE, buf = out;

	/* prepare output dma for Q samples */
	DMA1C5->CCR &= ~DMA_CCR_EN;
	/* set data destination pointer */
	DMA1C5->CMAR = (uint32_t)(buf);
	/* set number of samples */
	DMA1C5->CNDTR = buf_smpls;
	/* eanable dma */
	DMA1C5->CCR |= DMA_CCR_EN;

	/* prepare input dma for Q samples */
	DMA2C7->CCR &= ~DMA_CCR_EN;
	/* set source pointer */
	DMA2C7->CMAR = (uint32_t)(in);
	/* set the number of samples */
	DMA2C7->CNDTR = num / (sizeof(out[0]) / sizeof(in[0]));
	/* enable dma */
	DMA2C7->CCR |= DMA_CCR_EN;

	/* sync call was made? */
	while (callback == CB_SYNC);
    /* this function returns nothing */
    return 0;
}

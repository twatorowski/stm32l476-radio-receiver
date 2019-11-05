/**
 * @file i2c1.c
 * 
 * @date 2019-11-05
 * @author twatorowski
 * 
 * @brief I2C1 Driver Module
 */

#include <stddef.h>
#include <stdint.h>

#include "assert.h"
#include "compiler.h"
#include "err.h"
#include "dev/i2c1.h"
#include "stm32l476/dma.h"
#include "stm32l476/gpio.h"
#include "stm32l476/i2c.h"
#include "stm32l476/nvic.h"
#include "stm32l476/rcc.h"
#include "sys/critical.h"
#include "sys/sem.h"
#include "util/msblsb.h"

#define DEBUG
#include "debug.h"

/* bus semaphore */
sem_t i2c1_sem;

/* initialization status */
static int init = ENOINIT;

/* transfer callback */
static cb_t callback;
/* callback argument */
static i2c1_cbarg_t callback_arg;

/* operation type operation errors */
static volatile int type, error, address, sub_address;
/* data pointer */
static uint8_t *d_ptr;
/* data size */
static size_t d_size, d_transferred;
/* initialization status */
static int init;
/* transfer semaphore */
static sem_t t_sem;

/* end transfer */
static void I2C1_EndTransfer(int error, size_t size)
{
	/* store result in error variable */
	callback_arg.error = error;
    callback_arg.size = size;

	/* sync call */
	if (callback == CB_SYNC) {
		callback = CB_NONE;
	/* async call was made? */
	} else if (callback != CB_NONE) {
		callback(&callback_arg);
	}
}
/* event isr */
void I2C1_I2C1EvIsr(void)
{
	/* read status */
	uint32_t isr = I2C1->ISR;

	/* need to write the transmission data? */
	if (isr & I2C_ISR_TXIS) {
		/* sub_address phase? */
		if (sub_address != -1) {
			/* send sub address, clear it's value */
			I2C1->TXDR = sub_address, sub_address = -1;
		/* data phase */
		} else {
			I2C1->TXDR = *(d_ptr++), d_transferred++;
		}
	}

	/* transfer complete? */
	if (isr & I2C_ISR_TC) {
		/* end of write operation */
		if (type == I2C1_WRITE) {
			/* disable dma transfer */
			STM32_BB(&I2C1->CR1, LSB(I2C_CR1_TXDMAEN)) = 0;
			/* generate stop condition */
			STM32_BB(&I2C1->CR2, LSB(I2C_CR2_STOP)) = 1;
		/* read operation 1st stage (addressing) */
		} else if (STM32_BB(&I2C1->CR2, LSB(I2C_CR2_RD_WRN)) == 0) {
			/* disable dma channel for re-configuration */
			DMA2C6->CCR &= ~DMA_CCR_EN;
			/* set up the dma transfer */
			DMA2C6->CMAR = (uint32_t)d_ptr;
			/* set the number of bytes */
			DMA2C6->CNDTR = d_size;
			/* enable dma */
			DMA2C6->CCR |= DMA_CCR_EN;
			/* enable dma transfer */
			STM32_BB(&I2C1->CR1, LSB(I2C_CR1_RXDMAEN)) = 1;
			/* set up address */
			I2C1->CR2 = address << 1 | I2C_CR2_RD_WRN | d_size << 16 | 
                I2C_CR2_START;
		/* end of read operation */
		} else {
			/* number of bytes transferred */
			d_transferred = d_size - DMA2C6->CNDTR;
			/* disable dma transfer */
			STM32_BB(&I2C1->CR1, LSB(I2C_CR1_RXDMAEN)) = 0;
			/* generate stop condition */
			STM32_BB(&I2C1->CR2, LSB(I2C_CR2_STOP)) = 1;
		}
	}

	/* nack received */
	if (isr & I2C_ISR_NACKF) {
		/* clear interrupt */
		I2C1->ICR = I2C_ICR_NACKCF;
		/* end the transfer */
		if (Sem_Lock(&t_sem, CB_NONE) == EOK)
			I2C1_EndTransfer(EFATAL, 0);
	}

	/* end of transfer */
	if (isr & I2C_ISR_STOPF) {
		/* clear interrupt */
		I2C1->ICR = I2C_ICR_STOPCF;
		/* end the transfer */
		if (Sem_Lock(&t_sem, CB_NONE) == EOK)
			I2C1_EndTransfer(EOK, d_transferred);
	}
}

/* error isr */
void I2C1_I2C1ErIsr(void)
{
	/* show error information */
	dprintf("i2c error = %#x\n", I2C1->ISR);
	/* try to end the transfer */
	if (Sem_Lock(&t_sem, CB_NONE) == EOK)
		I2C1_EndTransfer(EFATAL, 0);
}

/* initialize i2c1 */
int I2C1_Init(void)
{
	/* disable interrupts to ensure atomicity of register access */
	Critical_Enter();

	/* enable dma2 */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	/* enable gpio b */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	/* enable i2c2 */
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;

	/* enable reset */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C1RST;
	/* disable reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C1RST;

	/* reset function */
	GPIOB->AFRL &= ~(0xf << (6 * 4) | 0xf << (7 * 4));
	/* set alternate function */
	GPIOB->AFRL |=  (0x4 << (6 * 4) | 0x4 << (7 * 4));
	/* open drain output */
	GPIOB->OTYPER |= GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7;
    /* reset */
	GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	/* BUGFIX: i2c slaves can block sda when reset occurs in the middle of the
	 * transmission. In order to restore normal operation master has to clock
	 * some pulses till slave releases sda. */
	/* set clock line as output */
	GPIOB->MODER |= GPIO_MODER_MODER6_0;
	/* clock pulses till sda is idle */
	for (int i = 0; i < 32; i++) {
		/* clock toggle */
		GPIOB->BSRR = GPIO_BSRR_BR_6;
		/* delay */
		for (int j = 0; j < 100; j++)
			ASM volatile ("nop\n");
		/* this is going to be delayed by the loop itself */
		GPIOB->BSRR = GPIO_BSRR_BS_6;
		/* delay */
		for (int j = 0; j < 100; j++)
			ASM volatile ("nop\n");
	}
	/* release clock drive */
	GPIOB->MODER &= ~GPIO_MODER_MODER6_0;
	/* set alternate function */
	GPIOB->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;

	/* rx dma */
	/* set appropriate channel */
	DMA2->CSELR = (DMA2->CSELR & ~DMA_CSELR_C6S) | DMA2_CSELR_C6S_I2C1_RX;
	/* peripheral address */
	DMA2C6->CPAR = (uint32_t)&I2C1->RXDR;
	/* configure rx dma for circular buffer operation */
	DMA2C6->CCR = DMA_CCR_MINC;

	/* prepare i2c */
	/* configure signal filtration */
	I2C1->CR1 |= I2C_CR1_ANFOFF;
	/* configure interrupts */
	I2C1->CR1 |= I2C_CR1_RXIE | I2C_CR1_TXIE | I2C_CR1_NACKIE | I2C_CR1_ERRIE |
			I2C_CR1_TCIE | I2C_CR1_STOPIE;
	/* configure prescaler = 48MHz / 16, scl low = 15, scl high = 15 -> 100kHz */
	I2C1->TIMINGR = 15 << 28 | 15 << 8 | 15 << 0;
	/* enable periph */
	I2C1->CR1 |= I2C_CR1_PE;

	/* set interrupt priority  */
	NVIC_SETINTPRI(STM32_INT_I2C1_EV, 0xf0);
	NVIC_SETINTPRI(STM32_INT_I2C1_ER, 0xf0);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_I2C1_EV);
	NVIC_ENABLEINT(STM32_INT_I2C1_ER);

    /* set status */
	init = EOK;

	/* restore interrupts */
	Critical_Exit();

	/* reset sem */
	Sem_Release(&i2c1_sem);

	/* report status */
	return init;
}

/* i2c transfer */
i2c1_cbarg_t * I2C1_Transfer(int oper_type, uint8_t addr, uint8_t sub_addr, 
    void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int sync = cb == CB_SYNC;

	/* store callback */
	callback = cb;
	/* store transaction information */
	address = addr; sub_address = sub_addr; type = oper_type;
	/* data buffer information */
	d_ptr = ptr, d_size = size, d_transferred = 0;

	/* release transfer semaphore */
	Sem_Release(&t_sem);

	/* read operation */
	if (oper_type == I2C1_READ) {
		/* 1st transacion during read is a write transaction with sub_addr filed
		 * being the only byte of data transmitted */
		I2C1->CR2 = (addr << 1) << LSB(I2C_CR2_SADD) | 
            1 << LSB(I2C_CR2_NBYTES);
	} else {
		/* complete data buffer can be sent during writes + additional byte for
		 * sub_addr */
		I2C1->CR2 = (addr << 1) << LSB(I2C_CR2_SADD) | 
            (size + 1) << LSB(I2C_CR2_NBYTES);
	}

	/* generate start condition */
	STM32_BB(&I2C1->CR2, LSB(I2C_CR2_START)) = 1;

    /* interrupt will alter cb_tx address after transfer has finished */
    while (sync && callback == CB_SYNC);
    /* report status */
    return &callback_arg;
}

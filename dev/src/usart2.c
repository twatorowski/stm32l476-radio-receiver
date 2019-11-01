/**
 * @file usart2.c
 *
 * @date 30.06.2019
 * @author twatorowski
 *
 * @brief USART2 Driver
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "dev/usart2.h"
#include "stm32l476/rcc.h"
#include "stm32l476/usart.h"
#include "stm32l476/gpio.h"
#include "stm32l476/dma.h"
#include "stm32l476/nvic.h"
#include "sys/cb.h"
#include "sys/critical.h"
#include "sys/sem.h"
#include "util/elems.h"
#include "util/minmax.h"
#include "util/msblsb.h"
#include "util/string.h"

/* semaphore */
sem_t usart2tx_sem, usart2rx_sem;

/* rx buffer */
static uint8_t *rx_ptr;
/* buffer size */
static size_t rx_size, tx_size;
/* callback */
static cb_t rx_cb, tx_cb;

/* circular buffer */
static uint8_t circ[128];
/* buffer tail pointer */
static uint32_t tail;

/* gets data from circular buffer */
static size_t USART2_GetDataFromCircBuf(void *ptr, size_t size)
{
    /* update current head offset */
    uint32_t head = sizeof(circ) - DMA1C6->CNDTR;
    /* no data is currently buffered? */
    if (head - tail == 0)
        return 0;

    /* get number of bytes to copy */
    uint32_t bnum = min((head - tail) % elems(circ), size);
    /* number of bytes before circ buffer wraps */
    uint32_t wrap = min(bnum, elems(circ) - tail);

    /* copy data before wrapping */
    memcpy(rx_ptr, circ + tail, wrap);
    /* copy data after wrapping */
    if (bnum - wrap)
        memcpy(rx_ptr + wrap, circ, bnum - wrap);
    /* update tail pointer */
    tail = (tail + bnum) % elems(circ);

    /* report number of bytes copied */
    return bnum;
}

/* process transfer complete interrupt */
static void USART2_USART2TransferCompleteIsr(void)
{
    /* disable transfer complete interrupt */
    STM32_BB(&USART2->CR1, LSB(USART_CR1_TCIE)) = 0;

    /* sync call? */
    if (tx_cb == CB_SYNC) {
        tx_cb = CB_NONE;
    /* async call was made? */
    } else if (tx_cb != CB_NONE) {
        tx_cb(&tx_size);
    }
}

/* process idle character detection */
static void USART2_USART2IdleIsr(void)
{
    /* clear idle interrupt */
    USART2->ICR = USART_ICR_IDLECF;
    /* prevent second ending interrupt from firing */
    NVIC_SETPENDING(STM32_INT_DMA1C6);
}

/* uart interrupts */
void USART2_USART2Isr(void)
{
    /* get status register, mask out unused interrupts */
    uint32_t sr = USART2->ISR & USART2->CR1 & (USART_ISR_TC | USART_ISR_IDLE);

    /* transfer complete */
    if (sr & USART_ISR_TC)
        USART2_USART2TransferCompleteIsr();

    /* idle state detected */
    if (sr & USART_ISR_IDLE)
        USART2_USART2IdleIsr();
}

/* tx dma interrupt */
void USART2_DMA1C7Isr(void)
{
    /* clear interrupt */
    DMA1->IFCR = DMA_IFCR_CGIF7;
    /* enable transfer complete interrupt */
    STM32_BB(&USART2->CR1, LSB(USART_CR1_TCIE)) = 1;
}

/* rx dma interrupt */
void USART2_DMA1C6Isr(void)
{
    /* clear interrupt */
    DMA1->IFCR = DMA_IFCR_CGIF6;
    /* mask out idle interrupt */
    STM32_BB(&USART2->CR1, LSB(USART_CR1_IDLEIE)) = 1;
    /* fetch data from buffer */
    size_t bnum = USART2_GetDataFromCircBuf(rx_ptr, rx_size);
    /* no data received? */
    if (bnum == 0)
        return;

    /* disable interrupt generation */
    NVIC_DISABLEINT(STM32_INT_DMA1C6);
    /* prevent second ending interrupt from firing */
    STM32_BB(&USART2->CR1, LSB(USART_CR1_IDLEIE)) = 0;
    /* call callback */
    if (rx_cb == CB_SYNC) {
        rx_cb = CB_NONE;
    /* async call was made? */
    } else if (rx_cb != CB_NONE) {
        rx_cb(&bnum);
    }
}

/* initialize usart2 */
int USART2_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable dma */
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	/* enable gpioa and dma */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
	/* enable usart1 clock */
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	/* reset usart */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART2RST;
	/* disable reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART2RST;

	/* reset moder configutration */
	GPIOD->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
	/* set alternate function to usart */
	GPIOA->AFRL |= 7 << (5 * 4) | 7 << (6 * 4);
	/* enable pull up for rxd line */
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_0;
	/* set both as alternate function */
	GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1;

    /* set appropriate channel for tx */
    DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C7S) | DMA1_CSELR_C7S_USART2_TX;
    /* configure tx dma */
    DMA1C7->CCR = DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE;
    /* peripheral address */
    DMA1C7->CPAR = (uint32_t)&USART2->TDR;

    /* set appropriate channel for rx */
    DMA1->CSELR = (DMA1->CSELR & ~DMA_CSELR_C6S) | DMA1_CSELR_C6S_USART2_RX;
    /* peripheral address */
    DMA1C6->CPAR = (uint32_t)&USART2->RDR;
    /* data goes to circular buffer */
    DMA1C6->CMAR = (uint32_t)circ;
    /* setup circular buffer size */
    DMA1C6->CNDTR = sizeof(circ);
    /* configure rx dma for circular buffer operation */
    DMA1C6->CCR = DMA_CCR_EN | DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_TCIE |
            DMA_CCR_HTIE;

	/* configure baud rate */
	USART2->BRR = 0x821;
    /* x-mission dma request generation enable */
    USART2->CR3 = USART_CR3_DMAR | USART_CR3_DMAT;
    /* enable oversampling and tx/rx support */
    USART2->CR1 = USART_CR1_OVER8 | USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;

	/* set low priority for tx transfer */
	NVIC_SETINTPRI(STM32_INT_USART2, 0xf0);
	/* enable tx transfer interrupts */
	NVIC_ENABLEINT(STM32_INT_USART2);

    /* set low priority for tx transfer */
    NVIC_SETINTPRI(STM32_INT_DMA1C7, 0xf0);
    /* enable tx transfer interrupts */
    NVIC_ENABLEINT(STM32_INT_DMA1C7);

    /* set low priority for rx transfer (it will be enabled later), just make sure
     * that this interrupt is of the same priority as the usart2 interrupt (meaning
     * both interrupts are executed one after another [without preemption]) */
    NVIC_SETINTPRI(STM32_INT_DMA1C6, 0xf0);

	/* exit critical section */
	Critical_Exit();

	/* reset lock */
	Sem_Release(&usart2rx_sem);
	Sem_Release(&usart2tx_sem);

	/* report status */
	return EOK;
}

/* send data */
int USART2_Send(const void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int rc = size, sync = cb == CB_SYNC;

	/* store information */
	tx_cb = cb, tx_size = size;

    /* disable dma for reconfiguration */
    DMA1C7->CCR &= ~DMA_CCR_EN;
    /* store memory pointer */
    DMA1C7->CMAR = (uint32_t)ptr;
    /* store transfer size */
    DMA1C7->CNDTR = size;
    /* enable transfer */
    DMA1C7->CCR |= DMA_CCR_EN;

	/* wait loop used for sync  */
	while (sync && tx_cb == CB_SYNC);

	/* report status */
	return rc;
}

/* receive data */
int USART2_Recv(void *ptr, size_t size, cb_t cb)
{
    /* result code, sync or async call? */
    int rc = size, sync = cb == CB_SYNC;

    /* store callback information */
    rx_cb = cb, rx_size = size, rx_ptr = ptr;
    /* use the interrupt to initiate reception */
    NVIC_SETPENDING(STM32_INT_DMA1C6);
    /* enable dma interrupt */
    NVIC_ENABLEINT(STM32_INT_DMA1C6);

    /* wait-state for sync accesses */
    while (sync && rx_cb == CB_SYNC);
    /* report status */
    return rc;
}

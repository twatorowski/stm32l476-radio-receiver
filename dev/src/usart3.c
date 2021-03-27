/**
 * @file usart3.c
 * 
 * @date 2021-01-20
 * @author twatorowski 
 * 
 * @brief USART3 Driver
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "err.h"
#include "dev/usart3.h"
#include "stm32h743/dma.h"
#include "stm32h743/dmamux.h"
#include "stm32h743/nvic.h"
#include "stm32h743/rcc.h"
#include "stm32h743/gpio.h"
#include "stm32h743/usart.h"
#include "sys/critical.h"
#include "sys/yield.h"
#include "util/elems.h"
#include "util/minmax.h"
#include "util/msblsb.h"
#include "util/string.h"

/* reception circular buffer */
static uint8_t circ[512];
/* buffer tail pointer */
static uint32_t head, tail;

/* initialize usart3 driver */
err_t USART3_Init(void)
{
    /* enter critical section */
    Critical_Enter();

    /* enable dma */
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    /* enable gpiod */
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN;
    /* enable usart3 clock */
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;

    /* pd8 - txd, pd9 - rxd */
    GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    /* set alternate function to usart */
    GPIOD->AFRH |= GPIO_AF7_USART3 << LSB(GPIO_AFRH_AFSEL8) | 
        GPIO_AF7_USART3 << LSB(GPIO_AFRH_AFSEL9);
    /* enable pull up for rxd line */
    GPIOD->PUPDR |= GPIO_PUPDR_PUPD9_0;
    /* set both as alternate function */
    GPIOD->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;

    /* tx dma configuration */
    /* peripheral address */
    DMA1C0->PAR = (uint32_t)&USART3->TDR;
    /* configure tx dma */
    DMA1C0->CR = DMA_CR_MINC | DMA_CR_DIR_0;
    /* connect the usart 3 tx dma request */
    DMAMUX1->C0CR = DMAMUX1_USART3_TX_DMA << LSB(DMAMUX_CCR_DMAREQ_ID);

    /* rx dma configuration */
    /* peripheral address */
    DMA1C1->PAR = (uint32_t)&USART3->RDR;
    /* data goes to circular buffer */
    DMA1C1->M0AR = (uint32_t)circ;
    /* setup circular buffer size */
    DMA1C1->NDTR = sizeof(circ);
    /* configure rx dma for circular buffer operation */
    DMA1C1->CR = DMA_CR_EN | DMA_CR_MINC | DMA_CR_CIRC;
    /* connect the usart 3 rx dma request */
    DMAMUX1->C1CR = DMAMUX1_USART3_RX_DMA << LSB(DMAMUX_CCR_DMAREQ_ID);

    /* configure baud rate */
    USART3->BRR = (APB1CLOCK_HZ + USART3_BAURDRATE / 2) / USART3_BAURDRATE;
    // /* x-mission dma request generation enable */
    USART3->CR3 = USART_CR3_DMAR | USART_CR3_DMAT;
    /* start the receiver and transmitter */
    USART3->CR1 = USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;

    /* exit critical section */
    Critical_Exit();

    /* return status */
    return EOK;
}

/* send data */
err_t USART3_Send(const void *ptr, size_t size, dtime_t timeout)
{
    /* current time */
    time_t ts = time(0);

    /* clear interrupt flag */
    DMA1->LIFCR = DMA_LIFCR_CTCIF0;

    /* disable dma for reconfiguration */
    DMA1C0->CR &= ~DMA_CR_EN;
    /* store memory pointer */
    DMA1C0->M0AR = (uint32_t)ptr;
    /* store transfer size */
    DMA1C0->NDTR = size;
    /* enable transfer */
    DMA1C0->CR |= DMA_CR_EN;

    /* poll as long as there is data in buffer */
    while (!(DMA1->LISR & DMA_LISR_TCIF0) || !(USART3->ISR & USART_ISR_TC)) {
        /* check for timeout */
        if (timeout && dtime(time(0), ts) > timeout)
            return ETIMEOUT;
        /* no timeout, continue waiting */
        Yield();
    }

    /* return information about how many bytes were sent */
    return size;
}

/* receive data */
err_t USART3_Recv(void *ptr, size_t size, dtime_t timeout)
{
    /* byte-wise pointer */
    uint8_t *p = ptr; 
    /* current time */
    time_t ts = time(0);

    /* wait for data loop */
    while ((head = elems(circ) - DMA1C1->NDTR) - tail == 0) {
        /* check for timeout */
        if (timeout && dtime(time(0), ts) > timeout)
            return ETIMEOUT;
        /* no timeout, continue waiting */
        Yield();
    }
    
    /* get number of bytes to copy */
    uint32_t bnum = min((head - tail) % elems(circ), size);
    /* number of bytes before circ buffer wraps */
    uint32_t wrap = min(bnum, elems(circ) - tail);

    /* copy data before wrapping */
    memcpy(p, circ + tail, wrap);
    /* copy data after wrapping */
    if (bnum - wrap)
        memcpy(p + wrap, circ, bnum - wrap);
    
    /* update tail pointer */
    tail = (tail + bnum) % elems(circ);

    /* report the number of bytes read */
    return bnum;
}

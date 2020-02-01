/**
 * @file led.c
 * 
 * @date 2020-01-18
 * @author twatorowski 
 * 
 * @brief On-Board LED Driver
 */

#include "err.h"
#include "dev/led.h"
#include "stm32l476/gpio.h"
#include "stm32l476/rcc.h"
#include "sys/critical.h"

int Led_Init(void)
{
    /* enter critcal section */
    Critical_Enter();

    /* enable gpio b */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* pb2 - red led */
    GPIOB->MODER &= ~(GPIO_MODER_MODER2);
    /* crank up the speed */
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
    /* default state */
    GPIOB->BSRR = GPIO_BSRR_BR_2;
    /* set as output */
    GPIOB->MODER |= GPIO_MODER_MODER2_0;

    /* exti critical section */
    Critical_Exit();
    /* report status */
    return EOK;
}

/* set led state */
void Led_SetState(int enable, uint32_t leds)
{
	/* split across the ports */
	uint32_t portb = leds & LED_RED;
	/* set port */
	GPIOB->BSRR = enable ? portb : portb << 16;
}
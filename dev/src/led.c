/**
 * @file led.c
 * 
 * @date 2020-03-12
 * @author twatorowski 
 * 
 * @brief On-Board LED Driver
 */

#include "err.h"
#include "dev/led.h"
#include "stm32h743/gpio.h"
#include "stm32h743/rcc.h"
#include "sys/critical.h"

/* initialize led driver */
int Led_Init(void)
{
    /* enter critcal section */
    Critical_Enter();

    /* enable gpiob & gpioe */
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOEEN;

    /* pb0 - green, pb14 - red,  */
    GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER14);
    /* set the pin high */
    GPIOB->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR14;
    /* set as output */
    GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER14_0;


    /* pe1 - yellow */
    GPIOE->MODER &= ~(GPIO_MODER_MODER1);
    /* default state */
    GPIOE->BSRR = GPIO_BSRR_BR1;
    /* set as output */
    GPIOE->MODER |= GPIO_MODER_MODER1_0;

    /* exti critical section */
    Critical_Exit();
    /* report status */
    return EOK;
}

/* set led state */
void Led_SetState(int enable, led_colors_t leds)
{
    /* green led logic */
    if (leds & LED_GRN) 
        GPIOB->BSRR = enable ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0;
    /* red led logic */
    if (leds & LED_RED) 
        GPIOB->BSRR = enable ? GPIO_BSRR_BS14 : GPIO_BSRR_BR14;
    /* yellow led logic */
    if (leds & LED_YEL) 
        GPIOE->BSRR = enable ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1;
}
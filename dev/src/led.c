/**
 * @file led.c
 * 
 * @date 2020-03-12
 * @author twatorowski 
 * 
 * @brief On-Board LED Driver
 */

#include "err.h"
#include "dev/gpio.h"
#include "dev/led.h"
#include "sys/critical.h"

/* initialize led driver */
int Led_Init(void)
{
    /* enter critcal section */
    Critical_Enter();

    /* pb0 - green, pb14 - red */
    GPIO_CfgOutput(GPIOB,  0, GPIO_OTYPE_PP, 0);
    GPIO_CfgOutput(GPIOB, 14, GPIO_OTYPE_PP, 0);
    /* pe1 - yellow */
    GPIO_CfgOutput(GPIOE,  1, GPIO_OTYPE_PP, 0);

    /* exti critical section */
    Critical_Exit();
    /* report status */
    return EOK;
}

/* set led state */
void Led_SetState(int enable, led_colors_t leds)
{
    /* green led logic */
    if (leds & LED_GRN) GPIO_Set(GPIOB,  0, enable);
    /* red led logic */
    if (leds & LED_RED) GPIO_Set(GPIOB, 14, enable);
    /* yellow led logic */
    if (leds & LED_YEL) GPIO_Set(GPIOE,  1, enable);
}
/**
 * @file gpio.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-05-06
 * 
 * @brief General Purpose Input-Output
 */

#include "err.h"
#include "dev/gpio.h"
#include "stm32h743/gpio.h"
#include "stm32h743/rcc.h"
#include "sys/critical.h"

/* initialize gpio */
err_t GPIO_Init(void)
{
    /* enter critcal section */
    Critical_Enter();

    /* enable all of the gpios */
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | 
        RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_GPIODEN | RCC_AHB4ENR_GPIOEEN | 
        RCC_AHB4ENR_GPIOFEN | RCC_AHB4ENR_GPIOGEN | RCC_AHB4ENR_GPIOHEN;
    
    /* exit critical section */
    Critical_Exit();
    /* report status */
    return EOK;
}

/* configure the pin as output */
err_t GPIO_CfgOutput(gpio_t *gpio, gpio_pin_t pin, gpio_otype_t otype, 
    int initial_value)
{
    /* clear the moder register */
    gpio->MODER &= ~(GPIO_MODER_MODER0 << (pin * 2));
    /* set initial value */
    gpio->BSRR = (initial_value ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0) << pin;
    /* update the output type */
    gpio->OTYPER = (gpio->OTYPER & ~(GPIO_OTYPER_OT0 << pin)) |
        otype << pin;
    /* set as output */
    gpio->MODER |= GPIO_MODER_MODER0_0 << (pin * 2);

    /* report status */
    return EOK;
}

/* configure the output type */
err_t GPIO_CfgOutputType(gpio_t *gpio, gpio_pin_t pin, gpio_otype_t otype)
{
    /* update the output type */
    gpio->OTYPER = (gpio->OTYPER & ~(GPIO_OTYPER_OT0 << pin)) |
        otype << pin;
    /* report status */
    return EOK;
}

/* configure pin as output */
err_t GPIO_CfgInput(gpio_t *gpio, gpio_pin_t pin)
{
    /* set as input */
    gpio->MODER &= ~(GPIO_MODER_MODER0 << (pin * 2));
    /* report status */
    return EOK;
}

/* configure pulling resistor type */
err_t GPIO_CfgPull(gpio_t *gpio, gpio_pin_t pin, gpio_pull_t pull)
{
    /* write new value to the pull register */
    gpio->PUPDR = (gpio->PUPDR * ~(GPIO_PUPDR_PUPD0 << (pin * 2))) |
        pull << (pin * 2);
    /* report status */
    return EOK;
}

/* configure given pin as analog input */
err_t GPIO_CfgAnalog(gpio_t *gpio, gpio_pin_t pin)
{
    /* set both bits in moder register */
    gpio->MODER |= GPIO_MODER_MODER0 << (pin * 2);
    /* report status */
    return EOK;
}

/* configure given pin as alternate function */
err_t GPIO_CfgAlternatefunction(gpio_t *gpio, gpio_pin_t pin, gpio_af_t af)
{
    /* select right alternate function register */
    reg32_t *afr = pin < 8 ? &gpio->AFRL : &gpio->AFRH;
    /* bit field position */
    int pos = (pin % 8) * 4;

    /* clear the moder register */
    gpio->MODER &= ~(GPIO_MODER_MODER0 << (pin * 2));
    /* setup alternate function register */
    *afr = (*afr & ~(GPIO_AFRL_AFSEL0 << pos)) | af << pos; 
    /* set as alternate function */
    gpio->MODER |= GPIO_MODER_MODER0_1 << (pin * 2);

    /* report status */
    return EOK;
}


/**
 * @file analog.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-05-08
 * 
 * @brief Analog to digital converter
 */

#include "err.h"
#include "dev/analog.h"
#include "dev/gpio.h"
#include "stm32h743/rcc.h"
#include "stm32h743/gpio.h"
#include "stm32h743/adc.h"
#include "sys/critical.h"
#include "sys/delay.h"
#include "util/msblsb.h"

/* analog to digital converter driver initialization */
err_t Analog_Init(void)
{
    /* enter critical section */
    Critical_Enter();

    /* pa0 - AIN0 - A0, pa1 - AIN1 - A1, pa4 - AIN4 - A2 */
    GPIO_CfgAnalog(GPIOA, GPIO_PIN_0);
    GPIO_CfgAnalog(GPIOA, GPIO_PIN_1);
    GPIO_CfgAnalog(GPIOA, GPIO_PIN_4);
    /* pb0 - AIN8 - A3 */
    GPIO_CfgAnalog(GPIOB, GPIO_PIN_0);
    /* pc0 - AIN10 - A4, pc1 - AIN11 - A5 */
    GPIO_CfgAnalog(GPIOC, GPIO_PIN_0);
    GPIO_CfgAnalog(GPIOC, GPIO_PIN_1);

    /* enable clock for the adc 1 */
    RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN;
    /* select peripheral clock as the clock for the adc */
    RCC->D3CCIPR |= 2 << LSB(RCC_D3CCIPR_ADCSRC);

    /* disable power down */
    ADC1->CR &= ~ADC_CR_DEEPPWD;
    /* wait for the adc to exit power down */
    while ((ADC1->CR & ADC_CR_DEEPPWD));

    /* enable the ldo */
    ADC1->CR |= ADC_CR_ADVREGEN;
    /* wait for the ldo to stabilize */
    Delay(100);
    
    /* clear the ready bit */
    ADC1->ISR = ADC_ISR_ADRDY;
    /* enable adc */
    ADC1->CR |= ADC_CR_ADEN;
    /* wait till it's enabled */
    while (!(ADC1->ISR & ADC_ISR_ADRDY));

    /* exit critical section */
    Critical_Exit();
    /* report status */
    return EOK;
}

/* perform conversion on given channel */
err_t Analog_Convert(analog_channel_t channel, uint16_t *value)
{
    /* conversion on single channel */
    ADC1->SQR1 = channel << LSB(ADC_SQR1_SQ1) | 0 << LSB(ADC_SQR1_L);
    
    /* start the software-triggered conversion */
    ADC1->CR |= ADC_CR_ADSTART;
    /* wait for the end of conversion */
    while (!(ADC1->ISR & ADC_ISR_EOC));
    
    /* read the value from the data register */
    *value = ADC1->DR;
    /* return status */
    return EOK;
}
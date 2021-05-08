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
#include "util/bit.h"
#include "util/msblsb.h"

/* analog to digital converter driver initialization */
err_t Analog_Init(void)
{
    /* enter critical section */
    Critical_Enter();

    /* pa3 - ADC12_INP15 - A0, pc0 - ADC123_INP10 - A1, 
     * pc3 - ADC12_INP13 - A2 */
    GPIO_CfgAnalog(GPIOA, GPIO_PIN_3);
    GPIO_CfgAnalog(GPIOC, GPIO_PIN_0);
    GPIO_CfgAnalog(GPIOC, GPIO_PIN_3);
    /* pb1 - ADC12_INP5 - A3 */
    GPIO_CfgAnalog(GPIOB, GPIO_PIN_1);
    /* pc2 - ADC123_INP12 - A4, pf10 - ADC3_INP6, - A5 */
    GPIO_CfgAnalog(GPIOC, GPIO_PIN_2);
    GPIO_CfgAnalog(GPIOF, GPIO_PIN_10);

    /* enable clock for the adc 1 */
    RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN;
    /* select  hclk/23 as the clock */
    ADC12_COMMON->CCR = ADC_CCR_CKMODE_1;

    /* disable power down */
    ADC1->CR &= ~ADC_CR_DEEPPWD;
    /* wait for the adc to exit power down */
    while ((ADC1->CR & ADC_CR_DEEPPWD));

    /* enable the ldo */
    ADC1->CR |= ADC_CR_ADVREGEN;
    /* wait for the ldo to stabilize */
    Delay(100);

    /* enable adc */
    ADC1->CR |= ADC_CR_ADCAL;
    /* wait till it's enabled */
    while (ADC1->CR & ADC_CR_ADCAL);
    
    /* clear the ready bit */
    ADC1->ISR = ADC_ISR_ADRDY;
    /* enable adc */
    ADC1->CR |= ADC_CR_ADEN;
    /* wait till it's enabled */
    while (!(ADC1->ISR & ADC_ISR_ADRDY));

    /* preselections */
    ADC1->PCSEL = BIT_VAL(ANALOG_A0) | BIT_VAL(ANALOG_A1) | BIT_VAL(ANALOG_A2) | 
        BIT_VAL(ANALOG_A3) | BIT_VAL(ANALOG_A4) | BIT_VAL(ANALOG_A5); 

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
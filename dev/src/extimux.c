/**
 * @file extimux.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-05-05
 * 
 * @brief Exti interrupt multiplexer
 */

#include "assert.h"
#include "config.h"
#include "err.h"
#include "dev/extimux.h"
#include "stm32h743/exti.h"
#include "stm32h743/gpio.h"
#include "stm32h743/nvic.h"
#include "stm32h743/rcc.h"
#include "stm32h743/syscfg.h"
#include "sys/critical.h"
#include "util/elems.h"

/* exti-mux routines */
static extimux_hndl_t routines[16];

/* exti interrupt mux for line 0 */
void ExtiMux_Exti0Isr(void)
{
    routines[0](EXTIMUX_CH_0);
}

/* exti interrupt mux for line 1 */
void ExtiMux_Exti1Isr(void)
{
    routines[1](EXTIMUX_CH_1);
}

/* exti interrupt mux for line 2 */
void ExtiMux_Exti2Isr(void)
{
    routines[2](EXTIMUX_CH_2);
}

/* exti interrupt mux for line 3 */
void ExtiMux_Exti3Isr(void)
{
    routines[3](EXTIMUX_CH_3);
}

/* exti interrupt mux for line 4 */
void ExtiMux_Exti4Isr(void)
{
    routines[4](EXTIMUX_CH_4);
}

/* exti interrupt mux for lines 5 to 9 */
void ExtiMux_Exti9_5Isr(void)
{
    /* get pending register */
    uint32_t pr = EXTI->PR1;

    /* execute handlers */
    if (pr & EXTI_PR1_PR5) routines[5](EXTIMUX_CH_5);
    if (pr & EXTI_PR1_PR6) routines[6](EXTIMUX_CH_6); 
    if (pr & EXTI_PR1_PR7) routines[7](EXTIMUX_CH_7); 
    if (pr & EXTI_PR1_PR8) routines[8](EXTIMUX_CH_8); 
    if (pr & EXTI_PR1_PR9) routines[9](EXTIMUX_CH_9); 
}

/* exti interrupt mux for lines 4 to 15 */
void ExtiMux_Exti15_10Isr(void)
{
    /* get pending register */
    uint32_t pr = EXTI->PR1;

    /* execute handlers */
    if (pr & EXTI_PR1_PR10) routines[10](EXTIMUX_CH_10);
    if (pr & EXTI_PR1_PR11) routines[11](EXTIMUX_CH_11); 
    if (pr & EXTI_PR1_PR12) routines[12](EXTIMUX_CH_12); 
    if (pr & EXTI_PR1_PR13) routines[13](EXTIMUX_CH_13); 
    if (pr & EXTI_PR1_PR14) routines[14](EXTIMUX_CH_14); 
    if (pr & EXTI_PR1_PR15) routines[15](EXTIMUX_CH_15); 
}

/* initialize exti multiplexer */
err_t ExtiMux_Init(void)
{
    /* enter critical section */
    Critical_Enter();
    /* enable sys cfg */
    RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
    
    /* set priority */
    NVIC_SETINTPRI(STM32_INT_EXTI0, INT_PRI_EXTIMUX_0);
    NVIC_SETINTPRI(STM32_INT_EXTI1, INT_PRI_EXTIMUX_1);
    NVIC_SETINTPRI(STM32_INT_EXTI2, INT_PRI_EXTIMUX_2);
    NVIC_SETINTPRI(STM32_INT_EXTI3, INT_PRI_EXTIMUX_3);
    NVIC_SETINTPRI(STM32_INT_EXTI4, INT_PRI_EXTIMUX_4);
    NVIC_SETINTPRI(STM32_INT_EXTI9_5, INT_PRI_EXTIMUX_9_5);
    NVIC_SETINTPRI(STM32_INT_EXTI15_10, INT_PRI_EXTIMUX_15_10);
    /* enable */
    NVIC_ENABLEINT(STM32_INT_EXTI0);    
    NVIC_ENABLEINT(STM32_INT_EXTI1);
    NVIC_ENABLEINT(STM32_INT_EXTI2);
    NVIC_ENABLEINT(STM32_INT_EXTI3);
    NVIC_ENABLEINT(STM32_INT_EXTI4);
    NVIC_ENABLEINT(STM32_INT_EXTI9_5);
    NVIC_ENABLEINT(STM32_INT_EXTI15_10);

    /* exit critical section */
    Critical_Exit();

    /* return error code */
    return EOK;
}

/* register interrupt routine */
err_t ExtiMux_RegisterRoutine(extimux_ch_t ch, extimux_hndl_t hndl)
{
    /* invalid channel number */
    if (ch < EXTIMUX_CH_0 || ch > EXTIMUX_CH_15)
        return EARGVAL;
    
    /* sanity check */
    assert(routines[ch] == 0, "extimux routine already assigned", ch);
    /* assign routine */
    routines[ch] = hndl;

    /* report status */
    return EOK;
}

/* route given external interrupt line to given gpio */
err_t ExtiMux_RouteToGPIO(extimux_ch_t ch, gpio_t *gpio)
{   
    /* invalid channel number */
    if (ch < EXTIMUX_CH_0 || ch > EXTIMUX_CH_15)
        return EARGVAL;

    /* mapping between channel and configuring register name */
    reg32_t * const lut_exticr[] = {
        &SYSCFG->EXTICR1, &SYSCFG->EXTICR2, 
        &SYSCFG->EXTICR3, &SYSCFG->EXTICR4
    }, *exticr = lut_exticr[ch / 4];
    /* bit offset in the exticr register */
    int bit_offs = (ch % 3) * 4; 

    /* mapping between gpio and bit value that we are supposed to write to 
     * exticr */
    const struct {gpio_t *gpio; uint32_t mask; } lut_mask[] = {
        {GPIOA, 0}, {GPIOB, 1}, {GPIOC, 2}, {GPIOD, 3}, 
        {GPIOE, 4}, {GPIOF, 5}, {GPIOG, 6}, {GPIOH, 7},
    }, *mask = lut_mask;
    
    /* look for the mask value */
    for (; mask != lut_mask + elems(lut_mask) && mask->gpio != gpio; mask++);
    /* none found? */
    if (mask == lut_mask + elems(lut_mask))
        return EARGVAL;

    /* update the exticr register */
    *exticr = (*exticr & ~(SYSCFG_EXTICR1_EXTI0 << bit_offs)) |
        mask->mask << bit_offs; 
    
    /* report status */
    return EOK;
}
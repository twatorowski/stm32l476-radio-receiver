/**
 * @file vectors.c
 * 
 * @date 2019-09-19
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief Interrupt/Exception vector table
 */

#include <stdint.h>
#include <stddef.h>

#include "defhndl.h"
#include "linker.h"
#include "startup.h"
#include "vectors.h"
#include "stm32l476/stm32l476.h"

/* includes with interrupt/exceptions handlers */
#include "dev/analog.h"
#include "dev/await.h"
#include "dev/dec.h"
#include "dev/extimux.h"
#include "dev/i2c1.h"
#include "dev/invoke.h"
#include "dev/joystick.h"
#include "dev/sai1a.h"
#include "dev/usart2.h"

/* shorthands so that the vector table looks neat! */
#define SET_SP(sp)                  [STM32_VECTOR_STACK_PTR_BASE].v = sp
#define SET_EXC_VEC(index, func)    [STM32_VECTOR_EXC_BASE + index].f = &func
#define SET_INT_VEC(index, func)    [STM32_VECTOR_INT_BASE + index].f = &func

/* vectors */
SECTION(".flash_vectors") vector_entry_t flash_vectors[] = {
    /* stack pointer */
    SET_SP(&__stack),

    /* exception vectors */
    /* reset vector */
    SET_EXC_VEC(STM32_EXC_RESET, Startup_ResetHandler),
    /* hard-fault */
    SET_EXC_VEC(STM32_EXC_HARDFAULT, DefHndl_DefaultHandler),

    /* interrupts */
    /* usart2 */
    SET_INT_VEC(STM32_INT_USART2, USART2_USART2Isr),
    SET_INT_VEC(STM32_INT_DMA1C7, USART2_DMA1C7Isr),
    SET_INT_VEC(STM32_INT_DMA1C6, USART2_DMA1C6Isr),

    /* ADC sampler */
    SET_INT_VEC(STM32_INT_DMA1C1, Analog_DMA1C1Isr),

    /* decimators */
    SET_INT_VEC(STM32_INT_DMA1C4, Dec_DMA1C4Isr),

    /* i2c1 */
    SET_INT_VEC(STM32_INT_I2C1_EV, I2C1_I2C1EvIsr),
    SET_INT_VEC(STM32_INT_I2C1_ER, I2C1_I2C1ErIsr),

    /* await module */
    SET_INT_VEC(STM32_INT_TIM3, Await_TIM3Isr),

    /* joystick interrupts */
    SET_INT_VEC(STM32_INT_EXTI0, Joystick_Exti0_3_5Isr),
    SET_INT_VEC(STM32_INT_EXTI1, Joystick_Exti0_3_5Isr),
    SET_INT_VEC(STM32_INT_EXTI2, Joystick_Exti0_3_5Isr),
    SET_INT_VEC(STM32_INT_EXTI3, Joystick_Exti0_3_5Isr),

    /* extimux */
    SET_INT_VEC(STM32_INT_EXTI5_9, ExtiMux_Exti5_9Isr),
    SET_INT_VEC(STM32_INT_EXTI10_15, ExtiMux_Exti10_15Isr),

    /* invoke module */
    SET_INT_VEC(STM32_INT_FMC, Invoke_FMCIsr),
};

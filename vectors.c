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

#include "compiler.h"
#include "defhndl.h"
#include "linker.h"
#include "startup.h"
#include "vectors.h"
#include "stm32h743/stm32h743.h"

/* includes with interrupt/exceptions handlers */
#include "sys/yield.h"
#include "dev/extimux.h"

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

    /* pending service */
    SET_EXC_VEC(STM32_EXC_PENDSV, Yield_PendSVHandler),


    /* interrupts */
    /* exti interrupt handlers */
    SET_INT_VEC(STM32_INT_EXTI0, ExtiMux_Exti0Isr),
    SET_INT_VEC(STM32_INT_EXTI1, ExtiMux_Exti1Isr),
    SET_INT_VEC(STM32_INT_EXTI2, ExtiMux_Exti2Isr),
    SET_INT_VEC(STM32_INT_EXTI3, ExtiMux_Exti3Isr),
    SET_INT_VEC(STM32_INT_EXTI4, ExtiMux_Exti4Isr),
    SET_INT_VEC(STM32_INT_EXTI9_5, ExtiMux_Exti9_5Isr),
    SET_INT_VEC(STM32_INT_EXTI15_10, ExtiMux_Exti15_10Isr),
};

/**
 * @file dynamic_int.c
 * 
 * @date 2020-02-02
 * @author twatorowski 
 * 
 * @brief Test for dynamic interrupts level changing
 */

#include "assert.h"
#include "compiler.h"
#include "err.h"
#include "arch/arch.h"
#include "dev/invoke.h"
#include "stm32l476/nvic.h"
#include "stm32l476/scb.h"
#include "sys/critical.h"

/* counter */
static volatile int cnt;

typedef struct waitstate {
    int exc_num, priority;
} waitstate_t;

/* start the waitstate */
static waitstate_t TestDynInt_WaitStateStart(void)
{
    /* get current exception number */
    waitstate_t wsi = {
        /* read current exception number */
        .exc_num = Arch_ReadIPSR() & 0xff,
        /* setup the priority, 256 = lowest possible */
        .priority = 256,
    };

    /* thread mode */
    if (wsi.exc_num < STM32_VECTOR_EXC_BASE) {
        // DO nothing
    /* some exceptions cannot be messed around with */
    } else if (wsi.exc_num <= (STM32_VECTOR_EXC_BASE + STM32_EXC_HARDFAULT)) {
        assert(0, "waitstate called on the special core exception", 0);
    /* core exception */
    } else if (wsi.exc_num < STM32_VECTOR_INT_BASE) {
        /* get current exception priority */
        wsi.priority = SCB_GETEXCPRI(wsi.exc_num);
        /* set lowest possible priority */
        SCB_SETEXCPRI(wsi.exc_num, 255);
    /* interrupt routines */
    } else {
        /* get current interrupt priority */
        wsi.priority = NVIC_GETINTPRI(wsi.exc_num - STM32_VECTOR_INT_BASE);
        /* set lowest possible priority */
        NVIC_SETINTPRI(wsi.exc_num - STM32_VECTOR_INT_BASE, 255);
    }

    /* report the waitstate info */
    return wsi;
}

/* end the waitstate */
static int TestDynInt_WaitStateEnd(waitstate_t wsi)
{
    /* thread mode */
    if (wsi.exc_num < STM32_VECTOR_EXC_BASE) {
        // do nothing
    /* core exception */
    } else if (wsi.exc_num < STM32_VECTOR_INT_BASE) {
        /* restore the priority of the exception vector */
        SCB_SETEXCPRI(wsi.exc_num, wsi.priority);
    /* interrupt */
    } else {
        /* restore the priority of the interrupt */
        NVIC_SETINTPRI(wsi.exc_num - STM32_VECTOR_INT_BASE, wsi.priority);
    }

    /* report status */
    return EOK;
}

/* invoked callback - low priority */
static int TestDynInt_InvokedCallback(void *ptr)
{
    cnt = 1;
    /* report status */
    return EOK;
}

/* lcd interrupt - high level one */
void TestDynInt_LCDIsr(void)
{
    /* call on the low priority level */
    Invoke_CallMeElsewhere(TestDynInt_InvokedCallback, 0);

    /* wait in lowest priority possible */
    for (waitstate_t wsi = TestDynInt_WaitStateStart(); 
        cnt == 0 || TestDynInt_WaitStateEnd(wsi); );

}

/* initialize test */
int TestDynInt_Init(void)
{
    /* enter critical section */
    Critical_Enter();
    /* set high priority */
    NVIC_SETINTPRI(STM32_INT_LCD, 0x10);
    /* enable interrupt */
    NVIC_ENABLEINT(STM32_INT_LCD);
    /* exit critical section */
    Critical_Exit();

    /* start the execution */
    NVIC_SETPENDING(STM32_INT_LCD);
    /* report status */
    return EOK;
}
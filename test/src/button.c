/**
 * @file button.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-05-07
 * 
 * @brief Test for the user button serviced by exti interrupts
 */

#include "err.h"
#include "dev/gpio.h"
#include "dev/extimux.h"
#include "dev/led.h"
#include "sys/yield.h"
#include "sys/sleep.h"

#define DEBUG
#include "debug.h"

/* button pressed flag */
static int pressed = 0;

/* exti interrupt routine */
static void TestButton_ExtiIsr(extimux_ch_t ch)
{
    /* clear pending bit */
    ExtiMux_ClearPending(ch);
    /* mark the button as being pressed */
    pressed = 1;
}

/* button debounce task */
static void TestButton_Debounce(void *arg)
{
    /* monitor the pressed status */
    for (;; Sleep(100)) {
        /* button was pressed? */
        if (pressed) {
            pressed = 0; dprintf("pressed!\n");
        }
    }
}

/* test the clicy-clicky button */
err_t TestButton_Init(void)
{
    /* create the task that monitors the button state change */
    Yield_CreateTask(TestButton_Debounce, 0, 1024);

    /* configure button line as input */
    GPIO_CfgInput(GPIOC, 13);
    /* setup interrupt generation */
    ExtiMux_RegisterRoutine(EXTIMUX_CH_13, TestButton_ExtiIsr);
    /* rising edge sensitive */
    ExtiMux_CfgSensitivity(EXTIMUX_CH_13, EXTIMUX_SENS_RISE);
    /* route line13 to gpioc */
    ExtiMux_RouteToGPIO(EXTIMUX_CH_13, GPIOC);
    /* enable interrupt generation */
    ExtiMux_CfgInterrupt(EXTIMUX_CH_13, 1);

    /* report status */
    return EOK;
}
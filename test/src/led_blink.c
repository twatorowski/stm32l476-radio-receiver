/**
 * @file led_blink.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-11
 * 
 * @brief Blinking led that shows the os activity
 */

#include "err.h"
#include "dev/led.h"
#include "sys/sleep.h"
#include "sys/yield.h"


/* task that monitors os activity */
static void TestLEDBlink_Task(void *arg)
{
    /* encless task loop */
    while (1) {
        /* keep the led blinking */
        /* led on */
        Led_SetState(1, LED_RED);
        Sleep(250);
        /* led off */
        Led_SetState(0, LED_RED);
        Sleep(250);
    }
}

/* initialize the test */
err_t TestLEDBlink_Init(void)
{
    /* tasks' stack */
    static uint32_t stack[128];
    /* start the task */
    Yield_CreateTask(TestLEDBlink_Task, 0, stack, sizeof(stack));

    /* report status */
    return EOK;
}
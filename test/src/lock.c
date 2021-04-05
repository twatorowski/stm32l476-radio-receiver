/**
 * @file lock.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-05
 * 
 * @brief Test for locks
 */

#include "err.h"
#include "dev/led.h"
#include "sys/sem.h"
#include "sys/sleep.h"
#include "sys/time.h"
#include "sys/yield.h"

/* led lock */
static sem_t led_lock;
/* led task for setting the led on or off */
static void TestLock_LedTask(void *arg)
{
    /* led will be set if the argument is non-zero */
    int enable = arg != 0;

    /* endless task */
    while (1) {
        /* lock the led resource */
        Sem_Lock(&led_lock, 0);
        /* set the state */
        Led_SetState(enable, LED_RED);
        /* wait */
        Sleep(1000);
        /* release the lock */
        Sem_Release(&led_lock);
    }
}

/* initialize test */
err_t TestLock_Init(void)
{
    static uint32_t stack[2][128];

    /* start tasks */
    Yield_CreateTask(TestLock_LedTask, (void *)0, stack[0], sizeof(stack[0]));
    Yield_CreateTask(TestLock_LedTask, (void *)1, stack[1], sizeof(stack[1]));

    /* report status */
    return EOK;
}
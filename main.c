/**
 * @file main.c
 *
 * @date 23.06.2019
 * @author twatorowski (tw@mightydevices.com)
 *
 * @brief main application file
 */

#include "compiler.h"
#include "vectors.h"
#include "dev/analog.h"
#include "dev/extimux.h"
#include "dev/fpu.h"
#include "dev/gpio.h"
#include "dev/keypad.h"
#include "dev/lcd.h"
#include "dev/led.h"
#include "dev/systime.h"
#include "dev/usart3.h"
#include "sys/heap.h"
#include "sys/yield.h"

#define DEBUG
#include "debug.h"

/* tests */
#include "test/led_blink.h"

/* program main function, must return int so that gcc does not complain in 
 * pedantic mode (-Wmain) */
void Main(void *arg);

/* program init function, called before main with interrupts disabled */
void Init(void)
{
    /* initialize dynamic memory */
    Heap_Init();
    /* start the context switcher */
    Yield_Init();

    /* create the entry task */
    Yield_CreateTask(Main, 0, 2048);
    /* this shall initialize the scheduler */
    Yield_Start();
}

/* program main function, must return int so that gcc does not complain in 
 * pedantic mode (-Wmain) */
void Main(void *arg)
{
    /* enable the floating point unit */
    FPU_Init();
    /* initialize system timer */
    SysTime_Init();
    /* initialize gpio driver */
    GPIO_Init();
    /* adc driver */
    Analog_Init();
    /* initialize exti driver */
    ExtiMux_Init();

    /* initialize usart 3 */
    USART3_Init();

    /* initialize led driver */
    Led_Init();
    /* set led state */
    Led_SetState(1, LED_GRN | LED_RED | LED_YEL);

    /* initialize keypad driver */
    Keypad_Init();
    /* initialize lcd driver */
    LCD_Init();

    /* show some debug activity */
    dprintf("Welcome!\n", 0);

    /* tests */
    TestLEDBlink_Init();

    /* execution loop */
    while (1) {
        Yield();
    }
}

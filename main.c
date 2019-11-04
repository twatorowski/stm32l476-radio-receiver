/**
 * @file main.c
 *
 * @date 23.06.2019
 * @author twatorowski (tw@mightydevices.com)
 *
 * @brief main application file
 */

#include "assert.h"
#include "at/at.h"
#include "dev/cpuclock.h"
#include "dev/fpu.h"
#include "dev/usart2.h"
#include "dev/watchdog.h"
#include "test/usart2.h"

#define DEBUG
#include "debug.h"

/* program init function, called before main with interrupts disabled */
void Init(void)
{

}

/* program main function */
void Main(void)
{
    /* initialize the watchdog */
    Watchdog_Init();
    /* setup the cpu frequency */
    CpuClock_Init();
    /* enable the fpu */
    FPU_Init();

    /* start debugging */
    Debug_Init();
    /* internals */
    /* initialize usart2 */
    USART2_Init();

    /* at commands protocol */
    AT_Init();

    /* tests */
    /* initialize usart2 test */
    TestUSART2_Init();

    int i = 0;
	/* execution loop */
    while (1) {
        /* poll at protocol routines */
		AT_Poll();

        i++;
        assert(i < 1000000, "oopsey...");
        
        /* tests */
        /* poll usart2 test */
        TestUSART2_Poll();

        /* kick the dog counter */
        Watchdog_Kick();
	}
}

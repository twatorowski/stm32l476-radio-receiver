/**
 * @file main.c
 *
 * @date 23.06.2019
 * @author twatorowski (tw@mightydevices.com)
 *
 * @brief main application file
 */

#include "dev/cpuclock.h"
#include "dev/usart2.h"
#include "dev/watchdog.h"
#include "test/usart2.h"

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

    /* internals */
    /* initialize usart2 */
    USART2_Init();


    /* tests */
    /* initialize usart2 test */
    TestUSART2_Init();

	/* execution loop */
    while (1) {
        /* tests */
        /* poll usart2 test */
        TestUSART2_Poll();

        /* kick the dog counter */
        Watchdog_Kick();
	}
}

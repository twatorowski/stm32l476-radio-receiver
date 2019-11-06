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
#include "dev/analog.h"
#include "dev/cpuclock.h"
#include "dev/deci.h"
#include "dev/decq.h"
#include "dev/fpu.h"
#include "dev/i2c1.h"
#include "dev/rfin.h"
#include "dev/sai1a.h"
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
    /* intiialize adc sampler module */
    Analog_Init();
    /* initialize decimator for the in-phase channel */
    DecI_Init();
    /* initialize decimator for the quadrature channel */
    DecQ_Init();
    /* initialize i2c1 */
	I2C1_Init();
	/* initialize sai1a interface */
	SAI1A_Init();
    /* initialize rf input pin */
    RFIn_Init();

    /* externals */
    



    /* at commands protocol */
    AT_Init();

    /* tests */
    /* initialize usart2 test */
    TestUSART2_Init();

	/* execution loop */
    while (1) {
        /* poll at protocol routines */
		AT_Poll();
        
        /* tests */
        /* poll usart2 test */
        TestUSART2_Poll();

        /* kick the dog counter */
        Watchdog_Kick();
	}
}

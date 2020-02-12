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
#include "dev/await.h"
#include "dev/cpuclock.h"
#include "dev/cs43l22.h"
#include "dev/dec.h"
#include "dev/display.h"
#include "dev/extimux.h"
#include "dev/fpu.h"
#include "dev/i2c1.h"
#include "dev/invoke.h"
#include "dev/joystick.h"
#include "dev/led.h"
#include "dev/lsi.h"
#include "dev/rfin.h"
#include "dev/sai1a.h"
#include "dev/systime.h"
#include "dev/timemeas.h"
#include "dev/usart2.h"
#include "dev/usb.h"
#include "dev/usbcore.h"
#include "dev/usbdesc.h"
#include "dev/usb_audiosrc.h"
#include "dev/usb_vcp.h"
#include "dev/watchdog.h"
#include "radio/radio.h"
#include "test/am_radio.h"
#include "test/dac_sine.h"
#include "test/dec.h"
#include "test/float_fixp.h"
#include "test/radio.h"
#include "test/usart2.h"
#include "test/vcp.h"
#include "test/vcp_rate.h"

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
    /* enable the fpu */
    FPU_Init();

    /* setup the cpu frequency */
    CpuClock_Init();
    /* initialize low speed oscillator */
    LSI_Init();
    /* start systime */
	SysTime_Init();

    /* start debugging */
    Debug_Init();

    /* internals */
    /* invoke module */
    Invoke_Init();
    /* time measurement */
    TimeMeas_Init();
    /* exti mux */
    ExtiMux_Init();
    /* async awaiter */
    Await_Init();
    /* initialize usart2 */
    USART2_Init();
    /* intiialize adc sampler module */
    Analog_Init();
    /* initialize decimator for the rf data */
    Dec_Init();
    /* initialize i2c1 */
	I2C1_Init();
	/* initialize sai1a interface */
	SAI1A_Init();
    /* initialize rf input pin */
    RFIn_Init();
    /* initialize usb */
	USB_Init();
	/* initialize usb descriptors */
	USBDesc_Init();
	/* initialize core support */
	USBCore_Init();
    /* initialize audio source */
    USBAudioSrc_Init();
	/* initialize vcp */
	USBVCP_Init();
    

    /* externals */
    /* led */
    Led_Init();
    /* lcd display */
    Display_Init();
    /* joystick */
    Joystick_Init();
    /* bring up the dac */
    CS43L22_Init();

    /* at commands protocol */
    // AT_Init();

    /* initialize the radio receiver logic */
    // Radio_Init();

    /* tests */
    /* initialize usart2 test */
    // TestUSART2_Init();
    /* initialize dac test */
    // TestDACSine_Init();
    /* initialize decimators test */
    // TestDec_Init();
    /* test radio */
    // TestRadio_Init();
    // TestAMRadio_Init();
    /* test dynamic interrupt levels */
    // TestDynInt_Init();
    
        /* start usb action */
    USB_Connect(1);
    /* test the virtual com port */
    TestVCP_Init();
    // TestVCP2_Init();

    // USBVCP2_Recv(test, 10, te);
    // TestVCPRate_Init();

	/* execution loop */
    while (1) {
        /* poll at protocol routines */
		// AT_Poll();

        // TestVCP_Poll();


        /* kick the dog counter */
        Watchdog_Kick();
	}
}

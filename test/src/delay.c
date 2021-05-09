/**
 * @file delay.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief Test for delay function
 */

#include "err.h"
#include "dev/led.h"
#include "sys/delay.h"

/* start the delay test */
err_t TestDelay_Init(void)
{
    /* endless loop of led blinking */
    while (1) {
        Delay(100);
        Led_SetState(0, LED_GRN);
        Delay(100);
        Led_SetState(1, LED_GRN);
    }
    
    /* return status */
    return EOK;
}
/**
 * @file idle.c
 * 
 * @date 2020-02-15
 * @author twatorowski 
 * 
 * @brief Idle mode support
 */

#include "compiler.h"
#include "config.h"
#include "err.h"
#include "dev/led.h"
#include "dev/watchdog.h"
#include "stm32l476/stm32l476.h"

/* enter sleep mode */
static void Idle_EnterSleepMode(void)
{
	/* go to sleep, wait for wakeup event */
	ASM volatile ("wfi");
    /* kick the dog */
    Watchdog_Kick();
}

/* initialize idle mode monitor */
int Idle_Init(void)
{
	/* report status */
	return EOK;
}

/* polling in idle mode */
void Idle_Poll(void)
{
	/* disable interrupts globally. we cannot use basepri masking
	 * (i.e. CriticalEnter) because it will disable wakeup on interrupts
	 * with low priority */
	STM32_DISABLEINTS();
    /* notify of entering low power mode */
    #if LED_IDLE_SHOW_ACTIVITY
        Led_SetState(0, LED_RED);
    #endif
    /* enter sleep mode */
    Idle_EnterSleepMode();
	/* notify of exiting low power mode */
	#if LED_IDLE_SHOW_ACTIVITY
		Led_SetState(1, LED_RED);
    #endif
	/* re-enable interrupts */
	STM32_ENABLEINTS();
}
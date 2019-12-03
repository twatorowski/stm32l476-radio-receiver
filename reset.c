/**
 * @file reset.c
 * 
 * @date 2019-11-13
 * @author twatorowski 
 * 
 * @brief Routine to reset the MCU
 */

#include "compiler.h"
#include "stm32l476/scb.h"

/* resets the mcu */
void Reset_ResetMCU(void)
{
    /* perform the reset using the scb */
    SCB->AIRCR = SCB_AIRCR_SYSRESETREQ | SCB_AIRCR_VECTKEYSTAT;
}
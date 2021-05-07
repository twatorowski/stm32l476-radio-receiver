/**
 * @file reset.c
 * 
 * @date 2019-11-13
 * @author twatorowski 
 * 
 * @brief Routine to reset the MCU
 */

#include "compiler.h"
#include "stm32h743/scb.h"

/* resets the mcu */
void NORETURN Reset_ResetMCU(void)
{
    /* perform the reset using the scb */
    SCB->AIRCR = SCB_AIRCR_SYSRESETREQ | SCB_AIRCR_VECTKEY;
    /* this is so that the gcc does not complain */
    while (1);
}

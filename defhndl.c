/**
 * @file defhndl.c
 * 
 * @date 2019-09-19
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief Default Exception/Interrupt Handler
 */

#include "compiler.h"
#include "reset.h"

/* default interrupt/exception handler */
void NAKED DefHndl_DefaultHandler(void)
{
    /* reset the system */
    Reset_ResetMCU();
}


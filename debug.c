/**
 * @file debug.c
 * 
 * @date 2019-10-27
 * @author twatorowski
 * 
 * @brief Debugging related stuff
 */

#include <stdint.h>

#include "compiler.h"
#include "err.h"
#include "version.h"
#include "sys/sem.h"

#define DEBUG
#include "debug.h"

/** storage space for storing mcu state during critical failures */
debug_scb_info_t SECTION(".no_init") debug_scb_info;
debug_exc_info_t SECTION(".no_init") debug_exc_info;
debug_stack_frame_t SECTION(".no_init") debug_stack_frame;
debug_assert_info_t SECTION(".no_init") debug_assert_info;

/* print the introduction message */
static void Debug_PrintIntro(void)
{
    /* initial string */
    dprintf("-------------------------------------------------------\n", 0);
	dprintf("Radio 2.4.0, hw = %s, sw = %s\n", VERSION_HW_STR, 
        VERSION_HW_STR);
    dprintf("-------------------------------------------------------\n", 0);
}

/* display the stack frame */
static void Debug_PrintStackFrame(debug_stack_frame_t *sf)
{
    /* not a valid entry? */
    if ((sf->valid ^= DEBUG_VALID_ENTRY) != 0)
        return;

    /* intro message */
    dprintf("STACK FRAME:\n", 0);
    /* show the values of the registers r0-r3 */
    dprintf("r0 = %#x, r1 = %#x, r2 = %#x, r3 = %#x\n", 
        sf->r0, sf->r1, sf->r2, sf->r3);
    /* show the values of the rest of the registers */
    dprintf("r12 = %#x, lr = %#x, pc = %#x, xpsr = %#x\n", 
        sf->r12, sf->lr, sf->pc, sf->xpsr);
}

/* print the exception information */
static void Debug_PrintExcInfo(debug_exc_info_t *ei)
{
    /* not a valid entry? */
    if ((ei->valid ^= DEBUG_VALID_ENTRY) != 0)
        return;

    /* intro message */
    dprintf("EXCEPTION INFO:\n", 0);
    /* show the values of the interrupt program status register */
    dprintf("ipsr = %#x\n", ei->ipsr);
}

/* print the system control block information */
static void Debug_PrintSCBInfo(debug_scb_info_t *si)
{
    /* not a valid entry? */
    if ((si->valid ^= DEBUG_VALID_ENTRY) != 0)
        return;

    /* intro message */
    dprintf("SYSTEM CONTROL BLOCK:\n", 0);
    /* show the values of scb registers */
    dprintf("cfsr = %#x, hfsr = %#x\n", si->cfsr, si->hfsr);
    /* show pending exceptions */
    dprintf("mmar = %#x, bfar = %#x, shcsr = %#x\n", 
        si->mmar, si->bfar, si->shcsr);
}

/* print the system control block information */
static void Debug_PrintAssertInfo(debug_assert_info_t *ai)
{
    /* not a valid entry? */
    if ((ai->valid ^= DEBUG_VALID_ENTRY) != 0)
        return;

    /* intro message */
    dprintf("LAST ASSERT INFO:\n", 0);
    /* show last assert message */
    dprintf("message = %.128s\n", ai->message);
}


/* initialize debugging */
int Debug_Init(void)
{
    /* print intro message */
    Debug_PrintIntro();
    /* print all the information */
    Debug_PrintStackFrame(&debug_stack_frame);
    Debug_PrintExcInfo(&debug_exc_info);
    Debug_PrintSCBInfo(&debug_scb_info);
    Debug_PrintAssertInfo(&debug_assert_info);

    /* report status */
    return EOK;
}
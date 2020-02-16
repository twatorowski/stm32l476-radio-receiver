/**
 * @file defhndl.c
 * 
 * @date 2019-09-19
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief Default Exception/Interrupt Handler
 */

#include "compiler.h"

#include "err.h"
#include "reset.h"
#include "arch/arch.h"
#include "stm32l476/scb.h"

#define DEBUG
#include "debug_dump.h"

/* dump information to storage */
static void OPTIMIZE ("O0") DefHndl_Dump(void *sp, uint32_t ipsr)
{
    /* placeholders */
    volatile debug_exc_info_t *ei = &debug_exc_info; 
    volatile debug_scb_info_t *si = &debug_scb_info;
    volatile debug_stack_frame_t *sf = &debug_stack_frame;
    /* stack frame */
    struct ff {
        /* general purpose registers */
        uint32_t r0, r1, r2, r3;
        /* all other registers */
        uint32_t r12, lr, pc, xpsr; 
    } PACKED *frame = sp;

    /* copy general purpose registers */
    sf->r0 = frame->r0, sf->r1 = frame->r1; 
    sf->r2 = frame->r2, sf->r3 = frame->r3, sf->r12 = frame->r12;
    /* copy the rest of the registers */
    sf->lr = frame->lr, sf->pc = frame->pc, sf->xpsr = frame->xpsr;
    /* set as valid */
    sf->valid = DEBUG_VALID_ENTRY;

    /* store exception information */
    ei->ipsr = ipsr;
    /* set as valid */
    ei->valid = DEBUG_VALID_ENTRY;
    
    /* store system control block information */
    si->bfar = SCB->BFAR; si->cfsr = SCB->CFSR; 
    si->hfsr = SCB->HFSR; si->mmar = SCB->MMAR;
    si->shcsr = SCB->SHCSR;
    /* set as valid */
    si->valid = DEBUG_VALID_ENTRY;
}

/* default interrupt/exception handler */
void OPTIMIZE ("O0") NAKED DefHndl_DefaultHandler(void)
{
    /* read the stack pointer */
    void * sp = (void *)Arch_ReadMSP();
    /* read the interrupt program status reg */
    uint32_t ipsr = Arch_ReadIPSR();

    /* dump all the information */
    DefHndl_Dump(sp, ipsr);

    /* reset the system */
    Reset_ResetMCU();
}

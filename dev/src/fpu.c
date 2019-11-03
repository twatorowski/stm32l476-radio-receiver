/**
 * @file fpu.c
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief Floating Point Unit
 */

#include "err.h"
#include "arch/arch.h"
#include "stm32l476/scb.h"
#include "sys/critical.h"

/* initialize fpu */
int FPU_Init(void)
{
    /* enter critical section */
    Critical_Enter();

    /* enable co-processor access */
    SCB->CPACR |= 0xf << 20;
    /* synchronize cpu */
    Arch_DSB();
    Arch_ISB();

    /* exit critical section */
    Critical_Exit();

    /* report status */
    return EOK;
}

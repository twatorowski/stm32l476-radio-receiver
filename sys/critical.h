/**
 * @file critical.h
 *
 * @date 23.06.2019
 * @author twatorowski
 *
 * @brief 
 */

#ifndef SYS_CRITICAL_H_
#define SYS_CRITICAL_H_

#include "compiler.h"
#include "arch/arch.h"

/* critical section counter - used for nesting critical sections */
extern int critical_nesting_cnt;

/**
 * @brief enter critical section. this does not prevent the interrupt routines with
 * highest priority (0x00) to be executed. Shall be followed by Critical_Exit()
 */
static inline ALWAYS_INLINE void Critical_Enter(void)
{
	/* set interrupt base priority register */
	Arch_WriteBasepri(0x10);
	/* increment counter */
	critical_nesting_cnt++;
}

/**
 * @brief exit the critcal section and restore the normal operation
 */
static inline ALWAYS_INLINE void Critical_Exit(void)
{
	/* decrement counter, re-enable interrupts if needed */
	if (--critical_nesting_cnt == 0)
		Arch_WriteBasepri(0x00);
}

#endif /* SYS_CRITICAL_H_ */

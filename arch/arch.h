/**
 * @file arch.h
 *
 * @date 23.06.2019
 * @author twatorowski
 *
 * @brief architecture dependent instructions
 */

#ifndef ARCH_ARCH_H_
#define ARCH_ARCH_H_

#include <stdint.h>
#include "compiler.h"

/**
 * @brief Do nothing
 */
static inline ALWAYS_INLINE void Arch_NOP(void)
{
	/* instruction itself */
	ASM volatile ("nop\n");
}

/**
 * @brief the LDREX instruction loads a word from memory, initializing the 
 * state of the exclusive monitor(s) to track the synchronization operation
 *
 * @param src source address to load from. must be 32-bit aligned
 * @return 32-bit value present at address @p ptr
 */
static inline ALWAYS_INLINE uint32_t Arch_LDREX(void *src)
{
	/* result */
	uint32_t result;
	/* instruction itself */
	ASM volatile (
		"ldrex		%[result], [%[src]]	\n"
		: [result] "=r" (result)
		: [src] "r" (src)
	);
	/* report result */
	return result;
}

/**
 * @brief The STREX instruction performs a conditional store of a word to memory.
 * If the exclusive monitor(s) permit the store, the operation updates the 
 * memory location and returns the value 0 in the destination register, 
 * indicating that the operation succeeded. If the exclusive monitor(s) do not 
 * permit the store, the operation does not update the memory location and 
 * returns the value 1 in the destination register.
 *
 * @param dst destination address to store to. must be 32-bit aligned.
 * @param value value to be stored
 * @return 0 in case of success, 1 otherwise
 */
static inline ALWAYS_INLINE int Arch_STREX(void *dst, uint32_t value)
{
	/* storage result */
	int result;
	/* instruction itself */
	ASM volatile (
		"strex %[result], %[value], [%[dst]] \n"
		: [result] "=r" (result)
		: [value] "r" (value), [dst] "r" (dst)
	);
	/* report result */
	return result;
}

/**
 * @brief The DSB instruction completes when all explicit memory accesses 
 * before it complete.
 */
static inline ALWAYS_INLINE void Arch_DSB(void)
{
    /* this will stop the execution until all memory accesses are complete */
	ASM volatile ("dsb \n");
}

/**
 * @brief It flushes the pipeline of the processor, so that all instructions
 * following the ISB are fetched from cache or memory again, after the ISB 
 * instruction has been completed.
 */
static inline ALWAYS_INLINE void Arch_ISB(void)
{
    /* flush pipeline */
	ASM volatile ("isb \n");
}

/**
 * @brief The BASEPRI register defines the minimum priority for exception 
 * processing. When BASEPRI is set to a nonzero value, it prevents the 
 * activation of all exceptions with the same or lower priority level as the 
 * BASEPRI value.
 *
 * @param x value to be written
 */
static inline ALWAYS_INLINE void Arch_WriteBasepri(uint32_t x)
{
	/* assembly code */
	ASM volatile (
		"msr basepri, %[x] \n"
		:
		: [x] "r" (x)
	);
}

/**
 * @brief read the BASEPRI register value.
 *
 * @return value that was in the BASEPRI register.
 */
static inline ALWAYS_INLINE uint32_t Arch_ReadBasepri(void)
{
	/* result */
	uint32_t result;
	/* assembly code */
	__asm__ volatile (
		"mrs %[result], basepri	\n"
		: [result] "=r" (result)
		:
	);

	/* report result */
	return result;
}

/**
 * @brief compute the square root
 *
 * @param x number to compute the square root of
 *
 * @return square root value
 */
static inline ALWAYS_INLINE float Arch_VSQRT(float x)
{
	float result;
	/* some assembly magic */
	__asm__ volatile (
		"vsqrt.f32	  %0, %1\n"
		: "=w" (result)
		: "w" (x)
	);
	/* report result */
	return result;
}

/**
 * @brief compute the absolute value of the floating point number
 *
 * @param x number to compute the absolute value of
 *
 * @return absolute value
 */
static inline ALWAYS_INLINE float Arch_VABS(float x)
{
	float result;
	/* some assembly magic */
	__asm__ volatile (
		"vabs.f32	 %0, %1\n"
		: "=w" (result)
		: "w" (x)
	);
	/* report result */
	return result;
}

/**
 * @brief Returns the value of the stack pointer
 *
 * @return stack pointer value
 */
static inline ALWAYS_INLINE void * Arch_ReadMSP(void)
{
	/* result */
	void * result;
	/* some assembly magic */
	__asm__ volatile (
		"mrs		%0, msp			\n"
		: "=r" (result)
		:
	);

	/* report result */
	return result;
}

/**
 * @brief Returns the value of the interrupt program status register 
 *
 * @return interrupt program status register value
 */
static inline ALWAYS_INLINE uint32_t Arch_ReadIPSR(void)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"mrs		%0, ipsr		\n"
		: "=r" (result)
		:
	);

	/* report result */
	return result;
}

#endif /* ARCH_ARCH_H_ */

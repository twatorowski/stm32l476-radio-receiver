/*
 * atomic.h
 *
 *	Created on: 04-07-2015
 *		Author: Tomek
 */

#ifndef SYS_ATOMIC_H_
#define SYS_ATOMIC_H_

#include "compiler.h"
#include "err.h"
#include "arch/arch.h"

/* increment value */
static inline ALWAYS_INLINE uint32_t Atomic_ADD32(void *dst, uint32_t value)
{
	/* previous value */
	uint32_t val;

	/* loop until operation succeeds */
	do {
		/* read current value */
		val = Arch_LDREX(dst);
	/* try to write back */
	} while (Arch_STREX(dst, val + value));

    /* return the value as it was before the operation */
	return val;
}

/* and value */
static inline ALWAYS_INLINE uint32_t Atomic_AND32(void *dst, uint32_t value)
{
	/* previous value */
	uint32_t val;

	/* loop until operation succeeds */
	do {
		/* read current value */
		val = Arch_LDREX(dst);
	/* try to write back */
	} while (Arch_STREX(dst, val & value));

    /* return the value as it was before the operation */
	return val;
}

/* or value */
static inline ALWAYS_INLINE uint32_t Atomic_OR32(void *dst, uint32_t value)
{
	/* previous value */
	uint32_t val;

	/* loop until operation succeeds */
	do {
		/* read current value */
		val = Arch_LDREX(dst);
	/* try to write back */
	} while (Arch_STREX(dst, val | value));

    /* return the value as it was before the operation */
	return val;
}

/* xor value */
static inline ALWAYS_INLINE uint32_t Atomic_XOR32(void *dst, uint32_t value)
{
	/* previous value */
	uint32_t val;

	/* loop until operation succeeds */
	do {
		/* read current value */
		val = Arch_LDREX(dst);
	/* try to write back */
	} while (Arch_STREX(dst, val ^ value));

    /* return the value as it was before the operation */
	return val;
}

/* load value */
static inline ALWAYS_INLINE uint32_t Atomic_LDR32(void *src)
{
    /* load the value */
    return Arch_LDREX(src);
}

/* store value, return the status of the store */
static inline ALWAYS_INLINE int Atomic_STR32(void *dst, uint32_t value)
{
    /* try to store the value */
    return Arch_STREX(dst, value) == 0 ? EOK : EFATAL;
}

#endif /* SYS_ATOMIC_H_ */

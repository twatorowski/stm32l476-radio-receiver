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


/**
 * @brief Move the immediate value atomically from source to destination
 * 
 * @param dst destination
 * @param src source
 */
static inline ALWAYS_INLINE void Atomic_MOV32(volatile void *dst, volatile void *src)
{
    /* read-write until success */
    do {
        /* this read is just to start the exclusive access monitor */
        Arch_LDREX((void *)dst);
    /* write back */
    } while (Arch_STREX((void *)dst, *(volatile uint32_t *)src) != 0);
}

/**
 * @brief Increment value from *dst with `value`. Ensures atomicity of the 
 * operation.
 * 
 * @param dst source/destination pointer
 * @param value value to xor with
 * 
 * @return uint32_t value under *dst before incrementing
 */
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

/**
 * @brief AND value from *dst with `value`. Ensures atomicity of the operation.
 * 
 * @param dst source/destination pointer
 * @param value value to xor with
 * 
 * @return uint32_t value under *dst before ANDing
 */
static inline ALWAYS_INLINE uint32_t Atomic_AND32(volatile void *dst, 
    uint32_t value)
{
	/* previous value */
	uint32_t val;

	/* loop until operation succeeds */
	do {
		/* read current value */
		val = Arch_LDREX((void *)dst);
	/* try to write back */
	} while (Arch_STREX((void *)dst, val & value));

    /* return the value as it was before the operation */
	return val;
}


/*TODO: */
static inline ALWAYS_INLINE uint32_t Atomic_AND(uint32_t value, 
    volatile void *dst)
{
	/* previous value */
	uint32_t val;

	/* loop until operation succeeds */
	do {
		/* read current value */
		val = Arch_LDREX((void *)dst);
	/* try to write back */
	} while (Arch_STREX((void *)dst, val & value));

    /* return the value as it was before the operation */
	return val;
}
//TODO:
static inline ALWAYS_INLINE uint32_t Atomic_OR(uint32_t value, volatile void *dst)
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



/**
 * @brief OR value from *dst with `value`. Ensures atomicity of the operation.
 * 
 * @param dst source/destination pointer
 * @param value value to xor with
 * 
 * @return uint32_t value under *dst before ORing
 */
static inline ALWAYS_INLINE uint32_t Atomic_OR32(volatile void *dst, 
    uint32_t value)
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

/**
 * @brief XOR value from *dst with `value`. Ensures atomicity of the operation.
 * 
 * @param dst source/destination pointer
 * @param value value to xor with
 * 
 * @return uint32_t value under *dst before XORing
 */
static inline ALWAYS_INLINE uint32_t Atomic_XOR32(volatile void *dst, uint32_t value)
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

/**
 * @brief Loads value from source pointer. Start the atomic operation block. To 
 * be followed by Atomic_STR32()
 * 
 * @param src source pointer
 * 
 * @return uint32_t value read from the source
 */
static inline ALWAYS_INLINE uint32_t Atomic_LDR32(void *src)
{
    /* load the value */
    return Arch_LDREX(src);
}

/**
 * @brief Store the value after is was read by Atomic_LDR32(). Return the status 
 * of the store.
 * 
 * @param dst destination pointer
 * @param value value to be stored
 * 
 * @return ALWAYS_INLINE EOK is store was atomic, error otherwise 
 */
static inline ALWAYS_INLINE int Atomic_STR32(void *dst, uint32_t value)
{
    /* try to store the value */
    return Arch_STREX(dst, value) == 0 ? EOK : EFATAL;
}



#endif /* SYS_ATOMIC_H_ */

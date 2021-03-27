/**
 * @file atomic.h
 * 
 * @date 2020-03-12
 * @author twatorowski 
 * 
 * @brief Atomic operations
 */

#ifndef SYS_ATOMIC_H_
#define SYS_ATOMIC_H_

#include "compiler.h"
#include "err.h"
#include "sys/critical.h"

/**
 * @brief Move the immediate value atomically from source to destination
 * 
 * @param dst destination
 * @param src source
 * 
 *  @return uint32_t value under *dst before moving
 */
static inline ALWAYS_INLINE uint32_t Atomic_MOV32(volatile void *dst, 
    volatile void *src)
{
    /* value before update took place */
    uint32_t val;

    /* enter critical section */
    Critical_Enter();
    /* read the current value */
    val = *(volatile uint32_t *)dst;
    /* update with the new one */
    *(volatile uint32_t *)dst = *(volatile uint32_t *)src;
    /* exit critical section */
    Critical_Exit();
    
    /* return the value that was set prior to this function call */
    return val;
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
static inline ALWAYS_INLINE uint32_t Atomic_ADD32(volatile void *dst, 
    uint32_t value)
{
    /* previous value */
    uint32_t val;

    /* enter critical section */
    Critical_Enter();
    /* read the current value */
    val = *(volatile uint32_t *)dst;
    /* update with the new one */
    *(volatile uint32_t *)dst = val + value;
    /* exit critical section */
    Critical_Exit();

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

    /* enter critical section */
    Critical_Enter();
    /* read the current value */
    val = *(volatile uint32_t *)dst;
    /* update with the new one */
    *(volatile uint32_t *)dst = val & value;
    /* exit critical section */
    Critical_Exit();

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

    /* enter critical section */
    Critical_Enter();
    /* read the current value */
    val = *(volatile uint32_t *)dst;
    /* update with the new one */
    *(volatile uint32_t *)dst = val | value;
    /* exit critical section */
    Critical_Exit();

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
static inline ALWAYS_INLINE uint32_t Atomic_XOR32(volatile void *dst, 
    uint32_t value)
{
    /* previous value */
    uint32_t val;

    /* enter critical section */
    Critical_Enter();
    /* read the current value */
    val = *(volatile uint32_t *)dst;
    /* update with the new one */
    *(volatile uint32_t *)dst = val ^ value;
    /* exit critical section */
    Critical_Exit();

    /* return the value as it was before the operation */
    return val;
}

#endif /* SYS_ATOMIC_H_ */
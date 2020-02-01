/**
 * @file arch.h
 *
 * @date 23.06.2019
 * @author twatorowski
 *
 * @brief architecture dependent instructions
 */

#ifndef ARCH_ARCH_FPU_H_
#define ARCH_ARCH_FPU_H_

#include <stdint.h>
#include "compiler.h"

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
	ASM volatile (
		"vsqrt.f32	  %[result], %[x]\n"
		: [result] "=w" (result)
		: [x] "w" (x)
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
	ASM volatile (
		"vabs.f32	 %[result], %[x]\n"
		: [result] "=w" (result)
		: [x] "w" (x)
	);
	/* report result */
	return result;
}

/**
 * @brief convert the floating point to signed 32-bit fixed point notation. For 
 * numbers that exceed the fixed point notation boundaries saturation is used.
 *
 * @param x floating point number to convert
 * @param frac_bits number of fractional bits
 *
 * @return signed fixed point number
 */
static inline ALWAYS_INLINE int32_t Arch_VCVT_S32_F32(float x, 
    const int frac_bits)
{
	int32_t result;
	/* some assembly magic */
	ASM volatile (
		"vcvt.s32.f32	 %[result], %[x], %[frac_bits]\n"
		: [result] "=w" (result)
		: [x] "%[result]" (x), [frac_bits] "M" (frac_bits)
	);
	/* report result */
	return result;
}

/**
 * @brief convert the floating point to signed 16-bit fixed point notation. For 
 * numbers that exceed the fixed point notation boundaries saturation is used.
 *
 * @param x floating point number to convert
 * @param frac_bits number of fractional bits
 *
 * @return signed fixed point number
 */
static inline ALWAYS_INLINE int16_t Arch_VCVT_S16_F32(float x, 
    const int frac_bits)
{
	int16_t result;
	/* some assembly magic */
	ASM volatile (
		"vcvt.s16.f32	 %[result], %[x], %[frac_bits]\n"
		: [result] "=w" (result)
		: [x] "%[result]" (x), [frac_bits] "M" (frac_bits)
	);
	/* report result */
	return result;
}

/**
 * @brief Convert signed 32-bit fixed point notation number to floating point.
 * 
 * @param x input value in SQx.y format
 * @param frac_bits number of fractional bits ('y' in SQx.y)
 * 
 * @return converted number in a floating point representation 
 */
static inline ALWAYS_INLINE float Arch_VCVT_F32_S32(int32_t x, 
    const int frac_bits)
{
	float result;
	/* some assembly magic */
	ASM volatile (
		"vcvt.f32.s32	 %[result], %[x], %[frac_bits] \n"
		: [result] "=w" (result)
		: [x] "%[result]" (x), [frac_bits] "M" (frac_bits)
	);
	/* report result */
	return result;
}

/**
 * @brief Convert signed 16-bit fixed point notation number to floating point.
 * 
 * @param x input value in SQx.y format
 * @param frac_bits number of fractional bits ('y' in SQx.y)
 * 
 * @return converted number in a floating point representation 
 */
static inline ALWAYS_INLINE float Arch_VCVT_F32_S16(int16_t x, 
    const int frac_bits)
{
	float result;
	/* some assembly magic */
	ASM volatile (
		"vcvt.f32.s16	 %[result], %[x], %[frac_bits] \n"
		: [result] "=w" (result)
		: [x] "%[result]" (x), [frac_bits] "M" (frac_bits)
	);
	/* report result */
	return result;
}

#endif /* ARCH_ARCH_FPU_H_ */
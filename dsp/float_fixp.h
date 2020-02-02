/**
 * @file float_fixp.h
 * 
 * @date 2020-01-14
 * @author twatorowski 
 * 
 * @brief Conversions beteween floating point and fixed point number arrays
 */

#ifndef FLOAT_FIXP_H
#define FLOAT_FIXP_H

#include <stdint.h>

#include "compiler.h"
#include "arch/arch_fpu.h"

/**
 * @brief convert the 32-bit fixed point number to floating point.
 * notation SQx.y. This is implemented as inline function so that the nunber of 
 * 'frac_bits' can be set by the caller. It needs to be a compile-time constant.
 * 
 * @param in fixed-point number array that is about to be converted
 * @param num number of values to convert
 * @param frac_bits number of fractional bits (compile-time constant)
 * @param out destination array for the floating point numbers
 * 
 */
static inline ALWAYS_INLINE void OPTIMIZE("O3") LOOP_UNROLL 
    FloatFixp_Fixp32ToFloat(const int32_t *in, int num, const int frac_bits, 
    float *out)
{
    int i = 0;
    /* process four at the time */
    for (; i + 4 <= num; i += 4) {
        out[i + 0] = Arch_VCVT_F32_S32(in[i + 0], frac_bits);
        out[i + 1] = Arch_VCVT_F32_S32(in[i + 1], frac_bits);
        out[i + 2] = Arch_VCVT_F32_S32(in[i + 2], frac_bits);
        out[i + 3] = Arch_VCVT_F32_S32(in[i + 3], frac_bits);
    }

    /* process the remainder */
    for (; i < num; i++)
        out[i] = Arch_VCVT_F32_S32(in[i], frac_bits);
}

/**
 * @brief convert the 16-bit fixed point number to floating point.
 * notation SQx.y. This is implemented as inline function so that the nunber of 
 * 'frac_bits' can be set by the caller. It needs to be a compile-time constant,
 * so inline and optimize is a must here.
 * 
 * @param in fixed-point number array that is about to be converted
 * @param num number of values to convert
 * @param frac_bits number of fractional bits (compile-time constant)
 * @param out destination array for the floating point numbers
 * 
 */
static inline ALWAYS_INLINE void OPTIMIZE("O3") LOOP_UNROLL 
    FloatFixp_Fixp16ToFloat(const int16_t *in, int num, const int frac_bits, 
    float *out)
{
    int i = 0;
    /* process four at the time */
    for (; i + 4 <= num; i += 4) {
        out[i + 0] = Arch_VCVT_F32_S16(in[i + 0], frac_bits);
        out[i + 1] = Arch_VCVT_F32_S16(in[i + 1], frac_bits);
        out[i + 2] = Arch_VCVT_F32_S16(in[i + 2], frac_bits);
        out[i + 3] = Arch_VCVT_F32_S16(in[i + 3], frac_bits);
    }

    /* this will get unrolled */
    for (; i < num; i++)
        out[i] = Arch_VCVT_F32_S16(in[i], frac_bits);
}

/**
 * @brief convert the floating point numbers to 32-bit fixed point numbers in 
 * notation SQx.y. This is implemented as inline function so that the number of 
 * 'frac_bits' can be set by the caller. It needs to be a compile-time constant,
 * so inline and optimize is a must here.
 * 
 * @param in floating-point number array that is about to be converted
 * @param num number of values to convert
 * @param frac_bits number of fractional bits (compile-time constant)
 * @param out destination array for the fixed-point numbers
 * 
 */
static inline ALWAYS_INLINE void OPTIMIZE("O3") LOOP_UNROLL 
    FloatFixp_FloatToFixp32(const float *in, int num, const int frac_bits, 
    int32_t *out)
{
    int i = 0;
    /* process four at the time */
    for (; i + 4 <= num; i += 4) {
        out[i + 0] = Arch_VCVT_S32_F32(in[i + 0], frac_bits);
        out[i + 1] = Arch_VCVT_S32_F32(in[i + 1], frac_bits);
        out[i + 2] = Arch_VCVT_S32_F32(in[i + 2], frac_bits);
        out[i + 3] = Arch_VCVT_S32_F32(in[i + 3], frac_bits);
    }

    /* process the remainder */
    for (; i < num; i++)
        out[i] = Arch_VCVT_S32_F32(in[i], frac_bits);
}

/**
 * @brief convert the floating point numbers to 16-bit fixed point numbers in 
 * notation SQx.y. This is implemented as inline function so that the number of 
 * 'frac_bits' can be set by the caller. It needs to be a compile-time constant,
 * so inline and optimize is a must here.
 * 
 * @param in floating point number array that is about to be converted
 * @param num number of values to convert
 * @param frac_bits number of fractional bits (compile-time constant)
 * @param out destination array for the fixed-point numbers
 * 
 */
static inline ALWAYS_INLINE void OPTIMIZE("O3") LOOP_UNROLL 
    FloatFixp_FloatToFixp16(const float *in, int num, const int frac_bits, 
    int16_t *out)
{
    int i = 0;
    /* process four at the time */
    for (; i + 4 <= num; i += 4) {
        out[i + 0] = Arch_VCVT_S16_F32(in[i + 0], frac_bits);
        out[i + 1] = Arch_VCVT_S16_F32(in[i + 1], frac_bits);
        out[i + 2] = Arch_VCVT_S16_F32(in[i + 2], frac_bits);
        out[i + 3] = Arch_VCVT_S16_F32(in[i + 3], frac_bits);
    }

    /* this will get unrolled */
    for (; i < num; i++)
        out[i] = Arch_VCVT_S16_F32(in[i], frac_bits);
}



#endif /* FLOAT_FIXP_H */

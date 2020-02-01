/**
 * @file fp.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Macros for dealing with floating point operations
 */


#ifndef UTIL_FP_H_
#define UTIL_FP_H_

#include <math.h>
#include <float.h>

#include "arch/arch_fpu.h"


#ifndef __FLT_EPSILON__
#define __FLT_EPSILON__ 1.19209290e-07F
#endif

/** @brief epsilon value for floats */
#define fp_EPSILON							FLT_EPSILON
/** @brief pi value */
#define fp_PI								3.14159265358979323846

/** @brief square root */
#define fp_sqrt(x)							Arch_VSQRT(x)
/** @brief absolute value */
#define fp_fabs(x)							Arch_VABS(x)
/** @brief power function */
#define fp_pow(a, b)						pow(a, b)
/** @brief cube root function */
#define fp_cbrt(x)							cbrtf(x)
/** @brief rounding function */
#define fp_round(a)							roundf(a)
/** @brief rounding function */
#define fp_floor(a)							floorf(a)
/** @brief ceil function */
#define fp_ceil(x)							ceilf(x)
/** @brief square */
#define fp_sq(x)							((x) * (x))
/** @brief hypothenuse	*/
#define fp_hypot(x, y)						hypot(x, y)
/** @brief arc tangent */
#define fp_atan2(y, x)						atan2(y, x)
/** @brief sine */
#define fp_sin(x)							sinf(x)
/** @brief cosine */
#define fp_cos(x)							cosf(x)
/** @brief natural logarithm */
#define fp_log(x)                           logf(x)
/** @brief break into integral and fractional part */
#define fp_modf(x, int_part)                modff(x, int_part)

/** @brief is zero */
#define fp_zero(x)							(fabs(x) < fp_EPSILON)
/** @brief is not zero */
#define fp_not_zero(x)						(fabs(x) > fp_EPSILON)
/** @brief is equal */
#define fp_eq(x, y)							(fabs(x - y) < fp_EPSILON)
/** @brief check if number is NaN */
#define fp_isnan(x)							isnan(x)


#endif /* UTIL_FP_H_ */

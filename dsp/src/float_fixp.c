/**
 * @file float_fix.c
 * 
 * @date 2020-01-14
 * @author twatorowski 
 * 
 * @brief Convert fixed point notation to floating point 
 */

#include <stdint.h>

#include "compiler.h"
#include "err.h"
#include "arch/arch_fpu.h"

/* convert the fixed point notation 32-bit signed number to floating point 
 * number */
void inline FloatFixp_SQ32ToFloat(const int32_t *in, int num, 
    const int frac_bits, float *out)
{
    int i = 0;
    /* unrolling */
    for (; i + 4 <= num; i += 4) {
        *out++ = Arch_VCVT_F32_S32(*in++, frac_bits);
        *out++ = Arch_VCVT_F32_S32(*in++, frac_bits);
        *out++ = Arch_VCVT_F32_S32(*in++, frac_bits);
        *out++ = Arch_VCVT_F32_S32(*in++, frac_bits);
    }
    /* do the rest of the data */
    for (; i < num; i++)
        *out++ = Arch_VCVT_F32_S32(*in++, frac_bits);
}

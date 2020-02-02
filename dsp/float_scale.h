/**
 * @file floatscale.h
 * 
 * @date 2020-02-02
 * @author twatorowski 
 * 
 * @brief Appply scaling factor to the floating point numbers array
 */

#ifndef DSP_FLOAT_SCALE_H
#define DSP_FLOAT_SCALE_H

#include <stdint.h>

#include "compiler.h"
#include "arch/arch_fpu.h"


/**
 * @brief scale the input array of the floating point numbers by the scaling 
 * factor. May be done in situ
 * 
 * @param in input array to be scaled
 * @param num number of values to convert
 * @param scaling_factor value that every array entry will be multiplied by
 * @param out destination array
 */
static inline ALWAYS_INLINE void OPTIMIZE("O3") LOOP_UNROLL 
    FloatScale_Scale(const float *in, int num, const float scaling_factor, 
    float *out)
{
    int i = 0;
    /* process four at the time */
    for (; i + 4 <= num; i += 4) {
        out[i + 0] = in[i + 0] * scaling_factor;
        out[i + 1] = in[i + 1] * scaling_factor;
        out[i + 2] = in[i + 2] * scaling_factor;
        out[i + 3] = in[i + 3] * scaling_factor;
    }

    /* process the remainder */
    for (; i < num; i++)
        out[i] = in[i] * scaling_factor;
}
    

#endif /* DSP_FLOATSCALE_H */

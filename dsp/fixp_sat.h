/**
 * @file fixp_sat.h
 * 
 * @date 2020-02-02
 * @author twatorowski 
 * 
 * @brief Apply staturative arithmetic to the fixed point notations
 */

#ifndef DSP_FIXP_SAT_H
#define DSP_FIXP_SAT_H

#include <stdint.h>

#include "compiler.h"
#include "arch/arch.h"


/**
 * @brief apply the saturation (hard-clipping) so that all numbers of the input 
 * array are representable using @p bits number of bits. All numbers above the 
 * representable range will get clipped. May be done in-situ.
 * 
 * @param in signed numbers to be hard-clipped
 * @param num number of values to process
 * @param bits number bits for the output numbers to be represented on
 * @param out destination array
 */
static inline ALWAYS_INLINE void OPTIMIZE("O3") LOOP_UNROLL 
    FixpSat_Saturate(const int32_t *in, int num, const int bits, 
    int32_t *out)
{
    /* iterating variable */
    int i = 0;

    /* process four at the time */
    for (; i + 4 <= num; i += 4) {
        out[i + 0] = Arch_SSAT(in[i + 0], bits);
        out[i + 1] = Arch_SSAT(in[i + 1], bits);
        out[i + 2] = Arch_SSAT(in[i + 2], bits);
        out[i + 3] = Arch_SSAT(in[i + 3], bits);
    }

    /* process the remainder */
    for (; i < num; i++) {
        out[i] = Arch_SSAT(in[i], bits);
    }
}

#endif /* FIXP_SAT_H */

/**
 * @file biquad.c
 * 
 * @date 2019-12-01
 * @author twatorowski 
 * 
 * @brief Biquadratic IIR filter implementation using floating point arithmetic
 */

#include "compiler.h"
#include "dsp/biquad.h"

/* reset the delay line of the biquad filter */
void BiQuad_SetTaps(biquad_t *bq, const biquad_taps_t *taps)
{
    /* update taps if requested */
    if (taps) bq->taps = taps;
    /* reset the delay line */
    bq->dl[0] = 0, bq->dl[1] = 0;
}

/* biquadratic iir filter implementation, transposed form II */
void BiQuad_Filter(float *dst, const float *src, int len, biquad_t *bq)
{
    /* taps pointer shorthand */
    const biquad_taps_t *taps = bq->taps;

    /* all done in assembly for the best efficiency */
    ASM volatile(
        /* load taps: a1, a2 -> s0, s1,  */
        "vldr s0, [%[a1_addr]]				    \n"
        "vldr s1, [%[a2_addr]]				    \n"
        /* load taps: b0, b1, b2 -> s2, s3, s4 */
        "vldr s2, [%[b0_addr]]				    \n"
        "vldr s3, [%[b1_addr]]			        \n"
        "vldr s4, [%[b2_addr]]			        \n"
        /* load initial state of the delay line: w[n-1] -> s5, w[n-2]-> s6 */
        "vldr s5, [%[dl_addr], #0]			    \n"
        "vldr s6, [%[dl_addr], #4]			    \n"
        
        /* main loop */
        "1:										\n"
        /* calculate output */
        /* load input sample to s7 */
        "vldr s7, [%[src_addr]]					\n"
        /* calculate y[n] = x[n]*b0 + w[n-1], y[n] goes to s8 */
        "vmul.f32 s8, s7, s2					\n"
        "vadd.f32 s8, s5						\n"
        /* store the output */
        "vstr s8, [%[dst_addr]]					\n"
        /* calculate w[n-1] = x[n]*b1 - y[n]*a1 + w[n-2] */
        "vmul.f32 s5, s7, s3					\n"
        "vmls.f32 s5, s8, s0					\n"
        "vadd.f32 s5, s6						\n"
        /* calculate w[n-2] = x[n]*b2 - y[n]*a2 */
        "vmul.f32 s6, s7, s4					\n"
        "vmls.f32 s6, s8, s1					\n"
        /* update pointers */
        "add %[src_addr], #4					\n"
        "add %[dst_addr], #4					\n"
        /* loop back if we are not done yet */
        "subs %[len], #1						\n"
        "bne 1b									\n"

        /* store the delay line */
        "vstr s5, [%[dl_addr], #0]				\n"
        "vstr s6, [%[dl_addr], #4]				\n"
        /* output operands */
        : [src_addr] "+r" (src), [dst_addr] "+r" (dst), [len] "+r" (len)
        /* input operands */
        : [a1_addr] "r" (&taps->a1), [a2_addr] "r" (&taps->a2),
          [b0_addr] "r" (&taps->b0), [b1_addr] "r" (&taps->b1),
          [b2_addr] "r" (&taps->b2), [dl_addr] "r" (bq->dl)
        /* clobber */
        : "cc", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8"
    );
}
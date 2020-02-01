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
void OPTIMIZE("O3") LOOP_UNROLL BiQuad_Filter(const float *src, int len, 
    biquad_t *bq, float *dst)
{
    /* taps pointer */
    const biquad_taps_t *t = bq->taps;
    /* read the delay line */
    float w1 = bq->dl[0], w2 = bq->dl[1];
    /* read the taps */
    float a1 = t->a1, a2 = t->a2, b0 = t->b0, b1 = t->b1, b2 = t->b2;
    /* input and output variables */
    float x, y;

    /* process all the samples */
    for (int i = 0; i < len; i++) {
        x = *src++;
        /* get the output value */
        y = x * b0 + w1;
        /* calculate */
        w1 = x * b1 - y * a1 + w2;
        w2 = x * b2 - y * a2;
        /* store data in the destination array */
        *dst++ = y;
    }

    /* update the delay line */
    bq->dl[0] = w1, bq->dl[1] = w2;
}
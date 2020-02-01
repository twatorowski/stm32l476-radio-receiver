/**
 * @file demod_am.c
 * 
 * @date 2020-01-19
 * @author twatorowski 
 * 
 * @brief Demodulate AM signal
 */

#include "assert.h"
#include "compiler.h"
#include "err.h"
#include "dsp/biquad.h"
#include "util/fp.h"
#include "util/elems.h"

/* am demodulation band-pass filter */
static const biquad_taps_t taps[] = {
    { .b0 = +4.19699253e-03, .b1 = +8.39398505e-03, .b2 = +4.19699253e-03, 
      .a1 = -1.08068892e+00, .a2 = +3.12260037e-01 },
    { .b0 = +1.00000000e+00, .b1 = +2.00000000e+00, .b2 = +1.00000000e+00, 
      .a1 = -1.35328754e+00, .a2 = +6.43271373e-01 },
};

/* biquad filters */
static biquad_t bq_i[] = { 
    { .taps = &taps[0] }, { .taps = &taps[1] },
};

/* biquad filters */
static biquad_t bq_q[] = { 
    { .taps = &taps[0] }, { .taps = &taps[1] },
};

/* filtration before demodulation */
void OPTIMIZE("O3") LOOP_UNROLL DemodAM_Filter(const float *i, 
    const float *q, int num, float *i_out, float *q_out)
{
    /* filter incoming data for the in-phase channel */
    for (int cnt = 0; cnt < elems(bq_i); cnt++)
        BiQuad_Filter(i, num, &bq_i[cnt], i_out);

    /* filter incoming data for the quadrature channel */
    for (int cnt = 0; cnt < elems(bq_q); cnt++)
        BiQuad_Filter(q, num, &bq_q[cnt], q_out);
}

/* simple demodulation routine */
void OPTIMIZE("O3") LOOP_UNROLL DemodAM_Demodulate(const float *i, 
    const float *q, int num, float *out)
{
    /* get the magnitude */
    for (int cnt = 0; cnt < num; cnt++)
        out[cnt] = fp_sqrt(fp_sq(i[cnt]) + fp_sq(q[cnt]));
}

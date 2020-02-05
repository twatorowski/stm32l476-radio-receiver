/**
 * @file dec4.c
 * 
 * @date 2020-02-05
 * @author twatorowski 
 * 
 * @brief Decimation by 4 logic
 */

#include "assert.h"
#include "compiler.h"
#include "err.h"
#include "dsp/biquad.h"
#include "util/fp.h"
#include "util/elems.h"

/* decimation low pass filter (for selectivity) */
static const biquad_taps_t dec4_taps[] = {
    { .b0 = +4.824343e-03, .b1 = +9.648687e-03, .b2 = +4.824343e-03, 
      .a1 = -1.048600e+00, .a2 = +2.961404e-01 },
    { .b0 = +1.000000e+00, .b1 = +2.000000e+00, .b2 = +1.000000e+00, 
      .a1 = -1.320913e+00, .a2 = +6.327388e-01 },
};

/* low-pass filters */
static biquad_t dec4_i[] = { 
    { .taps = &dec4_taps[0] }, { .taps = &dec4_taps[1] } 
};
static biquad_t dec4_q[] = { 
    { .taps = &dec4_taps[0] }, { .taps = &dec4_taps[1] } 
};

/* filtration before demodulation */
void OPTIMIZE("O3") LOOP_UNROLL Dec4_Filter(const float *i, 
    const float *q, int num, float *i_out, float *q_out)
{
    /* filter incoming data for the in-phase channel */
    for (int cnt = 0; cnt < elems(dec4_i); cnt++)
        BiQuad_Filter(i, num, &dec4_i[cnt], i_out);

    /* filter incoming data for the quadrature channel */
    for (int cnt = 0; cnt < elems(dec4_q); cnt++)
        BiQuad_Filter(q, num, &dec4_q[cnt], q_out);
}

/* do the actual decimation (drop unused samples  */
void OPTIMIZE("03") LOOP_UNROLL Dec4_Decimate(const float *i, 
    const float *q, int num, float *i_out, float *q_out)
{
    /* counter */
    int cnt = 0;

    /* do the bulk of the decimation */
    for (; cnt + 16 <= num; cnt += 16) {
        *i_out++ = i[cnt +  0]; *q_out++ = q[cnt +  0];
        *i_out++ = i[cnt +  4]; *q_out++ = q[cnt +  4];
        *i_out++ = i[cnt +  8]; *q_out++ = q[cnt +  8];
        *i_out++ = i[cnt + 12]; *q_out++ = q[cnt + 12];
    }

    /* do the rest */
    for (; cnt < num; cnt += 4) {
        *i_out++ = i[cnt]; *q_out++ = q[cnt];
    }
}

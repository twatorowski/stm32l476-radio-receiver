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

/* am demodulation input low pass filter (for selectivity) */
static const biquad_taps_t lpf_taps[] = {
    { .b0 = +2.234892e-03, .b1 = +4.469783e-03, .b2 = +2.234892e-03, 
      .a1 = -1.212812e+00, .a2 = +3.840042e-01 },
    { .b0 = +1.000000e+00, .b1 = +2.000000e+00, .b2 = +1.000000e+00, 
      .a1 = -1.479799e+00, .a2 = +6.886770e-01 },
};

/* am demodulation output high pass filter (for removing the dc offset) */
static const biquad_taps_t hpf_taps[] = {
    { .b0 = +9.957439e-01, .b1 = -1.991488e+00, .b2 = +9.957439e-01, 
      .a1 = -1.991470e+00, .a2 = +9.915059e-01 },
};

/* low-pass input filters */
static biquad_t lpf_i[] = { { .taps = &lpf_taps[0] }, { .taps = &lpf_taps[1] } };
static biquad_t lpf_q[] = { { .taps = &lpf_taps[0] }, { .taps = &lpf_taps[1] } };
/* output high pass filter */
static biquad_t hpf[] = { { .taps = &hpf_taps[0] } };

/* filtration before demodulation */
void OPTIMIZE("O3") LOOP_UNROLL DemodAM_Filter(const float *i, 
    const float *q, int num, float *i_out, float *q_out)
{
    /* filter incoming data for the in-phase channel */
    for (int cnt = 0; cnt < elems(lpf_i); cnt++)
        BiQuad_Filter(i, num, &lpf_i[cnt], i_out);

    /* filter incoming data for the quadrature channel */
    for (int cnt = 0; cnt < elems(lpf_q); cnt++)
        BiQuad_Filter(q, num, &lpf_q[cnt], q_out);
}

/* simple demodulation routine */
void OPTIMIZE("O3") LOOP_UNROLL DemodAM_Demodulate(const float *i, 
    const float *q, int num, float *out)
{
    /* get the magnitude */
    for (int cnt = 0; cnt < num; cnt++)
        out[cnt] = fp_sqrt(fp_sq(i[cnt]) + fp_sq(q[cnt]));
    
    /* remove the dc offset */
    for (int cnt = 0; cnt < elems(hpf); cnt++)
        BiQuad_Filter(out, num, &hpf[cnt], out);
}

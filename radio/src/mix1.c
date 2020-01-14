/**
 * @file mix1.c
 * 
 * @date 2020-01-13
 * @author twatorowski 
 * 
 * @brief 1st stage mixer
 */

#include <stdint.h>

#include "assert.h"
#include "compiler.h"
#include "config.h"
#include "err.h"
#include "sys/critical.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"

/* cosine look-up table, 64 samples, full scale  */
static const int16_t cos_lut[] = {
    +0x7fff, +0x7f61, +0x7d89, +0x7a7c, +0x7640, +0x70e1, +0x6a6c, +0x62f1,
    +0x5a81, +0x5133, +0x471c, +0x3c56, +0x30fb, +0x2527, +0x18f8, +0x0c8b,
    +0x0000, -0x0c8b, -0x18f8, -0x2527, -0x30fb, -0x3c56, -0x471c, -0x5133,
    -0x5a81, -0x62f1, -0x6a6c, -0x70e1, -0x7640, -0x7a7c, -0x7d89, -0x7f61,
    -0x7fff, -0x7f61, -0x7d89, -0x7a7c, -0x7640, -0x70e1, -0x6a6c, -0x62f1,
    -0x5a81, -0x5133, -0x471c, -0x3c56, -0x30fb, -0x2527, -0x18f8, -0x0c8b,
    +0x0000, +0x0c8b, +0x18f8, +0x2527, +0x30fb, +0x3c56, +0x471c, +0x5133,
    +0x5a81, +0x62f1, +0x6a6c, +0x70e1, +0x7640, +0x7a7c, +0x7d89, +0x7f61,
};

/* 1st local oscillator look-up table (subsampled sine lut values) */
static int16_t i_lut[elems(cos_lut)], q_lut[elems(cos_lut)];
/* current band */
static int curr_band;

/* mix the rf signal with the local oscillator, rf is assumed to be of length 
 * equal to the length of the local oscillator lut */
static void LOOP_UNROLL OPTIMIZE("O3") Mix1_Iter(const int16_t *rf, int16_t *i, 
    int16_t *q)
{
    /* mix */
    for (int cnt = 0; cnt < elems(i_lut); cnt++) {
        i[cnt] = ((int32_t)rf[cnt] * i_lut[cnt]) >> 15;
        q[cnt] = ((int32_t)rf[cnt] * q_lut[cnt]) >> 15;
    }
}

/* mix the incoming rf signal by mixing it with lo */
void Mix1_Mix(const int16_t *rf, int num, int16_t *i, int16_t *q)
{
    /* assert on the number of elements */
    assert(num % 64 == elems(i_lut), 
        "number of samples not divisible by lut length", num);
    /* mix with local oscillator */
    for (int cnt = 0; cnt < num; cnt += elems(i_lut))
        Mix1_Iter(rf + cnt, i + cnt, q + cnt);
}

/* set the current lo frequency */
int Mix1_SetLOFrequency(int hz)
{
    /* get the actual band that we are about to select for the 1st lo */
    int band = (elems(cos_lut) * hz + (RF_SAMPLING_FREQ / 2)) / 
        RF_SAMPLING_FREQ;
    
    /* sanity check */
    assert(band > 0 && band <= elems(cos_lut) / 2, 
        "unsupported band for mix1", band);

    /* setup luts for in-phase and quadrature components. 
     * in-phase = cos(band * t), quadrature = -sin(band * t) */
    for (int i = 0; i < elems(cos_lut); i++) {
        i_lut[i] = cos_lut[(i * band) % elems(cos_lut)];
        q_lut[i] = cos_lut[(elems(cos_lut) / 4 + i * band) % elems(cos_lut)];
    }
    /* store current band */
    curr_band = band;
    /* return the actual frequency */
    return band * RF_SAMPLING_FREQ /elems(cos_lut);
}

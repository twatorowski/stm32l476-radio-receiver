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
#include "util/fp.h"

#define DEBUG
#include "debug.h"

/* cosine look-up table, scaled by 2^30 so that it fits into 31 bits. last bit 
 * from the 32 bit word is left to accomodate the rounding factor used during 
 * mixing */
static const int32_t cos_lut[] = {
    +0x3fffffff, +0x3ffb10c0, +0x3fec43c6, +0x3fd39b59,
    +0x3fb11b47, +0x3f84c8e1, +0x3f4eaafd, +0x3f0ec9f4,
    +0x3ec52f9f, +0x3e71e758, +0x3e14fdf6, +0x3dae81ce,
    +0x3d3e82ad, +0x3cc511d8, +0x3c424209, +0x3bb6276d,
    +0x3b20d79d, +0x3a8269a2, +0x39daf5e8, +0x392a9642,
    +0x387165e2, +0x37af8158, +0x36e50689, +0x361214af,
    +0x3536cc51, +0x34534f40, +0x3367c08f, +0x32744492,
    +0x317900d5, +0x30761c17, +0x2f6bbe44, +0x2e5a106f,
    +0x2d413ccc, +0x2c216eaa, +0x2afad268, +0x29cd9577,
    +0x2899e649, +0x275ff452, +0x261feff9, +0x24da0a99,
    +0x238e7673, +0x223d66a8, +0x20e70f32, +0x1f8ba4db,
    +0x1e2b5d38, +0x1cc66e99, +0x1b5d1009, +0x19ef7943,
    +0x187de2a6, +0x17088531, +0x158f9a75, +0x14135c94,
    +0x1294062f, +0x1111d262, +0x0f8cfcbd, +0x0e05c135,
    +0x0c7c5c1e, +0x0af10a22, +0x09640837, +0x07d59396,
    +0x0645e9af, +0x04b54825, +0x0323ecbe, +0x0192155f,
    +0x00000000, -0x0192155f, -0x0323ecbe, -0x04b54825,
    -0x0645e9af, -0x07d59396, -0x09640837, -0x0af10a22,
    -0x0c7c5c1e, -0x0e05c135, -0x0f8cfcbd, -0x1111d262,
    -0x1294062f, -0x14135c94, -0x158f9a75, -0x17088531,
    -0x187de2a6, -0x19ef7943, -0x1b5d1009, -0x1cc66e99,
    -0x1e2b5d38, -0x1f8ba4db, -0x20e70f32, -0x223d66a8,
    -0x238e7673, -0x24da0a99, -0x261feff9, -0x275ff452,
    -0x2899e649, -0x29cd9577, -0x2afad268, -0x2c216eaa,
    -0x2d413ccc, -0x2e5a106f, -0x2f6bbe44, -0x30761c17,
    -0x317900d5, -0x32744492, -0x3367c08f, -0x34534f40,
    -0x3536cc51, -0x361214af, -0x36e50689, -0x37af8158,
    -0x387165e2, -0x392a9642, -0x39daf5e8, -0x3a8269a2,
    -0x3b20d79d, -0x3bb6276d, -0x3c424209, -0x3cc511d8,
    -0x3d3e82ad, -0x3dae81ce, -0x3e14fdf6, -0x3e71e758,
    -0x3ec52f9f, -0x3f0ec9f4, -0x3f4eaafd, -0x3f84c8e1,
    -0x3fb11b47, -0x3fd39b59, -0x3fec43c6, -0x3ffb10c0,
    -0x3fffffff, -0x3ffb10c0, -0x3fec43c6, -0x3fd39b59,
    -0x3fb11b47, -0x3f84c8e1, -0x3f4eaafd, -0x3f0ec9f4,
    -0x3ec52f9f, -0x3e71e758, -0x3e14fdf6, -0x3dae81ce,
    -0x3d3e82ad, -0x3cc511d8, -0x3c424209, -0x3bb6276d,
    -0x3b20d79d, -0x3a8269a2, -0x39daf5e8, -0x392a9642,
    -0x387165e2, -0x37af8158, -0x36e50689, -0x361214af,
    -0x3536cc51, -0x34534f40, -0x3367c08f, -0x32744492,
    -0x317900d5, -0x30761c17, -0x2f6bbe44, -0x2e5a106f,
    -0x2d413ccc, -0x2c216eaa, -0x2afad268, -0x29cd9577,
    -0x2899e649, -0x275ff452, -0x261feff9, -0x24da0a99,
    -0x238e7673, -0x223d66a8, -0x20e70f32, -0x1f8ba4db,
    -0x1e2b5d38, -0x1cc66e99, -0x1b5d1009, -0x19ef7943,
    -0x187de2a6, -0x17088531, -0x158f9a75, -0x14135c94,
    -0x1294062f, -0x1111d262, -0x0f8cfcbd, -0x0e05c135,
    -0x0c7c5c1e, -0x0af10a22, -0x09640837, -0x07d59396,
    -0x0645e9af, -0x04b54825, -0x0323ecbe, -0x0192155f,
    +0x00000000, +0x0192155f, +0x0323ecbe, +0x04b54825,
    +0x0645e9af, +0x07d59396, +0x09640837, +0x0af10a22,
    +0x0c7c5c1e, +0x0e05c135, +0x0f8cfcbd, +0x1111d262,
    +0x1294062f, +0x14135c94, +0x158f9a75, +0x17088531,
    +0x187de2a6, +0x19ef7943, +0x1b5d1009, +0x1cc66e99,
    +0x1e2b5d38, +0x1f8ba4db, +0x20e70f32, +0x223d66a8,
    +0x238e7673, +0x24da0a99, +0x261feff9, +0x275ff452,
    +0x2899e649, +0x29cd9577, +0x2afad268, +0x2c216eaa,
    +0x2d413ccc, +0x2e5a106f, +0x2f6bbe44, +0x30761c17,
    +0x317900d5, +0x32744492, +0x3367c08f, +0x34534f40,
    +0x3536cc51, +0x361214af, +0x36e50689, +0x37af8158,
    +0x387165e2, +0x392a9642, +0x39daf5e8, +0x3a8269a2,
    +0x3b20d79d, +0x3bb6276d, +0x3c424209, +0x3cc511d8,
    +0x3d3e82ad, +0x3dae81ce, +0x3e14fdf6, +0x3e71e758,
    +0x3ec52f9f, +0x3f0ec9f4, +0x3f4eaafd, +0x3f84c8e1,
    +0x3fb11b47, +0x3fd39b59, +0x3fec43c6, +0x3ffb10c0,
};

/* 1st local oscillator look-up table (subsampled sine lut values) */
static int32_t i_lut[elems(cos_lut)], q_lut[elems(cos_lut)];
/* current band */
static int curr_band;

/* mix the rf signal with the local oscillator, rf is assumed to be of length 
 * equal to the length of the local oscillator lut */
static void LOOP_UNROLL OPTIMIZE("O3") Mix1_Iter(const int16_t *rf, int16_t *i, 
    int16_t *q)
{
    /* mix the incoming signals with the complex local oscillator. the lo lut 
     * entries are prepared in such a way that the multiplication results in 
     * 31 bit word thus leaving some space for the rounding factor. See the 
     * Mix1_SetLOFrequency function for the details. We need to add the rounding 
     * term before the bit shift otherwise a DC shift will be introduced which 
     * then will be convertoed to a tone by 2nd stage mixing. This is obviously 
     * undesirable */
    const int bshift = 31 - DEC_MAX_INPUT_BITS - 1;
    const uint32_t rounding_f = 1 << (bshift - 1);

    /* do the actual mixing, normalize by rounding and shifting */
    for (int cnt = 0; cnt < elems(i_lut); cnt++) {
        i[cnt] = ((int32_t)rf[cnt] * i_lut[cnt] + rounding_f) >> bshift;
        q[cnt] = ((int32_t)rf[cnt] * q_lut[cnt] + rounding_f) >> bshift;
    }
}

/* mix the incoming rf signal by mixing it with lo */
void Mix1_Mix(const int16_t *rf, int num, int16_t *i, int16_t *q)
{
    /* assert on the number of elements */
    assert(num % elems(i_lut) == 0, 
        "number of samples not divisible by lut length", num);
    /* mix with local oscillator */
    for (int cnt = 0; cnt < num; cnt += elems(i_lut))
        Mix1_Iter(rf + cnt, i + cnt, q + cnt);
}

/* set the current lo frequency */
float Mix1_SetLOFrequency(float f)
{
    /* determine band spacing that is offered by the local oscillator */
    const float band_spacing = (float)RF_SAMPLING_FREQ / elems(cos_lut);
    /* get the actual band that we are about to select for the 1st lo */
    int band = fp_round(f / band_spacing);

    /* rounding factor to be added before truncation */
    const int32_t rounding_f = 1 << (RF_SAMPLING_BITS - 1);
    
    /* sanity check */
    assert(band >= 0 && band <= elems(cos_lut) / 2, 
        "unsupported band for mix1", band);

    /* setup luts for in-phase and quadrature components. in-phase = 
     * cos(band * t), quadrature = -sin(band * t) this results in the 
     * complex oscillator in form x(t) = exp(-2j * pi * t). the minus sign in 
     * front of the '-2j' denotes that mixing with this oscillator will bring 
     * the positive frequencies down to near DC. */
    for (int i = 0; i < elems(cos_lut); i++) {
        /* add rounding factor and shift by the number of bits that rf samples 
         * are represented on to make space for them during multiplication 
         * (or mixing, if you like)*/
        i_lut[i] = (cos_lut[(i * band) & (elems(cos_lut) - 1)] + 
            rounding_f) >> RF_SAMPLING_BITS;
        q_lut[i] = (cos_lut[(elems(cos_lut) / 4 + i * band) & 
            (elems(cos_lut) - 1)] + rounding_f) >> RF_SAMPLING_BITS;
    }
    
    /* store current band */
    curr_band = band;
    /* return the actual frequency */
    return band * band_spacing;
}

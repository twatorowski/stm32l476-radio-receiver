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
 * mixing, the length of the lut must divide the data portion length that 
 * you'll be feeding to the mixer */
static const int32_t cos_lut[] = {
    +0x40000000, +0x3ff7ea5d, +0x3fdfab80, +0x3fb74988, +0x3f7ecea9, +0x3f364928,
    +0x3eddcb58, +0x3e756b94, +0x3dfd443a, +0x3d7573a6, +0x3cde1c27, +0x3c3763f9,
    +0x3b81753c, +0x3abc7de6, +0x39e8afba, +0x3906403a, +0x3815689d, +0x371665ba,
    +0x360977ff, +0x34eee35c, +0x33c6ef37, +0x3291e654, +0x315016c7, +0x3001d1dc,
    +0x2ea76c08, +0x2d413ccd, +0x2bcf9eaa, +0x2a52ef01, +0x28cb8dfd, +0x2739de82,
    +0x259e4609, +0x23f92c8f, +0x224afc78, +0x20942272, +0x1ed50d5d, +0x1d0e2e2b,
    +0x1b3ff7c9, +0x196adefc, +0x178f5a49, +0x15ade1d0, +0x13c6ef37, +0x11dafd83,
    +0x0fea88fd, +0x0df60f12, +0x0bfe0e33, +0x0a0305b4, +0x080575af, +0x0605dee0,
    +0x0404c287, +0x0202a246, +0x00000000, -0x0202a246, -0x0404c287, -0x0605dee0,
    -0x080575af, -0x0a0305b4, -0x0bfe0e33, -0x0df60f12, -0x0fea88fd, -0x11dafd83,
    -0x13c6ef37, -0x15ade1d0, -0x178f5a49, -0x196adefc, -0x1b3ff7c9, -0x1d0e2e2b,
    -0x1ed50d5d, -0x20942272, -0x224afc78, -0x23f92c8f, -0x259e4609, -0x2739de82,
    -0x28cb8dfd, -0x2a52ef01, -0x2bcf9eaa, -0x2d413ccd, -0x2ea76c08, -0x3001d1dc,
    -0x315016c7, -0x3291e654, -0x33c6ef37, -0x34eee35c, -0x360977ff, -0x371665ba,
    -0x3815689d, -0x3906403a, -0x39e8afba, -0x3abc7de6, -0x3b81753c, -0x3c3763f9,
    -0x3cde1c27, -0x3d7573a6, -0x3dfd443a, -0x3e756b94, -0x3eddcb58, -0x3f364928,
    -0x3f7ecea9, -0x3fb74988, -0x3fdfab80, -0x3ff7ea5d, -0x40000000, -0x3ff7ea5d,
    -0x3fdfab80, -0x3fb74988, -0x3f7ecea9, -0x3f364928, -0x3eddcb58, -0x3e756b94,
    -0x3dfd443a, -0x3d7573a6, -0x3cde1c27, -0x3c3763f9, -0x3b81753c, -0x3abc7de6,
    -0x39e8afba, -0x3906403a, -0x3815689d, -0x371665ba, -0x360977ff, -0x34eee35c,
    -0x33c6ef37, -0x3291e654, -0x315016c7, -0x3001d1dc, -0x2ea76c08, -0x2d413ccd,
    -0x2bcf9eaa, -0x2a52ef01, -0x28cb8dfd, -0x2739de82, -0x259e4609, -0x23f92c8f,
    -0x224afc78, -0x20942272, -0x1ed50d5d, -0x1d0e2e2b, -0x1b3ff7c9, -0x196adefc,
    -0x178f5a49, -0x15ade1d0, -0x13c6ef37, -0x11dafd83, -0x0fea88fd, -0x0df60f12,
    -0x0bfe0e33, -0x0a0305b4, -0x080575af, -0x0605dee0, -0x0404c287, -0x0202a246,
    +0x00000000, +0x0202a246, +0x0404c287, +0x0605dee0, +0x080575af, +0x0a0305b4,
    +0x0bfe0e33, +0x0df60f12, +0x0fea88fd, +0x11dafd83, +0x13c6ef37, +0x15ade1d0,
    +0x178f5a49, +0x196adefc, +0x1b3ff7c9, +0x1d0e2e2b, +0x1ed50d5d, +0x20942272,
    +0x224afc78, +0x23f92c8f, +0x259e4609, +0x2739de82, +0x28cb8dfd, +0x2a52ef01,
    +0x2bcf9eaa, +0x2d413ccd, +0x2ea76c08, +0x3001d1dc, +0x315016c7, +0x3291e654,
    +0x33c6ef37, +0x34eee35c, +0x360977ff, +0x371665ba, +0x3815689d, +0x3906403a,
    +0x39e8afba, +0x3abc7de6, +0x3b81753c, +0x3c3763f9, +0x3cde1c27, +0x3d7573a6,
    +0x3dfd443a, +0x3e756b94, +0x3eddcb58, +0x3f364928, +0x3f7ecea9, +0x3fb74988,
    +0x3fdfab80, +0x3ff7ea5d,
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
        i_lut[i] = (cos_lut[(i * band) % elems(cos_lut)] + 
            rounding_f) >> RF_SAMPLING_BITS;
        q_lut[i] = (cos_lut[(elems(cos_lut) / 4 + i * band) % elems(cos_lut)] + 
            rounding_f) >> RF_SAMPLING_BITS;
    }
    
    /* store current band */
    curr_band = band;
    /* return the actual frequency */
    return band * band_spacing;
}

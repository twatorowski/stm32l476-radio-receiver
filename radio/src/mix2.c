/**
 * @file mix2.c
 * 
 * @date 2020-01-19
 * @author twatorowski 
 * 
 * @brief 2nd stage mixer. Uses floating point arithmetic
 */

#include "assert.h"
#include "compiler.h"
#include "config.h"
#include "err.h"
#include "sys/critical.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"

/* cosine look up table */
static const float cos_lut[] = {
   +0x1.000000p+0, +0x1.ffd886p-1, +0x1.ff621ep-1, +0x1.fe9cdap-1,
   +0x1.fd88dap-1, +0x1.fc2648p-1, +0x1.fa7558p-1, +0x1.f87650p-1,
   +0x1.f6297cp-1, +0x1.f38f3ap-1, +0x1.f0a7f0p-1, +0x1.ed740ep-1,
   +0x1.e9f416p-1, +0x1.e6288ep-1, +0x1.e21210p-1, +0x1.ddb13cp-1,
   +0x1.d906bcp-1, +0x1.d4134ep-1, +0x1.ced7b0p-1, +0x1.c954b2p-1,
   +0x1.c38b30p-1, +0x1.bd7c0ap-1, +0x1.b72834p-1, +0x1.b090a6p-1,
   +0x1.a9b662p-1, +0x1.a29a7ap-1, +0x1.9b3e04p-1, +0x1.93a224p-1,
   +0x1.8bc806p-1, +0x1.83b0e0p-1, +0x1.7b5df2p-1, +0x1.72d084p-1,
   +0x1.6a09e6p-1, +0x1.610b76p-1, +0x1.57d694p-1, +0x1.4e6cacp-1,
   +0x1.44cf32p-1, +0x1.3affa2p-1, +0x1.30ff80p-1, +0x1.26d054p-1,
   +0x1.1c73b4p-1, +0x1.11eb36p-1, +0x1.07387ap-1, +0x1.f8ba4ep-2,
   +0x1.e2b5d4p-2, +0x1.cc66eap-2, +0x1.b5d100p-2, +0x1.9ef794p-2,
   +0x1.87de2ap-2, +0x1.708854p-2, +0x1.58f9a8p-2, +0x1.4135cap-2,
   +0x1.294062p-2, +0x1.111d26p-2, +0x1.f19f98p-3, +0x1.c0b826p-3,
   +0x1.8f8b84p-3, +0x1.5e2144p-3, +0x1.2c8106p-3, +0x1.f564e6p-4,
   +0x1.917a6cp-4, +0x1.2d520ap-4, +0x1.91f660p-5, +0x1.921560p-6,
   +0x0.000000p-0, -0x1.921560p-6, -0x1.91f660p-5, -0x1.2d520ap-4,
   -0x1.917a6cp-4, -0x1.f564e6p-4, -0x1.2c8106p-3, -0x1.5e2144p-3,
   -0x1.8f8b84p-3, -0x1.c0b826p-3, -0x1.f19f98p-3, -0x1.111d26p-2,
   -0x1.294062p-2, -0x1.4135cap-2, -0x1.58f9a8p-2, -0x1.708854p-2,
   -0x1.87de2ap-2, -0x1.9ef794p-2, -0x1.b5d100p-2, -0x1.cc66eap-2,
   -0x1.e2b5d4p-2, -0x1.f8ba4ep-2, -0x1.07387ap-1, -0x1.11eb36p-1,
   -0x1.1c73b4p-1, -0x1.26d054p-1, -0x1.30ff80p-1, -0x1.3affa2p-1,
   -0x1.44cf32p-1, -0x1.4e6cacp-1, -0x1.57d694p-1, -0x1.610b76p-1,
   -0x1.6a09e6p-1, -0x1.72d084p-1, -0x1.7b5df2p-1, -0x1.83b0e0p-1,
   -0x1.8bc806p-1, -0x1.93a224p-1, -0x1.9b3e04p-1, -0x1.a29a7ap-1,
   -0x1.a9b662p-1, -0x1.b090a6p-1, -0x1.b72834p-1, -0x1.bd7c0ap-1,
   -0x1.c38b30p-1, -0x1.c954b2p-1, -0x1.ced7b0p-1, -0x1.d4134ep-1,
   -0x1.d906bcp-1, -0x1.ddb13cp-1, -0x1.e21210p-1, -0x1.e6288ep-1,
   -0x1.e9f416p-1, -0x1.ed740ep-1, -0x1.f0a7f0p-1, -0x1.f38f3ap-1,
   -0x1.f6297cp-1, -0x1.f87650p-1, -0x1.fa7558p-1, -0x1.fc2648p-1,
   -0x1.fd88dap-1, -0x1.fe9cdap-1, -0x1.ff621ep-1, -0x1.ffd886p-1,
   -0x1.000000p+0, -0x1.ffd886p-1, -0x1.ff621ep-1, -0x1.fe9cdap-1,
   -0x1.fd88dap-1, -0x1.fc2648p-1, -0x1.fa7558p-1, -0x1.f87650p-1,
   -0x1.f6297cp-1, -0x1.f38f3ap-1, -0x1.f0a7f0p-1, -0x1.ed740ep-1,
   -0x1.e9f416p-1, -0x1.e6288ep-1, -0x1.e21210p-1, -0x1.ddb13cp-1,
   -0x1.d906bcp-1, -0x1.d4134ep-1, -0x1.ced7b0p-1, -0x1.c954b2p-1,
   -0x1.c38b30p-1, -0x1.bd7c0ap-1, -0x1.b72834p-1, -0x1.b090a6p-1,
   -0x1.a9b662p-1, -0x1.a29a7ap-1, -0x1.9b3e04p-1, -0x1.93a224p-1,
   -0x1.8bc806p-1, -0x1.83b0e0p-1, -0x1.7b5df2p-1, -0x1.72d084p-1,
   -0x1.6a09e6p-1, -0x1.610b76p-1, -0x1.57d694p-1, -0x1.4e6cacp-1,
   -0x1.44cf32p-1, -0x1.3affa2p-1, -0x1.30ff80p-1, -0x1.26d054p-1,
   -0x1.1c73b4p-1, -0x1.11eb36p-1, -0x1.07387ap-1, -0x1.f8ba4ep-2,
   -0x1.e2b5d4p-2, -0x1.cc66eap-2, -0x1.b5d100p-2, -0x1.9ef794p-2,
   -0x1.87de2ap-2, -0x1.708854p-2, -0x1.58f9a8p-2, -0x1.4135cap-2,
   -0x1.294062p-2, -0x1.111d26p-2, -0x1.f19f98p-3, -0x1.c0b826p-3,
   -0x1.8f8b84p-3, -0x1.5e2144p-3, -0x1.2c8106p-3, -0x1.f564e6p-4,
   -0x1.917a6cp-4, -0x1.2d520ap-4, -0x1.91f660p-5, -0x1.921560p-6,
   -0x0.000000p-0, +0x1.921560p-6, +0x1.91f660p-5, +0x1.2d520ap-4,
   +0x1.917a6cp-4, +0x1.f564e6p-4, +0x1.2c8106p-3, +0x1.5e2144p-3,
   +0x1.8f8b84p-3, +0x1.c0b826p-3, +0x1.f19f98p-3, +0x1.111d26p-2,
   +0x1.294062p-2, +0x1.4135cap-2, +0x1.58f9a8p-2, +0x1.708854p-2,
   +0x1.87de2ap-2, +0x1.9ef794p-2, +0x1.b5d100p-2, +0x1.cc66eap-2,
   +0x1.e2b5d4p-2, +0x1.f8ba4ep-2, +0x1.07387ap-1, +0x1.11eb36p-1,
   +0x1.1c73b4p-1, +0x1.26d054p-1, +0x1.30ff80p-1, +0x1.3affa2p-1,
   +0x1.44cf32p-1, +0x1.4e6cacp-1, +0x1.57d694p-1, +0x1.610b76p-1,
   +0x1.6a09e6p-1, +0x1.72d084p-1, +0x1.7b5df2p-1, +0x1.83b0e0p-1,
   +0x1.8bc806p-1, +0x1.93a224p-1, +0x1.9b3e04p-1, +0x1.a29a7ap-1,
   +0x1.a9b662p-1, +0x1.b090a6p-1, +0x1.b72834p-1, +0x1.bd7c0ap-1,
   +0x1.c38b30p-1, +0x1.c954b2p-1, +0x1.ced7b0p-1, +0x1.d4134ep-1,
   +0x1.d906bcp-1, +0x1.ddb13cp-1, +0x1.e21210p-1, +0x1.e6288ep-1,
   +0x1.e9f416p-1, +0x1.ed740ep-1, +0x1.f0a7f0p-1, +0x1.f38f3ap-1,
   +0x1.f6297cp-1, +0x1.f87650p-1, +0x1.fa7558p-1, +0x1.fc2648p-1,
   +0x1.fd88dap-1, +0x1.fe9cdap-1, +0x1.ff621ep-1, +0x1.ffd886p-1,
};

/* 1st local oscillator look-up table (subsampled cosine lut values) */
static float i_lut[elems(cos_lut)], q_lut[elems(cos_lut)];
/* currently selected band */
static int curr_band;
/* phase accumulator */
static unsigned int phase;

/* mix the rf signal with the local oscillator, rf is assumed to be of length 
 * equal to the length of the local oscillator lut */
void OPTIMIZE("O3") Mix2_Mix(const float *i, const float *q, 
    int num, float *i_out, float *q_out)
{
    /* temporary storage */
    float _i, _q;
    /* do the complex multiplication */
    for (int cnt = 0; cnt < num; cnt++, phase = (phase + 1) % elems(i_lut)) {
        /* (a + bi) * (c + di) = (ac - bd) + i(ad + bc) */
        _i = i[cnt] * i_lut[phase] - q[cnt] * q_lut[phase];
        _q = i[cnt] * q_lut[phase] + q[cnt] * i_lut[phase];
        /* using temporary registers allows for in-situ operation */
        i_out[cnt] = _i, q_out[cnt] = _q;
    }
}

/* set the current lo frequency */
int Mix2_SetLOFrequency(int hz)
{
    /* get the actual band */
    int band = (int)elems(cos_lut) * hz / 
        (RF_SAMPLING_FREQ / DEC_DECIMATION_RATE);

    /* sanity check */
    assert(band > -(int)elems(cos_lut) / 2 && band <= (int)elems(cos_lut) / 2, 
        "unsupported band for mix2", band);

    /* setup luts for in-phase and quadrature components. 
     * in-phase = cos(band * t), quadrature = -sin(band * t) */
    for (int i = 0; i < elems(cos_lut); i++) {
        i_lut[i] = cos_lut[(i * band) & (elems(cos_lut) - 1)];
        q_lut[i] = cos_lut[(elems(cos_lut) / 4 + i * band) & (elems(cos_lut) - 1)];
    }
    /* store current band */
    curr_band = band;
    /* return the actual frequency */
    return band * RF_SAMPLING_FREQ / DEC_DECIMATION_RATE / (int)elems(cos_lut);
}
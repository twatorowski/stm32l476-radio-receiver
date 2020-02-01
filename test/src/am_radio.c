/**
 * @file am_radio.c
 * 
 * @date 2020-01-18
 * @author twatorowski 
 * 
 * @brief Test for the signal path of a complete am radio receiver
 */

#include <stdint.h>

#include "assert.h"
#include "err.h"
#include "dev/dec.h"
#include "dev/led.h"
#include "dev/timemeas.h"
#include "radio/mix1.h"
#include "radio/mix2.h"
#include "radio/demod_am.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"

#define FREQ                                187500
/* radio frequency signal (187.5kHz, mod: am 10% 4*976Hz) */
static const int16_t rf[] = {
    +0x0000, +0x04c2, +0x03aa, -0x01ff, -0x053f, -0x0205, +0x03c1, +0x04ef,
    +0x0000, -0x04fd, -0x03d7, +0x0217, +0x057e, +0x021d, -0x03ed, -0x0528,
    +0x0000, +0x0536, +0x0402, -0x022e, -0x05b9, -0x0233, +0x0416, +0x055d,
    +0x0000, -0x0569, -0x0429, +0x0243, +0x05ee, +0x0247, -0x043a, -0x058c,
    +0x0000, +0x0596, +0x044a, -0x0254, -0x061c, -0x0258, +0x0459, +0x05b2,
    +0x0000, -0x05bb, -0x0465, +0x0263, +0x0640, +0x0266, -0x0470, -0x05d0,
    +0x0000, +0x05d5, +0x0479, -0x026d, -0x0658, -0x026e, +0x0480, +0x05e2,
    +0x0000, -0x05e5, -0x0484, +0x0272, +0x0665, +0x0273, -0x0486, -0x05ea,
    +0x0000, +0x05ea, +0x0486, -0x0273, -0x0665, -0x0272, +0x0484, +0x05e5,
    +0x0000, -0x05e2, -0x0480, +0x026e, +0x0658, +0x026d, -0x0479, -0x05d5,
    +0x0000, +0x05d0, +0x0470, -0x0266, -0x0640, -0x0263, +0x0466, +0x05bb,
    +0x0000, -0x05b3, -0x0459, +0x0259, +0x061c, +0x0255, -0x044b, -0x0596,
    +0x0000, +0x058c, +0x043b, -0x0248, -0x05ef, -0x0243, +0x0429, +0x056a,
    +0x0000, -0x055d, -0x0416, +0x0234, +0x05ba, +0x022e, -0x0402, -0x0536,
    +0x0000, +0x0528, +0x03ed, -0x021d, -0x057e, -0x0217, +0x03d7, +0x04fe,
    +0x0000, -0x04ef, -0x03c1, +0x0205, +0x053f, +0x01ff, -0x03ab, -0x04c3,
    +0x0000, +0x04b4, +0x0394, -0x01ed, -0x04ff, -0x01e6, +0x037d, +0x0488,
    +0x0000, -0x0479, -0x0367, +0x01d4, +0x04c0, +0x01ce, -0x0351, -0x044f,
    +0x0000, +0x0441, +0x033c, -0x01bd, -0x0485, -0x01b8, +0x0328, +0x0419,
    +0x0000, -0x040d, -0x0315, +0x01a9, +0x044f, +0x01a4, -0x0304, -0x03eb,
    +0x0000, +0x03e0, +0x02f3, -0x0197, -0x0422, -0x0193, +0x02e5, +0x03c4,
    +0x0000, -0x03bc, -0x02d8, +0x0189, +0x03fe, +0x0186, -0x02ce, -0x03a6,
    +0x0000, +0x03a1, +0x02c5, -0x017f, -0x03e5, -0x017d, +0x02be, +0x0394,
    +0x0000, -0x0391, -0x02ba, +0x0179, +0x03d9, +0x0179, -0x02b7, -0x038c,
    +0x0000, +0x038c, +0x02b7, -0x0178, -0x03d9, -0x0179, +0x02ba, +0x0390,
    +0x0000, -0x0393, -0x02be, +0x017d, +0x03e5, +0x017e, -0x02c4, -0x03a0,
    +0x0000, +0x03a6, +0x02cd, -0x0185, -0x03fd, -0x0188, +0x02d8, +0x03bb,
    +0x0000, -0x03c3, -0x02e4, +0x0192, +0x0421, +0x0196, -0x02f3, -0x03df,
    +0x0000, +0x03e9, +0x0303, -0x01a3, -0x044e, -0x01a8, +0x0314, +0x040c,
    +0x0000, -0x0418, -0x0327, +0x01b7, +0x0483, +0x01bd, -0x033b, -0x043f,
    +0x0000, +0x044d, +0x0350, -0x01ce, -0x04be, -0x01d4, +0x0366, +0x0478,
    +0x0000, -0x0486, -0x037c, +0x01e6, +0x04fd, +0x01ec, -0x0393, -0x04b2,
    +0x0000, +0x04c1, +0x03a9, -0x01fe, -0x053e, -0x0204, +0x03c0, +0x04ee,
    +0x0000, -0x04fc, -0x03d6, +0x0217, +0x057d, +0x021c, -0x03ec, -0x0527,
    +0x0000, +0x0535, +0x0401, -0x022e, -0x05b8, -0x0233, +0x0415, +0x055c,
    +0x0000, -0x0568, -0x0428, +0x0242, +0x05ee, +0x0247, -0x043a, -0x058b,
    +0x0000, +0x0595, +0x044a, -0x0254, -0x061b, -0x0258, +0x0458, +0x05b2,
    +0x0000, -0x05ba, -0x0465, +0x0262, +0x063f, +0x0265, -0x0470, -0x05cf,
    +0x0000, +0x05d5, +0x0479, -0x026c, -0x0658, -0x026e, +0x047f, +0x05e2,
    +0x0000, -0x05e5, -0x0484, +0x0272, +0x0665, +0x0273, -0x0486, -0x05ea,
    +0x0000, +0x05ea, +0x0486, -0x0273, -0x0665, -0x0272, +0x0484, +0x05e5,
    +0x0000, -0x05e3, -0x0480, +0x026f, +0x0659, +0x026d, -0x0479, -0x05d6,
    +0x0000, +0x05d0, +0x0471, -0x0266, -0x0640, -0x0263, +0x0466, +0x05bb,
    +0x0000, -0x05b3, -0x045a, +0x0259, +0x061d, +0x0255, -0x044b, -0x0597,
    +0x0000, +0x058d, +0x043b, -0x0248, -0x05f0, -0x0243, +0x042a, +0x056a,
    +0x0000, -0x055e, -0x0417, +0x0234, +0x05bb, +0x022f, -0x0403, -0x0537,
    +0x0000, +0x0529, +0x03ee, -0x021e, -0x057f, -0x0218, +0x03d8, +0x04ff,
    +0x0000, -0x04f0, -0x03c2, +0x0206, +0x0541, +0x01ff, -0x03ab, -0x04c4,
    +0x0000, +0x04b5, +0x0395, -0x01ed, -0x0500, -0x01e7, +0x037e, +0x0489,
    +0x0000, -0x047a, -0x0368, +0x01d5, +0x04c1, +0x01cf, -0x0352, -0x0450,
    +0x0000, +0x0442, +0x033d, -0x01be, -0x0486, -0x01b8, +0x0329, +0x041a,
    +0x0000, -0x040e, -0x0316, +0x01a9, +0x0450, +0x01a4, -0x0304, -0x03eb,
    +0x0000, +0x03e1, +0x02f4, -0x0197, -0x0423, -0x0193, +0x02e6, +0x03c4,
    +0x0000, -0x03bc, -0x02d9, +0x0189, +0x03ff, +0x0186, -0x02ce, -0x03a7,
    +0x0000, +0x03a1, +0x02c5, -0x017f, -0x03e6, -0x017d, +0x02be, +0x0394,
    +0x0000, -0x0391, -0x02ba, +0x0179, +0x03d9, +0x0179, -0x02b7, -0x038c,
    +0x0000, +0x038c, +0x02b7, -0x0178, -0x03d8, -0x0179, +0x02b9, +0x0390,
    +0x0000, -0x0393, -0x02be, +0x017d, +0x03e5, +0x017e, -0x02c4, -0x03a0,
    +0x0000, +0x03a5, +0x02cd, -0x0185, -0x03fd, -0x0188, +0x02d7, +0x03ba,
    +0x0000, -0x03c2, -0x02e4, +0x0192, +0x0420, +0x0196, -0x02f2, -0x03de,
    +0x0000, +0x03e9, +0x0302, -0x01a3, -0x044d, -0x01a8, +0x0313, +0x040b,
    +0x0000, -0x0417, -0x0326, +0x01b7, +0x0482, +0x01bc, -0x033a, -0x043e,
    +0x0000, +0x044c, +0x034f, -0x01cd, -0x04bd, -0x01d3, +0x0365, +0x0476,
    +0x0000, -0x0485, -0x037b, +0x01e5, +0x04fc, +0x01eb, -0x0392, -0x04b1,
    +0x0000, +0x04c0, +0x03a8, -0x01fe, -0x053c, -0x0204, +0x03bf, +0x04ec,
    +0x0000, -0x04fb, -0x03d5, +0x0216, +0x057b, +0x021c, -0x03eb, -0x0526,
    +0x0000, +0x0534, +0x0400, -0x022d, -0x05b7, -0x0233, +0x0414, +0x055b,
    +0x0000, -0x0567, -0x0427, +0x0242, +0x05ed, +0x0247, -0x0439, -0x058a,
    +0x0000, +0x0595, +0x0449, -0x0254, -0x061a, -0x0258, +0x0458, +0x05b1,
    +0x0000, -0x05b9, -0x0465, +0x0262, +0x063e, +0x0265, -0x046f, -0x05cf,
    +0x0000, +0x05d4, +0x0478, -0x026c, -0x0657, -0x026e, +0x047f, +0x05e2,
    +0x0000, -0x05e5, -0x0484, +0x0272, +0x0665, +0x0273, -0x0486, -0x05e9,
    +0x0000, +0x05ea, +0x0486, -0x0273, -0x0665, -0x0272, +0x0484, +0x05e6,
    +0x0000, -0x05e3, -0x0480, +0x026f, +0x0659, +0x026d, -0x047a, -0x05d6,
    +0x0000, +0x05d1, +0x0471, -0x0266, -0x0641, -0x0263, +0x0467, +0x05bc,
    +0x0000, -0x05b4, -0x045a, +0x0259, +0x061e, +0x0255, -0x044c, -0x0598,
    +0x0000, +0x058e, +0x043c, -0x0248, -0x05f1, -0x0244, +0x042a, +0x056b,
    +0x0000, -0x055f, -0x0418, +0x0234, +0x05bc, +0x022f, -0x0404, -0x0538,
    +0x0000, +0x052a, +0x03ef, -0x021e, -0x0581, -0x0218, +0x03d9, +0x0500,
    +0x0000, -0x04f1, -0x03c3, +0x0206, +0x0542, +0x0200, -0x03ac, -0x04c5,
    +0x0000, +0x04b6, +0x0396, -0x01ed, -0x0502, -0x01e7, +0x037f, +0x048a,
    +0x0000, -0x047b, -0x0369, +0x01d5, +0x04c2, +0x01cf, -0x0353, -0x0451,
    +0x0000, +0x0443, +0x033e, -0x01be, -0x0487, -0x01b9, +0x032a, +0x041b,
    +0x0000, -0x040f, -0x0317, +0x01a9, +0x0451, +0x01a5, -0x0305, -0x03ec,
    +0x0000, +0x03e2, +0x02f5, -0x0197, -0x0423, -0x0193, +0x02e6, +0x03c5,
    +0x0000, -0x03bd, -0x02d9, +0x0189, +0x03ff, +0x0186, -0x02ce, -0x03a7,
    +0x0000, +0x03a2, +0x02c5, -0x017f, -0x03e6, -0x017d, +0x02bf, +0x0394,
    +0x0000, -0x0391, -0x02ba, +0x0179, +0x03d9, +0x0179, -0x02b7, -0x038c,
    +0x0000, +0x038c, +0x02b7, -0x0178, -0x03d8, -0x0179, +0x02b9, +0x0390,
    +0x0000, -0x0393, -0x02bd, +0x017c, +0x03e4, +0x017e, -0x02c4, -0x039f,
    +0x0000, +0x03a5, +0x02cc, -0x0185, -0x03fc, -0x0188, +0x02d7, +0x03b9,
    +0x0000, -0x03c2, -0x02e3, +0x0192, +0x041f, +0x0196, -0x02f2, -0x03de,
    +0x0000, +0x03e8, +0x0301, -0x01a3, -0x044c, -0x01a7, +0x0313, +0x040a,
    +0x0000, -0x0416, -0x0326, +0x01b7, +0x0481, +0x01bc, -0x033a, -0x043d,
    +0x0000, +0x044b, +0x034e, -0x01cd, -0x04bc, -0x01d3, +0x0364, +0x0475,
    +0x0000, -0x0484, -0x037a, +0x01e5, +0x04fb, +0x01eb, -0x0391, -0x04b0,
    +0x0000, +0x04bf, +0x03a8, -0x01fd, -0x053b, -0x0204, +0x03be, +0x04eb,
    +0x0000, -0x04fa, -0x03d5, +0x0216, +0x057a, +0x021c, -0x03ea, -0x0525,
    +0x0000, +0x0533, +0x0400, -0x022d, -0x05b6, -0x0232, +0x0414, +0x055a,
    +0x0000, -0x0566, -0x0427, +0x0242, +0x05ec, +0x0246, -0x0438, -0x0589,
    +0x0000, +0x0594, +0x0449, -0x0254, -0x061a, -0x0258, +0x0457, +0x05b0,
    +0x0000, -0x05b9, -0x0464, +0x0262, +0x063e, +0x0265, -0x046f, -0x05ce,
    +0x0000, +0x05d4, +0x0478, -0x026c, -0x0657, -0x026e, +0x047f, +0x05e1,
    +0x0000, -0x05e5, -0x0484, +0x0272, +0x0664, +0x0273, -0x0486, -0x05e9,
    +0x0000, +0x05ea, +0x0486, -0x0273, -0x0665, -0x0272, +0x0484, +0x05e6,
    +0x0000, -0x05e3, -0x0480, +0x026f, +0x0659, +0x026d, -0x047a, -0x05d7,
    +0x0000, +0x05d1, +0x0471, -0x0266, -0x0641, -0x0263, +0x0467, +0x05bd,
    +0x0000, -0x05b5, -0x045b, +0x0259, +0x061e, +0x0256, -0x044c, -0x0599,
    +0x0000, +0x058e, +0x043c, -0x0249, -0x05f2, -0x0244, +0x042b, +0x056c,
    +0x0000, -0x0560, -0x0418, +0x0235, +0x05bd, +0x022f, -0x0404, -0x0539,
    +0x0000, +0x052b, +0x03f0, -0x021e, -0x0582, -0x0219, +0x03da, +0x0501,
    +0x0000, -0x04f2, -0x03c4, +0x0206, +0x0543, +0x0200, -0x03ad, -0x04c6,
    +0x0000, +0x04b7, +0x0396, -0x01ee, -0x0503, -0x01e8, +0x0380, +0x048b,
    +0x0000, -0x047c, -0x0369, +0x01d6, +0x04c4, +0x01d0, -0x0354, -0x0452,
    +0x0000, +0x0444, +0x033e, -0x01bf, -0x0488, -0x01b9, +0x032a, +0x041c,
    +0x0000, -0x0410, -0x0317, +0x01aa, +0x0452, +0x01a5, -0x0305, -0x03ed,
    +0x0000, +0x03e2, +0x02f5, -0x0198, -0x0424, -0x0194, +0x02e7, +0x03c6,
    +0x0000, -0x03bd, -0x02da, +0x0189, +0x0400, +0x0186, -0x02cf, -0x03a8,
    +0x0000, +0x03a2, +0x02c6, -0x017f, -0x03e6, -0x017d, +0x02bf, +0x0394,
    +0x0000, -0x0391, -0x02ba, +0x0179, +0x03d9, +0x0179, -0x02b8, -0x038c,
    +0x0000, +0x038c, +0x02b7, -0x0178, -0x03d8, -0x0179, +0x02b9, +0x0390,
    +0x0000, -0x0393, -0x02bd, +0x017c, +0x03e4, +0x017e, -0x02c4, -0x039f,
    +0x0000, +0x03a4, +0x02cc, -0x0185, -0x03fc, -0x0188, +0x02d6, +0x03b9,
    +0x0000, -0x03c1, -0x02e3, +0x0192, +0x041f, +0x0195, -0x02f1, -0x03dd,
    +0x0000, +0x03e7, +0x0301, -0x01a2, -0x044b, -0x01a7, +0x0312, +0x0409,
    +0x0000, -0x0415, -0x0325, +0x01b6, +0x0480, +0x01bc, -0x0339, -0x043c,
    +0x0000, +0x044a, +0x034e, -0x01cd, -0x04bb, -0x01d2, +0x0363, +0x0474,
    +0x0000, -0x0483, -0x0379, +0x01e4, +0x04fa, +0x01eb, -0x0390, -0x04af,
};

/* initialize test */
int TestAMRadio_Init(void)
{
    /* products of the 1st stage mixer */
    int16_t i_mix1[elems(rf)], q_mix1[elems(rf)];
    /* float data */
    float i_dec[elems(rf) / DEC_DECIMATION_RATE];
    float q_dec[elems(rf) / DEC_DECIMATION_RATE];
    /* demodulated output */
    float dem[elems(i_dec)];

    /* set the frequency of the 1st mixer */
    int mix1_freq = Mix1_SetLOFrequency(FREQ);
    /* bring to the baseband */
    Mix2_SetLOFrequency(FREQ - mix1_freq);

    /* experiment start */
    uint16_t start = TimeMeas_GetTimeStamp();
    /* do the mixing */
    Mix1_Mix(rf, elems(rf), i_mix1, q_mix1);
    /* decimate data */
    Dec_Decimate(i_mix1, q_mix1, elems(rf), i_dec, q_dec, CB_SYNC);
    /* do the mixing */
    Mix2_Mix(i_dec, q_dec, elems(i_dec), i_dec, q_dec);
    /* demodulate the output data */
    DemodAM_Demodulate(i_dec, q_dec, elems(i_dec), dem);
    /* experiment end */
    uint16_t end = TimeMeas_GetTimeStamp();

    /* show the demodulation result */
    dprintf("demodulation took = %d, us per sample = %e\n", end - start, 
        (float)(end - start) / elems(rf));

    /* report status */
    return EOK;
}

/* poll am radio test */
void TestAMRadio_Poll(void)
{

}
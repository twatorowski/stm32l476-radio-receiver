/**
 * @file radio.c
 * 
 * @date 2020-01-18
 * @author twatorowski 
 * 
 * @brief Test the radio signal path correctnes and performance.
 */

#include <stdint.h>

#include "assert.h"
#include "err.h"
#include "arch/arch.h"
#include "dev/analog.h"
#include "dev/await.h"
#include "dev/cs43l22.h"
#include "dev/dec.h"
#include "dev/invoke.h"
#include "dev/led.h"
#include "dev/sai1a.h"
#include "dev/timemeas.h"
#include "dsp/float_fixp.h"
#include "radio/demod_am.h"
#include "radio/mix1.h"
#include "radio/mix2.h"
#include "util/elems.h"
#include "sys/ev.h"
#include "sys/sem.h"

#define DEBUG
#include "debug.h"

/* rf signal buffer, current data pointer */
static int16_t rf[1024], *rf_ptr;
/* number of samples to process */
static int rf_samples_num;
/* dac samples buffer */
static int32_t dac[1024];
/* dac pointers */
static uint32_t dac_head;
/* states of the dac */
static enum states {
    LOCK, INIT, PLAY, VOLUME, ON, ERR,
} state;

/* guarding semaphore */
static sem_t sem = { .released = 1 };

/* radio frequency signal (187.5kHz, mod: am 10% 4*976Hz) */
static const int16_t _rf[] = {
    +0x0000, +0x04bd, +0x03a2, -0x01f8, -0x0527, -0x01f9, +0x03a7, +0x04c8,
    +0x0000, -0x04cc, -0x03ad, +0x01fe, +0x0537, +0x0200, -0x03b3, -0x04d7,
    +0x0000, +0x04da, +0x03b8, -0x0204, -0x0547, -0x0206, +0x03be, +0x04e5,
    +0x0000, -0x04e9, -0x03c4, +0x020a, +0x0557, +0x020c, -0x03c9, -0x04f4,
    +0x0000, +0x04f8, +0x03cf, -0x0210, -0x0566, -0x0212, +0x03d4, +0x0503,
    +0x0000, -0x0506, -0x03da, +0x0216, +0x0576, +0x0218, -0x03df, -0x0511,
    +0x0000, +0x0515, +0x03e5, -0x021c, -0x0585, -0x021e, +0x03ea, +0x051f,
    +0x0000, -0x0523, -0x03ef, +0x0222, +0x0595, +0x0223, -0x03f5, -0x052d,
    +0x0000, +0x0530, +0x03fa, -0x0228, -0x05a3, -0x0229, +0x03ff, +0x053b,
    +0x0000, -0x053e, -0x0404, +0x022d, +0x05b2, +0x022f, -0x0409, -0x0548,
    +0x0000, +0x054b, +0x040e, -0x0233, -0x05c0, -0x0234, +0x0413, +0x0555,
    +0x0000, -0x0558, -0x0418, +0x0238, +0x05ce, +0x0239, -0x041d, -0x0561,
    +0x0000, +0x0565, +0x0422, -0x023d, -0x05db, -0x023e, +0x0426, +0x056e,
    +0x0000, -0x0571, -0x042b, +0x0242, +0x05e8, +0x0243, -0x042f, -0x0579,
    +0x0000, +0x057c, +0x0434, -0x0247, -0x05f5, -0x0248, +0x0438, +0x0585,
    +0x0000, -0x0587, -0x043c, +0x024b, +0x0601, +0x024d, -0x0441, -0x0590,
    +0x0000, +0x0592, +0x0445, -0x0250, -0x060c, -0x0251, +0x0448, +0x059a,
    +0x0000, -0x059c, -0x044c, +0x0254, +0x0617, +0x0255, -0x0450, -0x05a4,
    +0x0000, +0x05a6, +0x0454, -0x0258, -0x0621, -0x0259, +0x0457, +0x05ad,
    +0x0000, -0x05af, -0x045a, +0x025c, +0x062a, +0x025c, -0x045e, -0x05b5,
    +0x0000, +0x05b8, +0x0461, -0x025f, -0x0633, -0x0260, +0x0464, +0x05be,
    +0x0000, -0x05bf, -0x0467, +0x0262, +0x063c, +0x0263, -0x046a, -0x05c5,
    +0x0000, +0x05c7, +0x046c, -0x0265, -0x0643, -0x0266, +0x046f, +0x05cc,
    +0x0000, -0x05cd, -0x0471, +0x0268, +0x064a, +0x0268, -0x0474, -0x05d2,
    +0x0000, +0x05d3, +0x0476, -0x026a, -0x0650, -0x026b, +0x0478, +0x05d7,
    +0x0000, -0x05d8, -0x047a, +0x026c, +0x0656, +0x026d, -0x047c, -0x05dc,
    +0x0000, +0x05dd, +0x047d, -0x026e, -0x065a, -0x026f, +0x047f, +0x05e0,
    +0x0000, -0x05e1, -0x0480, +0x0270, +0x065e, +0x0270, -0x0481, -0x05e3,
    +0x0000, +0x05e4, +0x0483, -0x0271, -0x0661, -0x0271, +0x0484, +0x05e6,
    +0x0000, -0x05e7, -0x0484, +0x0272, +0x0664, +0x0272, -0x0485, -0x05e8,
    +0x0000, +0x05e8, +0x0486, -0x0273, -0x0665, -0x0273, +0x0486, +0x05e9,
    +0x0000, -0x05e9, -0x0486, +0x0273, +0x0666, +0x0273, -0x0486, -0x05ea,
    +0x0000, +0x05ea, +0x0486, -0x0273, -0x0666, -0x0273, +0x0486, +0x05e9,
    +0x0000, -0x05e9, -0x0486, +0x0273, +0x0665, +0x0273, -0x0486, -0x05e8,
    +0x0000, +0x05e8, +0x0485, -0x0272, -0x0664, -0x0272, +0x0484, +0x05e7,
    +0x0000, -0x05e6, -0x0484, +0x0271, +0x0662, +0x0271, -0x0483, -0x05e4,
    +0x0000, +0x05e4, +0x0482, -0x0270, -0x065e, -0x0270, +0x0480, +0x05e1,
    +0x0000, -0x05e0, -0x047f, +0x026f, +0x065b, +0x026e, -0x047d, -0x05dd,
    +0x0000, +0x05dc, +0x047c, -0x026d, -0x0656, -0x026c, +0x047a, +0x05d9,
    +0x0000, -0x05d7, -0x0478, +0x026b, +0x0651, +0x026a, -0x0476, -0x05d3,
    +0x0000, +0x05d2, +0x0474, -0x0269, -0x064a, -0x0268, +0x0472, +0x05ce,
    +0x0000, -0x05cc, -0x046f, +0x0266, +0x0644, +0x0265, -0x046d, -0x05c7,
    +0x0000, +0x05c5, +0x046a, -0x0263, -0x063c, -0x0262, +0x0467, +0x05c0,
    +0x0000, -0x05be, -0x0464, +0x0260, +0x0634, +0x025f, -0x0461, -0x05b8,
    +0x0000, +0x05b6, +0x045e, -0x025d, -0x062b, -0x025c, +0x045b, +0x05af,
    +0x0000, -0x05ad, -0x0457, +0x0259, +0x0621, +0x0258, -0x0454, -0x05a6,
    +0x0000, +0x05a4, +0x0450, -0x0255, -0x0617, -0x0254, +0x044d, +0x059d,
    +0x0000, -0x059a, -0x0449, +0x0251, +0x060c, +0x0250, -0x0445, -0x0593,
    +0x0000, +0x0590, +0x0441, -0x024d, -0x0601, -0x024c, +0x043d, +0x0588,
    +0x0000, -0x0585, -0x0439, +0x0248, +0x05f5, +0x0247, -0x0434, -0x057d,
    +0x0000, +0x057a, +0x0430, -0x0243, -0x05e9, -0x0242, +0x042b, +0x0571,
    +0x0000, -0x056e, -0x0427, +0x023f, +0x05dc, +0x023d, -0x0422, -0x0565,
    +0x0000, +0x0562, +0x041d, -0x0239, -0x05ce, -0x0238, +0x0419, +0x0559,
    +0x0000, -0x0555, -0x0414, +0x0234, +0x05c1, +0x0233, -0x040f, -0x054c,
    +0x0000, +0x0548, +0x040a, -0x022f, -0x05b2, -0x022d, +0x0405, +0x053e,
    +0x0000, -0x053b, -0x0400, +0x0229, +0x05a4, +0x0228, -0x03fa, -0x0531,
    +0x0000, +0x052d, +0x03f5, -0x0224, -0x0595, -0x0222, +0x03f0, +0x0523,
    +0x0000, -0x0520, -0x03eb, +0x021e, +0x0586, +0x021c, -0x03e5, -0x0515,
    +0x0000, +0x0511, +0x03e0, -0x0218, -0x0577, -0x0216, +0x03da, +0x0507,
    +0x0000, -0x0503, -0x03d5, +0x0212, +0x0567, +0x0211, -0x03cf, -0x04f8,
    +0x0000, +0x04f5, +0x03ca, -0x020c, -0x0557, -0x020a, +0x03c4, +0x04ea,
    +0x0000, -0x04e6, -0x03be, +0x0206, +0x0547, +0x0204, -0x03b9, -0x04db,
    +0x0000, +0x04d7, +0x03b3, -0x0200, -0x0537, -0x01fe, +0x03ad, +0x04cc,
    +0x0000, -0x04c8, -0x03a8, +0x01fa, +0x0527, +0x01f8, -0x03a2, -0x04bd,
    +0x0000, +0x04ba, +0x039c, -0x01f3, -0x0517, -0x01f2, +0x0397, +0x04ae,
    +0x0000, -0x04ab, -0x0391, +0x01ed, +0x0507, +0x01ec, -0x038b, -0x04a0,
    +0x0000, +0x049c, +0x0386, -0x01e7, -0x04f7, -0x01e6, +0x0380, +0x0491,
    +0x0000, -0x048d, -0x037a, +0x01e1, +0x04e7, +0x01e0, -0x0375, -0x0482,
    +0x0000, +0x047f, +0x036f, -0x01db, -0x04d8, -0x01da, +0x036a, +0x0474,
    +0x0000, -0x0470, -0x0364, +0x01d5, +0x04c8, +0x01d4, -0x035f, -0x0465,
    +0x0000, +0x0462, +0x0359, -0x01cf, -0x04b9, -0x01ce, +0x0354, +0x0457,
    +0x0000, -0x0454, -0x034f, +0x01c9, +0x04a9, +0x01c8, -0x0349, -0x0449,
    +0x0000, +0x0446, +0x0344, -0x01c4, -0x049b, -0x01c2, +0x033f, +0x043c,
    +0x0000, -0x0438, -0x033a, +0x01be, +0x048c, +0x01bd, -0x0335, -0x042e,
    +0x0000, +0x042b, +0x032f, -0x01b9, -0x047e, -0x01b7, +0x032b, +0x0421,
    +0x0000, -0x041e, -0x0326, +0x01b3, +0x0470, +0x01b2, -0x0321, -0x0415,
    +0x0000, +0x0412, +0x031c, -0x01ae, -0x0463, -0x01ad, +0x0317, +0x0409,
    +0x0000, -0x0406, -0x0313, +0x01a9, +0x0456, +0x01a8, -0x030e, -0x03fd,
    +0x0000, +0x03fa, +0x030a, -0x01a4, -0x0449, -0x01a3, +0x0306, +0x03f1,
    +0x0000, -0x03ef, -0x0301, +0x01a0, +0x043d, +0x019f, -0x02fd, -0x03e7,
    +0x0000, +0x03e4, +0x02f9, -0x019b, -0x0432, -0x019a, +0x02f5, +0x03dc,
    +0x0000, -0x03da, -0x02f2, +0x0197, +0x0427, +0x0196, -0x02ee, -0x03d3,
    +0x0000, +0x03d0, +0x02ea, -0x0193, -0x041d, -0x0192, +0x02e7, +0x03c9,
    +0x0000, -0x03c7, -0x02e3, +0x0190, +0x0413, +0x018f, -0x02e0, -0x03c1,
    +0x0000, +0x03bf, +0x02dd, -0x018c, -0x040a, -0x018b, +0x02da, +0x03b9,
    +0x0000, -0x03b7, -0x02d7, +0x0189, +0x0402, +0x0188, -0x02d4, -0x03b1,
    +0x0000, +0x03af, +0x02d1, -0x0186, -0x03fa, -0x0185, +0x02cf, +0x03aa,
    +0x0000, -0x03a9, -0x02cc, +0x0183, +0x03f3, +0x0183, -0x02ca, -0x03a4,
    +0x0000, +0x03a3, +0x02c8, -0x0181, -0x03ed, -0x0180, +0x02c6, +0x039f,
    +0x0000, -0x039e, -0x02c4, +0x017f, +0x03e8, +0x017e, -0x02c2, -0x039a,
    +0x0000, +0x0399, +0x02c0, -0x017d, -0x03e3, -0x017d, +0x02bf, +0x0396,
    +0x0000, -0x0395, -0x02be, +0x017b, +0x03df, +0x017b, -0x02bc, -0x0393,
    +0x0000, +0x0392, +0x02bb, -0x017a, -0x03dc, -0x017a, +0x02ba, +0x0390,
    +0x0000, -0x038f, -0x02b9, +0x0179, +0x03da, +0x0179, -0x02b9, -0x038e,
    +0x0000, +0x038e, +0x02b8, -0x0179, -0x03d8, -0x0178, +0x02b8, +0x038d,
    +0x0000, -0x038c, -0x02b7, +0x0178, +0x03d7, +0x0178, -0x02b7, -0x038c,
    +0x0000, +0x038c, +0x02b7, -0x0178, -0x03d7, -0x0178, +0x02b7, +0x038c,
    +0x0000, -0x038d, -0x02b7, +0x0178, +0x03d8, +0x0179, -0x02b8, -0x038d,
    +0x0000, +0x038e, +0x02b8, -0x0179, -0x03d9, -0x0179, +0x02b9, +0x038f,
    +0x0000, -0x0390, -0x02ba, +0x017a, +0x03dc, +0x017a, -0x02bb, -0x0391,
    +0x0000, +0x0392, +0x02bc, -0x017b, -0x03df, -0x017b, +0x02bd, +0x0395,
    +0x0000, -0x0395, -0x02bf, +0x017c, +0x03e3, +0x017d, -0x02c0, -0x0398,
    +0x0000, +0x039a, +0x02c2, -0x017e, -0x03e7, -0x017f, +0x02c3, +0x039d,
    +0x0000, -0x039e, -0x02c5, +0x0180, +0x03ed, +0x0181, -0x02c7, -0x03a2,
    +0x0000, +0x03a4, +0x02ca, -0x0182, -0x03f3, -0x0183, +0x02cc, +0x03a8,
    +0x0000, -0x03aa, -0x02ce, +0x0185, +0x03fa, +0x0186, -0x02d1, -0x03af,
    +0x0000, +0x03b0, +0x02d3, -0x0188, -0x0401, -0x0189, +0x02d6, +0x03b6,
    +0x0000, -0x03b8, -0x02d9, +0x018b, +0x0409, +0x018c, -0x02dc, -0x03be,
    +0x0000, +0x03c0, +0x02df, -0x018e, -0x0412, -0x018f, +0x02e3, +0x03c6,
    +0x0000, -0x03c8, -0x02e6, +0x0192, +0x041c, +0x0193, -0x02e9, -0x03cf,
    +0x0000, +0x03d1, +0x02ed, -0x0196, -0x0426, -0x0197, +0x02f1, +0x03d9,
    +0x0000, -0x03db, -0x02f5, +0x019a, +0x0431, +0x019b, -0x02f8, -0x03e3,
    +0x0000, +0x03e5, +0x02fc, -0x019e, -0x043c, -0x019f, +0x0301, +0x03ee,
    +0x0000, -0x03f0, -0x0305, +0x01a3, +0x0448, +0x01a4, -0x0309, -0x03f9,
    +0x0000, +0x03fc, +0x030d, -0x01a8, -0x0454, -0x01a9, +0x0312, +0x0404,
    +0x0000, -0x0407, -0x0316, +0x01ac, +0x0461, +0x01ae, -0x031b, -0x0410,
    +0x0000, +0x0413, +0x0320, -0x01b1, -0x046e, -0x01b3, +0x0325, +0x041d,
    +0x0000, -0x0420, -0x0329, +0x01b7, +0x047c, +0x01b8, -0x032e, -0x042a,
    +0x0000, +0x042d, +0x0333, -0x01bc, -0x048a, -0x01be, +0x0338, +0x0437,
    +0x0000, -0x043a, -0x033e, +0x01c2, +0x0499, +0x01c3, -0x0343, -0x0444,
    +0x0000, +0x0448, +0x0348, -0x01c7, -0x04a8, -0x01c9, +0x034d, +0x0452,
    +0x0000, -0x0456, -0x0353, +0x01cd, +0x04b7, +0x01cf, -0x0358, -0x0460,
    +0x0000, +0x0464, +0x035d, -0x01d3, -0x04c6, -0x01d4, +0x0363, +0x046f,
    +0x0000, -0x0472, -0x0368, +0x01d9, +0x04d6, +0x01da, -0x036e, -0x047d,
    +0x0000, +0x0481, +0x0374, -0x01df, -0x04e6, -0x01e0, +0x0379, +0x048c,
    +0x0000, -0x048f, -0x037f, +0x01e5, +0x04f5, +0x01e7, -0x0384, -0x049a,
    +0x0000, +0x049e, +0x038a, -0x01eb, -0x0505, -0x01ed, +0x0390, +0x04a9,
    +0x0000, -0x04ad, -0x0395, +0x01f1, +0x0515, +0x01f3, -0x039b, -0x04b8,
};

/* dac enable process callback */
static int TestRadio_DACEnableCallback(void *ptr)
{
    /* callback argument */
    cs43l22_cbarg_t *arg = ptr;
    /* shorthand, so that the code looks nicer */
    cb_t cb = TestRadio_DACEnableCallback;
    /* error code (if applicable) */
    int error = arg ? arg->error : EOK;

    /* got the error condition? */
    if (error)
        state = ERR;

    /* switch on current state */
    switch (state) {
    /* lock the resource */
    case LOCK : state = INIT, Sem_Lock(&cs43l22_sem, cb); break;
    /* do the initialization */
    case INIT : {
        /* start the initialization */
        state = PLAY, CS43L22_Initialize(cb); 
    } break;
    /* start the playback */
    case PLAY : state = VOLUME, CS43L22_Play(cb); break;
    /* set the volume */
    case VOLUME : state = ON, CS43L22_SetVolume(-0, cb); break;
    /* dac is now on or in error state, release the semaphore! */
    default : state = INIT; Sem_Release(&cs43l22_sem); break;
    }

    /* report status */
    return EOK;
}
int cnt, dh;
/* start the processing */
static int TestRadio_Process(void *ptr)
{
    /* products of the 1st stage mixer */
    int16_t i_mix1[elems(rf) / 2], q_mix1[elems(rf) / 2];
    /* current dac head pointer */
    uint32_t head = dac_head % elems(dac);
    /* decimated samples */
    float i_dec[elems(rf) / 2 / DEC_DECIMATION_RATE];
    float q_dec[elems(rf) / 2 / DEC_DECIMATION_RATE];
    /* demodulated samples */
    float dem[elems(rf) / 2 / DEC_DECIMATION_RATE];

    /* set the led on  */
    Led_SetState(1, LED_RED);

    /* do the mixing */
    Mix1_Mix(rf_ptr, rf_samples_num, i_mix1, q_mix1);
    /* decimate data */
    Dec_Decimate(i_mix1, q_mix1, elems(i_mix1), i_dec, q_dec, CB_SYNC);

    /* do the mixing */
    Mix2_Mix(i_dec, q_dec, elems(i_dec), i_dec, q_dec);

    /* filter before demodulation */
    DemodAM_Filter(i_dec, q_dec, elems(i_dec), i_dec, q_dec);
    /* demodulate the output data */
    DemodAM_Demodulate(i_dec, q_dec, elems(i_dec), dem);

    for (int i = 0; i < elems(dem); i++)
        dem[i] *= 16;

    /* convert to the fixed point notation for the dac */
    FloatFixp_FloatToFixp32(dem, elems(dem), 24, dac + head);

    /* update dac head */
    dac_head += elems(dem);

    /* start streaming audio to the dac */
    if (dac_head >= elems(dac) / 2 && Sem_Lock(&sai1a_sem, CB_NONE) == EOK) {
        /* start streaming data */
        SAI1A_StartStreaming(dac, elems(dac));
        /* start the dac enable procedure */
        Await_CallMeLater(100, TestRadio_DACEnableCallback, 0);
    }

    /* set the led off */
    Led_SetState(0, LED_RED);
    /* release the semaphore */
    Sem_Release(&sem);

    /* report status */
    return EOK;
}

/* rf data ready callback */
static int TestRadio_AnalogCallback(void *ptr)
{
    /* map event argument */
    analog_evarg_t *ea = ptr;

    /* check if calls do not overlap */
    assert(Sem_Lock(&sem, CB_NONE) == EOK, "unable to lock semaphore", 0);

    /* store information */
    rf_ptr = ea->samples; rf_samples_num = ea->num;
    /* invoke the processing on the low priority level */
    Invoke_CallMeElsewhere(TestRadio_Process, 0);

    /* report status */
    return EOK;
}

/* initialize test */
int TestRadio_Init(void)
{
    int mix1, mix2;
    /* check if the cpu clock is a multiple of rf sampling frequency */
    assert((int)(CPUCLOCK_FREQ / RF_SAMPLING_FREQ) * RF_SAMPLING_FREQ 
        == CPUCLOCK_FREQ, "cpu clock is not a integer multiple of rf "
        "sampling freq", 0);

    /* set the test frequencies */
    mix1 = Mix1_SetLOFrequency(1 * 225000);
    mix2 = Mix2_SetLOFrequency(1 * (225000 - mix1));

    dprintf("mix1 = %d, mix2 = %d\n", mix1, mix2);

    /* subscribe to rf data ready notifications */
    Ev_RegisterCallback(&analog_ev, TestRadio_AnalogCallback);
    /* start sampling */
    Analog_StartSampling(ANALOG_CH5, CPUCLOCK_FREQ / RF_SAMPLING_FREQ, rf, 
        elems(rf));
    
    /* report status */
    return EOK;
}
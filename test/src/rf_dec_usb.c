/**
 * @file rf_dec_usb.c
 * 
 * @date 2020-02-15
 * @author twatorowski 
 * 
 * @brief Test the RF sampler with conjunction with decimation unit
 */

#include <stdalign.h>

#include "assert.h"
#include "compiler.h"
#include "err.h"
#include "dev/dec.h"
#include "dev/led.h"
#include "dev/rfin.h"
#include "dev/usb.h"
#include "dev/usb_audiosrc.h"
#include "dsp/float_fixp.h"
#include "radio/mix1.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

/* radio samples buffer, for one millisecond of data per call */
static ALIGNED(4)int16_t rf[RF_SAMPLING_FREQ * 2 / 1000];
/* mixed samples buffer */
static ALIGNED(4) int16_t i_mix[elems(rf) / 2], q_mix[elems(rf) / 2];
/* decimation result holding array */
static float i_dec[2][elems(i_mix) / DEC_DECIMATION_RATE],
             q_dec[2][elems(q_mix) / DEC_DECIMATION_RATE];
/* ping pong buffer indicator */
static volatile int pp;

/* decimation callback */
static int TestRFDecUSB_DecimationDoneCallback(void *ptr)
{
    /* release the decimator */
    Sem_Release(&dec_sem);
    /* report status */
    return EOK;
}

/* got the samples ready? */
static int TestRFDecUSB_RFSamplesReady(void *ptr)
{
    /* cast event argument */
    rfin_evarg_t *ea = ptr;
    /* conversion buffers to prepare the data for the usb */
    int32_t i_dec_i32[elems(i_dec[0])], q_dec_i32[elems(q_dec[0])];

    /* update the ping-pong counter */
    pp = !pp;
    /* number of decimated frames */
    int rf_num = elems(rf) / 2, dec_num = elems(i_dec[0]);

    /* mix samples */
    Mix1_Mix(ea->samples, ea->num, i_mix, q_mix);
    
    /* prepare the decimator */
    assert(Sem_Lock(&dec_sem, CB_NONE) == EOK, 
        "unable to lock the decimator", 0);
    /* start decimating mixed data data */
    Dec_Decimate(i_mix, q_mix, rf_num, i_dec[pp], q_dec[pp], 
        TestRFDecUSB_DecimationDoneCallback);
    
    /* convert to the fixed point notation for the usb */
    FloatFixp_FloatToFixp32(i_dec[!pp], dec_num, 31, i_dec_i32);
    FloatFixp_FloatToFixp32(q_dec[!pp], dec_num, 31, q_dec_i32);

    /* store within the usb buffer */
    USBAudioSrc_PutSamples(i_dec_i32, q_dec_i32, elems(i_dec_i32));
    
    /* report status */
    return EOK;
}

/* test the rf + decimators */
int TestRFDecUSB_Init(void)
{   
    /* setup frequency */
    Mix1_SetLOFrequency(139000);

    /* register for 'samples' ready call */
    Ev_RegisterCallback(&rfin_ev, TestRFDecUSB_RFSamplesReady);

    /* start usb action */
    USB_Connect(1);
    /* start sampling the rf data */
    RFIn_StartSampling(rf, elems(rf));

    /* report status */
    return EOK;
}

/* poll the decimation test */
void TestRFDecUSB_Poll(void)
{
}
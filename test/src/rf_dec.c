/**
 * @file rf_dec.c
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
#include "dev/rfin.h"
#include "radio/mix1.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"


/* radio samples buffer */
static alignas(4)int16_t rf[DEC_DECIMATION_RATE * 2 * 20];
/* mixed samples buffer */
static ALIGNED(4) int16_t i_mix[elems(rf) / 2], q_mix[elems(rf) / 2];
/* output results holding array */
static float i_out[2][elems(i_mix) / DEC_DECIMATION_RATE];
static float q_out[2][elems(q_mix) / DEC_DECIMATION_RATE];
/* ping pong buffer indicator */
static int pp;

/* decimation callback */
static int TestRFDec_DecimationDoneCallback(void *ptr)
{
    /* update the pingpong counter */
    pp++;
    /* release the decimator */
    Sem_Release(&dec_sem);
    /* report status */
    return EOK;
}

/* got the samples ready? */
static int TestRFDec_RFSamplesReady(void *ptr)
{
    /* cast event argument */
    rfin_evarg_t *ea = ptr;
    /* pointers */
    int pp_head = pp & 1;

    /* mix samples */
    Mix1_Mix(ea->samples, ea->num, i_mix, q_mix);
    /* prepare the decimator */
    assert(Sem_Lock(&dec_sem, CB_NONE) == EOK, 
        "unable to lock the decimator", 0);
    /* start decimating mixed data data */
    Dec_Decimate(i_mix, q_mix, ea->num, i_out[pp_head], q_out[pp_head], 
        TestRFDec_DecimationDoneCallback);
    
    /* report status */
    return EOK;
}

/* test the rf + decimators */
int TestRFDec_Init(void)
{   
    /* setup frequency */
    Mix1_SetLOFrequency(RF_SAMPLING_FREQ / 7);

    /* register for 'samples' ready call */
    Ev_RegisterCallback(&rfin_ev, TestRFDec_RFSamplesReady);
    /* start sampling the rf data */
    RFIn_StartSampling(rf, elems(rf));

    /* report status */
    return EOK;
}

/* poll the decimation test */
void TestRFDec_Poll(void)
{
}
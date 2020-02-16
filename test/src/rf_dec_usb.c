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

/* usb sample type */
typedef struct { int32_t l, r; } usb_buf_elem_t;
/* data buffer */
static usb_buf_elem_t usb[elems(i_dec[0]) * 4];
/* linear memory space buffer */
static usb_buf_elem_t usb_lin[64];
/* head and tail pointers */
static uint32_t usb_head, usb_tail;

/* put samples into the usb buffer */
static int TestRFDecUSB_PutSamples(const int32_t *l, const int32_t *r, int num)
{
    /* space left, overall number of frames to store, head element index */
    uint32_t space_left, frames_to_store, head;
    /* samples to store before/after the circular buffer wraps */
    uint32_t frames_to_store_bwrap, frames_to_store_awrap;

    /* space left */
    space_left = elems(usb) - (usb_head - usb_tail);
    /* buffer is full */
    frames_to_store = min(space_left, (unsigned)num);
    
    /* get the head pointer */
    head = usb_head % elems(usb);
    /* limit the number of samples till/after the wrapping occurs */
    frames_to_store_bwrap = min(frames_to_store, elems(usb) - head);
    frames_to_store_awrap = frames_to_store -frames_to_store_bwrap;
    
    /* store data before the buffer wraps */
    for (int i = 0; i < (int)frames_to_store_bwrap; i++)
        usb[head + i].l = *l++, usb[head + i].r = *r++;

    /* store data */
    for (int i = 0; i < (int)frames_to_store_awrap; i++)
        usb[i].l = *l++, usb[i].r = *r++;
        
    /* update the head pointer */
    usb_head += frames_to_store;
    /* return the number of frames stored */
    return frames_to_store;
}

/* get samples from the buffer */
static int TestRFDecUSB_GetSamples(usb_buf_elem_t *buf, int num)
{
    /* space used within buffer, overall number frames to get, tail index */
    uint32_t space_used, frames_to_get, tail;
    /* samples to get before/after the circular buffer wraps */
    uint32_t frames_to_get_bwrap, frames_to_get_awrap;

    /* space used */
    space_used = usb_head - usb_tail;
    /* number of frames to get */
    frames_to_get = min(space_used, (unsigned)num);
    /* get the tail pointer */
    tail = usb_tail % elems(usb);
    /* limit the number of samples till wrapping occurs */
    frames_to_get_bwrap = min(frames_to_get, elems(usb) - tail);
    frames_to_get_awrap = frames_to_get - frames_to_get_bwrap;

    /* read data */
    for (int i = 0; i < (int)frames_to_get_bwrap; i++, buf++)
        buf->l = usb[tail + i].l, buf->r = usb[tail + i].r;
    
    /* read data */
    for (int i = 0; i < (int)frames_to_get_awrap; i++, buf++)
        buf->l = usb[i].l, buf->r = usb[i].r;
    
    /* update the tail pointer */
    usb_tail += frames_to_get;
    /* return the number of frames fetched from the buffer */
    return frames_to_get;
}

/* usb data requested? */
static int TestRFDecUSB_USBAudioCallback(void *ptr)
{
    /* space used in buffer */
    uint32_t space_used = usb_head - usb_tail;
    /* number of frames to fetch */
    uint32_t frames_to_get = USB_AUDIO_SRC_SAMPLES_PER_FRAME;

    /* buffer is getting full */
    if (space_used > elems(usb) / 2) {
        frames_to_get = elems(usb_lin);
    /* do not starve the buffer */
    } else if (space_used < elems(usb) / 4) {
        frames_to_get = USB_AUDIO_SRC_SAMPLES_PER_FRAME / 2;
    }
    
    /* get samples to the buffer */
    int frames_fetched = TestRFDecUSB_GetSamples(usb_lin, frames_to_get);
    /* no frames were fetched?: keep the stream going */
    if (frames_fetched == 0)
        frames_fetched = USB_AUDIO_SRC_SAMPLES_PER_FRAME;

    /* transfer audio */
    USBAudioSrc_Transfer(usb_lin, frames_fetched * sizeof(usb_buf_elem_t));
    /* report status */
    return EOK;
}

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

    /* update the pingpong counter */
    pp++;

    /* pointers */
    int pp_head = pp & 1, pp_tail = !(pp & 1);
    /* number of decimated frames */
    int rf_num = elems(rf) / 2, dec_num = elems(i_dec[0]);

    /* mix samples */
    Mix1_Mix(ea->samples, ea->num, i_mix, q_mix);
    
    /* prepare the decimator */
    assert(Sem_Lock(&dec_sem, CB_NONE) == EOK, 
        "unable to lock the decimator", 0);
    /* start decimating mixed data data */
    Dec_Decimate(i_mix, q_mix, rf_num, i_dec[pp_head], q_dec[pp_head], 
        TestRFDecUSB_DecimationDoneCallback);
    
    /* conversion buffers to prepare the data for the usb */
    int32_t i_dec_i32[elems(i_dec[0])], q_dec_i32[elems(q_dec[0])];
    /* convert to the fixed point notation for the usb */
    FloatFixp_FloatToFixp32(i_dec[pp_tail], dec_num, 31, i_dec_i32);
    FloatFixp_FloatToFixp32(q_dec[pp_tail], dec_num, 31, q_dec_i32);

    /* store within the usb buffer */
    TestRFDecUSB_PutSamples(i_dec_i32, q_dec_i32, elems(i_dec_i32));
    
    /* report status */
    return EOK;
}

/* test the rf + decimators */
int TestRFDecUSB_Init(void)
{   
    /* setup frequency */
    Mix1_SetLOFrequency(139000);

    // /* register for 'samples' ready call */
    Ev_RegisterCallback(&rfin_ev, TestRFDecUSB_RFSamplesReady);
    /* register callback for usb audio events */
    Ev_RegisterCallback(&usb_audio_ev, TestRFDecUSB_USBAudioCallback);

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
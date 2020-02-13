/**
 * @file rfin.c
 * 
 * @date 2020-02-13
 * @author twatorowski 
 * 
 * @brief Test for RFIn module
 */

#include <stdint.h>

#include "assert.h"
#include "err.h"
#include "dev/invoke.h"
#include "dev/led.h"
#include "dev/rfin.h"
#include "dev/timemeas.h"
#include "util/elems.h"

#define DEBUG
#include "debug.h"

/* samples buffer */
static int16_t buf[DEC_DECIMATION_RATE * 8];
/* timestamps for sampling rate estimation */
static uint16_t last_timestamp, curr_timestamp;
/* total number of samples sampled, total number of microseconds spent for 
 * sampling all this samples */
static uint32_t samples_cnt, us_cnt;
/* total rate */
static float rate;

/* display the sampling rate */
static int TestRFIn_DisplayCallback(void *ptr)
{   
    /* show the sampling rate */
    dprintf("sampling rate = %e\n", rate);
    /* return processing status */
    return EOK;
}

/* 'got samples' callback */
static int TestRFIn_RFInCallback(void *ptr)
{
    /* cast event argument */
    rfin_evarg_t *ea = ptr;
    
    /* set led state accordingly */
    Led_SetState(ea->type == RFIN_TYPE_HT, LED_RED);
    
    /* 1st batch of samples ever created */
    if (samples_cnt == 0) {
        last_timestamp = TimeMeas_GetTimeStamp();
    /* in the middle of the measurement process */
    } else {
        /* cet current timestamp */
        curr_timestamp = TimeMeas_GetTimeStamp();
        /* update the microsecond counter */
        us_cnt += (uint16_t)(curr_timestamp - last_timestamp);
        /* update the last timestamp */
        last_timestamp = curr_timestamp;
        /* one second of testing has elapsed? */
        if (us_cnt >= 1000000) {
            /* compute the rate */
            rate = (float)samples_cnt / us_cnt;
            /* clear variables */
            us_cnt = samples_cnt = 0;
            /* invoke the display on the other priority level as this callback 
             * are waaay too time sensitive */
            Invoke_CallMeElsewhere(TestRFIn_DisplayCallback, 0);
        }
    }
    /* update the samples counter */
    samples_cnt += ea->num;
    /* return processing status */
    return EOK;
}

/* test the rf sampler module */
int TestRFIn_Init(void)
{
    /* register callback */
    Ev_RegisterCallback(&rfin_ev, TestRFIn_RFInCallback);
    /* start the sampling process */
    RFIn_StartSampling(buf, elems(buf));
    /* report status */
    return EOK;
}

/* poll test logic */
void TestRFIn_Poll(void)
{

}
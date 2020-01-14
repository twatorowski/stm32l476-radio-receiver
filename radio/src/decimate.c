/**
 * @file decimate.c
 * 
 * @date 2020-01-13
 * @author twatorowski 
 * 
 * @brief Do the filtration and decimation to reduce the sample rate
 */

#include <stdint.h>

#include "config.h"
#include "err.h"
#include "dev/deci.h"
#include "dev/decq.h"
#include "radio/decimate.h"
#include "sys/atomic.h"

/* this variable helps to synchronize two independent decimator units */
static int32_t guard;
/* callback to be called after the decimation process has ended */
static cb_t callback;
/* callback argument */
static decimate_cbarg_t callback_arg;

/* decimation on in-phase or qudrature channel is complete */
static int Decimate_DecCallback(void *ptr)
{
    /* 1st decimator called the callback? need to wait for the second one to 
     * finish its job  */
    if (Atomic_ADD32(&guard, 1) == 0)
        return EOK;

    /* sync call */ 
	if (callback == CB_SYNC) {
		callback = CB_NONE;
	/* async call was made? */
	} else if (callback != CB_NONE) {
		callback(&callback_arg);
	}

    /* report status */
    return EOK;
}

/* decimate the input */
decimate_cbarg_t * Decimate_DecimateSamples(const int16_t *i, const int16_t *q, 
    int num, int32_t *i_dec, int32_t *q_dec, cb_t cb)
{
    /* synchronous operation requested? */
    int sync = cb == CB_SYNC;
    
    /* reset the guard */
    guard = 0;
    /* store the callback pointer */
    callback = cb; 
    /* prepare argument */
    callback_arg.i = i_dec, callback_arg.q = q_dec;
    callback_arg.num  = num / DEC_DECIMATION_RATE;

    /* call both decimator units */
    DecI_Decimate(i, num, i_dec, Decimate_DecCallback);
    DecQ_Decimate(q, num, q_dec, Decimate_DecCallback);

    /* sync call was made? */
    while (sync && callback == CB_SYNC);
    /* report callback arg in case of sync calls */
    return sync ? &callback_arg : 0;
}
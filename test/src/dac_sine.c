/**
 * @file dac_sine.c
 * 
 * @date 2019-10-28
 * @author twatorowski
 * 
 * @brief Test DAC output using sinusoidal signal
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "dev/await.h"
#include "dev/cs43l22.h"
#include "dev/sai1a.h"
#include "sys/time.h"
#include "util/elems.h"
#include "util/strerr.h"

#define DEBUG
#include "debug.h"

/* polling timer */
static time_t timer;
/* states of the dac */
static enum states {
    OFF, INIT, PLAY, VOLUME, ON, ERR,
} state;
/* stringified versions of the state names */
static const char *states_str[] = {
    [OFF] = "off", [INIT] = "init", [VOLUME] = "volume", 
    [PLAY] = "play", [ON] = "on", [ERR] = "error"
};
/* sine look-up table */
static uint32_t sine[] = {
    0x00000000, 0x001917a6, 0x0031f170, 0x004a5018, 0x0061f78a, 0x0078ad74,
    0x008e39d9, 0x00a26798, 0x00b504f2, 0x00c5e402, 0x00d4db30, 0x00e1c596,
    0x00ec835d, 0x00f4fa09, 0x00fb14bd, 0x00fec46c, 0x00ffffff, 0x00fec46c,
    0x00fb14bd, 0x00f4fa09, 0x00ec835d, 0x00e1c596, 0x00d4db30, 0x00c5e402,
    0x00b504f2, 0x00a26798, 0x008e39d9, 0x0078ad74, 0x0061f78a, 0x004a5018,
    0x0031f170, 0x001917a6, 0x00000000, 0xffe6e85a, 0xffce0e90, 0xffb5afe8,
    0xff9e0876, 0xff87528c, 0xff71c627, 0xff5d9868, 0xff4afb0e, 0xff3a1bfe,
    0xff2b24d0, 0xff1e3a6a, 0xff137ca3, 0xff0b05f7, 0xff04eb43, 0xff013b94,
    0xff000001, 0xff013b94, 0xff04eb43, 0xff0b05f7, 0xff137ca3, 0xff1e3a6a,
    0xff2b24d0, 0xff3a1bfe, 0xff4afb0e, 0xff5d9868, 0xff71c627, 0xff87528c,
    0xff9e0876, 0xffb5afe8, 0xffce0e90, 0xffe6e85a,
};

/* dac enable logic */
static int TestDACSine_EnCallback(void *ptr)
{
    /* callback argument */
    cs43l22_cbarg_t *arg = ptr;
    /* shorthand, so that the code looks nicer */
    cb_t cb = TestDACSine_EnCallback;
    /* error code (if applicable) */
    int error = arg ? arg->error : EOK;

    /* show message */
    dprintf("dac_en test state = %s, err = %d (%s)\n", states_str[state], 
        error, strerr(error));
    /* got the error condition? */
    if (error)
        state = ERR;

    /* switch on current state */
    switch (state) {
    /* dac is off, start streaming the sine wave  */
    case OFF : {
        /* advance the state machine */
        state = INIT; 
        /* start the serial audio data stream */
        SAI1A_StartStreaming((int32_t *)sine, elems(sine)); 
        /* lock the await module */
        Await_CallMeLater(100, TestDACSine_EnCallback);
    } break;
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

/* initalize test */
int TestDACSine_Init(void)
{
    /* scale the amplitude */
    for (int i = 0; i <(int)elems(sine); i++)
        sine[i] = (int32_t)sine[i] >> 1;

    /* report status */
    return EOK;
}

/* poll test */
void TestDACSine_Poll(void)
{
    /* check timer */
    if (dtime_past(time(), timer) < 2000)
        return;

    /* kick the timer */
    timer = time();
    /* start the process by acquiring the lock */
    Sem_Lock(&cs43l22_sem, TestDACSine_EnCallback);
}
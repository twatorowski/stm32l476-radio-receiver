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
    0x00000000, 0x10b5150f, 0x2120fb82, 0x30fbc54c, 0x3fffffff, 0x4debe4fd,
    0x5a827999, 0x658c9a2c, 0x6ed9eba0, 0x7641af3b, 0x7ba3751c, 0x7ee7aa4a,
    0x7fffffff, 0x7ee7aa4a, 0x7ba3751c, 0x7641af3b, 0x6ed9eba0, 0x658c9a2c,
    0x5a827999, 0x4debe4fd, 0x3fffffff, 0x30fbc54c, 0x2120fb82, 0x10b5150f,
    0x00000000, 0xef4aeaf1, 0xdedf047e, 0xcf043ab4, 0xc0000001, 0xb2141b03,
    0xa57d8667, 0x9a7365d4, 0x91261460, 0x89be50c5, 0x845c8ae4, 0x811855b6,
    0x80000001, 0x811855b6, 0x845c8ae4, 0x89be50c5, 0x91261460, 0x9a7365d4,
    0xa57d8667, 0xb2141b03, 0xc0000001, 0xcf043ab4, 0xdedf047e, 0xef4aeaf1
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
        Await_CallMeLater(100, TestDACSine_EnCallback, 0);
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
        sine[i] = (int32_t)sine[i] >> 8;

    /* start the process by acquiring the lock */
    Sem_Lock(&cs43l22_sem, TestDACSine_EnCallback);

    /* report status */
    return EOK;
}

/* poll test */
void TestDACSine_Poll(void)
{

}
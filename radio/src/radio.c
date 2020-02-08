/**
 * @file radio.c
 * 
 * @date 2020-02-02
 * @author twatorowski 
 * 
 * @brief Radio Receiver logic
 */

#include "assert.h"
#include "err.h"
#include "at/ntf/radio.h"
#include "dev/analog.h"
#include "dev/await.h"
#include "dev/cs43l22.h"
#include "dev/dec.h"
#include "dev/display.h"
#include "dev/invoke.h"
#include "dev/joystick.h"
#include "dev/led.h"
#include "dev/sai1a.h"
#include "dsp/fixp_sat.h"
#include "dsp/float_fixp.h"
#include "dsp/float_scale.h"
#include "radio/dec4.h"
#include "radio/demod_am.h"
#include "radio/mix1.h"
#include "radio/mix2.h"
#include "sys/sem.h"
#include "util/elems.h"
#include "util/minmax.h"

#define DEBUG
#include "debug.h"

/* frequencies */
static int set_frequency = 225000, actual_frequency;
/* frequencies of the local oscillator */
static float lo1_frequency, lo2_frequency;

/* rf samples buffer */
static int16_t rf[2048];
/* complex data after 1st stage mixing */
static int16_t i_mix1[elems(rf) / 2], q_mix1[elems(rf) / 2];
/* complex data after downsampling: in-phase channel, and quadrature channel. 
 * we use twice as much space needed to operate in ping-pong mode */
static float i_dec[2][elems(rf) / 2 / DEC_DECIMATION_RATE], 
    q_dec[2][elems(rf) / 2 / DEC_DECIMATION_RATE];
/* ping pong indicator */
static int dec_pp;

/* AM-demodulated audio samples */
static float dem[elems(rf) / 2 / DEC_DECIMATION_RATE];

/* audio gain */
static float set_gain = 10.0f;

/* fixed point dac samples buffer */
static int32_t dac[elems(rf)];
/* dac buffer head pointer */
static uint32_t dac_head;
/* states of the dac ic */
static enum dac_states {
    LOCK, INIT, PLAY, VOLUME, ON, ERR,
} dac_state;

/* callback called to update the frequencies of both local oscillators and to 
 * update the LCD display */
static int Radio_UpdateFrequencyCallback(void *ptr)
{
    /* display character buffer */
    char display_buf[7];

    /* set the frequencies for the local oscillators */
    lo1_frequency = Mix1_SetLOFrequency(set_frequency);
    lo2_frequency = Mix2_SetLOFrequency(set_frequency - lo1_frequency);

    /* calculate the actual frequency */
    actual_frequency = lo1_frequency + lo2_frequency;
    /* show the frequency */
    dprintf("set_frequency = %d, act_frequency = %d, lo1 = %.5e, lo2 = %.5e\n", 
        set_frequency, actual_frequency, lo1_frequency, lo2_frequency);
    /* show the gain */
    dprintf("gain = %e\n", set_gain);
    
    /* prepare the display content */
    int i, len = snprintf(display_buf, sizeof(display_buf), "%d", 
        actual_frequency);
    /* store the data in the display memory */
    for (i = 0 ; i < len; i++)
        Display_SetCharacter(i, display_buf[i]);
    /* fill the rest with spaces */
    for (; i < 6; i++)
        Display_SetCharacter(i, ' ');
    /* update the display */
    Display_Update();

    /* report status */
    return EOK;
}

/* joystick event callback */
static int Radio_JoystickCallback(void *ptr)
{
    /* cast event argument */
    joystick_evarg_t *ea = ptr;
    /* change in gain per joystick event (1dB, voltage-wise) */
    const float gain_change = 1.12202;
    /* change in freqency per joystick event */
    const int frequency_change = 1000;
    /* final settings */
    float new_gain = set_gain; int new_frequency = set_frequency;
    
    /* adjust volume */
    if (ea->status & JOYSTICK_STATUS_UP) new_gain *= gain_change;
    if (ea->status & JOYSTICK_STATUS_DOWN) new_gain /= gain_change;
    /* adjust frequency */
    if (ea->status & JOYSTICK_STATUS_RIGHT) new_frequency += frequency_change;
    if (ea->status & JOYSTICK_STATUS_LEFT) new_frequency -= frequency_change;

    /* sanity limits for the gain : +/- 40dB */
    new_gain = min(1000, max(new_gain, 0.01));
    /* sanity limits for the frequency: DC to Nyquist */
    new_frequency = min(RF_SAMPLING_FREQ / 2, max(0, new_frequency));

    /* store */
    set_gain = new_gain; set_frequency = new_frequency;
    /* invoke the update */
    Invoke_CallMeElsewhere(Radio_UpdateFrequencyCallback, 0);

    /* report status */
    return EOK;
}

/* dac enable process callback */
static int Radio_DACEnableCallback(void *ptr)
{
    /* callback argument */
    cs43l22_cbarg_t *arg = ptr;
    /* shorthand, so that the code looks nicer */
    cb_t cb = Radio_DACEnableCallback;
    /* error code (if applicable) */
    int error = arg ? arg->error : EOK;

    /* catch all the errors here */
    assert(error == EOK, "dac initialization error", error);

    /* switch on current state */
    switch (dac_state) {
    /* lock the resource */
    case LOCK : dac_state = INIT, Sem_Lock(&cs43l22_sem, cb); break;
    /* do the initialization */
    case INIT : {
        /* start the initialization */
        dac_state = PLAY, CS43L22_Initialize(cb); 
    } break;
    /* start the playback */
    case PLAY : dac_state = VOLUME, CS43L22_Play(cb); break;
    /* set the volume */
    case VOLUME : dac_state = ON, CS43L22_SetVolume(-0, cb); break;
    /* dac is now on or in error state, release the semaphore! */
    default : dac_state = INIT; Sem_Release(&cs43l22_sem); break;
    }

    /* report status */
    return EOK;
}

/* this is called after the samples get decimated */
static int Radio_DecimationCallback(void *ptr)
{
    /* make pings into pongs */
    dec_pp = !dec_pp;
    /* report callback processing status */
    return EOK;
}

/* adc rf samples  have arrived callback */
static int Radio_AnalogCallback(void *ptr)
{
    /* cast event argument */
    analog_evarg_t *ea = ptr;
    /* head/tail adjusted pointers to the ping-pong buffer phase indicator */
    float *i_dec_head = i_dec[ dec_pp], *q_dec_head = q_dec[ dec_pp];
    float *i_dec_tail = i_dec[!dec_pp], *q_dec_tail = q_dec[!dec_pp];
    /* number of samples after the hardware decimator */
    const int hw_dec_num = elems(i_dec[0]);
    /* number of samples after software decimator did it's job */
    const int sw_dec_num = hw_dec_num / 4;
    
    /* set the led on to indicate the start of the processing */
    Led_SetState(1, LED_RED);

    /* do the mixing */
    Mix1_Mix(ea->samples, ea->num, i_mix1, q_mix1);
    /* start the parallel process of rf samples decimation */
    Dec_Decimate(i_mix1, q_mix1, ea->num, i_dec_head, q_dec_head, 
        Radio_DecimationCallback);

    /* 2nd stage mixing, done in-situ */
    Mix2_Mix(i_dec_tail, q_dec_tail, hw_dec_num, i_dec_tail, q_dec_tail);

    /* decimation by 4 for the sake of processing speed-up and to allow pushing 
     * the data out using AT commands */
    /* firstly apply the filtration */
    Dec4_Filter(i_dec_tail, q_dec_tail, hw_dec_num, i_dec_tail, 
        q_dec_tail);
    /* then drop unused samples */
    Dec4_Decimate(i_dec_tail, q_dec_tail, hw_dec_num, i_dec_tail, 
        q_dec_tail);

    /* put the decimated data to the at notifications module */
    ATNtfRadio_PutIQSamples(i_dec_tail, q_dec_tail, sw_dec_num);

    /* filter before demodulation */
    DemodAM_Filter(i_dec_tail, q_dec_tail, sw_dec_num, i_dec_tail, 
        q_dec_tail);
    /* demodulate the output data */
    DemodAM_Demodulate(i_dec_tail, q_dec_tail, sw_dec_num, dem);

    /* apply gain */
    FloatScale_Scale(dem, sw_dec_num, set_gain, dem);
    /* convert to the fixed point notation for the dac */
    FloatFixp_FloatToFixp32(dem, sw_dec_num, 24, dac + dac_head);
    /* do the saturation to avoid overflows when the audio is getting loud */
    FixpSat_Saturate(dac + dac_head, sw_dec_num, 24, dac + dac_head);

    /* update dac head index */
    dac_head = (dac_head + sw_dec_num) % elems(dac);

    /* start streaming audio to the dac if not already started, but only if we 
     * have at least half of the dac buffer filled with data. this prevents the 
     * artifacts by ensuring that we are not writing data that is currenlty 
     * being sent to dac */
    if (dac_head >= elems(dac) / 2 && Sem_Lock(&sai1a_sem, CB_NONE) == EOK) {
        /* start streaming data */
        SAI1A_StartStreaming((float)RF_SAMPLING_FREQ / DEC_DECIMATION_RATE / 4, 
            dac, elems(dac));
        /* start the dac enable procedure 100 ms after the stream was started 
         * to avoid audio glitches */
        Await_CallMeLater(100, Radio_DACEnableCallback, 0);
    }

    /* set the led off to indicate the end of the processing */
    Led_SetState(0, LED_RED);
    
    /* report status */
    return EOK;
}

/* initialize radio receiver logic */
int Radio_Init(void)
{   
    /* sanity check */
    assert(((int)CPUCLOCK_FREQ / (int)RF_SAMPLING_FREQ) * RF_SAMPLING_FREQ == 
        CPUCLOCK_FREQ, "cpu clock frequency is not a multiple of the sampling "
        "frequency!", 0);

    /* subscribe to rf data ready notifications. the callback will be called 
     * every time a half of the buffer gets filled */
    Ev_RegisterCallback(&analog_ev, Radio_AnalogCallback);
    /* register callback for the joystick events */
    Ev_RegisterCallback(&joystick_ev, Radio_JoystickCallback);

    /* start sampling */
    Analog_StartSampling(ANALOG_CH5, CPUCLOCK_FREQ / RF_SAMPLING_FREQ, rf, 
        elems(rf));

    /* initialize the local oscillators */
    Invoke_CallMeElsewhere(Radio_UpdateFrequencyCallback, 0);
    /* report status */
    return EOK;
}

/* tune to given frequency */
int Radio_SetFrequency(float f)
{
    /* rsanity checks */
    if (f < 0 || f > RF_SAMPLING_FREQ / 2)
        return EFATAL;

    /* set the frequency */
    set_frequency = f;
    /* initialize the local oscillators */
    Invoke_CallMeElsewhere(Radio_UpdateFrequencyCallback, 0);

    /* report status */
    return EOK;
}

/* get current frequency */
int Radio_GetFrequency(float *f)
{
    /*report the actual frequency */
    *f = actual_frequency;
    /* report status */
    return EOK;
}
/**
 * @file keypad.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief Keypad driver
 */

#include "err.h"
#include "dev/analog.h"
#include "dev/keypad.h"
#include "util/elems.h"

/* adc range for every key */
static struct adc_range {
    /* key that is described by the adc range */
    keypad_key_mask_t key;
    /* acceptable adc range */
    uint16_t lo, hi;
} adc_ranges[] = {
    { KEYPAD_KEY_MASK_RIGHT,      0,    90 },
    { KEYPAD_KEY_MASK_LEFT,   38200, 39200 },
    { KEYPAD_KEY_MASK_UP,      9450,  9980 },
    { KEYPAD_KEY_MASK_DOWN,   24700, 25200 },
    { KEYPAD_KEY_MASK_SELECT, 58600, 59200 },
};

/* error code */
err_t Keypad_Init(void)
{
    /* return error code */
    return EOK;
}

/* get status */
err_t Keypad_GetKeyStatus(keypad_key_mask_t *keys)
{
    /* read the voltage value */
    uint16_t adc; Analog_Convert(ANALOG_A0, &adc);
    /* adc value range pointer */
    struct adc_range *ar;
    /* clear the mask */
    *keys = 0;

    /* check which keys are pressed by comparing the adc values */
    for (ar = adc_ranges; ar != adc_ranges + elems(adc_ranges); ar++)
        if (adc >= ar->lo && adc <= ar->hi)
            *keys |= ar->key;
    
    /* return status */
    return EOK;
}
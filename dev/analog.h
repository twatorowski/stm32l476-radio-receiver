/**
 * @file adc.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief Analog to digital converter
 */

#ifndef _DEV_ANALOG_H
#define _DEV_ANALOG_H

#include <stdint.h>

#include "err.h"

/** channels that are present on board */
typedef enum analog_channel {
    ANALOG_A0 = 16,
    ANALOG_A1 = 17,
    ANALOG_A2 = 18,
    ANALOG_A3 = 5,
    ANALOG_A4 = 10,
    ANALOG_A5 = 11,
} analog_channel_t;

/**
 * @brief initialize the analog to digital conversion driver
 * 
 * @return err_t init status
 */
err_t Analog_Init(void);

/**
 * @brief performs convrsion of given analog channel
 * 
 * @param channel channel number
 * @param value placeholder for the converted value
 * 
 * @return err_t conversion status
 */
err_t Analog_Convert(analog_channel_t channel, uint16_t *value);


#endif /* _DEV_ADC_H */

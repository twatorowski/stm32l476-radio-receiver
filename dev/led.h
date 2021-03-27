/**
 * @file led.h
 * 
 * @date 2020-01-18
 * @author twatorowski 
 * 
 * @brief On-Board LED Driver
 */

#ifndef DEV_LED_H_
#define DEV_LED_H_

#include <stdint.h>
#include "util/bit.h"

/** Led colors */
typedef enum led_colors {
    /** mask for green led */
    LED_GRN= BIT_VAL(0), 
    /** mask for red led */
    LED_RED = BIT_VAL(1), 
    /** mask for yellow leds */
    LED_YEL = BIT_VAL(2)
} led_colors_t;

/**
 * @brief initialize led module
 * 
 * @return int status
 */
int Led_Init(void);

/**
 * @brief Enable/disable certain leds
 * 
 * @param enable 1 - enable, 0 - disable
 * @param leds led mask
 * 
 */
void Led_SetState(int enable, led_colors_t leds);

#endif /* DEV_LED_H_ */
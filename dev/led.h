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

/* led colors */
#define LED_RED								(0x0004)

/* initialize leds */
int Led_Init(void);
/* set led state */
void Led_SetState(int enable, uint32_t leds);

#endif /* DEV_LED_H_ */
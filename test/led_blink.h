/**
 * @file led_blink.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-11
 * 
 * @brief Blinking led that shows the os activity 
 */

#ifndef _TEST_LED_BLINK_H
#define _TEST_LED_BLINK_H


#include "err.h"

/**
 * @brief Initialize the led blink test 
 * 
 * @return err_t status
 */
err_t TestLEDBlink_Init(void);


#endif /* _TEST_LED_BLINK_H */

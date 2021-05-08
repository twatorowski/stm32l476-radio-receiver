/**
 * @file keypad.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief Keypad driver
 */

#ifndef _DEV_KEYPAD_H
#define _DEV_KEYPAD_H

#include "util/bit.h"

/** key bit-mask */
typedef enum keypad_key_mask {
    KEYPAD_KEY_MASK_RIGHT = BIT_VAL(0),
    KEYPAD_KEY_MASK_LEFT = BIT_VAL(1),
    KEYPAD_KEY_MASK_UP = BIT_VAL(2),
    KEYPAD_KEY_MASK_DOWN = BIT_VAL(3),
    KEYPAD_KEY_MASK_SELECT = BIT_VAL(4),
} keypad_key_mask_t;

/**
 * @brief error code 
 * 
 * @return err_t status code
 */
err_t Keypad_Init(void);

/**
 * @brief get the mask of keys being pressed
 * 
 * @param keys mask of keys being pressed
 *  
 * @return err_t statuc
 */
err_t Keypad_GetKeyStatus(keypad_key_mask_t *keys);

#endif /* _DEV_KEYPAD_H */

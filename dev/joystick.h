/**
 * @file joystick.h
 * 
 * @date 2019-12-03
 * @author twatorowski 
 * 
 * @brief Joystick driver module that supports the 4-way joystick present on 
 * the stm32l4-discovery board.
 */

#ifndef DEV_JOYSTICK_H_
#define DEV_JOYSTICK_H_

#include "sys/ev.h"

/** @name Joystick state flags */
/** @{ */
/** @brief joystick moved to the left */
#define JOYSTICK_STATUS_LEFT                (1 << 0)
/** @brief joystick moved to the right */
#define JOYSTICK_STATUS_RIGHT               (1 << 1)
/** @brief joystick moved up */
#define JOYSTICK_STATUS_UP                  (1 << 2)
/** @brief joystick moved down */
#define JOYSTICK_STATUS_DOWN                (1 << 3)
/** @brief joystick center button pressed */
#define JOYSTICK_STATUS_CENTER              (1 << 4)
/** @} */

/** @brief joystick event */
typedef struct joystick_evarg {
    /** @brief current joystick status */
    int status;
} joystick_evarg_t;

/** @brief joystick event: emmited when the joystick state changes */
extern ev_t joystick_ev;

/** @brief interrupt for exti 0-3 and 5 */
void Joystick_Exti0_3_5Isr(void);

/**
 * @brief Initialize joystick module.
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int Joystick_Init(void);

/**
 * @brief Report current joystick status
 * 
 * @return int joystick status (see JOYSTICK_STATUS_ defines)
 */
int Joystick_GetStatus(void);

#endif /* DEV_JOYSTICK_H_ */

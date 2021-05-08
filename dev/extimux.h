/**
 * @file extimux.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-05-05
 * 
 * @brief Exti interrupt multiplexer
 */

#ifndef _DEV_EXTIMUX_H
#define _DEV_EXTIMUX_H

#include "err.h"
#include "dev/gpio.h"
#include "stm32h743/exti.h"
#include "util/bit.h"

/** overall number of extimux channels */
#define EXTIMUX_CH_NUM                      15

/** extimux channels */
typedef enum extimux_ch {
    /** external interrupt channels 0 to 15 */
    EXTIMUX_CH_0,
    EXTIMUX_CH_1,
    EXTIMUX_CH_2,
    EXTIMUX_CH_3,
    EXTIMUX_CH_4,
    EXTIMUX_CH_5,
    EXTIMUX_CH_6,
    EXTIMUX_CH_7,
    EXTIMUX_CH_8,
    EXTIMUX_CH_9,
    EXTIMUX_CH_10,
    EXTIMUX_CH_11,
    EXTIMUX_CH_12,
    EXTIMUX_CH_13,
    EXTIMUX_CH_14,
    EXTIMUX_CH_15,
} extimux_ch_t;

/** types of sensitivity */
typedef enum extimux_sensitivity {
    EXTIMUX_SENS_RISE = BIT_VAL(0),
    EXTIMUX_SENS_FALL = BIT_VAL(1),
} extimux_sensitivity_t;

/** extimux routine type */
typedef void (* extimux_hndl_t) (extimux_ch_t ch); 

/** @brief exti interrupt mux for line 0 */
void ExtiMux_Exti0Isr(void);
/** @brief exti interrupt mux for line 1 */
void ExtiMux_Exti1Isr(void);
/** @brief exti interrupt mux for line 2 */
void ExtiMux_Exti2Isr(void);
/** @brief exti interrupt mux for line 3 */
void ExtiMux_Exti3Isr(void);
/** @brief exti interrupt mux for line 4 */
void ExtiMux_Exti4Isr(void);
/** @brief exti interrupt mux for lines 5 to 9 */
void ExtiMux_Exti9_5Isr(void);
/** @brief exti interrupt mux for lines 10 to 15 */
void ExtiMux_Exti15_10Isr(void);

/**
 * @brief initialize exti interrupts demultiplexer
 * 
 * @return int 
 */
err_t ExtiMux_Init(void);

/**
 * @brief register interrupt routine
 * 
 * @param ch exti channel
 * @param hndl interrupt handler
 * 
 * @return err_t error code
 */
err_t ExtiMux_RegisterRoutine(extimux_ch_t ch, extimux_hndl_t hndl);

/**
 * @brief Route specific exti line to gpio port
 * 
 * @param ch exti channel
 * @param gpio gpio port
 * 
 * @return err_t status
 */
err_t ExtiMux_RouteToGPIO(extimux_ch_t ch, gpio_t *gpio);

/**
 * @brief Configure sensitivity for given line
 * 
 * @param ch exti channel
 * @param sens sensitivity 
 */
static inline ALWAYS_INLINE void ExtiMux_CfgSensitivity(extimux_ch_t ch, 
    extimux_sensitivity_t sens)
{
    /* configure the sensitivity setting registers */
    EXTI->RTSR1 = BIT_WR(EXTI->RTSR1, ch, sens & EXTIMUX_SENS_RISE);
    EXTI->FTSR1 = BIT_WR(EXTI->FTSR1, ch, sens & EXTIMUX_SENS_FALL);
}

/**
 * @brief Enables/disables interrupt generation on given exti line
 * 
 * @param ch exti channel
 * @param enable 1 - enable,  0 - disable
 */
static inline ALWAYS_INLINE void ExtiMux_CfgInterrupt(extimux_ch_t ch, 
    int enable)
{
    /* setup the interrupt mask register*/
    EXTI->IMR1 = BIT_WR(EXTI->IMR1, ch, enable);
}

/**
 * @brief Clears given pending bit and thus resolves the interrupt
 * 
 * @param ch channel for which the pending bit is cleared
 */
static inline ALWAYS_INLINE void ExtiMux_ClearPending(extimux_ch_t ch)
{
    /* pending bit is cleared by writing 1 to it */
    EXTI->PR1 = EXTI_PR1_PR0 << ch;
}


#endif /* _DEV_EXTIMUX_H */

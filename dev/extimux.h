/**
 * @file extimux.h
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief EXII Interrupts multiplexer. Since EXTI interrupts are grouped (at 
 * least the high-number extis) this piece of code is responsible for undoing 
 * the grouping.
 */

#ifndef DEV_EXTIMUX_H_
#define DEV_EXTIMUX_H_

/** @brief exti interrupt mux for lines 5 to 9 */
void ExtiMux_Exti5_9Isr(void);
/** @brief exti interrupt mux for lines 10 to 15 */
void ExtiMux_Exti10_15Isr(void);

/**
 * @brief Initialize EXTI Interrupt multiplexer
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int ExtiMux_Init(void);




#endif /* DEV_EXTIMUX_H_ */

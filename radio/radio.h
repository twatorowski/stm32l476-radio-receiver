/**
 * @file radio.h
 * 
 * @date 2020-02-02
 * @author twatorowski 
 * 
 * @brief Radio Receiver logic
 */

#ifndef RADIO_RADIO_H
#define RADIO_RADIO_H

/**
 * @brief Initialize radio receiver logic
 * 
 * @return int status 
 */
int Radio_Init(void);

/**
 * @brief tune to given frequency 
 * 
 * @param f frequency to tune to.
 * 
 * @return int status
 */
int Radio_SetFrequency(float f);

/**
 * @brief get current tunning frequency 
 * 
 * @param f place to put the frequency value to.
 * 
 * @return int status
 */
int Radio_GetFrequency(float *f);


#endif /* RADIO_RADIO_H */

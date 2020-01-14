/**
 * @file mix1.h
 * 
 * @date 2020-01-14
 * @author twatorowski 
 * 
 * @brief 1st mixer that converts the RF signal to near-zero IF. Local 
 * Oscillator is implemented using NCO and allows for selecting 64 even spaced 
 * frequencies from 0 to f_sample / 2
 */

#ifndef RADIO_MIX1_H
#define RADIO_MIX1_H

#include <stdint.h>


/**
 * @brief mix the incoming RF signal using the internally generated 
 * complex sinusoid.
 * 
 * @param rf fr signal input data
 * @param num number of samples to be downconverted
 * @param i resulting in-phase component
 * @param q resulting quadrature component
 * 
 */
int Mix1_Mix(const int16_t *rf, int num, int16_t *i, int16_t *q);

/**
 * @brief Sets the frequency for the numerically controlled oscillator that is 
 * used for downconversion. NCO has limited resolution: i.e. it can only operate 
 * on couple of frequencies. True frequency will be returned.
 * 
 * @param hz desired NCO frequency in Hz.
 * 
 * @return int actual frequency applied in Hz.
 */
int Mix1_SetLOFrequency(int hz);

#endif /* RADIO_MIX1_H */

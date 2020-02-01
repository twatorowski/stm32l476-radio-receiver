/**
 * @file mix2.h
 * 
 * @date 2020-01-18
 * @author twatorowski 
 * 
 * @brief 2nd stage mixer, that brings the decimated signal to DC. This one has 
 * a lot finer tunning capabilities as it uses NCO with bigger look-up table and 
 * operates as low-data rate.
 */

#ifndef RADIO_MIX2_H
#define RADIO_MIX2_H

#include <stdint.h>

/**
 * @brief Mix the complex input signal with the local oscillator
 * 
 * @param i In-phase channel data
 * @param q Quadrature channel data
 * @param num number of samples to be mixed
 * @param i_out pointer to the output I channel data
 * @param q_out pointer to the output Q channel data
 */
void Mix2_Mix(const float *i, const float *q, int num, float *i_out, 
    float *q_out);

/**
 * @brief Sets the local oscillator frequency for the 2nd stage mixer
 * 
 * @param hz desired frequency
 * 
 * @return int actual frequency
 */
int Mix2_SetLOFrequency(int hz);

#endif /* RADIO_MIX2_H */

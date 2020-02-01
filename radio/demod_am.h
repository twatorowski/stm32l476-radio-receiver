/**
 * @file demod_am.h
 * 
 * @date 2020-01-19
 * @author twatorowski 
 * 
 * @brief AM Demodulation 
 */

#ifndef RADIO_DEMOD_AM_H
#define RADIO_DEMOD_AM_H


/**
 * @brief Apply filtration before AM demodulation
 * 
 * @param i input in-phase channel
 * @param q input quadrature channel
 * @param num number of samples to filter
 * @param i_out filtered in-phase channel
 * @param q_out filtered quadrature channel
 * 
 */
void DemodAM_Filter(const float *i, const float *q, int num, float *i_out, 
    float *q_out);

/**
 * @brief Demodulate AM demodulation contained in the basenand I/Q data.
 * 
 * @param i In-phase data
 * @param q Quadrature data
 * @param num number of samples
 * @param out output data
 */
void DemodAM_Demodulate(const float *i, const float *q, int num, float *out);


#endif /* RADIO_DEMOD_AM_H */

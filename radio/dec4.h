/**
 * @file dec4.h
 * 
 * @date 2020-02-05
 * @author twatorowski 
 * 
 * @brief Decimate-by-Four module for the IQ Samples
 */

#ifndef RADIO_DEC4_H
#define RADIO_DEC4_H


/**
 * @brief Filter the incoming data with omega = 0.25 filter before decimating.
 * Can be performed in-situ.
 * 
 * @param i in phase data
 * @param q quadrature data
 * @param num number of samples to filter
 * @param i_out filtered in-phase output (still at original sampling rate)
 * @param q_out filtered quadrature output (still at original sampling rate)
 */
void Dec4_Filter(const float *i, const float *q, int num, float *i_out, 
    float *q_out);


/**
 * @brief Drop samples so that we are left with every 4th of them. Can be 
 * performed in-situ. Remember to apply filtration before decimating so you 
 * don't run into aliasing issues!
 * 
 * @param i in phase data
 * @param q quadrature data
 * @param num number of samples (must be divisible by 4)
 * @param i_out decimated in-phase data
 * @param q_out decimated quadrature data
 * 
 */
void Dec4_Decimate(const float *i, const float *q, int num, float *i_out, 
    float *q_out);

#endif /* RADIO_DEC4_H */

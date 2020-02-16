/**
 * @file dec.h
 * 
 * @date 2020-01-19
 * @author twatorowski 
 * 
 * @brief Decimators for the I/Q channels
 */

#ifndef DEV_DEC_H
#define DEV_DEC_H

#include <stdint.h>

#include "sys/cb.h"
#include "sys/sem.h"

/* decimator semaphore */
extern sem_t dec_sem;

/** @brief decimation callback argument type */
typedef struct dec_cbarg {
    /**< number of samples */
    int num;
    /**< downsampled data for the I channel */
    float *i;
    /**< downsampled data for the Q channel */
    float *q; 
} dec_cbarg_t;

/** @brief decimator interrupt routine */
void Dec_DMA1C4Isr(void);

/**
 * @brief Initialize two decimator channels for I and Q data
 * 
 * @return int status code
 */
int Dec_Init(void);

/* perform filtration and decimation */

/**
 * @brief Perform data filtration & decimation using SINC^3 filter. Decimation 
 * rate is specifier by the #define DEC_DECIMATION_RATE
 * 
 * @param i input I data (signed numbers 12 bits wide)
 * @param q input Q data (signed numbers 12 bits wide)
 * @param num number of input samples
 * @param i_out normalized (full scale is from -1  to +1) and decimated I 
 *        channel data
 * @param q_out normalized/decimated Q channel data
 * @param cb callback to be called when the decimation is over
 * 
 * @return dec_cbarg_t * callback argument for sync calls, null for async calls
 */
dec_cbarg_t * Dec_Decimate(const int16_t *i, const int16_t *q, int num, 
    float *i_out,  float *q_out, cb_t cb);



#endif /* DEV_DEC_H */

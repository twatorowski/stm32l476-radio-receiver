/**
 * @file decq.h
 * 
 * @date 2019-11-04
 * @author twatorowski
 * 
 * @brief Decimator for the In-Phase channel. Applies low-pass filtering using 
 * CIC filter and then decimates by factor of 32.
 */

#ifndef DEV_DECQ_H_
#define DEV_DECQ_H_

#include <stdint.h>

#include "sys/cb.h"

/** @brief decimation dma interrupt */
void DecQ_DMA1C5Isr(void);

/**
 * @brief Initialize Quadrature channel decimator
 * 
 * @return int status code (@ref ERR_ERROR_CODES)
 */
int DecQ_Init(void);

/**
 * @brief Decimate the input 16-bit data by a factor of 32. Data obtained is 
 * represented in 32-bit words.
 * 
 * @param in input data pointer
 * @param out output data pointer
 * @param num number of samples to decimate
 * @param cb callback to call when the decimation is over
 * 
 * @return void * null pointer
 */
void * DecQ_Decimate(int16_t *in, int32_t *out, int num, cb_t cb);



#endif /* DEV_DECQ_H_ */

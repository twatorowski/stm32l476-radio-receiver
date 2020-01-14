/**
 * @file deci.h
 * 
 * @date 2019-11-04
 * @author twatorowski
 * 
 * @brief Decimator for the In-Phase channel. Applies low-pass filtering using 
 * CIC filter and then decimates by factor of 32.
 */

#ifndef DEV_DECI_H_
#define DEV_DECI_H_

#include <stdint.h>

#include "sys/cb.h"

/** @brief decimation dma interrupt */
void DecI_DMA1C4Isr(void);

/**
 * @brief Initialize In-Phase channel decimator
 * 
 * @return int status code (@ref ERR_ERROR_CODES)
 */
int DecI_Init(void);

/**
 * @brief Decimate the input 16-bit data by a factor of 32. Data obtained is 
 * represented in 32-bit words.
 * 
 * @param in input data pointer
 * @param num number of samples to decimate
 * @param out output data pointer
 * @param cb callback to call when the decimation is over
 * 
 * @return void * null pointer
 */
void * DecI_Decimate(const int16_t *in, int num, int32_t *out,  cb_t cb);



#endif /* DEV_DECI_H_ */

/**
 * @file sai1.h
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief Serial Audio Interface Driver Module. Uses channel 1A to send 24-bit 
 * audio data using left-justified mode. Clocked from PLLSAI1 running @ 16MHz.
 * Outputs ausio samples @ 31.25ksps. Mono.
 */

#ifndef DEV_SAI1A_H_
#define DEV_SAI1A_H_

#include <stdint.h>

#include "sys/sem.h"

/* sai1a access semaphore */
extern sem_t sai1a_sem;

/**
 * @brief Initialize SAI1A Audio Interface.
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int SAI1A_Init(void);

/**
 * @brief Start Streaming audio samples stored in the cricular buffer pointed 
 * by ptr that is `num` samples in size
 * 
 * @param sampling_rate desired sampling rate
 * @param ptr buffer pointer
 * @param num size of buffer expressed in number of samples
 */
void SAI1A_StartStreaming(float sampling_rate, const int32_t *ptr, int num);


#endif /* DEV_SAI1A_H_ */

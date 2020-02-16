/**
 * @file rfin.h
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief RF Input driver module
 */

#ifndef DEV_RFIN_H_
#define DEV_RFIN_H_

#include <stdint.h>

#include "sys/ev.h"

/** @name event types */
/** @{ */
/** @brief half transfer */
#define RFIN_TYPE_HT						0x01
/** @brief full transfer */
#define RFIN_TYPE_FT	                    0x02
/**@} */					

/** @brief rf samples ready event */
extern ev_t rfin_ev;

/** @brief samples ready event argument */
typedef struct rfin_evarg {
    /**< number of samples */
	int type, num;
    /**< samples pointer */
    int16_t *samples;
} rfin_evarg_t;

/** @brief adc dma1 interrupt */
void RFIn_DMA1C1Isr(void);

/**
 * @brief Initialize and prepare the main RF input. Initialize the ADC. For 
 * sampling rate configuration please see the config.h
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int RFIn_Init(void);

/**
 * @brief Starts sampling with the period given by the prescaled HCLK clock. 
 * After the sampling is started then the data containing events will be 
 * produced.
 * 
 * @param ptr pointer to the circular data buffer
 * @param num size of buffer expressed in number of elements.
 */
void RFIn_StartSampling(int16_t *ptr, int num);

#endif /* DEV_RFIN_H_ */

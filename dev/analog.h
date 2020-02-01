/**
 * @file analog.h
 * 
 * @date 2019-11-05
 * @author twatorowski
 * 
 * @brief ADC sampler driver module
 */

#ifndef DEV_ANALOG_H_
#define DEV_ANALOG_H_

#include <stdint.h>

#include "sys/ev.h"

/** @name event types */
/** @{ */
/** @brief half transfer */
#define ANALOG_TYPE_HT						0x01
/** @brief full transfer */
#define ANALOG_TYPE_FT	                    0x02
/**@} */					

/** @brief analog event */
extern ev_t analog_ev;

/** @brief analog event argument */
typedef struct {
    /**< number of samples */
	int num;
    /**< samples pointer */
    int16_t *samples;
} analog_evarg_t;

/** @name ADC Channels */
/** @{ */
#define ANALOG_CH0							0
#define ANALOG_CH1							1
#define ANALOG_CH2							2
#define ANALOG_CH3							3
#define ANALOG_CH4							4
#define ANALOG_CH5							5
#define ANALOG_CH6							6
#define ANALOG_CH7							7
#define ANALOG_CH8							8
#define ANALOG_CH9							9
#define ANALOG_CH10							10
#define ANALOG_CH11							11
#define ANALOG_CH12							12
#define ANALOG_CH13							13
#define ANALOG_CH14							14
#define ANALOG_CH15							15
#define ANALOG_CH16							16
#define ANALOG_CH17							17
#define ANALOG_CH18							18
/** @} */

/** @brief adc dma1 interrupt */
void Analog_DMA1C1Isr(void);

/**
 * @brief Initializes ADC sampler module.
 * 
 * @return int status (@err ERR_ERROR_CODES)
 */
int Analog_Init(void);

/**
 * @brief Starts sampling with the period given by the prescaled HCLK clock. 
 * After the sampling is started then the data containing events will be 
 * produced.
 * 
 * @param channel channel to be sampled.
 * @param pres prescaler value (sampling_clk = HCLK / pres)
 * @param ptr pointer to the circular data buffer
 * @param num size of buffer expressed in number of elements.
 */
void Analog_StartSampling(int channel, int pres, int16_t *ptr, int num);

#endif /* DEV_ANALOG_H_ */

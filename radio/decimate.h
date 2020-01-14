/**
 * @file decimate.h
 * 
 * @date 2020-01-14
 * @author twatorowski 
 * 
 * @brief Filter & Decimate both I and Q after the 1st mixer for the sake of 
 * processing efficiency along the signal path
 */

#ifndef RADIO_DECIMATE_H
#define RADIO_DECIMATE_H

#include <stdint.h>

/** @brief transfer callback */
typedef struct decimate_cbarg {
    /**< number of decimated samples */
    int num;
    /**< in-phase samples */
    int32_t *i;
    /**< quadrature samples */
    int32_t *q;
} decimate_cbarg_t;


/**
 * @brief Decimate data from both channels: Q and I. Decimation is done using 
 * CIC filter which causes a bit growth, hence the output data is held in 
 * int32_t type array.
 * 
 * @param i input in-phase samples array (16 bit signed numbers)
 * @param q input quadrature samples array (16 bit signed numbers)
 * @param num number of samples to decimate
 * @param i_dec place where to store decimated data for the I channel
 * @param q_dec place where to store decimated data for the Q channel
 * @param cb callback to call when the operation is over
 * 
 * @return decimate_cbarg_t * in case of the synchronous calls this will point 
 * to the callback argument that holds the output information.
 */
decimate_cbarg_t * Decimate_DecimateSamples(const int16_t *i, const int16_t *q, 
    int num, int32_t *i_dec, int32_t *q_dec, cb_t cb);

#endif /* RADIO_DECIMATE_H */

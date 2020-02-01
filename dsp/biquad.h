
/**
 * @file biquad.h
 * 
 * @date 2019-12-01
 * @author twatorowski 
 * 
 * @brief Biquadratic filter implementation. Uses Transposed form II.
 */

#ifndef DSP_BIQUAD_H_
#define DSP_BIQUAD_H_

/** @brief biquadratic filter taps */
typedef struct biquad_taps {
    /** denominator coefficients */
    float a1, a2;
    /** numerator taps */
    float b0, b1, b2;
} biquad_taps_t;

/** @brief biquadratic filter struct */
typedef struct biquad {
    /** delay line */
    float dl[2];
    /** pointer to the structure holding the taps */
    const biquad_taps_t *taps;
} biquad_t;

/**
 * @brief Set the new taps and reset the delay line.
 * 
 * @param bq filter to be set up.
 * @param taps pointer to taps structure or null if you just want to reset the 
 * delay line
 */
void BiQuad_SetTaps(biquad_t *bq, const biquad_taps_t *taps);

/**
 * @brief Apply Filtration using biquadratic IIR filter. Can work in-situ.
 * 
 * @param src data to be filtered
 * @param len length of data to be filtered
 * @param bq filter structure
 * @param dst pointer for the output data
 */
void BiQuad_Filter(const float *src, int len, biquad_t *bq, float *dst);

#endif /* DSP_BIQUAD_H */

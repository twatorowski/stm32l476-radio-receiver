/**
 * @file float_fixp.h
 * 
 * @date 2020-01-14
 * @author twatorowski 
 * 
 * @brief 
 */

#ifndef FLOAT_FIXP_H
#define FLOAT_FIXP_H

#include <stdint.h>

/**
 * @brief convert the floating point number array to 16-bit fixed point 
 * notation SQ1.15
 * 
 * @param in floating point number array that is about to be converted
 * @param out destination array for the fixed point SQ1.15 numbers
 * @param num number of values to convert
 * 
 */
void FloatFixp_FloatTo1SQ15(const float *in, int16_t *out, int num);

#endif /* FLOAT_FIXP_H */

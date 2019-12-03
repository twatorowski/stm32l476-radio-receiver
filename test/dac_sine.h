/**
 * @file dac_sine.h
 * 
 * @date 2019-10-28
 * @author twatorowski
 * 
 * @brief Test DAC output using sinusoidal signal
 */

#ifndef TEST_DAC_SINE_H_
#define TEST_DAC_SINE_H_

/**
 * @brief Start test, pump the sine wave into dac and start playback
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int TestDACSine_Init(void);

/**
 * @brief poll test logic
 */
void TestDACSine_Poll(void);

#endif /* TEST_DAC_SINE_H_ */

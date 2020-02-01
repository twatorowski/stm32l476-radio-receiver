/**
 * @file am_radio.h
 * 
 * @date 2020-01-19
 * @author twatorowski 
 * 
 * @brief Test for the signal path of a complete am radio receiver
 */

#ifndef TEST_AM_RADIO_H
#define TEST_AM_RADIO_H

/**
 * @brief Initialize the test.
 * 
 * @return int status code
 */
int TestAMRadio_Init(void);

/**
 * @brief Poll the test routine.
 */
void TestAMRadio_Poll(void);

#endif /* TEST_AM_RADIO_H */

/**
 * @file usart2.h
 * 
 * @date 2019-11-02
 * @author twatorowski
 * 
 * @brief Test for USART2. Does the echo using callbacks.
 */

#ifndef TEST_USART2_H_
#define TEST_USART2_H_

/**
 * @brief Initialize USART2 test. Start the USART2 in the loopback mode
 * 
 * @return int initialization status error code @ref ERR_ERROR_CODES
 */
int TestUSART2_Init(void);

/**
 * @brief Poll test logic
 */
void TestUSART2_Poll(void);

#endif /* TEST_USART2_H_ */

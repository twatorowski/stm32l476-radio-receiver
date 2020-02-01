/**
 * @file float_fixp.h
 * 
 * @date 2020-01-18
 * @author twatorowski 
 * 
 * @brief Test for the float-fixp conversion module
 */

#ifndef TEST_FLOAT_FIXP_H
#define TEST_FLOAT_FIXP_H

/**
 * @brief Perform module test
 * 
 * @return int initialization status error code @ref ERR_ERROR_CODES
 */
int TestFloatFixp_Init(void);

/**
 * @brief Poll test logic.
 */
void TestFloatFixp_Poll(void);

#endif /* TEST_FLOAT_FIXP_H */

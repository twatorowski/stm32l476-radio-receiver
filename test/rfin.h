/**
 * @file rfin.h
 * 
 * @date 2020-02-13
 * @author twatorowski 
 * 
 * @brief Test for RFIn module
 */

#ifndef TEST_RFIN_H
#define TEST_RFIN_H

/**
 * @brief Test the RFIn module. Start sampling, measure the time difference 
 * between the calls.
 * 
 * @return int 
 */
int TestRFIn_Init(void);

/**
 * @brief Poll test logic.
 */
void TestRFIn_Poll(void);


#endif /* TEST_RFIN_H */

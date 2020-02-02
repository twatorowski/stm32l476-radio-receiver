/**
 * @file dynamic_int.h
 * 
 * @date 2020-02-02
 * @author twatorowski 
 * 
 * @brief Test for dynamic interrupts level changing
 */

#ifndef TEST_DYNAMIC_INT_H
#define TEST_DYNAMIC_INT_H

/** @brief lcd interrupt - high level one */
void TestDynInt_LCDIsr(void);

/**
 * @brief Initialize test
 * 
 * @return int status
 */
int TestDynInt_Init(void);


#endif /* TEST_DYNAMIC_INT_H */

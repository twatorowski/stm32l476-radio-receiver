/**
 * @file rf_dec.h
 * 
 * @date 2020-02-15
 * @author twatorowski 
 * 
 * @brief Test the RF sampler with conjunction with decimation unit
 */

#ifndef TEST_RF_DEC_H
#define TEST_RF_DEC_H

/* test the rf + decimators */
int TestRFDec_Init(void);

/* poll the decimation test */
void TestRFDec_Poll(void);

#endif /* RF_DEC_H */

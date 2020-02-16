/**
 * @file rf_dec_usb.h
 * 
 * @date 2020-02-15
 * @author twatorowski 
 * 
 * @brief Test for RF + Decimator + USB
 */

#ifndef RF_DEC_USB_H
#define RF_DEC_USB_H

/* test the rf + decimators */
int TestRFDecUSB_Init(void);
/* poll the decimation test */
void TestRFDecUSB_Poll(void);

#endif /* RF_DEC_USB_H */

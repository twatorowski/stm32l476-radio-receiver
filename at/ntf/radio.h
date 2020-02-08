/**
 * @file radio.h
 * 
 * @date 2020-02-05
 * @author twatorowski 
 * 
 * @brief AT Notifications: Radio.
 */

#ifndef AT_NTF_RADIO_H
#define AT_NTF_RADIO_H


/* initialize radio notifications submodule */
int ATNtfRadio_Init(void);
/* poll radio notifications submodule */
void ATNtfRadio_Poll(void);
/* store the iq data samples in at notifications buffer */
int ATNtfRadio_PutIQSamples(const float *i, const float *q, int num);

#endif /* AT_NTF_RADIO_H */

/**
 * @file vcp.h
 * 
 * @date 2020-02-10
 * @author twatorowski 
 * 
 * @brief Test for virtual COM port connection and data exchange
 */

#ifndef TEST_VCP_H
#define TEST_VCP_H

/* initialize virtual com port test */
int TestVCP_Init(void);
/* polling */
void TestVCP_Poll(void);


#endif /* TEST_VCP_H */

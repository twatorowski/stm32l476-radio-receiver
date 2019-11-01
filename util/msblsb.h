/**
 * @file msblsb.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Macro helpers for determining lsb/msb of provided words
 */

#ifndef UTIL_MSBLSB_H_
#define UTIL_MSBLSB_H_

/* msb macro */
#define MSB0(x)						((x) ? 0 : -1)
#define MSB1(x)						((x) > 0x0001 ?  1 + MSB0((x) >>  1) : MSB0(x))
#define MSB2(x)						((x) > 0x0003 ?  2 + MSB1((x) >>  2) : MSB1(x))
#define MSB3(x)						((x) > 0x000f ?  4 + MSB2((x) >>  4) : MSB2(x))
#define MSB4(x)						((x) > 0x00ff ?  8 + MSB3((x) >>  8) : MSB3(x))

/** @brief get the msb for the x word */
#define MSB(x)						((x) > 0xffff ? 16 + MSB4((x) >> 16) : MSB4(x))

/* lsb macro */
#define LSB0(x)						((x) ? 0 : -32)
#define LSB1(x)						((x) & 0x0001 ? LSB0(x) :  1 + LSB0((x) >>	1))
#define LSB2(x)						((x) & 0x0003 ? LSB1(x) :  2 + LSB1((x) >>	2))
#define LSB3(x)						((x) & 0x000f ? LSB2(x) :  4 + LSB2((x) >>	4))
#define LSB4(x)						((x) & 0x00ff ? LSB3(x) :  8 + LSB3((x) >>	8))

/** @brief get the lsb for the x word */
#define LSB(x)						((x) & 0xffff ? LSB4(x) : 16 + LSB4((x) >> 16))


#endif /* UTIL_MSBLSB_H_ */

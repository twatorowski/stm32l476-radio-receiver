
/**
 * @file bit.h
 * 
 * @date 2020-07-10
 * @author twatorowski 
 * 
 * @brief Bit operation macros, use with care
 */

#ifndef UTIL_BIT_H
#define UTIL_BIT_H

/** @bit value */
#define BIT_VAL(bit)                    (1UL << (bit))
/** @brief bit set */
#define BIT_SET(x, bit)                 ((x) |  (1 << (bit)))
/** @brief bit clear */
#define BIT_CLR(x, bit)                 ((x) & ~(1 << (bit)))
/** @brief bit write (at given position) */
#define BIT_WR(x, bit, val)            \
    ((val) ? BIT_SET((x), (bit)) : BIT_CLR((x), (bit)))
/** @brief bit read */
#define BIT_RD(x, bit)                  (!!(x & (1 << (bit))))

#endif /* UTIL_BIT_H */

/**
 * @file abs.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-25
 * 
 * @brief Naive macro for the absolute value calculation
 */
#ifndef _UTIL_ABS_H
#define _UTIL_ABS_H

/** calculate absolute value  */
#define abs(x)                                      ((x) < 0 ? -(x) : (x))


#endif /* _UTIL_ABS_H */

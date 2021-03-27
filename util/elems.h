/**
 * @file elems.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Macro helper for determining the number of array elements
 */

#ifndef UTIL_ELEMS_H_
#define UTIL_ELEMS_H_

/** @brief number of array elems */
#define elems(x)                                (sizeof(x) / (sizeof(x[0])))

#endif /* UTIL_ELEMS_H_ */

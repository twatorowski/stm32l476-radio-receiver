/**
 * @file concatstr.h
 * 
 * @date 2019-11-03
 * @author twatorowski
 * 
 * @brief Macro for concatenating strings
 */

#ifndef UTIL_CONCATSTR_H_
#define UTIL_CONCATSTR_H_

/* this is a helper to covert numbers to strings */
#define _CONCATSTR(x)                       #x
#define CONCATSTR(x)                        _CONCATSTR(x)

#endif /* UTIL_CONCATSTR_H_ */

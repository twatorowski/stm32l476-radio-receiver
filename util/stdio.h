/**
 * @file stdio.h
 *
 * @date 2019-09-13
 * @author twatorowski
 *
 * @brief Simple yet functional string print scan utilities
 */

#ifndef UTIL_STDIO_H_
#define UTIL_STDIO_H_

#include <stddef.h>

/**
 * @brief checks whether the character is a decimal digit.
 * 
 * @param x character to check
 * 
 * @return int 1 - character is a decimal digit, 0 - it's not.
 */
int isdigit(int c);

/**
 * @brief Checks whether the character is a hex digit. 
 * 
 * @param c character to check
 * 
 * @return int 1 - character is a hex digit, 0 - it's not.
 */
int isxdigit(int c);

/**
 * @brief Checks if character is a whitespace.
 * 
 * @param c character to check
 * 
 * @return int 1 - character is a whitespace, 0 - it's not.
 */
int isspace(int c);


/**
 * @brief Converts character to lowercase if its a valid letter.
 * 
 * @param c letter to convert
 * 
 * @return int lowercase version of the letter
 */
int tolower(int c);

/**
 * @brief Converts character to uppercase if its a valid letter.
 * 
 * @param c letter to convert
 * 
 * @return int uppercase version of the letter
 */
int toupper(int c);

/**
 * @brief Simplified snprintf implementation as known from the stdio.h. Supports 
 * printing: chars, strings, integers (of different size), floating point 
 * numbers (doubles only).
 * 
 * @param out pointer to where to print to
 * @param size maximal size of the print
 * @param fmt formatting string 
 * @param ... arguments to be printed
 * 
 * @return int number of characters printed
 */
int snprintf(char *out, size_t size, const char *fmt, ...);

/**
 * @brief Simplified sprintf implementation as known from the stdio.h. Supports 
 * printing: chars, strings, integers (of different size), floating point 
 * numbers (doubles only).
 * 
 * @param out pointer to where to print to
 * @param fmt formatting string 
 * @param ... arguments to be printed
 * 
 * @return int number of characters printed
 */
int sprintf(char *out, const char *fmt, ...);


/**
 * @brief Simplified sscanf with additional size parameter for improved safety.
 * Uses the same formating string conventions as snprintf, so if you would like 
 * to scan the string of 40 chars max and discard the result you would write:
 * "%*.40s" <- width is *, so denotes the result drop, precision is .40 so max 
 * 40 chars will be scanned.
 * 
 * @param str string to scan
 * @param size size of the string to scan
 * @param format formatting string
 * @param ... pointers to places where to store the scanning results 
 * 
 * @return int number of successful matches.
 */
int snscanf(const char *str, size_t size, const char *format, ...);


/**
 * @brief Simplified sscanf. Uses the same formating string conventions as 
 * snprintf, so if you would like to scan the string of 40 chars max and discard 
 * the result you would write: "%*.40s" <- width is *, so denotes the result 
 * drop, precision is .40 so max 40 chars will be scanned.
 * 
 * @param str string to scan
 * @param size size of the string to scan
 * @param format formatting string
 * @param ... pointers to places where to store the scanning results 
 * 
 * @return int number of successful matches.
 */
int sscanf(const char *str, const char *format, ...);

#endif /* UTIL_STDIO_H_ */

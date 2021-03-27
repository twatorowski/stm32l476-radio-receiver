/**
 * @file string.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief String manipulation functions
 */

#ifndef UTIL_STRING_H_
#define UTIL_STRING_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Compare two memory regions
 *
 * @param ptr1 pointer to the first memory region
 * @param ptr2 pointer to the second memory region
 * @param num number of bytes to be compared
 *
 * @return 0 if regions contain the same data, non-0 otherwise
 */
int memcmp(const void *ptr1, const void *ptr2, size_t num);

/**
 * @brief Copy @p num bytes of data from @p src memory region to @p dst region
 *
 * @param dst destination pointer
 * @param src source pointer
 * @param num number of bytes to be copied
 *
 * @return destination pointer
 */
void * memcpy(void *dst, const void *src, size_t num);

/**
 * @brief Set the memory contents (byte-by-byte) of the memory region pointer by
 * @p ptr to value @p value
 *
 * @param ptr pointer to the destination memory region
 * @param value value to be written (byte)
 * @param num number of bytes to be set to @p value
 *
 * @return ptr address
 */
void * memset(void *ptr, int value, size_t num);

/**
 * @brief Get the length of the '\0'-terminated string
 *
 * @param ptr pointer to the string
 *
 * @return length of the string (excluding the '\0' termination)
 */
size_t strlen(const char *ptr);

/**
 * @brief Get the length of the '\0'-terminated string that is assumed to be no
 * longer than @p max_len bytes
 *
 * @param ptr pointer to the string
 * @param max_len maximal assumed length of string
 *
 * @return length of the string (excluding the '\0' termination) or max_len whichever
 * is smaller
 */
size_t strnlen(const char *ptr, size_t max_len);

/**
 * @brief Compare two '\0'-terminated strings.
 *
 * @param s1 pointer to the 1st string
 * @param s2 pointer to the 2nd string
 *
 * @return the difference of the lastly compared characters, so 0 is returned if both
 * strings are equal. Non-zero values means that the strings differ.
 */
int strcmp(const char *s1, const char *s2);

/**
 * @brief Copy @p src string to the @p dst
 *
 * @param dst destination pointer, please ensure that it points to the memory region
 * that is long enough to hold the string pointed by the @p src
 * @param src source string pointer
 *
 * @return pointer to the destination string
 */
char * strcpy(char *dst, const char *src);

/**
 * @brief Copy @p src string to the @p dst. Number of bytes copied is never greater
 * than @p size. If the @p src string is shorter than @p size then the remaining space
 * in @p dst is filled with zeros
 *
 * @param dst destination pointer, please ensure that it points to the memory region
 * that is long enough to hold the string of length @p size
 * @param src source string pointer
 * @param size maximal number of bytes to copy
 *
 * @return pointer to the destination string
 */
char * strncpy(char *dst, const char *src, size_t size);

#endif /* UTIL_STRING_H_ */

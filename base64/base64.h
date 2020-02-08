/**
 * @file base64.h
 * 
 * @date 2019-11-27
 * @author twatorowski 
 * 
 * @brief Base64 encoding/decoding functions.
 */

#ifndef BASE64_BASE64_H_
#define BASE64_BASE64_H_

#include <stddef.h>

/* encode with base64 */

/**
 * @brief Encode the input data with Base64 encoding. The algorithm works 
 * backwards to make the in-situ operation possible if needed.
 * 
 * @param in input data pointer
 * @param in_size size of the input data
 * @param out output data pointer
 * @param out_size maximal size of the output buffer
 * 
 * @return int actual encoded data size
 */
int Base64_Encode(const void *in, size_t in_size, void *out, size_t out_size);
/* decode base64 string */

/**
 * @brief Decode the provided Base64 string. Can work in-situ.
 * 
 * @param in pointer to Base64 encoded data
 * @param in_size size of the input data
 * @param out 
 * @param out_size 
 * 
 * @return int 
 */
int Base64_Decode(const void *in, size_t in_size, void *out, size_t out_size);

#endif /* BASE64_BASE64_H_ */

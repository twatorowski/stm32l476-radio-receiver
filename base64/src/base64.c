/**
 * @file base64.c
 * 
 * @date 2019-11-27
 * @author twatorowski 
 * 
 * @brief Base64 encoding/decoding functions.
 */

#include <stddef.h>
#include <stdint.h>

#include "compiler.h"
#include "err.h"

/* encoding */
static const uint8_t enc[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

/* decoder array (offset by '+') */
static const uint8_t dec[] = {
    62, 64, 64, 64, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64,
    64, 64, 0,	64, 64, 64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    64, 64, 64, 64, 64, 64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
};

/* encode with base64 */
int OPTIMIZE("Os") Base64_Encode(const void *in, size_t in_size, void *out, 
    size_t out_size)
{
    /* number of whole words to process. word is a register that holds 24 bits 
     * of input data that we are about to convert to base 64 representation */
    int word_cnt = (in_size + 2) / 3;
    /* number of bytes that do not constitute the full word */
    int remainder = in_size % 3;
    /* move the input pointer so that it points at last valid 24-word of data */
    const uint8_t *inp = (const uint8_t *)in + (word_cnt - 1) * 3;
    /* output pointer shall point at last word to be written */
    uint8_t *outp = (uint8_t *)out + (word_cnt - 1) * 4;
    /* packing register */
    register uint32_t value;

    /* sanity check for the output/input size */
    if (word_cnt * 4 > out_size || !in_size)
        return EFATAL;

    /* got remaining data to pack? */
    if (remainder) {
        /* pack last remaining bytes */
        value = inp[0] << 16 | (remainder > 1 ? inp[1] << 8 : 0);
        /* at least two charactes must be produced */
        outp[0] = enc[(value >> 18) & 0x3f];
        outp[1] = enc[(value >> 12) & 0x3f];
        /* trailing '=' go here */
        outp[2] = remainder > 1 ? enc[(value >> 6) & 0x3f] : '=';
        outp[3] = '=';
        /* adjust pointers */
        inp -= 3, outp -= 4;
    }
    
    /* pack the data backwards */
    for (; (uintptr_t)inp >= (uintptr_t)in; inp -= 3, outp -= 4) {
        /* pack value */
        value = inp[0] << 16 | inp[1] << 8 | inp[2] << 0;
        /* encode */
        outp[0] = enc[(value >> 18) & 0x3f];
        outp[1] = enc[(value >> 12) & 0x3f];
        outp[2] = enc[(value >>  6) & 0x3f];
        outp[3] = enc[(value >>  0) & 0x3f];
    }

    /* return the number of bytes written */
    return word_cnt * 4;
}

/* decode base 64-string */
int OPTIMIZE("Os") Base64_Decode(const void *in, size_t in_size, void *out, 
    size_t out_size)
{
    /* number of base64 4-character words */
    int word_cnt = in_size / 4, remainder = in_size % 4;
    /* last word may be incomplete (trailing '=') */
    int last_word_len = 3;
    /* pointers */
    const uint8_t *inp = in; uint8_t *outp = out;
    /* packing register */
    register uint32_t value;

    /* '=' is a trailing character? */
    if (*(inp + in_size - 1) == '=') last_word_len--;
    if (*(inp + in_size - 2) == '=') last_word_len--;
    /* size sanity checks */
    if (!in_size || remainder || out_size < (word_cnt-1) * 3 + last_word_len)
        return EFATAL;

    /* process all but last word */
    while (1) {
        /* decode */
        value  = dec[*inp++ - '+'] << 18;
        value |= dec[*inp++ - '+'] << 12;
        value |= dec[*inp++ - '+'] <<  6;
        value |= dec[*inp++ - '+'] <<  0;
        /* break the loop on the last word */
        if (word_cnt-- <= 1)
            break;
        /* unpack */
        *outp++ = value >> 16, *outp++ = value >> 8, *outp++ = value >>	0;
    }

    /* '=' are automatically decoded as zeros */
    if (last_word_len > 0) *outp++ = value >> 16;
    if (last_word_len > 1) *outp++ = value >> 8;
    if (last_word_len > 2) *outp++ = value >> 0;

	/* report the number of bytes */
	return outp - (uint8_t *)out;
}

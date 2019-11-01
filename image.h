/**
 * @file image.h
 * 
 * @date 2019-09-20
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief Binary Image header
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>
#include <stddef.h>

#include "version.h"

/** @brief image header signature used to tell whether we are dealing with a 
 * valid image header. Also can be used to tell the version of the header */
#define IMGHDR_SIGNATURE_V1                       0xABCD1234


/** @brief type that represents the whole binary image header*/
typedef struct image_header {
    /* signature denoting that this is in fact a header */
    uint32_t signature, signature_neg;
    /* complete image size, address to which to put the image */
    uint32_t size, addr;
    /* hardware version for which this image is meant */
    version_t hw_ver;
    /* software version of this image */
    version_t sw_ver;
    /* offset of the checksum placeholder w.r.t this image header in octets */
    int32_t checksum_offs;
} image_header_t;

/* checksum type */
typedef struct image_checksum {
    /* checksum */
    uint8_t checksum[32];
} image_checksum_t;

#endif /* IMAGE_H_ */

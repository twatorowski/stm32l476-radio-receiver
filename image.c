/**
 * @file image.c
 * 
 * @date 2019-09-20
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief Firmware binary image related data
 */

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "image.h"
#include "linker.h"
#include "version.h"

/* checksum. left empty you may want to put some checksum information like 
 * md5 using the objcopy utility that allows to put data under certain 
 * sections in the *.elf file. */
SECTION(".image_checksum") image_checksum_t image_checksum = {
        .checksum = { 0 }
};

/* image header itself */
SECTION(".image_header") image_header_t image_header = {
    /* add signature and it's negation */
    .signature = IMGHDR_SIGNATURE_V1, .signature_neg = ~IMGHDR_SIGNATURE_V1,
    /* store the complete binary image size */
    .size = (uint32_t)&__flash_image_size,
    /* load address */
    .addr = (uint32_t)&__flash_code_addr,
    
    /* hardware version */
    .hw_ver = { .build = VERSION_HW_BUILD, .minor = VERSION_HW_MINOR, 
        .major = VERSION_SW_MAJOR },
    /* software version */
    .sw_ver = { .build = VERSION_SW_BUILD, .minor = VERSION_SW_MINOR,
        .major = VERSION_SW_MAJOR },

    /* store the checksum offset */
    .checksum_offs = (int32_t)&__image_checksum_offs,
};


/**
 * @file linker.h
 *
 * @date 23.06.2019
 * @author twatorowski (tw@mightydevices.com)
 *
 * @brief Linker defined symbols
 */

#ifndef LINKER_H_
#define LINKER_H_

#include <stdint.h>

/* basic memory layout: SRAM */
extern uintptr_t __sram_size, __sram_addr;
/* basic memory layout: SRAM2 */
extern uintptr_t __sram2_size, __sram2_addr;
/* basic memory layout: FLASH */
extern uintptr_t __flash_size, __flash_addr;


/* initial stack pointer */
extern uintptr_t __stack;

/* flash vectors address */
extern uintptr_t __flash_vectors;
/* total code size and it's initial position */
extern uintptr_t __flash_code_addr, __flash_code_size;
/* complete flash image size (code + data initializers) */
extern uintptr_t __flash_image_size;

/* data initialization by flash stored data */
/* source address */
extern uintptr_t __flash_sram_init_src_addr;
/* destination addresses inside the sections */
extern uintptr_t __ram_code_addr, __data_addr, __data2_addr;
/* size */
extern uintptr_t __ram_code_size, __data_size, __data2_size;

/* data initialization by zeroing out */
/* bss section */
extern uintptr_t __bss_addr, __bss_size, __bss2_addr, __bss2_size;

/* image header stuff */
/* address of the header and the checksum section */
extern uintptr_t __image_header_addr, __image_checksum_addr;
/* offset between the two above */
extern uintptr_t __image_checksum_offs;


#endif /* LINKER_H_ */

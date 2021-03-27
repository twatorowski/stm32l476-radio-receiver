/**
 * @file linker.h
 *
 * @date 23.06.2019
 * @author twatorowski (tw@mightydevices.com)
 *
 * @brief Linker defined symbols. These are kept as 'char' so that the optimizer 
 * does not think that the addresses are in any way aligned.
 */

#ifndef LINKER_H_
#define LINKER_H_

/* basic memory layout: SRAM */
extern char __sram_size, __sram_addr;
/* basic memory layout: FLASH */
extern char __flash_size, __flash_addr;


/* initial stack pointer */
extern char __stack;

/* flash vectors address */
extern char __flash_vectors;
/* total code size and it's initial position */
extern char __flash_code_addr, __flash_code_size;
/* complete flash image size (code + data initializers) */
extern char __flash_image_size;

/* flash storage size */
extern char __flash_strg_addr, __flash_strg_size;

/* data initialization by flash stored data */
/* source address */
extern char __flash_sram_init_src_addr;
/* destination addresses inside the sections */
extern char __ram_code_addr, __data_addr;
/* size */
extern char __ram_code_size, __data_size;

/* data initialization by zeroing out */
/* bss section */
extern char __bss_addr, __bss_size;



#endif /* LINKER_H_ */

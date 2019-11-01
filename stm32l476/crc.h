/**
 * @file crc.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: CRC
 */

#ifndef STM32L476_CRC_H_
#define STM32L476_CRC_H_

#include "stm32l476/stm32l476.h"

/* crc register base */
#define CRC_BASE							(0x40023000)
/* crc registers base address */
#define CRC									((crc_t *)CRC_BASE)

/* crc registers */
typedef struct {
	reg32_t DR;
	reg32_t IDR;
	reg32_t CR;
	reg32_t RESERVED2;
	reg32_t INIT;
	reg32_t POL;
} __attribute__((packed, aligned(4))) crc_t;

/*	Bit definition for CRC_DR register	*/
#define CRC_DR_DR							(0xFFFFFFFF)

/*	Bit definition for CRC_IDR register  */
#define CRC_IDR_IDR							(0xFF)

/*	Bit definition for CRC_CR register	*/
#define CRC_CR_RESET						(0x00000001)
#define CRC_CR_POLYSIZE						(0x00000018)
#define CRC_CR_POLYSIZE_0					(0x00000008)
#define CRC_CR_POLYSIZE_1					(0x00000010)
#define CRC_CR_REV_IN						(0x00000060)
#define CRC_CR_REV_IN_0						(0x00000020)
#define CRC_CR_REV_IN_1						(0x00000040)
#define CRC_CR_REV_OUT						(0x00000080)

/*	Bit definition for CRC_INIT register  */
#define CRC_INIT_INIT						(0xFFFFFFFF)

/*	Bit definition for CRC_POL register  */
#define CRC_POL_POL							(0xFFFFFFFF)

#endif /* STM32L476_CRC_H_ */

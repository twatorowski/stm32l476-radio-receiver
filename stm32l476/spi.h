/**
 * @file spi.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: SPI
 */

#ifndef STM32L476_SPI_H_
#define STM32L476_SPI_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define SPI1_BASE							0x40013000
#define SPI2_BASE							0x40003800
#define SPI3_BASE							0x40003C00

/* spis */
#define SPI1								((spi_t *) SPI1_BASE)
#define SPI2								((spi_t *) SPI2_BASE)
#define SPI3								((spi_t *) SPI3_BASE)

/* spi registers */
typedef struct {
	reg32_t CR1;
	reg32_t CR2;
	reg32_t SR;
	reg32_t DR;
	reg32_t CRCPR;
	reg32_t RXCRCR;
	reg32_t TXCRCR;
} __attribute__((packed, aligned(4))) spi_t;

/*	Bit definition for SPI_CR1 register  */
#define SPI_CR1_CPHA						(0x00000001)
#define SPI_CR1_CPOL						(0x00000002)
#define SPI_CR1_MSTR						(0x00000004)
#define SPI_CR1_BR							(0x00000038)
#define SPI_CR1_BR_0						(0x00000008)
#define SPI_CR1_BR_1						(0x00000010)
#define SPI_CR1_BR_2						(0x00000020)
#define SPI_CR1_SPE							(0x00000040)
#define SPI_CR1_LSBFIRST					(0x00000080)
#define SPI_CR1_SSI							(0x00000100)
#define SPI_CR1_SSM							(0x00000200)
#define SPI_CR1_RXONLY						(0x00000400)
#define SPI_CR1_CRCL						(0x00000800)
#define SPI_CR1_CRCNEXT						(0x00001000)
#define SPI_CR1_CRCEN						(0x00002000)
#define SPI_CR1_BIDIOE						(0x00004000)
#define SPI_CR1_BIDIMODE					(0x00008000)

/*	Bit definition for SPI_CR2 register  */
#define SPI_CR2_RXDMAEN						(0x00000001)
#define SPI_CR2_TXDMAEN						(0x00000002)
#define SPI_CR2_SSOE						(0x00000004)
#define SPI_CR2_NSSP						(0x00000008)
#define SPI_CR2_FRF							(0x00000010)
#define SPI_CR2_ERRIE						(0x00000020)
#define SPI_CR2_RXNEIE						(0x00000040)
#define SPI_CR2_TXEIE						(0x00000080)
#define SPI_CR2_DS							(0x00000F00)
#define SPI_CR2_DS_0						(0x00000100)
#define SPI_CR2_DS_1						(0x00000200)
#define SPI_CR2_DS_2						(0x00000400)
#define SPI_CR2_DS_3						(0x00000800)
#define SPI_CR2_FRXTH						(0x00001000)
#define SPI_CR2_LDMARX						(0x00002000)
#define SPI_CR2_LDMATX						(0x00004000)

/*	Bit definition for SPI_SR register	*/
#define SPI_SR_RXNE							(0x00000001)
#define SPI_SR_TXE							(0x00000002)
#define SPI_SR_CHSIDE						(0x00000004)
#define SPI_SR_UDR							(0x00000008)
#define SPI_SR_CRCERR						(0x00000010)
#define SPI_SR_MODF							(0x00000020)
#define SPI_SR_OVR							(0x00000040)
#define SPI_SR_BSY							(0x00000080)
#define SPI_SR_FRE							(0x00000100)
#define SPI_SR_FRLVL						(0x00000600)
#define SPI_SR_FRLVL_0						(0x00000200)
#define SPI_SR_FRLVL_1						(0x00000400)
#define SPI_SR_FTLVL						(0x00001800)
#define SPI_SR_FTLVL_0						(0x00000800)
#define SPI_SR_FTLVL_1						(0x00001000)

/*	Bit definition for SPI_DR register	*/
#define SPI_DR_DR							(0x0000FFFF)

/*	Bit definition for SPI_CRCPR register  */
#define SPI_CRCPR_CRCPOLY					(0x0000FFFF)

/*	Bit definition for SPI_RXCRCR register	*/
#define SPI_RXCRCR_RXCRC					(0x0000FFFF)

/*	Bit definition for SPI_TXCRCR register	*/
#define SPI_TXCRCR_TXCRC					(0x0000FFFF)

#endif /* STM32L476_SPI_H_ */

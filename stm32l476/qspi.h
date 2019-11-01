/**
 * @file qspi.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: QSPI
 */

#ifndef STM32L476_QSPI_H_
#define STM32L476_QSPI_H_

#include "stm32l476/stm32l476.h"

/* quad spi register base */
#define QSPI_BASE							(0xA0001000)
/* quad spi registers base address */
#define QSPI								((qspi_t *)QSPI_BASE)

/* registers */
typedef struct {
	reg32_t CR;
	reg32_t DCR;
	reg32_t SR;
	reg32_t FCR;
	reg32_t DLR;
	reg32_t CCR;
	reg32_t AR;
	reg32_t ABR;
	reg32_t DR;
	reg32_t PSMKR;
	reg32_t PSMAR;
	reg32_t PIR;
	reg32_t LPTR;
} __attribute__((packed, aligned(4))) qspi_t;

/*	Bit definition for QSPI_CR register  */
#define QSPI_CR_PRESCALER					0xFF000000
#define QSPI_CR_PMM							0x00800000
#define QSPI_CR_APMS						0x00400000
#define QSPI_CR_TOIE						0x00100000
#define QSPI_CR_SMIE						0x00080000
#define QSPI_CR_FTIE						0x00040000
#define QSPI_CR_TCIE						0x00020000
#define QSPI_CR_TEIE						0x00010000
#define QSPI_CR_FTHRES						0x00000f00
#define QSPI_CR_SSHIFT						0x00000010
#define QSPI_CR_TCEN						0x00000008
#define QSPI_CR_DMAEN						0x00000004
#define QSPI_CR_ABORT						0x00000002
#define QSPI_CR_EN							0x00000001

/*	Bit definition for QSPI_DCR register  */
#define QSPI_DCR_FSIZE						0x001f0000
#define QSPI_DCR_CSHT						0x00000700
#define QSPI_DCR_CKMODE						0x00000001

/*	Bit definition for QSPI_SR register  */
#define QSPI_SR_FLEVEL						0x00003f00
#define QSPI_SR_BUSY						0x00000020
#define QSPI_SR_TOF							0x00000010
#define QSPI_SR_SMF							0x00000008
#define QSPI_SR_FTF							0x00000004
#define QSPI_SR_TCF							0x00000002
#define QSPI_SR_TEF							0x00000001

/*	Bit definition for QSPI_FCR register  */
#define QSPI_FCR_CTOF						0x00000010
#define QSPI_FCR_CSMF						0x00000008
#define QSPI_FCR_CTCF						0x00000002
#define QSPI_FCR_CTEF						0x00000001

/*	Bit definition for QSPI_DLR register  */
#define QSPI_DLR_DL							0xFFFFFFFF

/*	Bit definition for QSPI_CCR register  */
#define QSPI_CCR_DDRM						0x80000000
#define QSPI_CCR_SIOO						0x10000000
#define QSPI_CCR_FMODE						0x0C000000
#define QSPI_CCR_DMODE						0x03000000
#define QSPI_CCR_DCYC						0x007C0000
#define QSPI_CCR_ABSIZE						0x00030000
#define QSPI_CCR_ABMODE						0x0000C000
#define QSPI_CCR_ADSIZE						0x00003000
#define QSPI_CCR_ADMODE						0x00000C00
#define QSPI_CCR_IMODE						0x00000300
#define QSPI_CCR_INSTRUCTION				0x00000000

/*	Bit definition for QSPI_AR register  */
#define QSPI_AR_ADDRESS						0xFFFFFFFF

/*	Bit definition for QSPI_ABR register  */
#define QSPI_ABR_ALTERNATE					0xFFFFFFFF

/*	Bit definition for QSPI_DR register  */
#define QSPI_DR_DATA						0xFFFFFFFF

/*	Bit definition for QSPI_PSMKR register	*/
#define QSPI_PSMKR_MASK						0xFFFFFFFF

/*	Bit definition for QSPI_PSMAR register	*/
#define QSPI_PSMAR_MATCH					0xFFFFFFFF

/*	Bit definition for QSPI_PIR register  */
#define QSPI_PIR_INTERVAL					0x0000FFFF

/*	Bit definition for QSPI_LPTR register  */
#define QSPI_LPTR_TIMEOUT					0x0000FFFF

#endif /* STM32L476_QSPI_H_ */

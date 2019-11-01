/**
 * @file i2c.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: I2C
 */

#ifndef STM32L476_I2C_H_
#define STM32L476_I2C_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define I2C1_BASE							(0x40005400)
#define I2C2_BASE							(0x40005800)
#define I2C3_BASE							(0x40005C00)

/* i2c units */
#define I2C1								((i2c_t *) I2C1_BASE)
#define I2C2								((i2c_t *) I2C2_BASE)
#define I2C3								((i2c_t *) I2C3_BASE)

/* i2c registers */
typedef struct {
	reg32_t CR1;
	reg32_t CR2;
	reg32_t OAR1;
	reg32_t OAR2;
	reg32_t TIMINGR;
	reg32_t TIMEOUTR;
	reg32_t ISR;
	reg32_t ICR;
	reg32_t PECR;
	reg32_t RXDR;
	reg32_t TXDR;
} __attribute__((packed, aligned(4))) i2c_t;

/*	Bit definition for I2C_CR1 register  */
#define I2C_CR1_PE							(0x00000001)
#define I2C_CR1_TXIE						(0x00000002)
#define I2C_CR1_RXIE						(0x00000004)
#define I2C_CR1_ADDRIE						(0x00000008)
#define I2C_CR1_NACKIE						(0x00000010)
#define I2C_CR1_STOPIE						(0x00000020)
#define I2C_CR1_TCIE						(0x00000040)
#define I2C_CR1_ERRIE						(0x00000080)
#define I2C_CR1_DNF							(0x00000F00)
#define I2C_CR1_ANFOFF						(0x00001000)
#define I2C_CR1_SWRST						(0x00002000)
#define I2C_CR1_TXDMAEN						(0x00004000)
#define I2C_CR1_RXDMAEN						(0x00008000)
#define I2C_CR1_SBC							(0x00010000)
#define I2C_CR1_NOSTRETCH					(0x00020000)
#define I2C_CR1_WUPEN						(0x00040000)
#define I2C_CR1_GCEN						(0x00080000)
#define I2C_CR1_SMBHEN						(0x00100000)
#define I2C_CR1_SMBDEN						(0x00200000)
#define I2C_CR1_ALERTEN						(0x00400000)
#define I2C_CR1_PECEN						(0x00800000)

/*	Bit definition for I2C_CR2 register  */
#define I2C_CR2_SADD						(0x000003FF)
#define I2C_CR2_RD_WRN						(0x00000400)
#define I2C_CR2_ADD10						(0x00000800)
#define I2C_CR2_HEAD10R						(0x00001000)
#define I2C_CR2_START						(0x00002000)
#define I2C_CR2_STOP						(0x00004000)
#define I2C_CR2_NACK						(0x00008000)
#define I2C_CR2_NBYTES						(0x00FF0000)
#define I2C_CR2_RELOAD						(0x01000000)
#define I2C_CR2_AUTOEND						(0x02000000)
#define I2C_CR2_PECBYTE						(0x04000000)

/*	Bit definition for I2C_OAR1 register  */
#define I2C_OAR1_OA1						(0x000003FF)
#define I2C_OAR1_OA1MODE					(0x00000400)
#define I2C_OAR1_OA1EN						(0x00008000)

/*	Bit definition for I2C_OAR2 register  */
#define I2C_OAR2_OA2						(0x000000FE)
#define I2C_OAR2_OA2MSK						(0x00000700)
#define I2C_OAR2_OA2NOMASK					(0x00000000)
#define I2C_OAR2_OA2MASK01					(0x00000100)
#define I2C_OAR2_OA2MASK02					(0x00000200)
#define I2C_OAR2_OA2MASK03					(0x00000300)
#define I2C_OAR2_OA2MASK04					(0x00000400)
#define I2C_OAR2_OA2MASK05					(0x00000500)
#define I2C_OAR2_OA2MASK06					(0x00000600)
#define I2C_OAR2_OA2MASK07					(0x00000700)
#define I2C_OAR2_OA2EN						(0x00008000)

/*	Bit definition for I2C_TIMINGR register */
#define I2C_TIMINGR_SCLL					(0x000000FF)
#define I2C_TIMINGR_SCLH					(0x0000FF00)
#define I2C_TIMINGR_SDADEL					(0x000F0000)
#define I2C_TIMINGR_SCLDEL					(0x00F00000)
#define I2C_TIMINGR_PRESC					(0xF0000000)

/* Bit definition for I2C_TIMEOUTR register */
#define I2C_TIMEOUTR_TIMEOUTA				(0x00000FFF)
#define I2C_TIMEOUTR_TIDLE					(0x00001000)
#define I2C_TIMEOUTR_TIMOUTEN				(0x00008000)
#define I2C_TIMEOUTR_TIMEOUTB				(0x0FFF0000)
#define I2C_TIMEOUTR_TEXTEN					(0x80000000)

/*	Bit definition for I2C_ISR register  */
#define I2C_ISR_TXE							(0x00000001)
#define I2C_ISR_TXIS						(0x00000002)
#define I2C_ISR_RXNE						(0x00000004)
#define I2C_ISR_ADDR						(0x00000008)
#define I2C_ISR_NACKF						(0x00000010)
#define I2C_ISR_STOPF						(0x00000020)
#define I2C_ISR_TC							(0x00000040)
#define I2C_ISR_TCR							(0x00000080)
#define I2C_ISR_BERR						(0x00000100)
#define I2C_ISR_ARLO						(0x00000200)
#define I2C_ISR_OVR							(0x00000400)
#define I2C_ISR_PECERR						(0x00000800)
#define I2C_ISR_TIMEOUT						(0x00001000)
#define I2C_ISR_ALERT						(0x00002000)
#define I2C_ISR_BUSY						(0x00008000)
#define I2C_ISR_DIR							(0x00010000)
#define I2C_ISR_ADDCODE						(0x00FE0000)

/*	Bit definition for I2C_ICR register  */
#define I2C_ICR_ADDRCF						(0x00000008)
#define I2C_ICR_NACKCF						(0x00000010)
#define I2C_ICR_STOPCF						(0x00000020)
#define I2C_ICR_BERRCF						(0x00000100)
#define I2C_ICR_ARLOCF						(0x00000200)
#define I2C_ICR_OVRCF						(0x00000400)
#define I2C_ICR_PECCF						(0x00000800)
#define I2C_ICR_TIMOUTCF					(0x00001000)
#define I2C_ICR_ALERTCF						(0x00002000)

/*	Bit definition for I2C_PECR register  */
#define I2C_PECR_PEC						(0x000000FF)

/*	Bit definition for I2C_RXDR register  */
#define I2C_RXDR_RXDATA						(0x000000FF)

/*	Bit definition for I2C_TXDR register  */
#define I2C_TXDR_TXDATA						(0x000000FF)

#endif /* STM32L476_I2C_H_ */

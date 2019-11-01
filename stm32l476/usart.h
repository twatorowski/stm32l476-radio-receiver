/**
 * @file usart.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: USART
 */

#ifndef STM32L476_USART_H_
#define STM32L476_USART_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define USART1_BASE							0x40013800
#define USART2_BASE							0x40004400
#define USART3_BASE							0x40004800
#define UART4_BASE							0x40004c00
#define UART5_BASE							0x40005000

/* usart */
#define USART1								((usart_t *) USART1_BASE)
#define USART2								((usart_t *) USART2_BASE)
#define USART3								((usart_t *) USART3_BASE)
#define UART4								((usart_t *) UART4_BASE)
#define UART5								((usart_t *) UART5_BASE)

/* usart registers */
typedef struct {
	reg32_t CR1;
	reg32_t CR2;
	reg32_t CR3;
	reg32_t BRR;
	reg16_t GTPR;
	reg16_t RESERVED2;
	reg32_t RTOR;
	reg16_t RQR;
	reg16_t RESERVED3;
	reg32_t ISR;
	reg32_t ICR;
	reg16_t RDR;
	reg16_t RESERVED4;
	reg16_t TDR;
	reg16_t RESERVED5;
} __attribute__((packed, aligned(4))) usart_t;

/*	Bit definition for USART_CR1 register  */
#define USART_CR1_UE						(0x00000001)
#define USART_CR1_UESM						(0x00000002)
#define USART_CR1_RE						(0x00000004)
#define USART_CR1_TE						(0x00000008)
#define USART_CR1_IDLEIE					(0x00000010)
#define USART_CR1_RXNEIE					(0x00000020)
#define USART_CR1_TCIE						(0x00000040)
#define USART_CR1_TXEIE						(0x00000080)
#define USART_CR1_PEIE						(0x00000100)
#define USART_CR1_PS						(0x00000200)
#define USART_CR1_PCE						(0x00000400)
#define USART_CR1_WAKE						(0x00000800)
#define USART_CR1_M							(0x10001000)
#define USART_CR1_M0						(0x00001000)
#define USART_CR1_MME						(0x00002000)
#define USART_CR1_CMIE						(0x00004000)
#define USART_CR1_OVER8						(0x00008000)
#define USART_CR1_DEDT						(0x001F0000)
#define USART_CR1_DEDT_0					(0x00010000)
#define USART_CR1_DEDT_1					(0x00020000)
#define USART_CR1_DEDT_2					(0x00040000)
#define USART_CR1_DEDT_3					(0x00080000)
#define USART_CR1_DEDT_4					(0x00100000)
#define USART_CR1_DEAT						(0x03E00000)
#define USART_CR1_DEAT_0					(0x00200000)
#define USART_CR1_DEAT_1					(0x00400000)
#define USART_CR1_DEAT_2					(0x00800000)
#define USART_CR1_DEAT_3					(0x01000000)
#define USART_CR1_DEAT_4					(0x02000000)
#define USART_CR1_RTOIE						(0x04000000)
#define USART_CR1_EOBIE						(0x08000000)
#define USART_CR1_M1						(0x10000000)

/*	Bit definition for USART_CR2 register  */
#define USART_CR2_ADDM7						(0x00000010)
#define USART_CR2_LBDL						(0x00000020)
#define USART_CR2_LBDIE						(0x00000040)
#define USART_CR2_LBCL						(0x00000100)
#define USART_CR2_CPHA						(0x00000200)
#define USART_CR2_CPOL						(0x00000400)
#define USART_CR2_CLKEN						(0x00000800)
#define USART_CR2_STOP						(0x00003000)
#define USART_CR2_STOP_0					(0x00001000)
#define USART_CR2_STOP_1					(0x00002000)
#define USART_CR2_LINEN						(0x00004000)
#define USART_CR2_SWAP						(0x00008000)
#define USART_CR2_RXINV						(0x00010000)
#define USART_CR2_TXINV						(0x00020000)
#define USART_CR2_DATAINV					(0x00040000)
#define USART_CR2_MSBFIRST					(0x00080000)
#define USART_CR2_ABREN						(0x00100000)
#define USART_CR2_ABRMODE					(0x00600000)
#define USART_CR2_ABRMODE_0					(0x00200000)
#define USART_CR2_ABRMODE_1					(0x00400000)
#define USART_CR2_RTOEN						(0x00800000)
#define USART_CR2_ADD						(0xFF000000)

/*	Bit definition for USART_CR3 register  */
#define USART_CR3_EIE						(0x00000001)
#define USART_CR3_IREN						(0x00000002)
#define USART_CR3_IRLP						(0x00000004)
#define USART_CR3_HDSEL						(0x00000008)
#define USART_CR3_NACK						(0x00000010)
#define USART_CR3_SCEN						(0x00000020)
#define USART_CR3_DMAR						(0x00000040)
#define USART_CR3_DMAT						(0x00000080)
#define USART_CR3_RTSE						(0x00000100)
#define USART_CR3_CTSE						(0x00000200)
#define USART_CR3_CTSIE						(0x00000400)
#define USART_CR3_ONEBIT					(0x00000800)
#define USART_CR3_OVRDIS					(0x00001000)
#define USART_CR3_DDRE						(0x00002000)
#define USART_CR3_DEM						(0x00004000)
#define USART_CR3_DEP						(0x00008000)
#define USART_CR3_SCARCNT					(0x000E0000)
#define USART_CR3_SCARCNT_0					(0x00020000)
#define USART_CR3_SCARCNT_1					(0x00040000)
#define USART_CR3_SCARCNT_2					(0x00080000)
#define USART_CR3_WUS						(0x00300000)
#define USART_CR3_WUS_0						(0x00100000)
#define USART_CR3_WUS_1						(0x00200000)
#define USART_CR3_WUFIE						(0x00400000)

/*	Bit definition for USART_BRR register  */
#define USART_BRR_DIV_FRACTION				(0x000F)
#define USART_BRR_DIV_MANTISSA				(0xFFF0)

/*	Bit definition for USART_GTPR register	*/
#define USART_GTPR_PSC						(0x000000FF)
#define USART_GTPR_GT						(0x0000FF00)


/*	Bit definition for USART_RTOR register	*/
#define USART_RTOR_RTO						(0x00FFFFFF)
#define USART_RTOR_BLEN						(0xFF000000)

/*	Bit definition for USART_RQR register  */
#define USART_RQR_ABRRQ						(0x0001)
#define USART_RQR_SBKRQ						(0x0002)
#define USART_RQR_MMRQ						(0x0004)
#define USART_RQR_RXFRQ						(0x0008)
#define USART_RQR_TXFRQ						(0x0010)

/*	Bit definition for USART_ISR register  */
#define USART_ISR_PE						(0x00000001)
#define USART_ISR_FE						(0x00000002)
#define USART_ISR_NE						(0x00000004)
#define USART_ISR_ORE						(0x00000008)
#define USART_ISR_IDLE						(0x00000010)
#define USART_ISR_RXNE						(0x00000020)
#define USART_ISR_TC						(0x00000040)
#define USART_ISR_TXE						(0x00000080)
#define USART_ISR_LBDF						(0x00000100)
#define USART_ISR_CTSIF						(0x00000200)
#define USART_ISR_CTS						(0x00000400)
#define USART_ISR_RTOF						(0x00000800)
#define USART_ISR_EOBF						(0x00001000)
#define USART_ISR_ABRE						(0x00004000)
#define USART_ISR_ABRF						(0x00008000)
#define USART_ISR_BUSY						(0x00010000)
#define USART_ISR_CMF						(0x00020000)
#define USART_ISR_SBKF						(0x00040000)
#define USART_ISR_RWU						(0x00080000)
#define USART_ISR_WUF						(0x00100000)
#define USART_ISR_TEACK						(0x00200000)
#define USART_ISR_REACK						(0x00400000)

/*	Bit definition for USART_ICR register  */
#define USART_ICR_PECF						(0x00000001)
#define USART_ICR_FECF						(0x00000002)
#define USART_ICR_NCF						(0x00000004)
#define USART_ICR_ORECF						(0x00000008)
#define USART_ICR_IDLECF					(0x00000010)
#define USART_ICR_TCCF						(0x00000040)
#define USART_ICR_LBDCF						(0x00000100)
#define USART_ICR_CTSCF						(0x00000200)
#define USART_ICR_RTOCF						(0x00000800)
#define USART_ICR_EOBCF						(0x00001000)
#define USART_ICR_CMCF						(0x00020000)
#define USART_ICR_WUCF						(0x00100000)

/*	Bit definition for USART_RDR register  */
#define USART_RDR_RDR						(0x01FF)

/*	Bit definition for USART_TDR register  */
#define USART_TDR_TDR						(0x01FF)

#endif /* STM32L476_USART_H_ */

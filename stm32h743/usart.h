/**
 * @file usart.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: USART
 */


#ifndef STM32H743_USART_H
#define STM32H743_USART_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define USART1_BASE                                         0x40011000U
#define USART2_BASE                                         0x40004400U
#define USART3_BASE                                         0x40004800U
#define UART4_BASE                                          0x40004c00U
#define UART5_BASE                                          0x40005000U
#define USART6_BASE                                         0x40011400U
#define UART7_BASE                                          0x40007800U
#define UART8_BASE                                          0x40007c00U

/* instances */
#define USART1                                              ((usart_t *)USART1_BASE)
#define USART2                                              ((usart_t *)USART2_BASE)
#define USART3                                              ((usart_t *)USART3_BASE)
#define UART4                                               ((usart_t *)UART4_BASE)
#define UART5                                               ((usart_t *)UART5_BASE)
#define USART6                                              ((usart_t *)USART6_BASE)
#define UART7                                               ((usart_t *)UART7_BASE)
#define UART8                                               ((usart_t *)UART8_BASE)

/* register bank */
typedef struct {
    reg32_t CR1;
    reg32_t CR2;
    reg32_t CR3;
    reg32_t BRR;
    reg32_t GTPR;
    reg32_t RTOR;
    reg32_t RQR;
    reg32_t ISR;
    reg32_t ICR;
    reg32_t RDR;
    reg32_t TDR;
    reg32_t PRESC;
} usart_t;

/******************* bit definitions for CR1 register *******************/
#define USART_CR1_RXFFIE                                    0x80000000
#define USART_CR1_TXFEIE                                    0x40000000
#define USART_CR1_FIFOEN                                    0x20000000
#define USART_CR1_M1                                        0x10000000
#define USART_CR1_EOBIE                                     0x08000000
#define USART_CR1_RTOIE                                     0x04000000
#define USART_CR1_DEAT4                                     0x02000000
#define USART_CR1_DEAT3                                     0x01000000
#define USART_CR1_DEAT2                                     0x00800000
#define USART_CR1_DEAT1                                     0x00400000
#define USART_CR1_DEAT0                                     0x00200000
#define USART_CR1_DEDT4                                     0x00100000
#define USART_CR1_DEDT3                                     0x00080000
#define USART_CR1_DEDT2                                     0x00040000
#define USART_CR1_DEDT1                                     0x00020000
#define USART_CR1_DEDT0                                     0x00010000
#define USART_CR1_OVER8                                     0x00008000
#define USART_CR1_CMIE                                      0x00004000
#define USART_CR1_MME                                       0x00002000
#define USART_CR1_M0                                        0x00001000
#define USART_CR1_WAKE                                      0x00000800
#define USART_CR1_PCE                                       0x00000400
#define USART_CR1_PS                                        0x00000200
#define USART_CR1_PEIE                                      0x00000100
#define USART_CR1_TXEIE                                     0x00000080
#define USART_CR1_TCIE                                      0x00000040
#define USART_CR1_RXNEIE                                    0x00000020
#define USART_CR1_IDLEIE                                    0x00000010
#define USART_CR1_TE                                        0x00000008
#define USART_CR1_RE                                        0x00000004
#define USART_CR1_UESM                                      0x00000002
#define USART_CR1_UE                                        0x00000001

/******************* bit definitions for CR2 register *******************/
#define USART_CR2_ADD4_7                                    0xf0000000
#define USART_CR2_ADD0_3                                    0x0f000000
#define USART_CR2_RTOEN                                     0x00800000
#define USART_CR2_ABRMOD1                                   0x00400000
#define USART_CR2_ABRMOD0                                   0x00200000
#define USART_CR2_ABREN                                     0x00100000
#define USART_CR2_MSBFIRST                                  0x00080000
#define USART_CR2_TAINV                                     0x00040000
#define USART_CR2_TXINV                                     0x00020000
#define USART_CR2_RXINV                                     0x00010000
#define USART_CR2_SWAP                                      0x00008000
#define USART_CR2_LINEN                                     0x00004000
#define USART_CR2_STOP                                      0x00003000
#define USART_CR2_CLKEN                                     0x00000800
#define USART_CR2_CPOL                                      0x00000400
#define USART_CR2_CPHA                                      0x00000200
#define USART_CR2_LBCL                                      0x00000100
#define USART_CR2_LBDIE                                     0x00000040
#define USART_CR2_LBDL                                      0x00000020
#define USART_CR2_ADDM7                                     0x00000010
#define USART_CR2_DIS_NSS                                   0x00000008
#define USART_CR2_SLVEN                                     0x00000001

/******************* bit definitions for CR3 register *******************/
#define USART_CR3_TXFTCFG                                   0xe0000000
#define USART_CR3_RXFTIE                                    0x10000000
#define USART_CR3_RXFTCFG                                   0x0e000000
#define USART_CR3_TCBGTIE                                   0x01000000
#define USART_CR3_TXFTIE                                    0x00800000
#define USART_CR3_WUFIE                                     0x00400000
#define USART_CR3_WUS                                       0x00300000
#define USART_CR3_SCARCNT                                   0x000e0000
#define USART_CR3_DEP                                       0x00008000
#define USART_CR3_DEM                                       0x00004000
#define USART_CR3_DDRE                                      0x00002000
#define USART_CR3_OVRDIS                                    0x00001000
#define USART_CR3_ONEBIT                                    0x00000800
#define USART_CR3_CTSIE                                     0x00000400
#define USART_CR3_CTSE                                      0x00000200
#define USART_CR3_RTSE                                      0x00000100
#define USART_CR3_DMAT                                      0x00000080
#define USART_CR3_DMAR                                      0x00000040
#define USART_CR3_SCEN                                      0x00000020
#define USART_CR3_NACK                                      0x00000010
#define USART_CR3_HDSEL                                     0x00000008
#define USART_CR3_IRLP                                      0x00000004
#define USART_CR3_IREN                                      0x00000002
#define USART_CR3_EIE                                       0x00000001

/******************* bit definitions for BRR register *******************/
#define USART_BRR_BRR_4_15                                  0x0000fff0
#define USART_BRR_BRR_0_3                                   0x0000000f

/****************** bit definitions for GTPR register *******************/
#define USART_GTPR_GT                                       0x0000ff00
#define USART_GTPR_PSC                                      0x000000ff

/****************** bit definitions for RTOR register *******************/
#define USART_RTOR_BLEN                                     0xff000000
#define USART_RTOR_RTO                                      0x00ffffff

/******************* bit definitions for RQR register *******************/
#define USART_RQR_TXFRQ                                     0x00000010
#define USART_RQR_RXFRQ                                     0x00000008
#define USART_RQR_MMRQ                                      0x00000004
#define USART_RQR_SBKRQ                                     0x00000002
#define USART_RQR_ABRRQ                                     0x00000001

/******************* bit definitions for ISR register *******************/
#define USART_ISR_TXFT                                      0x08000000
#define USART_ISR_RXFT                                      0x04000000
#define USART_ISR_TCBGT                                     0x02000000
#define USART_ISR_RXFF                                      0x01000000
#define USART_ISR_TXFE                                      0x00800000
#define USART_ISR_REACK                                     0x00400000
#define USART_ISR_TEACK                                     0x00200000
#define USART_ISR_WUF                                       0x00100000
#define USART_ISR_RWU                                       0x00080000
#define USART_ISR_SBKF                                      0x00040000
#define USART_ISR_CMF                                       0x00020000
#define USART_ISR_BUSY                                      0x00010000
#define USART_ISR_ABRF                                      0x00008000
#define USART_ISR_ABRE                                      0x00004000
#define USART_ISR_UDR                                       0x00002000
#define USART_ISR_EOBF                                      0x00001000
#define USART_ISR_RTOF                                      0x00000800
#define USART_ISR_CTS                                       0x00000400
#define USART_ISR_CTSIF                                     0x00000200
#define USART_ISR_LBDF                                      0x00000100
#define USART_ISR_TXE                                       0x00000080
#define USART_ISR_TC                                        0x00000040
#define USART_ISR_RXNE                                      0x00000020
#define USART_ISR_IDLE                                      0x00000010
#define USART_ISR_ORE                                       0x00000008
#define USART_ISR_NF                                        0x00000004
#define USART_ISR_FE                                        0x00000002
#define USART_ISR_PE                                        0x00000001

/******************* bit definitions for ICR register *******************/
#define USART_ICR_WUCF                                      0x00100000
#define USART_ICR_CMCF                                      0x00020000
#define USART_ICR_UDRCF                                     0x00002000
#define USART_ICR_EOBCF                                     0x00001000
#define USART_ICR_RTOCF                                     0x00000800
#define USART_ICR_CTSCF                                     0x00000200
#define USART_ICR_LBDCF                                     0x00000100
#define USART_ICR_TCBGTC                                    0x00000080
#define USART_ICR_TCCF                                      0x00000040
#define USART_ICR_TXFECF                                    0x00000020
#define USART_ICR_IDLECF                                    0x00000010
#define USART_ICR_ORECF                                     0x00000008
#define USART_ICR_NCF                                       0x00000004
#define USART_ICR_FECF                                      0x00000002
#define USART_ICR_PECF                                      0x00000001

/******************* bit definitions for RDR register *******************/
#define USART_RDR_RDR                                       0x000001ff

/******************* bit definitions for TDR register *******************/
#define USART_TDR_TDR                                       0x000001ff

/****************** bit definitions for PRESC register ******************/
#define USART_PRESC_PRESCALER                               0x0000000f


#endif /* STM32H743_USART_H */
/**
 * @file dmamux.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: DMAMUX
 */


#ifndef STM32H743_DMAMUX_H
#define STM32H743_DMAMUX_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define DMAMUX2_BASE                                        0x58025800U
#define DMAMUX1_BASE                                        0x40020800U

/* instances */
#define DMAMUX2                                             ((dmamux_t *)DMAMUX2_BASE)
#define DMAMUX1                                             ((dmamux_t *)DMAMUX1_BASE)

/* register bank */
typedef struct {
    reg32_t C0CR;
    reg32_t C1CR;
    reg32_t C2CR;
    reg32_t C3CR;
    reg32_t C4CR;
    reg32_t C5CR;
    reg32_t C6CR;
    reg32_t C7CR;
    reg32_t C8CR;
    reg32_t C9CR;
    reg32_t C10CR;
    reg32_t C11CR;
    reg32_t C12CR;
    reg32_t C13CR;
    reg32_t C14CR;
    reg32_t C15CR;
    reg8_t RESERVED0[64];
    reg32_t CSR;
    reg32_t CFR;
    reg8_t RESERVED1[120];
    reg32_t RG0CR;
    reg32_t RG1CR;
    reg32_t RG2CR;
    reg32_t RG3CR;
    reg32_t RG4CR;
    reg32_t RG5CR;
    reg32_t RG6CR;
    reg32_t RG7CR;
    reg8_t RESERVED2[32];
    reg32_t RGSR;
    reg32_t RGCFR;
} dmamux_t;

/****************** bit definitions for C0CR register *******************/
#define DMAMUX_CCR_DMAREQ_ID                                0x000000ff
#define DMAMUX_CCR_SOIE                                     0x00000100
#define DMAMUX_CCR_EGE                                      0x00000200
#define DMAMUX_CCR_SE                                       0x00010000
#define DMAMUX_CCR_SPOL                                     0x00060000
#define DMAMUX_CCR_NBREQ                                    0x00f80000
#define DMAMUX_CCR_SYNC_ID                                  0x1f000000

/******************* bit definitions for CSR register *******************/
#define DMAMUX_CSR_SOF                                      0x0000ffff

/******************* bit definitions for CFR register *******************/
#define DMAMUX_CFR_CSOF                                     0x0000ffff

/****************** bit definitions for RG0CR register ******************/
#define DMAMUX_RGCR_SIG_ID                                 0x0000001f
#define DMAMUX_RGCR_OIE                                    0x00000100
#define DMAMUX_RGCR_GE                                     0x00010000
#define DMAMUX_RGCR_GPOL                                   0x00060000
#define DMAMUX_RGCR_GNBREQ                                 0x00f80000

/****************** bit definitions for RGSR register *******************/
#define DMAMUX_RGSR_OF                                      0x000000ff

/****************** bit definitions for RGCFR register ******************/
#define DMAMUX_RGCFR_COF                                    0x000000ff

/*********************** DMAMUX1 Request mapping ************************/
#define DMAMUX1_DMAMUX1_REQ_GEN0                            1
#define DMAMUX1_DMAMUX1_REQ_GEN1                            2
#define DMAMUX1_DMAMUX1_REQ_GEN2                            3
#define DMAMUX1_DMAMUX1_REQ_GEN3                            4
#define DMAMUX1_DMAMUX1_REQ_GEN4                            5
#define DMAMUX1_DMAMUX1_REQ_GEN5                            6
#define DMAMUX1_DMAMUX1_REQ_GEN6                            7
#define DMAMUX1_DMAMUX1_REQ_GEN7                            8
#define DMAMUX1_ADC1_DMA                                    9
#define DMAMUX1_ADC2_DMA                                    10
#define DMAMUX1_TIM1_CH1                                    11
#define DMAMUX1_TIM1_CH2                                    12
#define DMAMUX1_TIM1_CH3                                    13
#define DMAMUX1_TIM1_CH4                                    14
#define DMAMUX1_TIM1_UP                                     15
#define DMAMUX1_TIM1_TRIG                                   16
#define DMAMUX1_TIM1_COM                                    17
#define DMAMUX1_TIM2_CH1                                    18
#define DMAMUX1_TIM2_CH2                                    19
#define DMAMUX1_TIM2_CH3                                    20
#define DMAMUX1_TIM2_CH4                                    21
#define DMAMUX1_TIM2_UP                                     22
#define DMAMUX1_TIM3_CH1                                    23
#define DMAMUX1_TIM3_CH2                                    24
#define DMAMUX1_TIM3_CH3                                    25
#define DMAMUX1_TIM3_CH4                                    26
#define DMAMUX1_TIM3_UP                                     27
#define DMAMUX1_TIM3_TRIG                                   28
#define DMAMUX1_TIM4_CH1                                    29
#define DMAMUX1_TIM4_CH2                                    30
#define DMAMUX1_TIM4_CH3                                    31
#define DMAMUX1_TIM4_UP                                     32
#define DMAMUX1_I2C1_RX_DMA                                 33
#define DMAMUX1_I2C1_TX_DMA                                 34
#define DMAMUX1_I2C2_RX_DMA                                 35
#define DMAMUX1_I2C2_TX_DMA                                 36
#define DMAMUX1_SPI1_RX_DMA                                 37
#define DMAMUX1_SPI1_TX_DMA                                 38
#define DMAMUX1_SPI2_RX_DMA                                 39
#define DMAMUX1_SPI2_TX_DMA                                 40
#define DMAMUX1_USART1_RX_DMA                               41
#define DMAMUX1_USART1_TX_DMA                               42
#define DMAMUX1_USART2_RX_DMA                               43
#define DMAMUX1_USART2_TX_DMA                               44
#define DMAMUX1_USART3_RX_DMA                               45
#define DMAMUX1_USART3_TX_DMA                               46
#define DMAMUX1_TIM8_CH1                                    47
#define DMAMUX1_TIM8_CH2                                    48
#define DMAMUX1_TIM8_CH3                                    49
#define DMAMUX1_TIM8_CH4                                    50
#define DMAMUX1_TIM8_UP                                     51
#define DMAMUX1_TIM8_TRIG                                   52
#define DMAMUX1_TIM8_COM                                    53
#define DMAMUX1_TIM5_CH1                                    55
#define DMAMUX1_TIM5_CH2                                    56
#define DMAMUX1_TIM5_CH3                                    57
#define DMAMUX1_TIM5_CH4                                    58
#define DMAMUX1_TIM5_UP                                     59
#define DMAMUX1_TIM5_TRIG                                   60
#define DMAMUX1_SPI3_RX_DMA                                 61
#define DMAMUX1_SPI3_TX_DMA                                 62
#define DMAMUX1_UART4_RX_DMA                                63
#define DMAMUX1_UART4_TX_DMA                                64
#define DMAMUX1_UART5_RX_DMA                                65
#define DMAMUX1_UART5_TX_DMA                                66
#define DMAMUX1_DAC_CH1_DMA                                 67
#define DMAMUX1_DAC_CH2_DMA                                 68
#define DMAMUX1_TIM6_UP                                     69
#define DMAMUX1_TIM7_UP                                     70
#define DMAMUX1_USART6_RX_DMA                               71
#define DMAMUX1_USART6_TX_DMA                               72
#define DMAMUX1_I2C3_RX_DMA                                 73
#define DMAMUX1_I2C3_TX_DMA                                 74
#define DMAMUX1_DCMI_DMA                                    75
#define DMAMUX1_CRYP_IN_DMA                                 76
#define DMAMUX1_CRYP_OUT_DMA                                77
#define DMAMUX1_HASH_IN_DMA                                 78
#define DMAMUX1_UART7_RX_DMA                                79
#define DMAMUX1_UART7_TX_DMA                                80
#define DMAMUX1_UART8_RX_DMA                                81
#define DMAMUX1_UART8_TX_DMA                                82
#define DMAMUX1_SPI4_RX_DMA                                 83
#define DMAMUX1_SPI4_TX_DMA                                 84
#define DMAMUX1_SPI5_RX_DMA                                 85
#define DMAMUX1_SPI5_TX_DMA                                 86
#define DMAMUX1_SAI1A_DMA                                   87
#define DMAMUX1_SAI1B_DMA                                   88
#define DMAMUX1_SAI2A_DMA                                   89
#define DMAMUX1_SAI2B_DMA                                   90
#define DMAMUX1_SWPMI_RX_DMA                                91
#define DMAMUX1_SWPMI_TX_DMA                                92
#define DMAMUX1_SPDIFRX_DAT_DMA                             93
#define DMAMUX1_SPDIFRX_CTRL_DMA                            94
#define DMAMUX1_HR_REQ_1                                    95
#define DMAMUX1_HR_REQ_2                                    96
#define DMAMUX1_HR_REQ_3                                    97
#define DMAMUX1_HR_REQ_4                                    98
#define DMAMUX1_HR_REQ_5                                    99
#define DMAMUX1_HR_REQ_6                                    100
#define DMAMUX1_DFSDM1_DMA0                                 101
#define DMAMUX1_DFSDM1_DMA1                                 102
#define DMAMUX1_DFSDM1_DMA2                                 103
#define DMAMUX1_DFSDM1_DMA3                                 104
#define DMAMUX1_TIM15_CH1                                   105
#define DMAMUX1_TIM15_UP                                    106
#define DMAMUX1_TIM15_TRIG                                  107
#define DMAMUX1_TIM15_COM                                   108
#define DMAMUX1_TIM16_CH1                                   109
#define DMAMUX1_TIM16_UP                                    110
#define DMAMUX1_TIM17_CH1                                   111
#define DMAMUX1_TIM17_UP                                    112
#define DMAMUX1_SAI3_A_DMA                                  113
#define DMAMUX1_SAI3_B_DMA                                  114
#define DMAMUX1_ADC3_DMA                                    115

/*********************** DMAMUX1 Request mapping ************************/
#define DMAMUX2_DMAMUX2_REQ_GEN0                            1
#define DMAMUX2_DMAMUX2_REQ_GEN1                            2
#define DMAMUX2_DMAMUX2_REQ_GEN2                            3
#define DMAMUX2_DMAMUX2_REQ_GEN3                            4
#define DMAMUX2_DMAMUX2_REQ_GEN4                            5
#define DMAMUX2_DMAMUX2_REQ_GEN5                            6
#define DMAMUX2_DMAMUX2_REQ_GEN6                            7
#define DMAMUX2_DMAMUX2_REQ_GEN7                            8
#define DMAMUX2_LPUART1_RX_DMA                              9
#define DMAMUX2_LPUART1_TX_DMA                              10
#define DMAMUX2_SPI6_RX_DMA                                 11
#define DMAMUX2_SPI6_TX_DMA                                 12
#define DMAMUX2_I2C4_RX_DMA                                 13
#define DMAMUX2_I2C4_TX_DMA                                 14
#define DMAMUX2_SAI4_A_DMA                                  15
#define DMAMUX2_SAI4_B_DMA                                  16
#define DMAMUX2_ADC3_DMA                                    17

#endif /* STM32H743_DMAMUX_H */
/**
 * @file eth.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743
 */

#ifndef STM32H743_STM32H743_H
#define STM32H743_STM32H743_H

#include <stdint.h>

#include "../compiler.h"

/* register type 8 bit */
typedef volatile uint8_t reg8_t;
/* register type 16 bit */
typedef volatile uint16_t reg16_t;
/* register type */
typedef volatile uint32_t reg32_t;

/* stack pointer */
/* base position for the stack pointer entry */
#define STM32_VECTOR_STACK_PTR_BASE                         0
/* base of the exception vectors */
#define STM32_VECTOR_EXC_BASE                               1
/* base position for the interrupt vectors */
#define STM32_VECTOR_INT_BASE                               16

/* stack pointer */
/* stack pointer entry id */
#define STM32_STACK_PTR                                     0

/* core exeptions */
/* reset routine */
#define STM32_EXC_RESET                                     0
/* Non maskable interrupt. The RCC Clock Security System (CSS) is
 * linked to the NMI vector. */
#define STM32_EXC_NMI                                       1
/* All class of fault */
#define STM32_EXC_HARDFAULT                                 2
/* Memory management */
#define STM32_EXC_MEMMANAGE                                 3
/* Pre-fetch fault, memory access fault */
#define STM32_EXC_BUSFAULT                                  4
/* Undefined instruction or illegal state */
#define STM32_EXC_USAGEFAULT                                5
/* System service call via SWI instruction */
#define STM32_EXC_SVC                                       10
/* Debug Monitor */
#define STM32_EXC_DEBUGMON                                  11
/* Pendable request for system service */
#define STM32_EXC_PENDSV                                    13
/* System tick timer */
#define STM32_EXC_SYSTICK                                   14

/** Window Watchdog interrupt */
#define STM32_INT_WWDG1                                     0
/** PVD through EXTI line */
#define STM32_INT_PVD_PVM                                   1
/** RTC tamper, timestamp */
#define STM32_INT_RTC_TAMP_STAMP_CSS_LSE                    2
/** RTC Wakeup interrupt */
#define STM32_INT_RTC_WKUP                                  3
/** Flash memory */
#define STM32_INT_FLASH                                     4
/** RCC global interrupt */
#define STM32_INT_RCC                                       5
/** EXTI Line 0 interrupt */
#define STM32_INT_EXTI0                                     6
/** EXTI Line 1 interrupt */
#define STM32_INT_EXTI1                                     7
/** EXTI Line 2 interrupt */
#define STM32_INT_EXTI2                                     8
/** EXTI Line 3interrupt */
#define STM32_INT_EXTI3                                     9
/** EXTI Line 4interrupt */
#define STM32_INT_EXTI4                                     10
/** DMA1 Stream0 */
#define STM32_INT_DMA1_STR0                                 11
/** DMA1 Stream1 */
#define STM32_INT_DMA1_STR1                                 12
/** DMA1 Stream2 */
#define STM32_INT_DMA1_STR2                                 13
/** DMA1 Stream3 */
#define STM32_INT_DMA1_STR3                                 14
/** DMA1 Stream4 */
#define STM32_INT_DMA1_STR4                                 15
/** DMA1 Stream5 */
#define STM32_INT_DMA1_STR5                                 16
/** DMA1 Stream6 */
#define STM32_INT_DMA1_STR6                                 17
/** ADC1 and ADC2 */
#define STM32_INT_ADC1_2                                    18
/** FDCAN1 Interrupt 0 */
#define STM32_INT_FDCAN1_IT0                                19
/** FDCAN2 Interrupt 0 */
#define STM32_INT_FDCAN2_IT0                                20
/** FDCAN1 Interrupt 1 */
#define STM32_INT_FDCAN1_IT1                                21
/** FDCAN2 Interrupt 1 */
#define STM32_INT_FDCAN2_IT1                                22
/** EXTI Line[9:5] interrupts */
#define STM32_INT_EXTI9_5                                   23
/** TIM1 break interrupt */
#define STM32_INT_TIM1_BRK                                  24
/** TIM1 update interrupt */
#define STM32_INT_TIM1_UP                                   25
/** TIM1 trigger and commutation */
#define STM32_INT_TIM1_TRG_COM                              26
/** TIM1 capture / compare */
#define STM32_INT_TIM_CC                                    27
/** TIM2 global interrupt */
#define STM32_INT_TIM2                                      28
/** TIM3 global interrupt */
#define STM32_INT_TIM3                                      29
/** TIM4 global interrupt */
#define STM32_INT_TIM4                                      30
/** I2C1 event interrupt */
#define STM32_INT_I2C1_EV                                   31
/** I2C1 error interrupt */
#define STM32_INT_I2C1_ER                                   32
/** I2C2 event interrupt */
#define STM32_INT_I2C2_EV                                   33
/** I2C2 error interrupt */
#define STM32_INT_I2C2_ER                                   34
/** SPI1 global interrupt */
#define STM32_INT_SPI1                                      35
/** SPI2 global interrupt */
#define STM32_INT_SPI2                                      36
/** USART1 global interrupt */
#define STM32_INT_USART1                                    37
/** USART2 global interrupt */
#define STM32_INT_USART2                                    38
/** USART3 global interrupt */
#define STM32_INT_USART3                                    39
/** EXTI Line[15:10] interrupts */
#define STM32_INT_EXTI15_10                                 40
/** RTC alarms (A and B) */
#define STM32_INT_RTC_ALARM                                 41
/** TIM8 and 12 break global */
#define STM32_INT_TIM8_BRK_TIM12                            43
/** TIM8 and 13 update global */
#define STM32_INT_TIM8_UP_TIM13                             44
/** TIM8 and 14 trigger /commutation and global */
#define STM32_INT_TIM8_TRG_COM_TIM14                        45
/** TIM8 capture / compare */
#define STM32_INT_TIM8_CC                                   46
/** DMA1 Stream7 */
#define STM32_INT_DMA1_STR7                                 47
/** FMC global interrupt */
#define STM32_INT_FMC                                       48
/** SDMMC global interrupt */
#define STM32_INT_SDMMC1                                    49
/** TIM5 global interrupt */
#define STM32_INT_TIM5                                      50
/** SPI3 global interrupt */
#define STM32_INT_SPI3                                      51
/** UART4 global interrupt */
#define STM32_INT_UART4                                     52
/** UART5 global interrupt */
#define STM32_INT_UART5                                     53
/** TIM6 global interrupt */
#define STM32_INT_TIM6_DAC                                  54
/** TIM7 global interrupt */
#define STM32_INT_TIM7                                      55
/** DMA2 Stream0 interrupt */
#define STM32_INT_DMA2_STR0                                 56
/** DMA2 Stream1 interrupt */
#define STM32_INT_DMA2_STR1                                 57
/** DMA2 Stream2 interrupt */
#define STM32_INT_DMA2_STR2                                 58
/** DMA2 Stream3 interrupt */
#define STM32_INT_DMA2_STR3                                 59
/** DMA2 Stream4 interrupt */
#define STM32_INT_DMA2_STR4                                 60
/** Ethernet global interrupt */
#define STM32_INT_ETH                                       61
/** Ethernet wakeup through EXTI */
#define STM32_INT_ETH_WKUP                                  62
/** CAN2TX interrupts */
#define STM32_INT_FDCAN_CAL                                 63
/** DMA2 Stream5 interrupt */
#define STM32_INT_DMA2_STR5                                 68
/** DMA2 Stream6 interrupt */
#define STM32_INT_DMA2_STR6                                 69
/** DMA2 Stream7 interrupt */
#define STM32_INT_DMA2_STR7                                 70
/** USART6 global interrupt */
#define STM32_INT_USART6                                    71
/** I2C3 event interrupt */
#define STM32_INT_I2C3_EV                                   72
/** I2C3 error interrupt */
#define STM32_INT_I2C3_ER                                   73
/** OTG_HS out global interrupt */
#define STM32_INT_OTG_HS_EP1_OUT                            74
/** OTG_HS in global interrupt */
#define STM32_INT_OTG_HS_EP1_IN                             75
/** OTG_HS wakeup interrupt */
#define STM32_INT_OTG_HS_WKUP                               76
/** OTG_HS global interrupt */
#define STM32_INT_OTG_HS                                    77
/** DCMI global interrupt */
#define STM32_INT_DCMI                                      78
/** Floating point unit interrupt */
#define STM32_INT_FPU                                       81
/** UART7 global interrupt */
#define STM32_INT_UART7                                     82
/** UART8 global interrupt */
#define STM32_INT_UART8                                     83
/** SPI4 global interrupt */
#define STM32_INT_SPI4                                      84
/** SPI5 global interrupt */
#define STM32_INT_SPI5                                      85
/** SPI6 global interrupt */
#define STM32_INT_SPI6                                      86
/** SAI1 global interrupt */
#define STM32_INT_SAI1                                      87
/** LCD-TFT global interrupt */
#define STM32_INT_LTDC                                      88
/** LCD-TFT error interrupt */
#define STM32_INT_LTDC_ER                                   89
/** DMA2D global interrupt */
#define STM32_INT_DMA2D                                     90
/** SAI2 global interrupt */
#define STM32_INT_SAI2                                      91
/** QuadSPI global interrupt */
#define STM32_INT_QUADSPI                                   92
/** LPTIM1 global interrupt */
#define STM32_INT_LPTIM1                                    93
/** HDMI-CEC global interrupt */
#define STM32_INT_CEC                                       94
/** I2C4 event interrupt */
#define STM32_INT_I2C4_EV                                   95
/** I2C4 error interrupt */
#define STM32_INT_I2C4_ER                                   96
/** SPDIFRX global interrupt */
#define STM32_INT_SPDIF                                     97
/** OTG_FS out global interrupt */
#define STM32_INT_OTG_FS_EP1_OUT                            98
/** OTG_FS in global interrupt */
#define STM32_INT_OTG_FS_EP1_IN                             99
/** OTG_FS wakeup */
#define STM32_INT_OTG_FS_WKUP                               100
/** OTG_FS global interrupt */
#define STM32_INT_OTG_FS                                    101
/** DMAMUX1 overrun interrupt */
#define STM32_INT_DMAMUX1_OV                                102
/** HRTIM1 master timer interrupt */
#define STM32_INT_HRTIM1_MST                                103
/** HRTIM1 timer A interrupt */
#define STM32_INT_HRTIM1_TIMA                               104
/** HRTIM1 timer B interrupt */
#define STM32_INT_HRTIM_TIMB                                105
/** HRTIM1 timer C interrupt */
#define STM32_INT_HRTIM1_TIMC                               106
/** HRTIM1 timer D interrupt */
#define STM32_INT_HRTIM1_TIMD                               107
/** HRTIM1 timer E interrupt */
#define STM32_INT_HRTIM_TIME                                108
/** HRTIM1 fault interrupt */
#define STM32_INT_HRTIM1_FLT                                109
/** DFSDM1 filter 0 interrupt */
#define STM32_INT_DFSDM1_FLT0                               110
/** DFSDM1 filter 1 interrupt */
#define STM32_INT_DFSDM1_FLT1                               111
/** DFSDM1 filter 2 interrupt */
#define STM32_INT_DFSDM1_FLT2                               112
/** DFSDM1 filter 3 interrupt */
#define STM32_INT_DFSDM1_FLT3                               113
/** SAI3 global interrupt */
#define STM32_INT_SAI3                                      114
/** SWPMI global interrupt */
#define STM32_INT_SWPMI1                                    115
/** TIM15 global interrupt */
#define STM32_INT_TIM15                                     116
/** TIM16 global interrupt */
#define STM32_INT_TIM16                                     117
/** TIM17 global interrupt */
#define STM32_INT_TIM17                                     118
/** MDIOS wakeup */
#define STM32_INT_MDIOS_WKUP                                119
/** MDIOS global interrupt */
#define STM32_INT_MDIOS                                     120
/** JPEG global interrupt */
#define STM32_INT_JPEG                                      121
/** MDMA */
#define STM32_INT_MDMA                                      122
/** SDMMC global interrupt */
#define STM32_INT_SDMMC                                     124
/** HSEM global interrupt 1 */
#define STM32_INT_HSEM0                                     125
/** ADC3 global interrupt */
#define STM32_INT_ADC3                                      127
/** DMAMUX2 overrun interrupt */
#define STM32_INT_DMAMUX2_OVR                               128
/** BDMA channel 1 interrupt */
#define STM32_INT_BDMA_CH1                                  129
/** BDMA channel 2 interrupt */
#define STM32_INT_BDMA_CH2                                  130
/** BDMA channel 3 interrupt */
#define STM32_INT_BDMA_CH3                                  131
/** BDMA channel 4 interrupt */
#define STM32_INT_BDMA_CH4                                  132
/** BDMA channel 5 interrupt */
#define STM32_INT_BDMA_CH5                                  133
/** BDMA channel 6 interrupt */
#define STM32_INT_BDMA_CH6                                  134
/** BDMA channel 7 interrupt */
#define STM32_INT_BDMA_CH7                                  135
/** BDMA channel 8 interrupt */
#define STM32_INT_BDMA_CH8                                  136
/** COMP1 and COMP2 */
#define STM32_INT_COMP                                      137
/** LPTIM2 timer interrupt */
#define STM32_INT_LPTIM2                                    138
/** LPTIM2 timer interrupt */
#define STM32_INT_LPTIM3                                    139
/** LPTIM2 timer interrupt */
#define STM32_INT_LPTIM4                                    140
/** LPTIM2 timer interrupt */
#define STM32_INT_LPTIM5                                    141
/** LPUART global interrupt */
#define STM32_INT_LPUART                                    142
/** Window Watchdog interrupt */
#define STM32_INT_WWDG1_RST                                 143
/** Clock Recovery System globa */
#define STM32_INT_CRS                                       144
/** SAI4 global interrupt */
#define STM32_INT_SAI4                                      146
/** WKUP1 to WKUP6 pins */
#define STM32_INT_WKUP                                      149

/* bitband access */
#define STM32_BB(reg, bit)                                                  \
            *((reg32_t *) (((uint32_t)(reg) & 0xf0000000) | 0x02000000 |    \
            ((uint32_t)(reg) & 0x000fffff) << 5 |                           \
            ((bit) << 2)))

/* enable interrupts globally */
#define STM32_ENABLEINTS()                      \
    __asm__ volatile ("cpsie i")

/* disable interrupts globally */
#define STM32_DISABLEINTS()                     \
    __asm__ volatile ("cpsid i")

#endif /* STM32H743_STM32H743_H */
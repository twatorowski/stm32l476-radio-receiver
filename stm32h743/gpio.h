/**
 * @file gpio.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: GPIO
 */


#ifndef STM32H743_GPIO_H
#define STM32H743_GPIO_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define GPIOA_BASE                                          0x58020000U
#define GPIOB_BASE                                          0x58020400U
#define GPIOC_BASE                                          0x58020800U
#define GPIOD_BASE                                          0x58020c00U
#define GPIOE_BASE                                          0x58021000U
#define GPIOF_BASE                                          0x58021400U
#define GPIOG_BASE                                          0x58021800U
#define GPIOH_BASE                                          0x58021c00U
#define GPIOI_BASE                                          0x58022000U
#define GPIOJ_BASE                                          0x58022400U
#define GPIOK_BASE                                          0x58022800U

/* instances */
#define GPIOA                                               ((gpio_t *)GPIOA_BASE)
#define GPIOB                                               ((gpio_t *)GPIOB_BASE)
#define GPIOC                                               ((gpio_t *)GPIOC_BASE)
#define GPIOD                                               ((gpio_t *)GPIOD_BASE)
#define GPIOE                                               ((gpio_t *)GPIOE_BASE)
#define GPIOF                                               ((gpio_t *)GPIOF_BASE)
#define GPIOG                                               ((gpio_t *)GPIOG_BASE)
#define GPIOH                                               ((gpio_t *)GPIOH_BASE)
#define GPIOI                                               ((gpio_t *)GPIOI_BASE)
#define GPIOJ                                               ((gpio_t *)GPIOJ_BASE)
#define GPIOK                                               ((gpio_t *)GPIOK_BASE)

/* register bank */
typedef struct {
    reg32_t MODER;
    reg32_t OTYPER;
    reg32_t OSPEEDR;
    reg32_t PUPDR;
    reg32_t IDR;
    reg32_t ODR;
    reg32_t BSRR;
    reg32_t LCKR;
    reg32_t AFRL;
    reg32_t AFRH;
} gpio_t;

/****************** bit definitions for MODER register ******************/
#define GPIO_MODER_MODER0                                   0x00000003
#define GPIO_MODER_MODER0_0                                 0x00000001
#define GPIO_MODER_MODER0_1                                 0x00000002
#define GPIO_MODER_MODER1                                   0x0000000c
#define GPIO_MODER_MODER1_0                                 0x00000004
#define GPIO_MODER_MODER1_1                                 0x00000008
#define GPIO_MODER_MODER2                                   0x00000030
#define GPIO_MODER_MODER2_0                                 0x00000010
#define GPIO_MODER_MODER2_1                                 0x00000020
#define GPIO_MODER_MODER3                                   0x000000c0
#define GPIO_MODER_MODER3_0                                 0x00000040
#define GPIO_MODER_MODER3_1                                 0x00000080
#define GPIO_MODER_MODER4                                   0x00000300
#define GPIO_MODER_MODER4_0                                 0x00000100
#define GPIO_MODER_MODER4_1                                 0x00000200
#define GPIO_MODER_MODER5                                   0x00000c00
#define GPIO_MODER_MODER5_0                                 0x00000400
#define GPIO_MODER_MODER5_1                                 0x00000800
#define GPIO_MODER_MODER6                                   0x00003000
#define GPIO_MODER_MODER6_0                                 0x00001000
#define GPIO_MODER_MODER6_1                                 0x00002000
#define GPIO_MODER_MODER7                                   0x0000c000
#define GPIO_MODER_MODER7_0                                 0x00004000
#define GPIO_MODER_MODER7_1                                 0x00008000
#define GPIO_MODER_MODER8                                   0x00030000
#define GPIO_MODER_MODER8_0                                 0x00010000
#define GPIO_MODER_MODER8_1                                 0x00020000
#define GPIO_MODER_MODER9                                   0x000c0000
#define GPIO_MODER_MODER9_0                                 0x00040000
#define GPIO_MODER_MODER9_1                                 0x00080000
#define GPIO_MODER_MODER10                                  0x00300000
#define GPIO_MODER_MODER10_0                                0x00100000
#define GPIO_MODER_MODER10_1                                0x00200000
#define GPIO_MODER_MODER11                                  0x00c00000
#define GPIO_MODER_MODER11_0                                0x00400000
#define GPIO_MODER_MODER11_1                                0x00800000
#define GPIO_MODER_MODER12                                  0x03000000
#define GPIO_MODER_MODER12_0                                0x01000000
#define GPIO_MODER_MODER12_1                                0x02000000
#define GPIO_MODER_MODER13                                  0x0c000000
#define GPIO_MODER_MODER13_0                                0x04000000
#define GPIO_MODER_MODER13_1                                0x08000000
#define GPIO_MODER_MODER14                                  0x30000000
#define GPIO_MODER_MODER14_0                                0x10000000
#define GPIO_MODER_MODER14_1                                0x20000000
#define GPIO_MODER_MODER15                                  0xc0000000
#define GPIO_MODER_MODER15_0                                0x40000000
#define GPIO_MODER_MODER15_1                                0x80000000

/***************** bit definitions for OTYPER register ******************/
#define GPIO_OTYPER_OT0                                     0x00000001
#define GPIO_OTYPER_OT1                                     0x00000002
#define GPIO_OTYPER_OT2                                     0x00000004
#define GPIO_OTYPER_OT3                                     0x00000008
#define GPIO_OTYPER_OT4                                     0x00000010
#define GPIO_OTYPER_OT5                                     0x00000020
#define GPIO_OTYPER_OT6                                     0x00000040
#define GPIO_OTYPER_OT7                                     0x00000080
#define GPIO_OTYPER_OT8                                     0x00000100
#define GPIO_OTYPER_OT9                                     0x00000200
#define GPIO_OTYPER_OT10                                    0x00000400
#define GPIO_OTYPER_OT11                                    0x00000800
#define GPIO_OTYPER_OT12                                    0x00001000
#define GPIO_OTYPER_OT13                                    0x00002000
#define GPIO_OTYPER_OT14                                    0x00004000
#define GPIO_OTYPER_OT15                                    0x00008000

/***************** bit definitions for OSPEEDR register *****************/
#define GPIO_OSPEEDR_OSPEEDR0                               0x00000003
#define GPIO_OSPEEDR_OSPEEDR0_0                             0x00000001
#define GPIO_OSPEEDR_OSPEEDR0_1                             0x00000002
#define GPIO_OSPEEDR_OSPEEDR1                               0x0000000c
#define GPIO_OSPEEDR_OSPEEDR1_0                             0x00000004
#define GPIO_OSPEEDR_OSPEEDR1_1                             0x00000008
#define GPIO_OSPEEDR_OSPEEDR2                               0x00000030
#define GPIO_OSPEEDR_OSPEEDR2_0                             0x00000010
#define GPIO_OSPEEDR_OSPEEDR2_1                             0x00000020
#define GPIO_OSPEEDR_OSPEEDR3                               0x000000c0
#define GPIO_OSPEEDR_OSPEEDR3_0                             0x00000040
#define GPIO_OSPEEDR_OSPEEDR3_1                             0x00000080
#define GPIO_OSPEEDR_OSPEEDR4                               0x00000300
#define GPIO_OSPEEDR_OSPEEDR4_0                             0x00000100
#define GPIO_OSPEEDR_OSPEEDR4_1                             0x00000200
#define GPIO_OSPEEDR_OSPEEDR5                               0x00000c00
#define GPIO_OSPEEDR_OSPEEDR5_0                             0x00000400
#define GPIO_OSPEEDR_OSPEEDR5_1                             0x00000800
#define GPIO_OSPEEDR_OSPEEDR6                               0x00003000
#define GPIO_OSPEEDR_OSPEEDR6_0                             0x00001000
#define GPIO_OSPEEDR_OSPEEDR6_1                             0x00002000
#define GPIO_OSPEEDR_OSPEEDR7                               0x0000c000
#define GPIO_OSPEEDR_OSPEEDR7_0                             0x00004000
#define GPIO_OSPEEDR_OSPEEDR7_1                             0x00008000
#define GPIO_OSPEEDR_OSPEEDR8                               0x00030000
#define GPIO_OSPEEDR_OSPEEDR8_0                             0x00010000
#define GPIO_OSPEEDR_OSPEEDR8_1                             0x00020000
#define GPIO_OSPEEDR_OSPEEDR9                               0x000c0000
#define GPIO_OSPEEDR_OSPEEDR9_0                             0x00040000
#define GPIO_OSPEEDR_OSPEEDR9_1                             0x00080000
#define GPIO_OSPEEDR_OSPEEDR10                              0x00300000
#define GPIO_OSPEEDR_OSPEEDR10_0                            0x00100000
#define GPIO_OSPEEDR_OSPEEDR10_1                            0x00200000
#define GPIO_OSPEEDR_OSPEEDR11                              0x00c00000
#define GPIO_OSPEEDR_OSPEEDR11_0                            0x00400000
#define GPIO_OSPEEDR_OSPEEDR11_1                            0x00800000
#define GPIO_OSPEEDR_OSPEEDR12                              0x03000000
#define GPIO_OSPEEDR_OSPEEDR12_0                            0x01000000
#define GPIO_OSPEEDR_OSPEEDR12_1                            0x02000000
#define GPIO_OSPEEDR_OSPEEDR13                              0x0c000000
#define GPIO_OSPEEDR_OSPEEDR13_0                            0x04000000
#define GPIO_OSPEEDR_OSPEEDR13_1                            0x08000000
#define GPIO_OSPEEDR_OSPEEDR14                              0x30000000
#define GPIO_OSPEEDR_OSPEEDR14_0                            0x10000000
#define GPIO_OSPEEDR_OSPEEDR14_1                            0x20000000
#define GPIO_OSPEEDR_OSPEEDR15                              0xc0000000
#define GPIO_OSPEEDR_OSPEEDR15_0                            0x40000000
#define GPIO_OSPEEDR_OSPEEDR15_1                            0x80000000

/****************** bit definitions for PUPDR register ******************/
#define GPIO_PUPDR_PUPD0                                    0x00000003
#define GPIO_PUPDR_PUPD0_0                                  0x00000001
#define GPIO_PUPDR_PUPD0_1                                  0x00000002
#define GPIO_PUPDR_PUPD1                                    0x0000000c
#define GPIO_PUPDR_PUPD1_0                                  0x00000004
#define GPIO_PUPDR_PUPD1_1                                  0x00000008
#define GPIO_PUPDR_PUPD2                                    0x00000030
#define GPIO_PUPDR_PUPD2_0                                  0x00000010
#define GPIO_PUPDR_PUPD2_1                                  0x00000020
#define GPIO_PUPDR_PUPD3                                    0x000000c0
#define GPIO_PUPDR_PUPD3_0                                  0x00000040
#define GPIO_PUPDR_PUPD3_1                                  0x00000080
#define GPIO_PUPDR_PUPD4                                    0x00000300
#define GPIO_PUPDR_PUPD4_0                                  0x00000100
#define GPIO_PUPDR_PUPD4_1                                  0x00000200
#define GPIO_PUPDR_PUPD5                                    0x00000c00
#define GPIO_PUPDR_PUPD5_0                                  0x00000400
#define GPIO_PUPDR_PUPD5_1                                  0x00000800
#define GPIO_PUPDR_PUPD6                                    0x00003000
#define GPIO_PUPDR_PUPD6_0                                  0x00001000
#define GPIO_PUPDR_PUPD6_1                                  0x00002000
#define GPIO_PUPDR_PUPD7                                    0x0000c000
#define GPIO_PUPDR_PUPD7_0                                  0x00004000
#define GPIO_PUPDR_PUPD7_1                                  0x00008000
#define GPIO_PUPDR_PUPD8                                    0x00030000
#define GPIO_PUPDR_PUPD8_0                                  0x00010000
#define GPIO_PUPDR_PUPD8_1                                  0x00020000
#define GPIO_PUPDR_PUPD9                                    0x000c0000
#define GPIO_PUPDR_PUPD9_0                                  0x00040000
#define GPIO_PUPDR_PUPD9_1                                  0x00080000
#define GPIO_PUPDR_PUPD10                                   0x00300000
#define GPIO_PUPDR_PUPD10_0                                 0x00100000
#define GPIO_PUPDR_PUPD10_1                                 0x00200000
#define GPIO_PUPDR_PUPD11                                   0x00c00000
#define GPIO_PUPDR_PUPD11_0                                 0x00400000
#define GPIO_PUPDR_PUPD11_1                                 0x00800000
#define GPIO_PUPDR_PUPD12                                   0x03000000
#define GPIO_PUPDR_PUPD12_0                                 0x01000000
#define GPIO_PUPDR_PUPD12_1                                 0x02000000
#define GPIO_PUPDR_PUPD13                                   0x0c000000
#define GPIO_PUPDR_PUPD13_0                                 0x04000000
#define GPIO_PUPDR_PUPD13_1                                 0x08000000
#define GPIO_PUPDR_PUPD14                                   0x30000000
#define GPIO_PUPDR_PUPD14_0                                 0x10000000
#define GPIO_PUPDR_PUPD14_1                                 0x20000000
#define GPIO_PUPDR_PUPD15                                   0xc0000000
#define GPIO_PUPDR_PUPD15_0                                 0x40000000
#define GPIO_PUPDR_PUPD15_1                                 0x80000000

/******************* bit definitions for IDR register *******************/
#define GPIO_IDR_ID0                                        0x00000001
#define GPIO_IDR_ID1                                        0x00000002
#define GPIO_IDR_ID2                                        0x00000004
#define GPIO_IDR_ID3                                        0x00000008
#define GPIO_IDR_ID4                                        0x00000010
#define GPIO_IDR_ID5                                        0x00000020
#define GPIO_IDR_ID6                                        0x00000040
#define GPIO_IDR_ID7                                        0x00000080
#define GPIO_IDR_ID8                                        0x00000100
#define GPIO_IDR_ID9                                        0x00000200
#define GPIO_IDR_ID10                                       0x00000400
#define GPIO_IDR_ID11                                       0x00000800
#define GPIO_IDR_ID12                                       0x00001000
#define GPIO_IDR_ID13                                       0x00002000
#define GPIO_IDR_ID14                                       0x00004000
#define GPIO_IDR_ID15                                       0x00008000

/******************* bit definitions for ODR register *******************/
#define GPIO_ODR_OD0                                        0x00000001
#define GPIO_ODR_OD1                                        0x00000002
#define GPIO_ODR_OD2                                        0x00000004
#define GPIO_ODR_OD3                                        0x00000008
#define GPIO_ODR_OD4                                        0x00000010
#define GPIO_ODR_OD5                                        0x00000020
#define GPIO_ODR_OD6                                        0x00000040
#define GPIO_ODR_OD7                                        0x00000080
#define GPIO_ODR_OD8                                        0x00000100
#define GPIO_ODR_OD9                                        0x00000200
#define GPIO_ODR_OD10                                       0x00000400
#define GPIO_ODR_OD11                                       0x00000800
#define GPIO_ODR_OD12                                       0x00001000
#define GPIO_ODR_OD13                                       0x00002000
#define GPIO_ODR_OD14                                       0x00004000
#define GPIO_ODR_OD15                                       0x00008000

/****************** bit definitions for BSRR register *******************/
#define GPIO_BSRR_BS0                                       0x00000001
#define GPIO_BSRR_BS1                                       0x00000002
#define GPIO_BSRR_BS2                                       0x00000004
#define GPIO_BSRR_BS3                                       0x00000008
#define GPIO_BSRR_BS4                                       0x00000010
#define GPIO_BSRR_BS5                                       0x00000020
#define GPIO_BSRR_BS6                                       0x00000040
#define GPIO_BSRR_BS7                                       0x00000080
#define GPIO_BSRR_BS8                                       0x00000100
#define GPIO_BSRR_BS9                                       0x00000200
#define GPIO_BSRR_BS10                                      0x00000400
#define GPIO_BSRR_BS11                                      0x00000800
#define GPIO_BSRR_BS12                                      0x00001000
#define GPIO_BSRR_BS13                                      0x00002000
#define GPIO_BSRR_BS14                                      0x00004000
#define GPIO_BSRR_BS15                                      0x00008000
#define GPIO_BSRR_BR0                                       0x00010000
#define GPIO_BSRR_BR1                                       0x00020000
#define GPIO_BSRR_BR2                                       0x00040000
#define GPIO_BSRR_BR3                                       0x00080000
#define GPIO_BSRR_BR4                                       0x00100000
#define GPIO_BSRR_BR5                                       0x00200000
#define GPIO_BSRR_BR6                                       0x00400000
#define GPIO_BSRR_BR7                                       0x00800000
#define GPIO_BSRR_BR8                                       0x01000000
#define GPIO_BSRR_BR9                                       0x02000000
#define GPIO_BSRR_BR10                                      0x04000000
#define GPIO_BSRR_BR11                                      0x08000000
#define GPIO_BSRR_BR12                                      0x10000000
#define GPIO_BSRR_BR13                                      0x20000000
#define GPIO_BSRR_BR14                                      0x40000000
#define GPIO_BSRR_BR15                                      0x80000000

/****************** bit definitions for LCKR register *******************/
#define GPIO_LCKR_LCK0                                      0x00000001
#define GPIO_LCKR_LCK1                                      0x00000002
#define GPIO_LCKR_LCK2                                      0x00000004
#define GPIO_LCKR_LCK3                                      0x00000008
#define GPIO_LCKR_LCK4                                      0x00000010
#define GPIO_LCKR_LCK5                                      0x00000020
#define GPIO_LCKR_LCK6                                      0x00000040
#define GPIO_LCKR_LCK7                                      0x00000080
#define GPIO_LCKR_LCK8                                      0x00000100
#define GPIO_LCKR_LCK9                                      0x00000200
#define GPIO_LCKR_LCK10                                     0x00000400
#define GPIO_LCKR_LCK11                                     0x00000800
#define GPIO_LCKR_LCK12                                     0x00001000
#define GPIO_LCKR_LCK13                                     0x00002000
#define GPIO_LCKR_LCK14                                     0x00004000
#define GPIO_LCKR_LCK15                                     0x00008000
#define GPIO_LCKR_LCKK                                      0x00010000

/****************** bit definitions for AFRL register *******************/
#define GPIO_AFRL_AFSEL0                                    0x0000000f
#define GPIO_AFRL_AFSEL1                                    0x000000f0
#define GPIO_AFRL_AFSEL2                                    0x00000f00
#define GPIO_AFRL_AFSEL3                                    0x0000f000
#define GPIO_AFRL_AFSEL4                                    0x000f0000
#define GPIO_AFRL_AFSEL5                                    0x00f00000
#define GPIO_AFRL_AFSEL6                                    0x0f000000
#define GPIO_AFRL_AFSEL7                                    0xf0000000

/****************** bit definitions for AFRH register *******************/
#define GPIO_AFRH_AFSEL8                                    0x0000000f
#define GPIO_AFRH_AFSEL9                                    0x000000f0
#define GPIO_AFRH_AFSEL10                                   0x00000f00
#define GPIO_AFRH_AFSEL11                                   0x0000f000
#define GPIO_AFRH_AFSEL12                                   0x000f0000
#define GPIO_AFRH_AFSEL13                                   0x00f00000
#define GPIO_AFRH_AFSEL14                                   0x0f000000
#define GPIO_AFRH_AFSEL15                                   0xf0000000

/******************* alternate functions definitions ********************/
#define GPIO_AF0_RTC_50Hz                                   0x00
#define GPIO_AF0_MCO                                        0x00
#define GPIO_AF0_SWJ                                        0x00
#define GPIO_AF0_TRACE                                      0x00
#define GPIO_AF1_TIM1                                       0x01
#define GPIO_AF1_TIM2                                       0x01
#define GPIO_AF2_TIM3                                       0x02
#define GPIO_AF2_TIM4                                       0x02
#define GPIO_AF2_TIM5                                       0x02
#define GPIO_AF3_TIM8                                       0x03
#define GPIO_AF3_TIM9                                       0x03
#define GPIO_AF3_TIM10                                      0x03
#define GPIO_AF3_TIM11                                      0x03
#define GPIO_AF3_LPTIM1                                     0x03
#define GPIO_AF3_CEC                                        0x03
#define GPIO_AF4_I2C1                                       0x04
#define GPIO_AF4_I2C2                                       0x04
#define GPIO_AF4_I2C3                                       0x04
#define GPIO_AF4_I2C4                                       0x04
#define GPIO_AF4_CEC                                        0x04
#define GPIO_AF5_SPI1                                       0x05
#define GPIO_AF5_SPI2                                       0x05
#define GPIO_AF5_SPI3                                       0x05
#define GPIO_AF5_SPI4                                       0x05
#define GPIO_AF5_SPI5                                       0x05
#define GPIO_AF5_SPI6                                       0x05
#define GPIO_AF6_SPI3                                       0x06
#define GPIO_AF6_SAI1                                       0x06
#define GPIO_AF7_USART1                                     0x07
#define GPIO_AF7_USART2                                     0x07
#define GPIO_AF7_USART3                                     0x07
#define GPIO_AF7_UART5                                      0x07
#define GPIO_AF7_SPDIFRX                                    0x07
#define GPIO_AF7_SPI2                                       0x07
#define GPIO_AF7_SPI3                                       0x07
#define GPIO_AF8_UART4                                      0x08
#define GPIO_AF8_UART5                                      0x08
#define GPIO_AF8_USART6                                     0x08
#define GPIO_AF8_UART7                                      0x08
#define GPIO_AF8_UART8                                      0x08
#define GPIO_AF8_SPDIFRX                                    0x08
#define GPIO_AF8_SAI2                                       0x08
#define GPIO_AF9_CAN1                                       0x09
#define GPIO_AF9_CAN2                                       0x09
#define GPIO_AF9_TIM12                                      0x09
#define GPIO_AF9_TIM13                                      0x09
#define GPIO_AF9_TIM14                                      0x09
#define GPIO_AF9_QUADSPI                                    0x09
#define GPIO_AF9_LTDC                                       0x09
#define GPIO_AF10_OTG_FS                                    0x0A
#define GPIO_AF10_OTG_HS                                    0x0A
#define GPIO_AF10_QUADSPI                                   0x0A
#define GPIO_AF10_SAI2                                      0x0A
#define GPIO_AF11_ETH                                       0x0B
#define GPIO_AF12_FMC                                       0x0C
#define GPIO_AF12_OTG_HS_FS                                 0x0C
#define GPIO_AF12_SDMMC1                                    0x0C
#define GPIO_AF13_DCMI                                      0x0D

#endif /* STM32H743_GPIO_H */
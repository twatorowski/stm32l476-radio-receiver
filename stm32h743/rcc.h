/* @file rcc.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: RCC
 */

#ifndef STM32H743_RCC_H
#define STM32H743_RCC_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define RCC_BASE                                            0x58024400U        

/* instances */
#define RCC                                                 ((rcc_t *)RCC_BASE)

/* register bank */
typedef struct {
    reg32_t CR;
    reg32_t ICSCR;
    reg32_t CRRCR;
    reg8_t RESERVED0[4];
    reg32_t CFGR;
    reg8_t RESERVED1[4];
    reg32_t D1CFGR;
    reg32_t D2CFGR;
    reg32_t D3CFGR;
    reg8_t RESERVED2[4];
    reg32_t PLLCKSELR;
    reg32_t PLLCFGR;
    reg32_t PLL1DIVR;
    reg32_t PLL1FRACR;
    reg32_t PLL2DIVR;
    reg32_t PLL2FRACR;
    reg32_t PLL3DIVR;
    reg32_t PLL3FRACR;
    reg8_t RESERVED3[4];
    reg32_t D1CCIPR;
    reg32_t D2CCIP1R;
    reg32_t D2CCIP2R;
    reg32_t D3CCIPR;
    reg8_t RESERVED4[4];
    reg32_t CIER;
    reg32_t CIFR;
    reg32_t CICR;
    reg8_t RESERVED5[4];
    reg32_t BDCR;
    reg32_t CSR;
    reg8_t RESERVED6[4];
    reg32_t AHB3RSTR;
    reg32_t AHB1RSTR;
    reg32_t AHB2RSTR;
    reg32_t AHB4RSTR;
    reg32_t APB3RSTR;
    reg32_t APB1LRSTR;
    reg32_t APB1HRSTR;
    reg32_t APB2RSTR;
    reg32_t APB4RSTR;
    reg32_t GCR;
    reg8_t RESERVED7[4];
    reg32_t D3AMR;
    reg8_t RESERVED8[36];
    reg32_t RSR;
    reg32_t AHB3ENR;
    reg32_t AHB1ENR;
    reg32_t AHB2ENR;
    reg32_t AHB4ENR;
    reg32_t APB3ENR;
    reg32_t APB1LENR;
    reg32_t APB1HENR;
    reg32_t APB2ENR;
    reg32_t APB4ENR;
    reg8_t RESERVED9[4];
    reg32_t AHB3LPENR;
    reg32_t AHB1LPENR;
    reg32_t AHB2LPENR;
    reg32_t AHB4LPENR;
    reg32_t APB3LPENR;
    reg32_t APB1LLPENR;
    reg32_t APB1HLPENR;
    reg32_t APB2LPENR;
    reg32_t APB4LPENR;
    reg8_t RESERVED10[16];
    reg32_t C1_RSR;
    reg32_t C1_AHB3ENR;
    reg32_t C1_AHB1ENR;
    reg32_t C1_AHB2ENR;
    reg32_t C1_AHB4ENR;
    reg32_t C1_APB3ENR;
    reg32_t C1_APB1LENR;
    reg32_t C1_APB1HENR;
    reg32_t C1_APB2ENR;
    reg32_t C1_APB4ENR;
    reg8_t RESERVED11[4];
    reg32_t C1_AHB3LPENR;
    reg32_t C1_AHB1LPENR;
    reg32_t C1_AHB2LPENR;
    reg32_t C1_AHB4LPENR;
    reg32_t C1_APB3LPENR;
    reg32_t C1_APB1LLPENR;
    reg32_t C1_APB1HLPENR;
    reg32_t C1_APB2LPENR;
    reg32_t C1_APB4LPENR;
} rcc_t;

/******************* bit definitions for CR register ********************/
#define RCC_CR_HSION                                        0x00000001
#define RCC_CR_HSIKERON                                     0x00000002
#define RCC_CR_HSIRDY                                       0x00000004
#define RCC_CR_HSIDIV                                       0x00000018
#define RCC_CR_HSIDIVF                                      0x00000020
#define RCC_CR_CSION                                        0x00000080
#define RCC_CR_CSIRDY                                       0x00000100
#define RCC_CR_CSIKERON                                     0x00000200
#define RCC_CR_RC48ON                                       0x00001000
#define RCC_CR_RC48RDY                                      0x00002000
#define RCC_CR_D1CKRDY                                      0x00004000
#define RCC_CR_D2CKRDY                                      0x00008000
#define RCC_CR_HSEON                                        0x00010000
#define RCC_CR_HSERDY                                       0x00020000
#define RCC_CR_HSEBYP                                       0x00040000
#define RCC_CR_HSECSSON                                     0x00080000
#define RCC_CR_PLL1ON                                       0x01000000
#define RCC_CR_PLL1RDY                                      0x02000000
#define RCC_CR_PLL2ON                                       0x04000000
#define RCC_CR_PLL2RDY                                      0x08000000
#define RCC_CR_PLL3ON                                       0x10000000
#define RCC_CR_PLL3RDY                                      0x20000000

/****************** bit definitions for ICSCR register ******************/
#define RCC_ICSCR_HSICAL                                    0x00000fff
#define RCC_ICSCR_HSITRIM                                   0x0003f000
#define RCC_ICSCR_CSICAL                                    0x03fc0000
#define RCC_ICSCR_CSITRIM                                   0x7c000000

/****************** bit definitions for CRRCR register ******************/
#define RCC_CRRCR_RC48CAL                                   0x000003ff

/****************** bit definitions for CFGR register *******************/
#define RCC_CFGR_SW                                         0x00000007
#define RCC_CFGR_SWS                                        0x00000038
#define RCC_CFGR_STOPWUCK                                   0x00000040
#define RCC_CFGR_STOPKERWUCK                                0x00000080
#define RCC_CFGR_RTCPRE                                     0x00003f00
#define RCC_CFGR_HRTIMSEL                                   0x00004000
#define RCC_CFGR_TIMPRE                                     0x00008000
#define RCC_CFGR_MCO1PRE                                    0x003c0000
#define RCC_CFGR_MCO1SEL                                    0x01c00000
#define RCC_CFGR_MCO2PRE                                    0x1e000000
#define RCC_CFGR_MCO2SEL                                    0xe0000000

/***************** bit definitions for D1CFGR register ******************/
#define RCC_D1CFGR_HPRE                                     0x0000000f
#define RCC_D1CFGR_D1PPRE                                   0x00000070
#define RCC_D1CFGR_D1CPRE                                   0x00000f00

/***************** bit definitions for D2CFGR register ******************/
#define RCC_D2CFGR_D2PPRE1                                  0x00000070
#define RCC_D2CFGR_D2PPRE2                                  0x00000700

/***************** bit definitions for D3CFGR register ******************/
#define RCC_D3CFGR_D3PPRE                                   0x00000070

/**************** bit definitions for PLLCKSELR register ****************/
#define RCC_PLLCKSELR_PLLSRC                                0x00000003
#define RCC_PLLCKSELR_DIVM1                                 0x000003f0
#define RCC_PLLCKSELR_DIVM2                                 0x0003f000
#define RCC_PLLCKSELR_DIVM3                                 0x03f00000

/***************** bit definitions for PLLCFGR register *****************/
#define RCC_PLLCFGR_PLL1FRACEN                              0x00000001
#define RCC_PLLCFGR_PLL1VCOSEL                              0x00000002
#define RCC_PLLCFGR_PLL1RGE                                 0x0000000c
#define RCC_PLLCFGR_PLL2FRACEN                              0x00000010
#define RCC_PLLCFGR_PLL2VCOSEL                              0x00000020
#define RCC_PLLCFGR_PLL2RGE                                 0x000000c0
#define RCC_PLLCFGR_PLL3FRACEN                              0x00000100
#define RCC_PLLCFGR_PLL3VCOSEL                              0x00000200
#define RCC_PLLCFGR_PLL3RGE                                 0x00000c00
#define RCC_PLLCFGR_DIVP1EN                                 0x00010000
#define RCC_PLLCFGR_DIVQ1EN                                 0x00020000
#define RCC_PLLCFGR_DIVR1EN                                 0x00040000
#define RCC_PLLCFGR_DIVP2EN                                 0x00080000
#define RCC_PLLCFGR_DIVQ2EN                                 0x00100000
#define RCC_PLLCFGR_DIVR2EN                                 0x00200000
#define RCC_PLLCFGR_DIVP3EN                                 0x00400000
#define RCC_PLLCFGR_DIVQ3EN                                 0x00800000
#define RCC_PLLCFGR_DIVR3EN                                 0x01000000

/**************** bit definitions for PLL1DIVR register *****************/
#define RCC_PLL1DIVR_DIVN1                                  0x000001ff
#define RCC_PLL1DIVR_DIVP1                                  0x0000fe00
#define RCC_PLL1DIVR_DIVQ1                                  0x007f0000
#define RCC_PLL1DIVR_DIVR1                                  0x7f000000

/**************** bit definitions for PLL1FRACR register ****************/
#define RCC_PLL1FRACR_FRACN1                                0x0000fff8

/**************** bit definitions for PLL2DIVR register *****************/
#define RCC_PLL2DIVR_DIVN1                                  0x000001ff
#define RCC_PLL2DIVR_DIVP1                                  0x0000fe00
#define RCC_PLL2DIVR_DIVQ1                                  0x007f0000
#define RCC_PLL2DIVR_DIVR1                                  0x7f000000

/**************** bit definitions for PLL2FRACR register ****************/
#define RCC_PLL2FRACR_FRACN2                                0x0000fff8

/**************** bit definitions for PLL3DIVR register *****************/
#define RCC_PLL3DIVR_DIVN3                                  0x000001ff
#define RCC_PLL3DIVR_DIVP3                                  0x0000fe00
#define RCC_PLL3DIVR_DIVQ3                                  0x007f0000
#define RCC_PLL3DIVR_DIVR3                                  0x7f000000

/**************** bit definitions for PLL3FRACR register ****************/
#define RCC_PLL3FRACR_FRACN3                                0x0000fff8

/***************** bit definitions for D1CCIPR register *****************/
#define RCC_D1CCIPR_FMCSRC                                  0x00000003
#define RCC_D1CCIPR_QSPISRC                                 0x00000030
#define RCC_D1CCIPR_SDMMCSRC                                0x00010000
#define RCC_D1CCIPR_CKPERSRC                                0x30000000

/**************** bit definitions for D2CCIP1R register *****************/
#define RCC_D2CCIP1R_SAI1SRC                                0x00000007
#define RCC_D2CCIP1R_SAI23SRC                               0x000001c0
#define RCC_D2CCIP1R_SPI123SRC                              0x00007000
#define RCC_D2CCIP1R_SPI45SRC                               0x00070000
#define RCC_D2CCIP1R_SPDIFSRC                               0x00300000
#define RCC_D2CCIP1R_DFSDM1SRC                              0x01000000
#define RCC_D2CCIP1R_FDCANSRC                               0x30000000
#define RCC_D2CCIP1R_SWPSRC                                 0x80000000

/**************** bit definitions for D2CCIP2R register *****************/
#define RCC_D2CCIP2R_USART234578SRC                         0x00000007
#define RCC_D2CCIP2R_USART16SRC                             0x00000038
#define RCC_D2CCIP2R_RNGSRC                                 0x00000300
#define RCC_D2CCIP2R_I2C123SRC                              0x00003000
#define RCC_D2CCIP2R_USBSRC                                 0x00300000
#define RCC_D2CCIP2R_CECSRC                                 0x00c00000
#define RCC_D2CCIP2R_LPTIM1SRC                              0x70000000

/***************** bit definitions for D3CCIPR register *****************/
#define RCC_D3CCIPR_LPUART1SRC                              0x00000007
#define RCC_D3CCIPR_I2C4SRC                                 0x00000300
#define RCC_D3CCIPR_LPTIM2SRC                               0x00001c00
#define RCC_D3CCIPR_LPTIM345SRC                             0x0000e000
#define RCC_D3CCIPR_ADCSRC                                  0x00030000
#define RCC_D3CCIPR_SAI4ASRC                                0x00e00000
#define RCC_D3CCIPR_SAI4BSRC                                0x07000000
#define RCC_D3CCIPR_SPI6SRC                                 0x70000000

/****************** bit definitions for CIER register *******************/
#define RCC_CIER_LSIRDYIE                                   0x00000001
#define RCC_CIER_LSERDYIE                                   0x00000002
#define RCC_CIER_HSIRDYIE                                   0x00000004
#define RCC_CIER_HSERDYIE                                   0x00000008
#define RCC_CIER_CSIRDYIE                                   0x00000010
#define RCC_CIER_RC48RDYIE                                  0x00000020
#define RCC_CIER_PLL1RDYIE                                  0x00000040
#define RCC_CIER_PLL2RDYIE                                  0x00000080
#define RCC_CIER_PLL3RDYIE                                  0x00000100
#define RCC_CIER_LSECSSIE                                   0x00000200

/****************** bit definitions for CIFR register *******************/
#define RCC_CIFR_LSIRDYF                                    0x00000001
#define RCC_CIFR_LSERDYF                                    0x00000002
#define RCC_CIFR_HSIRDYF                                    0x00000004
#define RCC_CIFR_HSERDYF                                    0x00000008
#define RCC_CIFR_CSIRDY                                     0x00000010
#define RCC_CIFR_RC48RDYF                                   0x00000020
#define RCC_CIFR_PLL1RDYF                                   0x00000040
#define RCC_CIFR_PLL2RDYF                                   0x00000080
#define RCC_CIFR_PLL3RDYF                                   0x00000100
#define RCC_CIFR_LSECSSF                                    0x00000200
#define RCC_CIFR_HSECSSF                                    0x00000400

/****************** bit definitions for CICR register *******************/
#define RCC_CICR_LSIRDYC                                    0x00000001
#define RCC_CICR_LSERDYC                                    0x00000002
#define RCC_CICR_HSIRDYC                                    0x00000004
#define RCC_CICR_HSERDYC                                    0x00000008
#define RCC_CICR_HSE_READY_INTERRUPT_CLEAR                  0x00000010
#define RCC_CICR_RC48RDYC                                   0x00000020
#define RCC_CICR_PLL1RDYC                                   0x00000040
#define RCC_CICR_PLL2RDYC                                   0x00000080
#define RCC_CICR_PLL3RDYC                                   0x00000100
#define RCC_CICR_LSECSSC                                    0x00000200
#define RCC_CICR_HSECSSC                                    0x00000400

/****************** bit definitions for BDCR register *******************/
#define RCC_BDCR_LSEON                                      0x00000001
#define RCC_BDCR_LSERDY                                     0x00000002
#define RCC_BDCR_LSEBYP                                     0x00000004
#define RCC_BDCR_LSEDRV                                     0x00000018
#define RCC_BDCR_LSECSSON                                   0x00000020
#define RCC_BDCR_LSECSSD                                    0x00000040
#define RCC_BDCR_RTCSRC                                     0x00000300
#define RCC_BDCR_RTCEN                                      0x00008000
#define RCC_BDCR_VSWRST                                     0x00010000

/******************* bit definitions for CSR register *******************/
#define RCC_CSR_LSION                                       0x00000001
#define RCC_CSR_LSIRDY                                      0x00000002

/**************** bit definitions for AHB3RSTR register *****************/
#define RCC_AHB3RSTR_MDMARST                                0x00000001
#define RCC_AHB3RSTR_DMA2DRST                               0x00000010
#define RCC_AHB3RSTR_JPGDECRST                              0x00000020
#define RCC_AHB3RSTR_FMCRST                                 0x00001000
#define RCC_AHB3RSTR_QSPIRST                                0x00004000
#define RCC_AHB3RSTR_SDMMC1RST                              0x00010000
#define RCC_AHB3RSTR_CPURST                                 0x80000000

/**************** bit definitions for AHB1RSTR register *****************/
#define RCC_AHB1RSTR_DMA1RST                                0x00000001
#define RCC_AHB1RSTR_DMA2RST                                0x00000002
#define RCC_AHB1RSTR_ADC12RST                               0x00000020
#define RCC_AHB1RSTR_ETH1MACRST                             0x00008000
#define RCC_AHB1RSTR_USB1OTGRST                             0x02000000
#define RCC_AHB1RSTR_USB2OTGRST                             0x08000000

/**************** bit definitions for AHB2RSTR register *****************/
#define RCC_AHB2RSTR_CAMITFRST                              0x00000001
#define RCC_AHB2RSTR_CRYPTRST                               0x00000010
#define RCC_AHB2RSTR_HASHRST                                0x00000020
#define RCC_AHB2RSTR_RNGRST                                 0x00000040
#define RCC_AHB2RSTR_SDMMC2RST                              0x00000200

/**************** bit definitions for AHB4RSTR register *****************/
#define RCC_AHB4RSTR_GPIOARST                               0x00000001
#define RCC_AHB4RSTR_GPIOBRST                               0x00000002
#define RCC_AHB4RSTR_GPIOCRST                               0x00000004
#define RCC_AHB4RSTR_GPIODRST                               0x00000008
#define RCC_AHB4RSTR_GPIOERST                               0x00000010
#define RCC_AHB4RSTR_GPIOFRST                               0x00000020
#define RCC_AHB4RSTR_GPIOGRST                               0x00000040
#define RCC_AHB4RSTR_GPIOHRST                               0x00000080
#define RCC_AHB4RSTR_GPIOIRST                               0x00000100
#define RCC_AHB4RSTR_GPIOJRST                               0x00000200
#define RCC_AHB4RSTR_GPIOKRST                               0x00000400
#define RCC_AHB4RSTR_CRCRST                                 0x00080000
#define RCC_AHB4RSTR_BDMARST                                0x00200000
#define RCC_AHB4RSTR_ADC3RST                                0x01000000
#define RCC_AHB4RSTR_HSEMRST                                0x02000000

/**************** bit definitions for APB3RSTR register *****************/
#define RCC_APB3RSTR_LTDCRST                                0x00000008

/**************** bit definitions for APB1LRSTR register ****************/
#define RCC_APB1LRSTR_TIM2RST                               0x00000001
#define RCC_APB1LRSTR_TIM3RST                               0x00000002
#define RCC_APB1LRSTR_TIM4RST                               0x00000004
#define RCC_APB1LRSTR_TIM5RST                               0x00000008
#define RCC_APB1LRSTR_TIM6RST                               0x00000010
#define RCC_APB1LRSTR_TIM7RST                               0x00000020
#define RCC_APB1LRSTR_TIM12RST                              0x00000040
#define RCC_APB1LRSTR_TIM13RST                              0x00000080
#define RCC_APB1LRSTR_TIM14RST                              0x00000100
#define RCC_APB1LRSTR_LPTIM1RST                             0x00000200
#define RCC_APB1LRSTR_SPI2RST                               0x00004000
#define RCC_APB1LRSTR_SPI3RST                               0x00008000
#define RCC_APB1LRSTR_SPDIFRXRST                            0x00010000
#define RCC_APB1LRSTR_USART2RST                             0x00020000
#define RCC_APB1LRSTR_USART3RST                             0x00040000
#define RCC_APB1LRSTR_UART4RST                              0x00080000
#define RCC_APB1LRSTR_UART5RST                              0x00100000
#define RCC_APB1LRSTR_I2C1RST                               0x00200000
#define RCC_APB1LRSTR_I2C2RST                               0x00400000
#define RCC_APB1LRSTR_I2C3RST                               0x00800000
#define RCC_APB1LRSTR_CECRST                                0x08000000
#define RCC_APB1LRSTR_DAC12RST                              0x20000000
#define RCC_APB1LRSTR_USART7RST                             0x40000000
#define RCC_APB1LRSTR_USART8RST                             0x80000000

/**************** bit definitions for APB1HRSTR register ****************/
#define RCC_APB1HRSTR_CRSRST                                0x00000002
#define RCC_APB1HRSTR_SWPRST                                0x00000004
#define RCC_APB1HRSTR_OPAMPRST                              0x00000010
#define RCC_APB1HRSTR_MDIOSRST                              0x00000020
#define RCC_APB1HRSTR_FDCANRST                              0x00000100

/**************** bit definitions for APB2RSTR register *****************/
#define RCC_APB2RSTR_TIM1RST                                0x00000001
#define RCC_APB2RSTR_TIM8RST                                0x00000002
#define RCC_APB2RSTR_USART1RST                              0x00000010
#define RCC_APB2RSTR_USART6RST                              0x00000020
#define RCC_APB2RSTR_SPI1RST                                0x00001000
#define RCC_APB2RSTR_SPI4RST                                0x00002000
#define RCC_APB2RSTR_TIM15RST                               0x00010000
#define RCC_APB2RSTR_TIM16RST                               0x00020000
#define RCC_APB2RSTR_TIM17RST                               0x00040000
#define RCC_APB2RSTR_SPI5RST                                0x00100000
#define RCC_APB2RSTR_SAI1RST                                0x00400000
#define RCC_APB2RSTR_SAI2RST                                0x00800000
#define RCC_APB2RSTR_SAI3RST                                0x01000000
#define RCC_APB2RSTR_DFSDM1RST                              0x10000000
#define RCC_APB2RSTR_HRTIMRST                               0x20000000

/**************** bit definitions for APB4RSTR register *****************/
#define RCC_APB4RSTR_SYSCFGRST                              0x00000002
#define RCC_APB4RSTR_LPUART1RST                             0x00000008
#define RCC_APB4RSTR_SPI6RST                                0x00000020
#define RCC_APB4RSTR_I2C4RST                                0x00000080
#define RCC_APB4RSTR_LPTIM2RST                              0x00000200
#define RCC_APB4RSTR_LPTIM3RST                              0x00000400
#define RCC_APB4RSTR_LPTIM4RST                              0x00000800
#define RCC_APB4RSTR_LPTIM5RST                              0x00001000
#define RCC_APB4RSTR_COMP12RST                              0x00004000
#define RCC_APB4RSTR_VREFRST                                0x00008000
#define RCC_APB4RSTR_SAI4RST                                0x00200000

/******************* bit definitions for GCR register *******************/
#define RCC_GCR_WW1RSC                                      0x00000001

/****************** bit definitions for D3AMR register ******************/
#define RCC_D3AMR_BDMAAMEN                                  0x00000001
#define RCC_D3AMR_LPUART1AMEN                               0x00000008
#define RCC_D3AMR_SPI6AMEN                                  0x00000020
#define RCC_D3AMR_I2C4AMEN                                  0x00000080
#define RCC_D3AMR_LPTIM2AMEN                                0x00000200
#define RCC_D3AMR_LPTIM3AMEN                                0x00000400
#define RCC_D3AMR_LPTIM4AMEN                                0x00000800
#define RCC_D3AMR_LPTIM5AMEN                                0x00001000
#define RCC_D3AMR_COMP12AMEN                                0x00004000
#define RCC_D3AMR_VREFAMEN                                  0x00008000
#define RCC_D3AMR_RTCAMEN                                   0x00010000
#define RCC_D3AMR_CRCAMEN                                   0x00080000
#define RCC_D3AMR_SAI4AMEN                                  0x00200000
#define RCC_D3AMR_ADC3AMEN                                  0x01000000
#define RCC_D3AMR_BKPRAMAMEN                                0x10000000
#define RCC_D3AMR_SRAM4AMEN                                 0x20000000

/******************* bit definitions for RSR register *******************/
#define RCC_RSR_RMVF                                        0x00010000
#define RCC_RSR_CPURSTF                                     0x00020000
#define RCC_RSR_D1RSTF                                      0x00080000
#define RCC_RSR_D2RSTF                                      0x00100000
#define RCC_RSR_BORRSTF                                     0x00200000
#define RCC_RSR_PINRSTF                                     0x00400000
#define RCC_RSR_PORRSTF                                     0x00800000
#define RCC_RSR_SFTRSTF                                     0x01000000
#define RCC_RSR_IWDG1RSTF                                   0x04000000
#define RCC_RSR_WWDG1RSTF                                   0x10000000
#define RCC_RSR_LPWRRSTF                                    0x40000000

/***************** bit definitions for AHB3ENR register *****************/
#define RCC_AHB3ENR_MDMAEN                                  0x00000001
#define RCC_AHB3ENR_DMA2DEN                                 0x00000010
#define RCC_AHB3ENR_JPGDECEN                                0x00000020
#define RCC_AHB3ENR_FMCEN                                   0x00001000
#define RCC_AHB3ENR_QSPIEN                                  0x00004000
#define RCC_AHB3ENR_SDMMC1EN                                0x00010000

/***************** bit definitions for AHB1ENR register *****************/
#define RCC_AHB1ENR_DMA1EN                                  0x00000001
#define RCC_AHB1ENR_DMA2EN                                  0x00000002
#define RCC_AHB1ENR_ADC12EN                                 0x00000020
#define RCC_AHB1ENR_ETH1MACEN                               0x00008000
#define RCC_AHB1ENR_ETH1TXEN                                0x00010000
#define RCC_AHB1ENR_ETH1RXEN                                0x00020000
#define RCC_AHB1ENR_USB2OTGHSULPIEN                         0x00040000
#define RCC_AHB1ENR_USB1OTGEN                               0x02000000
#define RCC_AHB1ENR_USB1ULPIEN                              0x04000000
#define RCC_AHB1ENR_USB2OTGEN                               0x08000000
#define RCC_AHB1ENR_USB2ULPIEN                              0x10000000

/***************** bit definitions for AHB2ENR register *****************/
#define RCC_AHB2ENR_CAMITFEN                                0x00000001
#define RCC_AHB2ENR_CRYPTEN                                 0x00000010
#define RCC_AHB2ENR_HASHEN                                  0x00000020
#define RCC_AHB2ENR_RNGEN                                   0x00000040
#define RCC_AHB2ENR_SDMMC2EN                                0x00000200
#define RCC_AHB2ENR_SRAM1EN                                 0x20000000
#define RCC_AHB2ENR_SRAM2EN                                 0x40000000
#define RCC_AHB2ENR_SRAM3EN                                 0x80000000

/***************** bit definitions for AHB4ENR register *****************/
#define RCC_AHB4ENR_GPIOAEN                                 0x00000001
#define RCC_AHB4ENR_GPIOBEN                                 0x00000002
#define RCC_AHB4ENR_GPIOCEN                                 0x00000004
#define RCC_AHB4ENR_GPIODEN                                 0x00000008
#define RCC_AHB4ENR_GPIOEEN                                 0x00000010
#define RCC_AHB4ENR_GPIOFEN                                 0x00000020
#define RCC_AHB4ENR_GPIOGEN                                 0x00000040
#define RCC_AHB4ENR_GPIOHEN                                 0x00000080
#define RCC_AHB4ENR_GPIOIEN                                 0x00000100
#define RCC_AHB4ENR_GPIOJEN                                 0x00000200
#define RCC_AHB4ENR_GPIOKEN                                 0x00000400
#define RCC_AHB4ENR_CRCEN                                   0x00080000
#define RCC_AHB4ENR_BDMAEN                                  0x00200000
#define RCC_AHB4ENR_ADC3EN                                  0x01000000
#define RCC_AHB4ENR_HSEMEN                                  0x02000000
#define RCC_AHB4ENR_BKPRAMEN                                0x10000000

/***************** bit definitions for APB3ENR register *****************/
#define RCC_APB3ENR_LTDCEN                                  0x00000008
#define RCC_APB3ENR_WWDG1EN                                 0x00000040

/**************** bit definitions for APB1LENR register *****************/
#define RCC_APB1LENR_TIM2EN                                 0x00000001
#define RCC_APB1LENR_TIM3EN                                 0x00000002
#define RCC_APB1LENR_TIM4EN                                 0x00000004
#define RCC_APB1LENR_TIM5EN                                 0x00000008
#define RCC_APB1LENR_TIM6EN                                 0x00000010
#define RCC_APB1LENR_TIM7EN                                 0x00000020
#define RCC_APB1LENR_TIM12EN                                0x00000040
#define RCC_APB1LENR_TIM13EN                                0x00000080
#define RCC_APB1LENR_TIM14EN                                0x00000100
#define RCC_APB1LENR_LPTIM1EN                               0x00000200
#define RCC_APB1LENR_SPI2EN                                 0x00004000
#define RCC_APB1LENR_SPI3EN                                 0x00008000
#define RCC_APB1LENR_SPDIFRXEN                              0x00010000
#define RCC_APB1LENR_USART2EN                               0x00020000
#define RCC_APB1LENR_USART3EN                               0x00040000
#define RCC_APB1LENR_UART4EN                                0x00080000
#define RCC_APB1LENR_UART5EN                                0x00100000
#define RCC_APB1LENR_I2C1EN                                 0x00200000
#define RCC_APB1LENR_I2C2EN                                 0x00400000
#define RCC_APB1LENR_I2C3EN                                 0x00800000
#define RCC_APB1LENR_CECEN                                  0x08000000
#define RCC_APB1LENR_DAC12EN                                0x20000000
#define RCC_APB1LENR_USART7EN                               0x40000000
#define RCC_APB1LENR_USART8EN                               0x80000000

/**************** bit definitions for APB1HENR register *****************/
#define RCC_APB1HENR_CRSEN                                  0x00000002
#define RCC_APB1HENR_SWPEN                                  0x00000004
#define RCC_APB1HENR_OPAMPEN                                0x00000010
#define RCC_APB1HENR_MDIOSEN                                0x00000020
#define RCC_APB1HENR_FDCANEN                                0x00000100

/***************** bit definitions for APB2ENR register *****************/
#define RCC_APB2ENR_TIM1EN                                  0x00000001
#define RCC_APB2ENR_TIM8EN                                  0x00000002
#define RCC_APB2ENR_USART1EN                                0x00000010
#define RCC_APB2ENR_USART6EN                                0x00000020
#define RCC_APB2ENR_SPI1EN                                  0x00001000
#define RCC_APB2ENR_SPI4EN                                  0x00002000
#define RCC_APB2ENR_TIM16EN                                 0x00020000
#define RCC_APB2ENR_TIM15EN                                 0x00010000
#define RCC_APB2ENR_TIM17EN                                 0x00040000
#define RCC_APB2ENR_SPI5EN                                  0x00100000
#define RCC_APB2ENR_SAI1EN                                  0x00400000
#define RCC_APB2ENR_SAI2EN                                  0x00800000
#define RCC_APB2ENR_SAI3EN                                  0x01000000
#define RCC_APB2ENR_DFSDM1EN                                0x10000000
#define RCC_APB2ENR_HRTIMEN                                 0x20000000

/***************** bit definitions for APB4ENR register *****************/
#define RCC_APB4ENR_SYSCFGEN                                0x00000002
#define RCC_APB4ENR_LPUART1EN                               0x00000008
#define RCC_APB4ENR_SPI6EN                                  0x00000020
#define RCC_APB4ENR_I2C4EN                                  0x00000080
#define RCC_APB4ENR_LPTIM2EN                                0x00000200
#define RCC_APB4ENR_LPTIM3EN                                0x00000400
#define RCC_APB4ENR_LPTIM4EN                                0x00000800
#define RCC_APB4ENR_LPTIM5EN                                0x00001000
#define RCC_APB4ENR_COMP12EN                                0x00004000
#define RCC_APB4ENR_VREFEN                                  0x00008000
#define RCC_APB4ENR_RTCAPBEN                                0x00010000
#define RCC_APB4ENR_SAI4EN                                  0x00200000

/**************** bit definitions for AHB3LPENR register ****************/
#define RCC_AHB3LPENR_MDMALPEN                              0x00000001
#define RCC_AHB3LPENR_DMA2DLPEN                             0x00000010
#define RCC_AHB3LPENR_JPGDECLPEN                            0x00000020
#define RCC_AHB3LPENR_FLASHLPEN                             0x00000100
#define RCC_AHB3LPENR_FMCLPEN                               0x00001000
#define RCC_AHB3LPENR_QSPILPEN                              0x00004000
#define RCC_AHB3LPENR_SDMMC1LPEN                            0x00010000
#define RCC_AHB3LPENR_D1DTCM1LPEN                           0x10000000
#define RCC_AHB3LPENR_DTCM2LPEN                             0x20000000
#define RCC_AHB3LPENR_ITCMLPEN                              0x40000000
#define RCC_AHB3LPENR_AXISRAMLPEN                           0x80000000

/**************** bit definitions for AHB1LPENR register ****************/
#define RCC_AHB1LPENR_DMA1LPEN                              0x00000001
#define RCC_AHB1LPENR_DMA2LPEN                              0x00000002
#define RCC_AHB1LPENR_ADC12LPEN                             0x00000020
#define RCC_AHB1LPENR_ETH1MACLPEN                           0x00008000
#define RCC_AHB1LPENR_ETH1TXLPEN                            0x00010000
#define RCC_AHB1LPENR_ETH1RXLPEN                            0x00020000
#define RCC_AHB1LPENR_USB1OTGHSLPEN                         0x02000000
#define RCC_AHB1LPENR_USB1OTGHSULPILPEN                     0x04000000
#define RCC_AHB1LPENR_USB2OTGHSLPEN                         0x08000000
#define RCC_AHB1LPENR_USB2OTGHSULPILPEN                     0x10000000

/**************** bit definitions for AHB2LPENR register ****************/
#define RCC_AHB2LPENR_CAMITFLPEN                            0x00000001
#define RCC_AHB2LPENR_CRYPTLPEN                             0x00000010
#define RCC_AHB2LPENR_HASHLPEN                              0x00000020
#define RCC_AHB2LPENR_SDMMC2LPEN                            0x00000200
#define RCC_AHB2LPENR_RNGLPEN                               0x00000040
#define RCC_AHB2LPENR_SRAM1LPEN                             0x20000000
#define RCC_AHB2LPENR_SRAM2LPEN                             0x40000000
#define RCC_AHB2LPENR_SRAM3LPEN                             0x80000000

/**************** bit definitions for AHB4LPENR register ****************/
#define RCC_AHB4LPENR_GPIOALPEN                             0x00000001
#define RCC_AHB4LPENR_GPIOBLPEN                             0x00000002
#define RCC_AHB4LPENR_GPIOCLPEN                             0x00000004
#define RCC_AHB4LPENR_GPIODLPEN                             0x00000008
#define RCC_AHB4LPENR_GPIOELPEN                             0x00000010
#define RCC_AHB4LPENR_GPIOFLPEN                             0x00000020
#define RCC_AHB4LPENR_GPIOGLPEN                             0x00000040
#define RCC_AHB4LPENR_GPIOHLPEN                             0x00000080
#define RCC_AHB4LPENR_GPIOILPEN                             0x00000100
#define RCC_AHB4LPENR_GPIOJLPEN                             0x00000200
#define RCC_AHB4LPENR_GPIOKLPEN                             0x00000400
#define RCC_AHB4LPENR_CRCLPEN                               0x00080000
#define RCC_AHB4LPENR_BDMALPEN                              0x00200000
#define RCC_AHB4LPENR_ADC3LPEN                              0x01000000
#define RCC_AHB4LPENR_BKPRAMLPEN                            0x10000000
#define RCC_AHB4LPENR_SRAM4LPEN                             0x20000000

/**************** bit definitions for APB3LPENR register ****************/
#define RCC_APB3LPENR_LTDCLPEN                              0x00000008
#define RCC_APB3LPENR_WWDG1LPEN                             0x00000040

/*************** bit definitions for APB1LLPENR register ****************/
#define RCC_APB1LLPENR_TIM2LPEN                             0x00000001
#define RCC_APB1LLPENR_TIM3LPEN                             0x00000002
#define RCC_APB1LLPENR_TIM4LPEN                             0x00000004
#define RCC_APB1LLPENR_TIM5LPEN                             0x00000008
#define RCC_APB1LLPENR_TIM6LPEN                             0x00000010
#define RCC_APB1LLPENR_TIM7LPEN                             0x00000020
#define RCC_APB1LLPENR_TIM12LPEN                            0x00000040
#define RCC_APB1LLPENR_TIM13LPEN                            0x00000080
#define RCC_APB1LLPENR_TIM14LPEN                            0x00000100
#define RCC_APB1LLPENR_LPTIM1LPEN                           0x00000200
#define RCC_APB1LLPENR_SPI2LPEN                             0x00004000
#define RCC_APB1LLPENR_SPI3LPEN                             0x00008000
#define RCC_APB1LLPENR_SPDIFRXLPEN                          0x00010000
#define RCC_APB1LLPENR_USART2LPEN                           0x00020000
#define RCC_APB1LLPENR_USART3LPEN                           0x00040000
#define RCC_APB1LLPENR_UART4LPEN                            0x00080000
#define RCC_APB1LLPENR_UART5LPEN                            0x00100000
#define RCC_APB1LLPENR_I2C1LPEN                             0x00200000
#define RCC_APB1LLPENR_I2C2LPEN                             0x00400000
#define RCC_APB1LLPENR_I2C3LPEN                             0x00800000
#define RCC_APB1LLPENR_HDMICECLPEN                          0x08000000
#define RCC_APB1LLPENR_DAC12LPEN                            0x20000000
#define RCC_APB1LLPENR_USART7LPEN                           0x40000000
#define RCC_APB1LLPENR_USART8LPEN                           0x80000000

/*************** bit definitions for APB1HLPENR register ****************/
#define RCC_APB1HLPENR_CRSLPEN                              0x00000002
#define RCC_APB1HLPENR_SWPLPEN                              0x00000004
#define RCC_APB1HLPENR_OPAMPLPEN                            0x00000010
#define RCC_APB1HLPENR_MDIOSLPEN                            0x00000020
#define RCC_APB1HLPENR_FDCANLPEN                            0x00000100

/**************** bit definitions for APB2LPENR register ****************/
#define RCC_APB2LPENR_TIM1LPEN                              0x00000001
#define RCC_APB2LPENR_TIM8LPEN                              0x00000002
#define RCC_APB2LPENR_USART1LPEN                            0x00000010
#define RCC_APB2LPENR_USART6LPEN                            0x00000020
#define RCC_APB2LPENR_SPI1LPEN                              0x00001000
#define RCC_APB2LPENR_SPI4LPEN                              0x00002000
#define RCC_APB2LPENR_TIM15LPEN                             0x00010000
#define RCC_APB2LPENR_TIM16LPEN                             0x00020000
#define RCC_APB2LPENR_TIM17LPEN                             0x00040000
#define RCC_APB2LPENR_SPI5LPEN                              0x00100000
#define RCC_APB2LPENR_SAI1LPEN                              0x00400000
#define RCC_APB2LPENR_SAI2LPEN                              0x00800000
#define RCC_APB2LPENR_SAI3LPEN                              0x01000000
#define RCC_APB2LPENR_DFSDM1LPEN                            0x10000000
#define RCC_APB2LPENR_HRTIMLPEN                             0x20000000

/**************** bit definitions for APB4LPENR register ****************/
#define RCC_APB4LPENR_SYSCFGLPEN                            0x00000002
#define RCC_APB4LPENR_LPUART1LPEN                           0x00000008
#define RCC_APB4LPENR_SPI6LPEN                              0x00000020
#define RCC_APB4LPENR_I2C4LPEN                              0x00000080
#define RCC_APB4LPENR_LPTIM2LPEN                            0x00000200
#define RCC_APB4LPENR_LPTIM3LPEN                            0x00000400
#define RCC_APB4LPENR_LPTIM4LPEN                            0x00000800
#define RCC_APB4LPENR_LPTIM5LPEN                            0x00001000
#define RCC_APB4LPENR_COMP12LPEN                            0x00004000
#define RCC_APB4LPENR_VREFLPEN                              0x00008000
#define RCC_APB4LPENR_RTCAPBLPEN                            0x00010000
#define RCC_APB4LPENR_SAI4LPEN                              0x00200000

/***************** bit definitions for C1_RSR register ******************/
#define RCC_C1_RSR_RMVF                                     0x00010000
#define RCC_C1_RSR_CPURSTF                                  0x00020000
#define RCC_C1_RSR_D1RSTF                                   0x00080000
#define RCC_C1_RSR_D2RSTF                                   0x00100000
#define RCC_C1_RSR_BORRSTF                                  0x00200000
#define RCC_C1_RSR_PINRSTF                                  0x00400000
#define RCC_C1_RSR_PORRSTF                                  0x00800000
#define RCC_C1_RSR_SFTRSTF                                  0x01000000
#define RCC_C1_RSR_IWDG1RSTF                                0x04000000
#define RCC_C1_RSR_WWDG1RSTF                                0x10000000
#define RCC_C1_RSR_LPWRRSTF                                 0x40000000

/*************** bit definitions for C1_AHB3ENR register ****************/
#define RCC_C1_AHB3ENR_MDMAEN                               0x00000001
#define RCC_C1_AHB3ENR_DMA2DEN                              0x00000010
#define RCC_C1_AHB3ENR_JPGDECEN                             0x00000020
#define RCC_C1_AHB3ENR_FMCEN                                0x00001000
#define RCC_C1_AHB3ENR_QSPIEN                               0x00004000
#define RCC_C1_AHB3ENR_SDMMC1EN                             0x00010000

/*************** bit definitions for C1_AHB1ENR register ****************/
#define RCC_C1_AHB1ENR_DMA1EN                               0x00000001
#define RCC_C1_AHB1ENR_DMA2EN                               0x00000002
#define RCC_C1_AHB1ENR_ADC12EN                              0x00000020
#define RCC_C1_AHB1ENR_ETH1MACEN                            0x00008000
#define RCC_C1_AHB1ENR_ETH1TXEN                             0x00010000
#define RCC_C1_AHB1ENR_ETH1RXEN                             0x00020000
#define RCC_C1_AHB1ENR_USB1OTGEN                            0x02000000
#define RCC_C1_AHB1ENR_USB1ULPIEN                           0x04000000
#define RCC_C1_AHB1ENR_USB2OTGEN                            0x08000000
#define RCC_C1_AHB1ENR_USB2ULPIEN                           0x10000000

/*************** bit definitions for C1_AHB2ENR register ****************/
#define RCC_C1_AHB2ENR_CAMITFEN                             0x00000001
#define RCC_C1_AHB2ENR_CRYPTEN                              0x00000010
#define RCC_C1_AHB2ENR_HASHEN                               0x00000020
#define RCC_C1_AHB2ENR_RNGEN                                0x00000040
#define RCC_C1_AHB2ENR_SDMMC2EN                             0x00000200
#define RCC_C1_AHB2ENR_SRAM1EN                              0x20000000
#define RCC_C1_AHB2ENR_SRAM2EN                              0x40000000
#define RCC_C1_AHB2ENR_SRAM3EN                              0x80000000

/*************** bit definitions for C1_AHB4ENR register ****************/
#define RCC_C1_AHB4ENR_GPIOAEN                              0x00000001
#define RCC_C1_AHB4ENR_GPIOBEN                              0x00000002
#define RCC_C1_AHB4ENR_GPIOCEN                              0x00000004
#define RCC_C1_AHB4ENR_GPIODEN                              0x00000008
#define RCC_C1_AHB4ENR_GPIOEEN                              0x00000010
#define RCC_C1_AHB4ENR_GPIOFEN                              0x00000020
#define RCC_C1_AHB4ENR_GPIOGEN                              0x00000040
#define RCC_C1_AHB4ENR_GPIOHEN                              0x00000080
#define RCC_C1_AHB4ENR_GPIOIEN                              0x00000100
#define RCC_C1_AHB4ENR_GPIOJEN                              0x00000200
#define RCC_C1_AHB4ENR_GPIOKEN                              0x00000400
#define RCC_C1_AHB4ENR_CRCEN                                0x00080000
#define RCC_C1_AHB4ENR_BDMAEN                               0x00200000
#define RCC_C1_AHB4ENR_ADC3EN                               0x01000000
#define RCC_C1_AHB4ENR_HSEMEN                               0x02000000
#define RCC_C1_AHB4ENR_BKPRAMEN                             0x10000000

/*************** bit definitions for C1_APB3ENR register ****************/
#define RCC_C1_APB3ENR_LTDCEN                               0x00000008
#define RCC_C1_APB3ENR_WWDG1EN                              0x00000040

/*************** bit definitions for C1_APB1LENR register ***************/
#define RCC_C1_APB1LENR_TIM2EN                              0x00000001
#define RCC_C1_APB1LENR_TIM3EN                              0x00000002
#define RCC_C1_APB1LENR_TIM4EN                              0x00000004
#define RCC_C1_APB1LENR_TIM5EN                              0x00000008
#define RCC_C1_APB1LENR_TIM6EN                              0x00000010
#define RCC_C1_APB1LENR_TIM7EN                              0x00000020
#define RCC_C1_APB1LENR_TIM12EN                             0x00000040
#define RCC_C1_APB1LENR_TIM13EN                             0x00000080
#define RCC_C1_APB1LENR_TIM14EN                             0x00000100
#define RCC_C1_APB1LENR_LPTIM1EN                            0x00000200
#define RCC_C1_APB1LENR_SPI2EN                              0x00004000
#define RCC_C1_APB1LENR_SPI3EN                              0x00008000
#define RCC_C1_APB1LENR_SPDIFRXEN                           0x00010000
#define RCC_C1_APB1LENR_USART2EN                            0x00020000
#define RCC_C1_APB1LENR_USART3EN                            0x00040000
#define RCC_C1_APB1LENR_UART4EN                             0x00080000
#define RCC_C1_APB1LENR_UART5EN                             0x00100000
#define RCC_C1_APB1LENR_I2C1EN                              0x00200000
#define RCC_C1_APB1LENR_I2C2EN                              0x00400000
#define RCC_C1_APB1LENR_I2C3EN                              0x00800000
#define RCC_C1_APB1LENR_HDMICECEN                           0x08000000
#define RCC_C1_APB1LENR_DAC12EN                             0x20000000
#define RCC_C1_APB1LENR_USART7EN                            0x40000000
#define RCC_C1_APB1LENR_USART8EN                            0x80000000

/*************** bit definitions for C1_APB1HENR register ***************/
#define RCC_C1_APB1HENR_CRSEN                               0x00000002
#define RCC_C1_APB1HENR_SWPEN                               0x00000004
#define RCC_C1_APB1HENR_OPAMPEN                             0x00000010
#define RCC_C1_APB1HENR_MDIOSEN                             0x00000020
#define RCC_C1_APB1HENR_FDCANEN                             0x00000100

/*************** bit definitions for C1_APB2ENR register ****************/
#define RCC_C1_APB2ENR_TIM1EN                               0x00000001
#define RCC_C1_APB2ENR_TIM8EN                               0x00000002
#define RCC_C1_APB2ENR_USART1EN                             0x00000010
#define RCC_C1_APB2ENR_USART6EN                             0x00000020
#define RCC_C1_APB2ENR_SPI1EN                               0x00001000
#define RCC_C1_APB2ENR_SPI4EN                               0x00002000
#define RCC_C1_APB2ENR_TIM16EN                              0x00020000
#define RCC_C1_APB2ENR_TIM15EN                              0x00010000
#define RCC_C1_APB2ENR_TIM17EN                              0x00040000
#define RCC_C1_APB2ENR_SPI5EN                               0x00100000
#define RCC_C1_APB2ENR_SAI1EN                               0x00400000
#define RCC_C1_APB2ENR_SAI2EN                               0x00800000
#define RCC_C1_APB2ENR_SAI3EN                               0x01000000
#define RCC_C1_APB2ENR_DFSDM1EN                             0x10000000
#define RCC_C1_APB2ENR_HRTIMEN                              0x20000000

/*************** bit definitions for C1_APB4ENR register ****************/
#define RCC_C1_APB4ENR_SYSCFGEN                             0x00000002
#define RCC_C1_APB4ENR_LPUART1EN                            0x00000008
#define RCC_C1_APB4ENR_SPI6EN                               0x00000020
#define RCC_C1_APB4ENR_I2C4EN                               0x00000080
#define RCC_C1_APB4ENR_LPTIM2EN                             0x00000200
#define RCC_C1_APB4ENR_LPTIM3EN                             0x00000400
#define RCC_C1_APB4ENR_LPTIM4EN                             0x00000800
#define RCC_C1_APB4ENR_LPTIM5EN                             0x00001000
#define RCC_C1_APB4ENR_COMP12EN                             0x00004000
#define RCC_C1_APB4ENR_VREFEN                               0x00008000
#define RCC_C1_APB4ENR_RTCAPBEN                             0x00010000
#define RCC_C1_APB4ENR_SAI4EN                               0x00200000

/************** bit definitions for C1_AHB3LPENR register ***************/
#define RCC_C1_AHB3LPENR_MDMALPEN                           0x00000001
#define RCC_C1_AHB3LPENR_DMA2DLPEN                          0x00000010
#define RCC_C1_AHB3LPENR_JPGDECLPEN                         0x00000020
#define RCC_C1_AHB3LPENR_FLITFLPEN                          0x00000100
#define RCC_C1_AHB3LPENR_FMCLPEN                            0x00001000
#define RCC_C1_AHB3LPENR_QSPILPEN                           0x00004000
#define RCC_C1_AHB3LPENR_SDMMC1LPEN                         0x00010000
#define RCC_C1_AHB3LPENR_D1DTCM1LPEN                        0x10000000
#define RCC_C1_AHB3LPENR_DTCM2LPEN                          0x20000000
#define RCC_C1_AHB3LPENR_ITCMLPEN                           0x40000000
#define RCC_C1_AHB3LPENR_AXISRAMLPEN                        0x80000000

/************** bit definitions for C1_AHB1LPENR register ***************/
#define RCC_C1_AHB1LPENR_DMA1LPEN                           0x00000001
#define RCC_C1_AHB1LPENR_DMA2LPEN                           0x00000002
#define RCC_C1_AHB1LPENR_ADC12LPEN                          0x00000020
#define RCC_C1_AHB1LPENR_ETH1MACLPEN                        0x00008000
#define RCC_C1_AHB1LPENR_ETH1TXLPEN                         0x00010000
#define RCC_C1_AHB1LPENR_ETH1RXLPEN                         0x00020000
#define RCC_C1_AHB1LPENR_USB1OTGLPEN                        0x02000000
#define RCC_C1_AHB1LPENR_USB1ULPILPEN                       0x04000000
#define RCC_C1_AHB1LPENR_USB2OTGLPEN                        0x08000000
#define RCC_C1_AHB1LPENR_USB2ULPILPEN                       0x10000000

/************** bit definitions for C1_AHB2LPENR register ***************/
#define RCC_C1_AHB2LPENR_CAMITFLPEN                         0x00000001
#define RCC_C1_AHB2LPENR_CRYPTLPEN                          0x00000010
#define RCC_C1_AHB2LPENR_HASHLPEN                           0x00000020
#define RCC_C1_AHB2LPENR_SDMMC2LPEN                         0x00000200
#define RCC_C1_AHB2LPENR_RNGLPEN                            0x00000040
#define RCC_C1_AHB2LPENR_SRAM1LPEN                          0x20000000
#define RCC_C1_AHB2LPENR_SRAM2LPEN                          0x40000000
#define RCC_C1_AHB2LPENR_SRAM3LPEN                          0x80000000

/************** bit definitions for C1_AHB4LPENR register ***************/
#define RCC_C1_AHB4LPENR_GPIOALPEN                          0x00000001
#define RCC_C1_AHB4LPENR_GPIOBLPEN                          0x00000002
#define RCC_C1_AHB4LPENR_GPIOCLPEN                          0x00000004
#define RCC_C1_AHB4LPENR_GPIODLPEN                          0x00000008
#define RCC_C1_AHB4LPENR_GPIOELPEN                          0x00000010
#define RCC_C1_AHB4LPENR_GPIOFLPEN                          0x00000020
#define RCC_C1_AHB4LPENR_GPIOGLPEN                          0x00000040
#define RCC_C1_AHB4LPENR_GPIOHLPEN                          0x00000080
#define RCC_C1_AHB4LPENR_GPIOILPEN                          0x00000100
#define RCC_C1_AHB4LPENR_GPIOJLPEN                          0x00000200
#define RCC_C1_AHB4LPENR_GPIOKLPEN                          0x00000400
#define RCC_C1_AHB4LPENR_CRCLPEN                            0x00080000
#define RCC_C1_AHB4LPENR_BDMALPEN                           0x00200000
#define RCC_C1_AHB4LPENR_ADC3LPEN                           0x01000000
#define RCC_C1_AHB4LPENR_BKPRAMLPEN                         0x10000000
#define RCC_C1_AHB4LPENR_SRAM4LPEN                          0x20000000

/************** bit definitions for C1_APB3LPENR register ***************/
#define RCC_C1_APB3LPENR_LTDCLPEN                           0x00000008
#define RCC_C1_APB3LPENR_WWDG1LPEN                          0x00000040

/************** bit definitions for C1_APB1LLPENR register **************/
#define RCC_C1_APB1LLPENR_TIM2LPEN                          0x00000001
#define RCC_C1_APB1LLPENR_TIM3LPEN                          0x00000002
#define RCC_C1_APB1LLPENR_TIM4LPEN                          0x00000004
#define RCC_C1_APB1LLPENR_TIM5LPEN                          0x00000008
#define RCC_C1_APB1LLPENR_TIM6LPEN                          0x00000010
#define RCC_C1_APB1LLPENR_TIM7LPEN                          0x00000020
#define RCC_C1_APB1LLPENR_TIM12LPEN                         0x00000040
#define RCC_C1_APB1LLPENR_TIM13LPEN                         0x00000080
#define RCC_C1_APB1LLPENR_TIM14LPEN                         0x00000100
#define RCC_C1_APB1LLPENR_LPTIM1LPEN                        0x00000200
#define RCC_C1_APB1LLPENR_SPI2LPEN                          0x00004000
#define RCC_C1_APB1LLPENR_SPI3LPEN                          0x00008000
#define RCC_C1_APB1LLPENR_SPDIFRXLPEN                       0x00010000
#define RCC_C1_APB1LLPENR_USART2LPEN                        0x00020000
#define RCC_C1_APB1LLPENR_USART3LPEN                        0x00040000
#define RCC_C1_APB1LLPENR_UART4LPEN                         0x00080000
#define RCC_C1_APB1LLPENR_UART5LPEN                         0x00100000
#define RCC_C1_APB1LLPENR_I2C1LPEN                          0x00200000
#define RCC_C1_APB1LLPENR_I2C2LPEN                          0x00400000
#define RCC_C1_APB1LLPENR_I2C3LPEN                          0x00800000
#define RCC_C1_APB1LLPENR_HDMICECLPEN                       0x08000000
#define RCC_C1_APB1LLPENR_DAC12LPEN                         0x20000000
#define RCC_C1_APB1LLPENR_USART7LPEN                        0x40000000
#define RCC_C1_APB1LLPENR_USART8LPEN                        0x80000000

/************** bit definitions for C1_APB1HLPENR register **************/
#define RCC_C1_APB1HLPENR_CRSLPEN                           0x00000002
#define RCC_C1_APB1HLPENR_SWPLPEN                           0x00000004
#define RCC_C1_APB1HLPENR_OPAMPLPEN                         0x00000010
#define RCC_C1_APB1HLPENR_MDIOSLPEN                         0x00000020
#define RCC_C1_APB1HLPENR_FDCANLPEN                         0x00000100

/************** bit definitions for C1_APB2LPENR register ***************/
#define RCC_C1_APB2LPENR_TIM1LPEN                           0x00000001
#define RCC_C1_APB2LPENR_TIM8LPEN                           0x00000002
#define RCC_C1_APB2LPENR_USART1LPEN                         0x00000010
#define RCC_C1_APB2LPENR_USART6LPEN                         0x00000020
#define RCC_C1_APB2LPENR_SPI1LPEN                           0x00001000
#define RCC_C1_APB2LPENR_SPI4LPEN                           0x00002000
#define RCC_C1_APB2LPENR_TIM15LPEN                          0x00010000
#define RCC_C1_APB2LPENR_TIM16LPEN                          0x00020000
#define RCC_C1_APB2LPENR_TIM17LPEN                          0x00040000
#define RCC_C1_APB2LPENR_SPI5LPEN                           0x00100000
#define RCC_C1_APB2LPENR_SAI1LPEN                           0x00400000
#define RCC_C1_APB2LPENR_SAI2LPEN                           0x00800000
#define RCC_C1_APB2LPENR_SAI3LPEN                           0x01000000
#define RCC_C1_APB2LPENR_DFSDM1LPEN                         0x10000000
#define RCC_C1_APB2LPENR_HRTIMLPEN                          0x20000000

/************** bit definitions for C1_APB4LPENR register ***************/
#define RCC_C1_APB4LPENR_SYSCFGLPEN                         0x00000002
#define RCC_C1_APB4LPENR_LPUART1LPEN                        0x00000008
#define RCC_C1_APB4LPENR_SPI6LPEN                           0x00000020
#define RCC_C1_APB4LPENR_I2C4LPEN                           0x00000080
#define RCC_C1_APB4LPENR_LPTIM2LPEN                         0x00000200
#define RCC_C1_APB4LPENR_LPTIM3LPEN                         0x00000400
#define RCC_C1_APB4LPENR_LPTIM4LPEN                         0x00000800
#define RCC_C1_APB4LPENR_LPTIM5LPEN                         0x00001000
#define RCC_C1_APB4LPENR_COMP12LPEN                         0x00004000
#define RCC_C1_APB4LPENR_VREFLPEN                           0x00008000
#define RCC_C1_APB4LPENR_RTCAPBLPEN                         0x00010000
#define RCC_C1_APB4LPENR_SAI4LPEN                           0x00200000

#endif /* STM32H743_RCC_H */

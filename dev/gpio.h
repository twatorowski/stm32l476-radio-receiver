/**
 * @file gpio.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-05-06
 * 
 * @brief General Purpose Input-Output
 */
#ifndef _DEV_GPIO_H
#define _DEV_GPIO_H

#include "compiler.h"
#include "err.h"
#include "stm32h743/gpio.h"

/** gpio pin enumeration */
typedef enum gpio_pin {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
} gpio_pin_t;

/** pull up / pull down bit masks */
typedef enum gpio_pull {
    GPIO_PULL_UP = GPIO_PUPDR_PUPD0_0,
    GPIO_PULL_DN = GPIO_PUPDR_PUPD0_1,
} gpio_pull_t;

/** output type - push-pull, open drain */
typedef enum gpio_otype {
    GPIO_OTYPE_PP = 0,
    GPIO_OTYPE_OD = GPIO_OTYPER_OT0,
} gpio_otype_t;

/** alternate functions */
typedef enum gpio_af_t {
    GPIO_AF_SYS = 0,
    GPIO_AF_TIM1_2_16_17_LPTIM1_HRTIM1,
    GPIO_AF_SAI1_TIM3_4_5_12_HRTIM1,
    GPIO_AF_LPUART_TIM8_LPTIM2_3_4_5_HRTIM1_DFSDM1_CEC,
    GPIO_AF_I2C1_2_3_4_USART1_TIM15_LPTIM2_DFSDM1_CEC,
    GPIO_AF_SPI1_2_3_4_5_6_CEC,
    GPIO_AF_SPI2_3_SAI1_3_I2C4_UART4_DFSDM,
    GPIO_AF_SPI2_3_6_USART1_2_3_6_UART7_SDMMC1,
    GPIO_AF_SPI6_SAI2_4_UART4_5_8LPUART_SDMMC1_SPDIFRX1,
    GPIO_AF_SAI4_FDCAN1_2TIM13_14_QUADSPI_FMC_SDMMC1_SPDIFRX1,
    GPIO_AF_SAI2_4_TIM8_QUADSPI_SDMMC2_OTG1_HS_OTG2_FS_LCD,
    GPIO_AF_I2C4_UART7_SWPMI1_TIM1_8_DFSDM1_SDMMC2_MDIOS_ETH,
    GPIO_AF_TIM1_8_FMC_SDMMC1_MDIOS_OTG1_FS_LCD,
    GPIO_AF_TIM1_DCMI_LCD_COMP,
    GPIO_AF_UART5_LCD,
    GPIO_AF_EVNOUT = 15,
} gpio_af_t;

/**
 * @brief Initialize gpio driver
 * 
 * @return err_t status code
 */
err_t GPIO_Init(void);

/**
 * @brief Configure given pin in gpio as output and set it's initial state
 * 
 * @param gpio gpio port
 * @param pin pin number
 * @param otype output type
 * @param initial_value initial output value
 * 
 * @return err_t status
 */
err_t GPIO_CfgOutput(gpio_t *gpio, gpio_pin_t pin, gpio_otype_t otype, 
    int initial_value);

/**
 * @brief configure the output type
 * 
 * @param gpio gpio port
 * @param pin pin number
 * @param otype output type
 * 
 * @return err_t error code
 */
err_t GPIO_CfgOutputType(gpio_t *gpio, gpio_pin_t pin, gpio_otype_t otype);

/**
 * @brief Configure given pin as input
 * 
 * @param gpio gpio port
 * @param pin pin number
 * 
 * @return err_t status code
 */
err_t GPIO_CfgInput(gpio_t *gpio, gpio_pin_t pin);

/**
 * @brief Setup pull resistor type on given pin
 * 
 * @param gpio gpio port
 * @param pin pin number
 * @param pull pull up/dn configuration
 * 
 * @return err_t status code
 */
err_t GPIO_CfgPull(gpio_t *gpio, gpio_pin_t pin, gpio_pull_t pull);

/**
 * @brief configure given pin as analog input
 * 
 * @param gpio gpio port
 * @param pin pin number
 * 
 * @return err_t status code
 */
err_t GPIO_CfgAnalog(gpio_t *gpio, gpio_pin_t pin);

/**
 * @brief configure given pin as alternate function
 * 
 * @param gpio gpio port
 * @param pin pin number
 * @param af alternate function
 * 
 * @return err_t status code
 */
err_t GPIO_CfgAlternatefunction(gpio_t *gpio, gpio_pin_t pin, gpio_af_t af);

/**
 * @brief Set pin state
 * 
 * @param gpio gpio port
 * @param pin pin number
 * @param value pin value
 */
static inline ALWAYS_INLINE void GPIO_Set(gpio_t *gpio, gpio_pin_t pin, 
    int value)
{
    /* write to bsrr register in order to get the pin state */
    gpio->BSRR = (value ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0) << pin;
}

/**
 * @brief Get pin state
 * 
 * @param gpio gpio port
 * @param pin pin number
 */
static inline ALWAYS_INLINE int GPIO_Get(gpio_t *gpio, gpio_pin_t pin)
{
    /* get the pin state */
    return !!(gpio->IDR & (GPIO_IDR_ID0 << pin));
}


#endif /* _DEV_GPIO_H */

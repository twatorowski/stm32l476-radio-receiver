/**
 * @file stm32l476.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: Main Header File
 */

#ifndef STM32L476_STM32L476_H_
#define STM32L476_STM32L476_H_

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
#define STM32_VECTOR_STACK_PTR_BASE         0
/* base of the exception vectors */
#define STM32_VECTOR_EXC_BASE               1
/* base position for the interrupt vectors */
#define STM32_VECTOR_INT_BASE               16

/* stack pointer */
/* stack pointer entry id */
#define STM32_STACK_PTR                     0

/* core exeptions */
/* reset routine */
#define STM32_EXC_RESET						0
/* Non maskable interrupt. The RCC Clock Security System (CSS) is
 * linked to the NMI vector. */
#define STM32_EXC_NMI						1
/* All class of fault */
#define STM32_EXC_HARDFAULT					2
/* Memory management */
#define STM32_EXC_MEMMANAGE					3
/* Pre-fetch fault, memory access fault */
#define STM32_EXC_BUSFAULT					4
/* Undefined instruction or illegal state */
#define STM32_EXC_USAGEFAULT				5
/* System service call via SWI instruction */
#define STM32_EXC_SVC						10
/* Debug Monitor */
#define STM32_EXC_DEBUGMON					11
/* Pendable request for system service */
#define STM32_EXC_PENDSV					13
/* System tick timer */
#define STM32_EXC_SYSTICK					14


/* interrupt sources */
/* Window Watchdog interrupt */
#define STM32_INT_WWDG						0
/* EXTI Line 16 interrupt / PVD through EXTI line detection interrupt */
#define STM32_INT_PVD						1
/* EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through
 * the EXTI line */
#define STM32_INT_TAMP_STAMP				2
/* EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line */
#define STM32_INT_RTC_WKUP					3
/* Flash global interrupt */
#define STM32_INT_FLASH						4
/* RCC global interrupt */
#define STM32_INT_RCC						5
/* EXTI Line0 interrupt */
#define STM32_INT_EXTI0						6
/* EXTI Line1 interrupt */
#define STM32_INT_EXTI1						7
/* EXTI Line2 interrupt */
#define STM32_INT_EXTI2						8
/* EXTI Line3 interrupt */
#define STM32_INT_EXTI3						9
/* EXTI Line4 interrupt */
#define STM32_INT_EXTI4						10
/* DMA1 Stream0 global interrupt  */
#define STM32_INT_DMA1C1					11
/* DMA1 Stream1 global interrupt */
#define STM32_INT_DMA1C2					12
/* DMA1 Stream2 global interrupt */
#define STM32_INT_DMA1C3					13
/* DMA1 Stream3 global interrupt */
#define STM32_INT_DMA1C4					14
/* DMA1 Stream4 global interrupt */
#define STM32_INT_DMA1C5					15
/* DMA1 Stream5 global interrupt */
#define STM32_INT_DMA1C6					16
/* DMA1 Stream6 global interrupt */
#define STM32_INT_DMA1C7					17
/* ADC global interrupts */
#define STM32_INT_ADC1_2					18
/* CAN1_TX interrupts */
#define STM32_INT_CAN1_TX					19
/* CAN1_RX0 interrupts */
#define STM32_INT_CAN1_RX0					20
/* CAN1_RX1 interrupt */
#define STM32_INT_CAN1_RX1					21
/* CAN1_SCE interrupt */
#define STM32_INT_CAN_SCE					22
/* EXTI Line[9:5] interrupts */
#define STM32_INT_EXTI5_9					23
/* TIM1 Break interrupt and TIM15 global interrupt */
#define STM32_INT_TIM1_BRK_TIM15			24
/* TIM1 Update interrupt and TIM16 global interrupt */
#define STM32_INT_TIM1_UP_TIM16				25
/* TIM1 Trigger and Commutation interrupts and TIM17 global interrupt */
#define STM32_INT_TIM1_TRG_COM_TIM17		26
/* TIM1 Capture Compare interrupt */
#define STM32_INT_TIM1_CC					27
/* TIM2 global interrupt */
#define STM32_INT_TIM2						28
/* TIM3 global interrupt */
#define STM32_INT_TIM3						29
/* TIM4 global interrupt */
#define STM32_INT_TIM4						30
/* I2C1 event interrupt */
#define STM32_INT_I2C1_EV					31
/* I2C1 error interrupt */
#define STM32_INT_I2C1_ER					32
/* I2C2 event interrupt */
#define STM32_INT_I2C2_EV					33
/* I2C2 error interrupt */
#define STM32_INT_I2C2_ER					34
/* SPI1 global interrupt */
#define STM32_INT_SPI1						35
/* SPI2 global interrupt */
#define STM32_INT_SPI2						36
/* USART1 global interrupt */
#define STM32_INT_USART1					37
/* USART2 global interrupt */
#define STM32_INT_USART2					38
/* USART3 global interrupt */
#define STM32_INT_USART3					39
/* EXTI Line[15:10] interrupts */
#define STM32_INT_EXTI10_15					40
/* EXTI Line 18 interrupt / RTC Alarms (A and B) through EXTI line interrupt */
#define STM32_INT_RTC_ALARM					41
/* DFSDM3 global interrupt */
#define STM32_INT_DFSDM3					42
/* TIM8_BRK interrupt */
#define STM32_INT_TIM8_BRK					43
/* TIM8_UP interrupt */
#define STM32_INT_TIM8_UP					44
/* TIM8_TRGCOM interrupt */
#define STM32_INT_TIM8_TRGCOM				45
/* TIM8_CC global interrupt */
#define STM32_INT_TIM8_CC					46
/* ADC3 global interrupt */
#define STM32_INT_ADC3						47
/* FMC global interrupt */
#define STM32_INT_FMC						48
/* SDMMC1 global interrupt */
#define STM32_INT_SDMMC1					49
/* TIM5 global interrupt */
#define STM32_INT_TIM5						50
/* SPI3 global interrupt */
#define STM32_INT_SPI3						51
/* USART4 global interrupt */
#define STM32_INT_USART4					52
/* USART5 global interrupt */
#define STM32_INT_USART5					53
/* TIM6_DACUNDER global interrupt */
#define STM32_INT_TIM6_DACUNDER				54
/* TIM7 global interrupt */
#define STM32_INT_TIM7						55
/* DMA2 Stream1 global interrupt  */
#define STM32_INT_DMA2C1					56
/* DMA2 Stream2 global interrupt  */
#define STM32_INT_DMA2C2					57
/* DMA2 Stream3 global interrupt */
#define STM32_INT_DMA2C3					58
/* DMA2 Stream4 global interrupt  */
#define STM32_INT_DMA2C4					59
/* DMA2 Stream5 global interrupt  */
#define STM32_INT_DMA2C5					60
/* DFSDM0 global interrupt */
#define STM32_INT_DFSDM0					61
/* DFSDM1 global interrupt */
#define STM32_INT_DFSDM1					62
/* DFSDM2 global interrupt */
#define STM32_INT_DFSDM2					63
/* COMP1/COMP2 through EXTI lines 21/22 interrupts */
#define STM32_INT_COMP						64
/* LPTIM1 global interrupt */
#define STM32_INT_LPTIM1					65
/* LPTIM2 global interrupt */
#define STM32_INT_LPTIM2					66
/* USB On The Go FS global interrupt */
#define STM32_INT_OTG_FS					67
/* DMA2 Stream5 global interrupt */
#define STM32_INT_DMA2C6					68
/* DMA2 Stream6 global interrupt  */
#define STM32_INT_DMA2C7					69
/* LPUART1 global interrupt  */
#define STM32_INT_LPUART					70
/* QUADSPI global interrupt */
#define STM32_INT_QUADSPI					71
/* I2C3 event interrupt */
#define STM32_INT_I2C3_EV					72
/* I2C3 error interrupt */
#define STM32_INT_I2C3_ER					73
/* SAI1 global interrupt */
#define STM32_INT_SAI1						74
/* SAI2 global interrupt */
#define STM32_INT_SAI2						75
/* SWPMI1 global interrupt */
#define STM32_INT_SWPMI1					76
/* TSC global interrupt */
#define STM32_INT_TSC						77
/* LCD global interrupt */
#define STM32_INT_LCD						78
/* AES global interrupt */
#define STM32_INT_AES						79
/* RNG global interrupt */
#define STM32_INT_RNG						80
/* FPU global interrupt */
#define STM32_INT_FPU						81

/* bitband access */
#define STM32_BB(reg, bit)													\
		*((reg32_t *) (((uint32_t)(reg) & 0xf0000000) | 0x02000000 |		\
					   ((uint32_t)(reg) & 0x000fffff) << 5 |				\
					   ((bit) << 2)))


/* enable interrupts globally */
#define STM32_ENABLEINTS()					\
	__asm__ volatile ("cpsie i")

/* disable interrupts globally */
#define STM32_DISABLEINTS()					\
	__asm__ volatile ("cpsid i")


#endif /* STM32L476_STM32L476_H_ */

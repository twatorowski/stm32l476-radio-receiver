/**
 * @file dma.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: DMA
 */

#ifndef STM32L476_DMA_H_
#define STM32L476_DMA_H_

#include "stm32l476/stm32l476.h"

/* registers bases */
#define DMA1_BASE							(0x40020000)
/* channel bases */
#define DMA1_CHAN1_OFFS						(0x00000008)
#define DMA1_CHAN2_OFFS						(0x0000001c)
#define DMA1_CHAN3_OFFS						(0x00000030)
#define DMA1_CHAN4_OFFS						(0x00000044)
#define DMA1_CHAN5_OFFS						(0x00000058)
#define DMA1_CHAN6_OFFS						(0x0000006c)
#define DMA1_CHAN7_OFFS						(0x00000080)

/* register base */
#define DMA2_BASE							(0x40020400)
/* channel bases */
#define DMA2_CHAN1_OFFS						(0x00000008)
#define DMA2_CHAN2_OFFS						(0x0000001c)
#define DMA2_CHAN3_OFFS						(0x00000030)
#define DMA2_CHAN4_OFFS						(0x00000044)
#define DMA2_CHAN5_OFFS						(0x00000058)
#define DMA2_CHAN6_OFFS						(0x0000006c)
#define DMA2_CHAN7_OFFS						(0x00000080)

/* dma common registers */
#define DMA1								((dma_t *)DMA1_BASE)
#define DMA2								((dma_t *)DMA2_BASE)
/* dma channel */
#define DMA1C1								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN1_OFFS))
/* dma channel */
#define DMA1C2								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN2_OFFS))
/* dma channel */
#define DMA1C3								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN3_OFFS))
/* dma channel */
#define DMA1C4								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN4_OFFS))
/* dma channel */
#define DMA1C5								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN5_OFFS))
/* dma channel */
#define DMA1C6								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN6_OFFS))
/* dma channel */
#define DMA1C7								((dma_chan_t *)(DMA1_BASE + \
												DMA1_CHAN7_OFFS))
/* dma channel */
#define DMA2C1								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN1_OFFS))
/* dma channel */
#define DMA2C2								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN2_OFFS))
/* dma channel */
#define DMA2C3								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN3_OFFS))
/* dma channel */
#define DMA2C4								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN4_OFFS))
/* dma channel */
#define DMA2C5								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN5_OFFS))
/* dma channel */
#define DMA2C6								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN6_OFFS))
/* dma channel */
#define DMA2C7								((dma_chan_t *)(DMA2_BASE + \
												DMA2_CHAN7_OFFS))
/* registers */
typedef struct {
	reg32_t ISR;
	reg32_t IFCR;
	reg32_t RESERVED[40];
	reg32_t CSELR;
} __attribute__ ((packed, aligned(4))) dma_t;

/* DMA interrupt status register */
#define DMA_ISR_GIF1						(0x00000001)
#define DMA_ISR_TCIF1						(0x00000002)
#define DMA_ISR_HTIF1						(0x00000004)
#define DMA_ISR_TEIF1						(0x00000008)
#define DMA_ISR_GIF2						(0x00000010)
#define DMA_ISR_TCIF2						(0x00000020)
#define DMA_ISR_HTIF2						(0x00000040)
#define DMA_ISR_TEIF2						(0x00000080)
#define DMA_ISR_GIF3						(0x00000100)
#define DMA_ISR_TCIF3						(0x00000200)
#define DMA_ISR_HTIF3						(0x00000400)
#define DMA_ISR_TEIF3						(0x00000800)
#define DMA_ISR_GIF4						(0x00001000)
#define DMA_ISR_TCIF4						(0x00002000)
#define DMA_ISR_HTIF4						(0x00004000)
#define DMA_ISR_TEIF4						(0x00008000)
#define DMA_ISR_GIF5						(0x00010000)
#define DMA_ISR_TCIF5						(0x00020000)
#define DMA_ISR_HTIF5						(0x00040000)
#define DMA_ISR_TEIF5						(0x00080000)
#define DMA_ISR_GIF6						(0x00100000)
#define DMA_ISR_TCIF6						(0x00200000)
#define DMA_ISR_HTIF6						(0x00400000)
#define DMA_ISR_TEIF6						(0x00800000)
#define DMA_ISR_GIF7						(0x01000000)
#define DMA_ISR_TCIF7						(0x02000000)
#define DMA_ISR_HTIF7						(0x04000000)
#define DMA_ISR_TEIF7						(0x08000000)

/* DMA interrupt flag  clear register */
#define DMA_IFCR_CGIF1						(0x00000001)
#define DMA_IFCR_CTCIF1						(0x00000002)
#define DMA_IFCR_CHTIF1						(0x00000004)
#define DMA_IFCR_CTEIF1						(0x00000008)
#define DMA_IFCR_CGIF2						(0x00000010)
#define DMA_IFCR_CTCIF2						(0x00000020)
#define DMA_IFCR_CHTIF2						(0x00000040)
#define DMA_IFCR_CTEIF2						(0x00000080)
#define DMA_IFCR_CGIF3						(0x00000100)
#define DMA_IFCR_CTCIF3						(0x00000200)
#define DMA_IFCR_CHTIF3						(0x00000400)
#define DMA_IFCR_CTEIF3						(0x00000800)
#define DMA_IFCR_CGIF4						(0x00001000)
#define DMA_IFCR_CTCIF4						(0x00002000)
#define DMA_IFCR_CHTIF4						(0x00004000)
#define DMA_IFCR_CTEIF4						(0x00008000)
#define DMA_IFCR_CGIF5						(0x00010000)
#define DMA_IFCR_CTCIF5						(0x00020000)
#define DMA_IFCR_CHTIF5						(0x00040000)
#define DMA_IFCR_CTEIF5						(0x00080000)
#define DMA_IFCR_CGIF6						(0x00100000)
#define DMA_IFCR_CTCIF6						(0x00200000)
#define DMA_IFCR_CHTIF6						(0x00400000)
#define DMA_IFCR_CTEIF6						(0x00800000)
#define DMA_IFCR_CGIF7						(0x01000000)
#define DMA_IFCR_CTCIF7						(0x02000000)
#define DMA_IFCR_CHTIF7						(0x04000000)
#define DMA_IFCR_CTEIF7						(0x08000000)

/*	Bit definition for DMA_CSELR register  */
#define DMA_CSELR_C1S						(0x0000000F)
#define DMA1_CSELR_C1S_ADC1					(0x00000000)
#define DMA1_CSELR_C1S_TIM2_CH3				(0x00000004)
#define DMA1_CSELR_C1S_TIM17_CH1_UP			(0x00000005)
#define DMA1_CSELR_C1S_TIM4_CH1				(0x00000006)
#define DMA2_CSELR_C1S_SAI1_A				(0x00000001)
#define DMA2_CSELR_C1S_UART5_TX				(0x00000002)
#define DMA2_CSELR_C1S_SPI3_RX				(0x00000003)
#define DMA2_CSELR_C1S_SWPMI1_RX			(0x00000004)
#define DMA2_CSELR_C1S_TIM5_CH4_TRG_COM		(0x00000005)
#define DMA2_CSELR_C1S_AES_IN				(0x00000006)
#define DMA2_CSELR_C1S_TIM8_CH3_UP			(0x00000007)
#define DMA_CSELR_C2S						(0x000000F0)
#define DMA1_CSELR_C2S_ADC2					(0x00000000)
#define DMA1_CSELR_C2S_SPI1_RX				(0x00000010)
#define DMA1_CSELR_C2S_USART3_TX			(0x00000020)
#define DMA1_CSELR_C2S_I2C3_TX				(0x00000030)
#define DMA1_CSELR_C2S_TIM2_UP				(0x00000040)
#define DMA1_CSELR_C2S_TIM3_CH3				(0x00000050)
#define DMA1_CSELR_C2S_TIM1_CH1				(0x00000070)
#define DMA2_CSELR_C2S_SAI1_B				(0x00000010)
#define DMA2_CSELR_C2S_UART5_RX				(0x00000020)
#define DMA2_CSELR_C2S_SPI3_TX				(0x00000030)
#define DMA2_CSELR_C2S_SWPMI1_TX			(0x00000040)
#define DMA2_CSELR_C2S_TIM5_CH3_UP			(0x00000050)
#define DMA2_CSELR_C2S_AES_OUT				(0x00000060)
#define DMA2_CSELR_C2S_TIM8_CH4_TRG_COM		(0x00000070)
#define DMA_CSELR_C3S						(0x00000F00)
#define DMA1_CSELR_C3S_ADC3					(0x00000000)
#define DMA1_CSELR_C3S_SPI1_TX				(0x00000100)
#define DMA1_CSELR_C3S_USART3_RX			(0x00000200)
#define DMA1_CSELR_C3S_I2C3_RX				(0x00000300)
#define DMA1_CSELR_C3S_TIM16_CH1_UP			(0x00000400)
#define DMA1_CSELR_C3S_TIM3_CH4_UP			(0x00000500)
#define DMA1_CSELR_C3S_TIM6_UP_DAC1			(0x00000600)
#define DMA1_CSELR_C3S_TIM1_CH2				(0x00000700)
#define DMA2_CSELR_C3S_ADC1					(0x00000000)
#define DMA2_CSELR_C3S_SAI2_A				(0x00000100)
#define DMA2_CSELR_C3S_UART4_TX				(0x00000200)
#define DMA2_CSELR_C3S_SPI1_RX				(0x00000400)
#define DMA2_CSELR_C3S_AES_OUT				(0x00000600)
#define DMA_CSELR_C4S						(0x0000F000)
#define DMA1_CSELR_C4S_DFSDM0				(0x00000000)
#define DMA1_CSELR_C4S_SPI2_RX				(0x00001000)
#define DMA1_CSELR_C4S_USART1_TX			(0x00002000)
#define DMA1_CSELR_C4S_I2C2_TX				(0x00003000)
#define DMA1_CSELR_C4S_TIM7_UP_DAC2			(0x00005000)
#define DMA1_CSELR_C4S_TIM4_CH4				(0x00006000)
#define DMA1_CSELR_C4S_TIM1_CH4_TRG_COM		(0x00007000)
#define DMA2_CSELR_C4S_ADC2					(0x00000000)
#define DMA2_CSELR_C4S_SAI2_B				(0x00001000)
#define DMA2_CSELR_C4S_TIM6_UP_DAC1			(0x00003000)
#define DMA2_CSELR_C4S_SPI1_TX				(0x00004000)
#define DMA2_CSELR_C4S_TIM5_CH2				(0x00005000)
#define DMA2_CSELR_C4S_SDMMC1				(0x00007000)
#define DMA_CSELR_C5S						(0x000F0000)
#define DMA1_CSELR_C5S_DFSDM1				(0x00000000)
#define DMA1_CSELR_C5S_SPI2_TX				(0x00010000)
#define DMA1_CSELR_C5S_USART1_RX			(0x00020000)
#define DMA1_CSELR_C5S_I2C2_RX				(0x00030000)
#define DMA1_CSELR_C5S_TIM2_CH1				(0x00040000)
#define DMA1_CSELR_C5S_QUADSPI				(0x00050000)
#define DMA1_CSELR_C5S_TIM4_CH3				(0x00060000)
#define DMA1_CSELR_C5S_TIM15_CH1_UP_TRG_COM	(0x00070000)
#define DMA2_CSELR_C5S_ADC3					(0x00000000)
#define DMA2_CSELR_C5S_UART4_RX				(0x00020000)
#define DMA2_CSELR_C5S_TIM7_UP_DAC2			(0x00030000)
#define DMA2_CSELR_C5S_TIM5_CH1				(0x00050000)
#define DMA2_CSELR_C5S_AES_IN				(0x00060000)
#define DMA2_CSELR_C5S_SDMMC1				(0x00070000)
#define DMA_CSELR_C6S						(0x00F00000)
#define DMA1_CSELR_C6S_DFSDM2				(0x00000000)
#define DMA1_CSELR_C6S_SAI2_A				(0x00100000)
#define DMA1_CSELR_C6S_USART2_RX			(0x00200000)
#define DMA1_CSELR_C6S_I2C1_TX				(0x00300000)
#define DMA1_CSELR_C6S_TIM16_CH1_UP			(0x00400000)
#define DMA1_CSELR_C6S_TIM3_CH1_TRG			(0x00500000)
#define DMA1_CSELR_C6S_TIM1_UP				(0x00700000)
#define DMA2_CSELR_C6S_SAI1_A				(0x00100000)
#define DMA2_CSELR_C6S_USART1_TX			(0x00200000)
#define DMA2_CSELR_C6S_LPUART_TX			(0x00400000)
#define DMA2_CSELR_C6S_I2C1_RX				(0x00500000)
#define DMA2_CSELR_C6S_TIM8_CH1				(0x00700000)
#define DMA_CSELR_C7S						(0x0F000000)
#define DMA1_CSELR_C7S_DFSDM3				(0x00000000)
#define DMA1_CSELR_C7S_SAI2_B				(0x01000000)
#define DMA1_CSELR_C7S_USART2_TX			(0x02000000)
#define DMA1_CSELR_C7S_I2C1_RX				(0x03000000)
#define DMA1_CSELR_C7S_TIM2_CH2_CH4			(0x04000000)
#define DMA1_CSELR_C7S_TIM17_CH1_UP			(0x05000000)
#define DMA1_CSELR_C7S_TIM4_UP				(0x06000000)
#define DMA1_CSELR_C7S_TIM1_CH3				(0x07000000)
#define DMA2_CSELR_C7S_SAI1_B				(0x01000000)
#define DMA2_CSELR_C7S_USART1_RX			(0x02000000)
#define DMA2_CSELR_C7S_QUADSPI				(0x03000000)
#define DMA2_CSELR_C7S_LPUART_RX			(0x04000000)
#define DMA2_CSELR_C7S_I2C1_TX				(0x05000000)
#define DMA2_CSELR_C7S_TIM8_CH2				(0x07000000)

/* registers */
typedef struct {
	reg32_t CCR;
	reg32_t CNDTR;
	reg32_t CPAR;
	reg32_t CMAR;
} __attribute__((packed, aligned(4))) dma_chan_t;

/* DMA channel x configuration register */
#define DMA_CCR_EN							(0x0001)
#define DMA_CCR_TCIE						(0x0002)
#define DMA_CCR_HTIE						(0x0004)
#define DMA_CCR_TEIE						(0x0008)
#define DMA_CCR_DIR							(0x0010)
#define DMA_CCR_CIRC						(0x0020)
#define DMA_CCR_PINC						(0x0040)
#define DMA_CCR_MINC						(0x0080)
#define DMA_CCR_PSIZE						(0x0300)
#define DMA_CCR_PSIZE_0						(0x0100)
#define DMA_CCR_PSIZE_1						(0x0200)
#define DMA_CCR_MSIZE						(0x0C00)
#define DMA_CCR_MSIZE_0						(0x0400)
#define DMA_CCR_MSIZE_1						(0x0800)
#define DMA_CCR_PL							(0x3000)
#define DMA_CCR_PL_0						(0x1000)
#define DMA_CCR_PL_1						(0x2000)
#define DMA_CCR_MEM2MEM						(0x4000)

/* DMA channel x number of data register */
#define DMA_CNDTR_NDT						(0xFFFF)

/* DMA channel x peripheral address register */
#define DMA_CPAR_PA							(0xFFFFFFFF)

/* DMA channel x memory address register */
#define DMA_CMAR_MA							(0xFFFFFFFF)

#endif /* STM32L476_DMA_H_ */

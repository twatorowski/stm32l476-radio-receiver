/**
 * @file dma.h
 * 
 * @date 2021-01-19
 * @author twatorowski 
 * 
 * @brief STM32H743: DMA
 */


#ifndef STM32H743_DMA_H
#define STM32H743_DMA_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define DMA1_BASE                                           0x40020000U
#define DMA2_BASE                                           0x40020400U

/* instances */
#define DMA1                                                ((dma_t *)DMA1_BASE)
#define DMA2                                                ((dma_t *)DMA2_BASE)


/* register bank */
typedef struct {
    reg32_t LISR;
    reg32_t HISR;
    reg32_t LIFCR;
    reg32_t HIFCR;
} dma_t;


/****************** bit definitions for LISR register *******************/
#define DMA_LISR_TCIF3                                      0x08000000
#define DMA_LISR_HTIF3                                      0x04000000
#define DMA_LISR_TEIF3                                      0x02000000
#define DMA_LISR_DMEIF3                                     0x01000000
#define DMA_LISR_FEIF3                                      0x00400000
#define DMA_LISR_TCIF2                                      0x00200000
#define DMA_LISR_HTIF2                                      0x00100000
#define DMA_LISR_TEIF2                                      0x00080000
#define DMA_LISR_DMEIF2                                     0x00040000
#define DMA_LISR_FEIF2                                      0x00010000
#define DMA_LISR_TCIF1                                      0x00000800
#define DMA_LISR_HTIF1                                      0x00000400
#define DMA_LISR_TEIF1                                      0x00000200
#define DMA_LISR_DMEIF1                                     0x00000100
#define DMA_LISR_FEIF1                                      0x00000040
#define DMA_LISR_TCIF0                                      0x00000020
#define DMA_LISR_HTIF0                                      0x00000010
#define DMA_LISR_TEIF0                                      0x00000008
#define DMA_LISR_DMEIF0                                     0x00000004
#define DMA_LISR_FEIF0                                      0x00000001

/****************** bit definitions for HISR register *******************/
#define DMA_HISR_TCIF7                                      0x08000000
#define DMA_HISR_HTIF7                                      0x04000000
#define DMA_HISR_TEIF7                                      0x02000000
#define DMA_HISR_DMEIF7                                     0x01000000
#define DMA_HISR_FEIF7                                      0x00400000
#define DMA_HISR_TCIF6                                      0x00200000
#define DMA_HISR_HTIF6                                      0x00100000
#define DMA_HISR_TEIF6                                      0x00080000
#define DMA_HISR_DMEIF6                                     0x00040000
#define DMA_HISR_FEIF6                                      0x00010000
#define DMA_HISR_TCIF5                                      0x00000800
#define DMA_HISR_HTIF5                                      0x00000400
#define DMA_HISR_TEIF5                                      0x00000200
#define DMA_HISR_DMEIF5                                     0x00000100
#define DMA_HISR_FEIF5                                      0x00000040
#define DMA_HISR_TCIF4                                      0x00000020
#define DMA_HISR_HTIF4                                      0x00000010
#define DMA_HISR_TEIF4                                      0x00000008
#define DMA_HISR_DMEIF4                                     0x00000004
#define DMA_HISR_FEIF4                                      0x00000001

/****************** bit definitions for LIFCR register ******************/
#define DMA_LIFCR_CTCIF3                                    0x08000000
#define DMA_LIFCR_CHTIF3                                    0x04000000
#define DMA_LIFCR_CTEIF3                                    0x02000000
#define DMA_LIFCR_CDMEIF3                                   0x01000000
#define DMA_LIFCR_CFEIF3                                    0x00400000
#define DMA_LIFCR_CTCIF2                                    0x00200000
#define DMA_LIFCR_CHTIF2                                    0x00100000
#define DMA_LIFCR_CTEIF2                                    0x00080000
#define DMA_LIFCR_CDMEIF2                                   0x00040000
#define DMA_LIFCR_CFEIF2                                    0x00010000
#define DMA_LIFCR_CTCIF1                                    0x00000800
#define DMA_LIFCR_CHTIF1                                    0x00000400
#define DMA_LIFCR_CTEIF1                                    0x00000200
#define DMA_LIFCR_CDMEIF1                                   0x00000100
#define DMA_LIFCR_CFEIF1                                    0x00000040
#define DMA_LIFCR_CTCIF0                                    0x00000020
#define DMA_LIFCR_CHTIF0                                    0x00000010
#define DMA_LIFCR_CTEIF0                                    0x00000008
#define DMA_LIFCR_CDMEIF0                                   0x00000004
#define DMA_LIFCR_CFEIF0                                    0x00000001

/****************** bit definitions for HIFCR register ******************/
#define DMA_HIFCR_CTCIF7                                    0x08000000
#define DMA_HIFCR_CHTIF7                                    0x04000000
#define DMA_HIFCR_CTEIF7                                    0x02000000
#define DMA_HIFCR_CDMEIF7                                   0x01000000
#define DMA_HIFCR_CFEIF7                                    0x00400000
#define DMA_HIFCR_CTCIF6                                    0x00200000
#define DMA_HIFCR_CHTIF6                                    0x00100000
#define DMA_HIFCR_CTEIF6                                    0x00080000
#define DMA_HIFCR_CDMEIF6                                   0x00040000
#define DMA_HIFCR_CFEIF6                                    0x00010000
#define DMA_HIFCR_CTCIF5                                    0x00000800
#define DMA_HIFCR_CHTIF5                                    0x00000400
#define DMA_HIFCR_CTEIF5                                    0x00000200
#define DMA_HIFCR_CDMEIF5                                   0x00000100
#define DMA_HIFCR_CFEIF5                                    0x00000040
#define DMA_HIFCR_CTCIF4                                    0x00000020
#define DMA_HIFCR_CHTIF4                                    0x00000010
#define DMA_HIFCR_CTEIF4                                    0x00000008
#define DMA_HIFCR_CDMEIF4                                   0x00000004
#define DMA_HIFCR_CFEIF4                                    0x00000001


/* channel base addresses */
#define DMA1C0_BASE                                         (DMA1_BASE + 0x10)                                         
#define DMA1C1_BASE                                         (DMA1_BASE + 0x28)
#define DMA1C2_BASE                                         (DMA1_BASE + 0x40)
#define DMA1C3_BASE                                         (DMA1_BASE + 0x58)
#define DMA1C4_BASE                                         (DMA1_BASE + 0x70)
#define DMA1C5_BASE                                         (DMA1_BASE + 0x88)
#define DMA1C6_BASE                                         (DMA1_BASE + 0xA0)
#define DMA1C7_BASE                                         (DMA1_BASE + 0xB8)

/* channel base addresses */
#define DMA2C0_BASE                                         (DMA2_BASE + 0x10)                                         
#define DMA2C1_BASE                                         (DMA2_BASE + 0x28)
#define DMA2C2_BASE                                         (DMA2_BASE + 0x40)
#define DMA2C3_BASE                                         (DMA2_BASE + 0x58)
#define DMA2C4_BASE                                         (DMA2_BASE + 0x70)
#define DMA2C5_BASE                                         (DMA2_BASE + 0x88)
#define DMA2C6_BASE                                         (DMA2_BASE + 0xA0)
#define DMA2C7_BASE                                         (DMA2_BASE + 0xB8)

/* channel instances */
#define DMA1C0                                              ((dma_ch_t *)DMA1C0_BASE)
#define DMA1C1                                              ((dma_ch_t *)DMA1C1_BASE)
#define DMA1C2                                              ((dma_ch_t *)DMA1C2_BASE)
#define DMA1C3                                              ((dma_ch_t *)DMA1C3_BASE)
#define DMA1C4                                              ((dma_ch_t *)DMA1C4_BASE)
#define DMA1C5                                              ((dma_ch_t *)DMA1C5_BASE)
#define DMA1C6                                              ((dma_ch_t *)DMA1C6_BASE)
#define DMA1C7                                              ((dma_ch_t *)DMA1C7_BASE)

/* channel instances */
#define DMA2C0                                              ((dma_ch_t *)DMA2C0_BASE)
#define DMA2C1                                              ((dma_ch_t *)DMA2C1_BASE)
#define DMA2C2                                              ((dma_ch_t *)DMA2C2_BASE)
#define DMA2C3                                              ((dma_ch_t *)DMA2C3_BASE)
#define DMA2C4                                              ((dma_ch_t *)DMA2C4_BASE)
#define DMA2C5                                              ((dma_ch_t *)DMA2C5_BASE)
#define DMA2C6                                              ((dma_ch_t *)DMA2C6_BASE)
#define DMA2C7                                              ((dma_ch_t *)DMA2C7_BASE)

/* channel register bank */
typedef struct {
    reg32_t CR;
    reg32_t NDTR;
    reg32_t PAR;
    reg32_t M0AR;
    reg32_t M1AR;
    reg32_t FCR;
} dma_ch_t;

/******************* bit definitions for CR register ********************/
#define DMA_CR_MBURST                                       0x01800000
#define DMA_CR_MBURST_0                                     0x00800000
#define DMA_CR_MBURST_1                                     0x01000000
#define DMA_CR_PBURST                                       0x00600000
#define DMA_CR_PBURST_0                                     0x00200000
#define DMA_CR_PBURST_1                                     0x00400000
#define DMA_CR_CT                                           0x00080000
#define DMA_CR_DBM                                          0x00040000
#define DMA_CR_PL                                           0x00030000
#define DMA_CR_PL_0                                         0x00010000
#define DMA_CR_PL_1                                         0x00020000
#define DMA_CR_PINCOS                                       0x00008000
#define DMA_CR_MSIZE                                        0x00006000
#define DMA_CR_MSIZE_0                                      0x00004000
#define DMA_CR_MSIZE_1                                      0x00002000
#define DMA_CR_PSIZE                                        0x00001800
#define DMA_CR_PSIZE_0                                      0x00000800
#define DMA_CR_PSIZE_1                                      0x00001000
#define DMA_CR_MINC                                         0x00000400
#define DMA_CR_PINC                                         0x00000200
#define DMA_CR_CIRC                                         0x00000100
#define DMA_CR_DIR                                          0x000000c0
#define DMA_CR_DIR_0                                        0x00000040
#define DMA_CR_DIR_1                                        0x00000080
#define DMA_CR_PFCTRL                                       0x00000020
#define DMA_CR_TCIE                                         0x00000010
#define DMA_CR_HTIE                                         0x00000008
#define DMA_CR_TEIE                                         0x00000004
#define DMA_CR_DMEIE                                        0x00000002
#define DMA_CR_EN                                           0x00000001

/****************** bit definitions for NDTR register *******************/
#define DMA_NDTR_NDT                                        0x0000ffff

/******************* bit definitions for PAR register *******************/
#define DMA_PAR_PA                                          0xffffffff

/****************** bit definitions for M0AR register *******************/
#define DMA_M0AR_M0A                                        0xffffffff

/****************** bit definitions for M1AR register *******************/
#define DMA_M1AR_M1A                                        0xffffffff

/****************** bit definitions for FCR register *******************/
#define DMA_FCR_FEIE                                        0x00000080
#define DMA_FCR_FS                                          0x00000038
#define DMA_FCR_DMDIS                                       0x00000004
#define DMA_FCR_FTH                                         0x00000003



#endif /* STM32H743_DMA_H */
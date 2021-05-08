/**
* @file exti.h
* 
* @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
* @date 2021-05-07
* 
* @brief STM32H743: Exti driver
*/
#ifndef STM32H743_EXTI_H
#define STM32H743_EXTI_H

#include "stm32h743/stm32h743.h"

/* register base */
#define EXTI_BASE                               (0x58000000)

/* instances */
#define EXTI                                    ((exti_t *)EXTI_BASE)

/* register bank */
typedef struct {
    reg32_t RTSR1;               
    reg32_t FTSR1;               
    reg32_t SWIER1;              
    reg32_t D3PMR1;              
    reg32_t D3PCR1L;             
    reg32_t D3PCR1H;             
    reg32_t RESERVED1[2];        
    reg32_t RTSR2;               
    reg32_t FTSR2;               
    reg32_t SWIER2;              
    reg32_t D3PMR2;              
    reg32_t D3PCR2L;             
    reg32_t D3PCR2H;             
    reg32_t RESERVED2[2];        
    reg32_t RTSR3;               
    reg32_t FTSR3;               
    reg32_t SWIER3;              
    reg32_t D3PMR3;              
    reg32_t D3PCR3L;             
    reg32_t D3PCR3H;             
    reg32_t RESERVED3[10];       
    reg32_t IMR1;                
    reg32_t EMR1;                
    reg32_t PR1;                 
    reg32_t RESERVED4;           
    reg32_t IMR2;                
    reg32_t EMR2;                
    reg32_t PR2;                 
    reg32_t RESERVED5;           
    reg32_t IMR3;                
    reg32_t EMR3;                
    reg32_t PR3;                 
} PACKED ALIGNED(4) exti_t;

/******************  Bit definition for EXTI_RTSR1 register  *******************/
#define EXTI_RTSR1_TR                                       0x003FFFFFU
#define EXTI_RTSR1_TR0                                      0x00000001U
#define EXTI_RTSR1_TR1                                      0x00000002U
#define EXTI_RTSR1_TR2                                      0x00000004U
#define EXTI_RTSR1_TR3                                      0x00000008U
#define EXTI_RTSR1_TR4                                      0x00000010U
#define EXTI_RTSR1_TR5                                      0x00000020U
#define EXTI_RTSR1_TR6                                      0x00000040U
#define EXTI_RTSR1_TR7                                      0x00000080U
#define EXTI_RTSR1_TR8                                      0x00000100U
#define EXTI_RTSR1_TR9                                      0x00000200U
#define EXTI_RTSR1_TR10                                     0x00000400U
#define EXTI_RTSR1_TR11                                     0x00000800U
#define EXTI_RTSR1_TR12                                     0x00001000U
#define EXTI_RTSR1_TR13                                     0x00002000U
#define EXTI_RTSR1_TR14                                     0x00004000U
#define EXTI_RTSR1_TR15                                     0x00008000U
#define EXTI_RTSR1_TR16                                     0x00010000U
#define EXTI_RTSR1_TR17                                     0x00020000U
#define EXTI_RTSR1_TR18                                     0x00040000U
#define EXTI_RTSR1_TR19                                     0x00080000U
#define EXTI_RTSR1_TR20                                     0x00100000U
#define EXTI_RTSR1_TR21                                     0x00200000U

/******************  Bit definition for EXTI_FTSR1 register  *******************/
#define EXTI_FTSR1_TR                                       0x003FFFFFU
#define EXTI_FTSR1_TR0                                      0x00000001U
#define EXTI_FTSR1_TR1                                      0x00000002U
#define EXTI_FTSR1_TR2                                      0x00000004U
#define EXTI_FTSR1_TR3                                      0x00000008U
#define EXTI_FTSR1_TR4                                      0x00000010U
#define EXTI_FTSR1_TR5                                      0x00000020U
#define EXTI_FTSR1_TR6                                      0x00000040U
#define EXTI_FTSR1_TR7                                      0x00000080U
#define EXTI_FTSR1_TR8                                      0x00000100U
#define EXTI_FTSR1_TR9                                      0x00000200U
#define EXTI_FTSR1_TR10                                     0x00000400U
#define EXTI_FTSR1_TR11                                     0x00000800U
#define EXTI_FTSR1_TR12                                     0x00001000U
#define EXTI_FTSR1_TR13                                     0x00002000U
#define EXTI_FTSR1_TR14                                     0x00004000U
#define EXTI_FTSR1_TR15                                     0x00008000U
#define EXTI_FTSR1_TR16                                     0x00010000U
#define EXTI_FTSR1_TR17                                     0x00020000U
#define EXTI_FTSR1_TR18                                     0x00040000U
#define EXTI_FTSR1_TR19                                     0x00080000U
#define EXTI_FTSR1_TR20                                     0x00100000U
#define EXTI_FTSR1_TR21                                     0x00200000U

/******************  Bit definition for EXTI_SWIER1 register  ******************/
#define EXTI_SWIER1_SWIER0                                  0x00000001U
#define EXTI_SWIER1_SWIER1                                  0x00000002U
#define EXTI_SWIER1_SWIER2                                  0x00000004U
#define EXTI_SWIER1_SWIER3                                  0x00000008U
#define EXTI_SWIER1_SWIER4                                  0x00000010U
#define EXTI_SWIER1_SWIER5                                  0x00000020U
#define EXTI_SWIER1_SWIER6                                  0x00000040U
#define EXTI_SWIER1_SWIER7                                  0x00000080U
#define EXTI_SWIER1_SWIER8                                  0x00000100U
#define EXTI_SWIER1_SWIER9                                  0x00000200U
#define EXTI_SWIER1_SWIER10                                 0x00000400U
#define EXTI_SWIER1_SWIER11                                 0x00000800U
#define EXTI_SWIER1_SWIER12                                 0x00001000U
#define EXTI_SWIER1_SWIER13                                 0x00002000U
#define EXTI_SWIER1_SWIER14                                 0x00004000U
#define EXTI_SWIER1_SWIER15                                 0x00008000U
#define EXTI_SWIER1_SWIER16                                 0x00010000U
#define EXTI_SWIER1_SWIER17                                 0x00020000U
#define EXTI_SWIER1_SWIER18                                 0x00040000U
#define EXTI_SWIER1_SWIER19                                 0x00080000U
#define EXTI_SWIER1_SWIER20                                 0x00100000U
#define EXTI_SWIER1_SWIER21                                 0x00200000U

/******************  Bit definition for EXTI_D3PMR1 register  ******************/
#define EXTI_D3PMR1_MR0                                     0x00000001U
#define EXTI_D3PMR1_MR1                                     0x00000002U
#define EXTI_D3PMR1_MR2                                     0x00000004U
#define EXTI_D3PMR1_MR3                                     0x00000008U
#define EXTI_D3PMR1_MR4                                     0x00000010U
#define EXTI_D3PMR1_MR5                                     0x00000020U
#define EXTI_D3PMR1_MR6                                     0x00000040U
#define EXTI_D3PMR1_MR7                                     0x00000080U
#define EXTI_D3PMR1_MR8                                     0x00000100U
#define EXTI_D3PMR1_MR9                                     0x00000200U
#define EXTI_D3PMR1_MR10                                    0x00000400U
#define EXTI_D3PMR1_MR11                                    0x00000800U
#define EXTI_D3PMR1_MR12                                    0x00001000U
#define EXTI_D3PMR1_MR13                                    0x00002000U
#define EXTI_D3PMR1_MR14                                    0x00004000U
#define EXTI_D3PMR1_MR15                                    0x00008000U
#define EXTI_D3PMR1_MR19                                    0x00080000U
#define EXTI_D3PMR1_MR20                                    0x00100000U
#define EXTI_D3PMR1_MR21                                    0x00200000U
#define EXTI_D3PMR1_MR25                                    0x01000000U

/*******************  Bit definition for EXTI_D3PCR1L register  ****************/
#define EXTI_D3PCR1L_PCS0                                   0x00000003U
#define EXTI_D3PCR1L_PCS1                                   0x000000C0U
#define EXTI_D3PCR1L_PCS2                                   0x00000030U
#define EXTI_D3PCR1L_PCS3                                   0x000000C0U
#define EXTI_D3PCR1L_PCS4                                   0x00000300U
#define EXTI_D3PCR1L_PCS5                                   0x00000C00U
#define EXTI_D3PCR1L_PCS6                                   0x00003000U
#define EXTI_D3PCR1L_PCS7                                   0x0000C000U
#define EXTI_D3PCR1L_PCS8                                   0x00030000U
#define EXTI_D3PCR1L_PCS9                                   0x000C0000U
#define EXTI_D3PCR1L_PCS10                                  0x00300000U
#define EXTI_D3PCR1L_PCS11                                  0x00C00000U
#define EXTI_D3PCR1L_PCS12                                  0x03000000U
#define EXTI_D3PCR1L_PCS13                                  0x0C000000U
#define EXTI_D3PCR1L_PCS14                                  0x30000000U
#define EXTI_D3PCR1L_PCS15                                  0xC0000000U

/*******************  Bit definition for EXTI_D3PCR1H register  ****************/
#define EXTI_D3PCR1H_PCS19                                  0x000000C0U
#define EXTI_D3PCR1H_PCS20                                  0x00000300U
#define EXTI_D3PCR1H_PCS21                                  0x00000C00U
#define EXTI_D3PCR1H_PCS25                                  0x000C0000U

/******************  Bit definition for EXTI_RTSR2 register  *******************/
#define EXTI_RTSR2_TR                                       0x000A0000U
#define EXTI_RTSR2_TR49                                     0x00020000U
#define EXTI_RTSR2_TR51                                     0x00080000U

/******************  Bit definition for EXTI_FTSR2 register  *******************/
#define EXTI_FTSR2_TR                                       0x000A0000U
#define EXTI_FTSR2_TR49                                     0x00020000U
#define EXTI_FTSR2_TR51                                     0x00080000U

/******************  Bit definition for EXTI_SWIER2 register  ******************/
#define EXTI_SWIER2_SWIER49                                 0x00020000U
#define EXTI_SWIER2_SWIER51                                 0x00080000U

/******************  Bit definition for EXTI_D3PMR2 register  ******************/
#define EXTI_D3PMR2_MR34                                    0x00000004U
#define EXTI_D3PMR2_MR35                                    0x00000008U
#define EXTI_D3PMR2_MR41                                    0x00000200U
#define EXTI_D3PMR2_MR48                                    0x00010000U
#define EXTI_D3PMR2_MR49                                    0x00020000U
#define EXTI_D3PMR2_MR50                                    0x00040000U
#define EXTI_D3PMR2_MR51                                    0x00080000U
#define EXTI_D3PMR2_MR52                                    0x00100000U
#define EXTI_D3PMR2_MR53                                    0x00200000U

/*******************  Bit definition for EXTI_D3PCR2L register  ****************/
#define EXTI_D3PCR2L_PCS34                                  0x00000030U
#define EXTI_D3PCR2L_PCS35                                  0x000000C0U
#define EXTI_D3PCR2L_PCS41                                  0x000C0000U

/*******************  Bit definition for EXTI_D3PCR2H register  ****************/
#define EXTI_D3PCR2H_PCS48                                  0x00000003U
#define EXTI_D3PCR2H_PCS49                                  0x0000000CU
#define EXTI_D3PCR2H_PCS50                                  0x00000030U
#define EXTI_D3PCR2H_PCS51                                  0x000000C0U
#define EXTI_D3PCR2H_PCS52                                  0x00000300U
#define EXTI_D3PCR2H_PCS53                                  0x00000C00U

/******************  Bit definition for EXTI_RTSR3 register  *******************/
#define EXTI_RTSR3_TR                                       0x00740000U
#define EXTI_RTSR3_TR82                                     0x00040000U
#define EXTI_RTSR3_TR84                                     0x00100000U
#define EXTI_RTSR3_TR85                                     0x00200000U
#define EXTI_RTSR3_TR86                                     0x00400000U

/******************  Bit definition for EXTI_FTSR3 register  *******************/
#define EXTI_FTSR3_TR                                       0x00740000U
#define EXTI_FTSR3_TR82                                     0x00040000U
#define EXTI_FTSR3_TR84                                     0x00100000U
#define EXTI_FTSR3_TR85                                     0x00200000U
#define EXTI_FTSR3_TR86                                     0x00400000U

/******************  Bit definition for EXTI_SWIER3 register  ******************/
#define EXTI_SWIER3_SWI                                     0x00740000U
#define EXTI_SWIER3_SWIER82                                 0x00040000U
#define EXTI_SWIER3_SWIER84                                 0x00100000U
#define EXTI_SWIER3_SWIER85                                 0x00200000U
#define EXTI_SWIER3_SWIER86                                 0x00400000U

/*******************  Bit definition for EXTI_IMR1 register  *******************/
#define EXTI_IMR1_IM                                        0xFFFFFFFFU
#define EXTI_IMR1_IM0                                       0x00000001U
#define EXTI_IMR1_IM1                                       0x00000002U
#define EXTI_IMR1_IM2                                       0x00000004U
#define EXTI_IMR1_IM3                                       0x00000008U
#define EXTI_IMR1_IM4                                       0x00000010U
#define EXTI_IMR1_IM5                                       0x00000020U
#define EXTI_IMR1_IM6                                       0x00000040U
#define EXTI_IMR1_IM7                                       0x00000080U
#define EXTI_IMR1_IM8                                       0x00000100U
#define EXTI_IMR1_IM9                                       0x00000200U
#define EXTI_IMR1_IM10                                      0x00000400U
#define EXTI_IMR1_IM11                                      0x00000800U
#define EXTI_IMR1_IM12                                      0x00001000U
#define EXTI_IMR1_IM13                                      0x00002000U
#define EXTI_IMR1_IM14                                      0x00004000U
#define EXTI_IMR1_IM15                                      0x00008000U
#define EXTI_IMR1_IM16                                      0x00010000U
#define EXTI_IMR1_IM17                                      0x00020000U
#define EXTI_IMR1_IM18                                      0x00040000U
#define EXTI_IMR1_IM19                                      0x00080000U
#define EXTI_IMR1_IM20                                      0x00100000U
#define EXTI_IMR1_IM21                                      0x00200000U
#define EXTI_IMR1_IM22                                      0x00400000U
#define EXTI_IMR1_IM23                                      0x00800000U
#define EXTI_IMR1_IM24                                      0x01000000U
#define EXTI_IMR1_IM25                                      0x02000000U
#define EXTI_IMR1_IM26                                      0x04000000U
#define EXTI_IMR1_IM27                                      0x08000000U
#define EXTI_IMR1_IM28                                      0x10000000U
#define EXTI_IMR1_IM29                                      0x20000000U
#define EXTI_IMR1_IM30                                      0x40000000U
#define EXTI_IMR1_IM31                                      0x80000000U

/*******************  Bit definition for EXTI_EMR1 register  *******************/
#define EXTI_EMR1_EM                                        0xFFFFFFFFU
#define EXTI_EMR1_EM0                                       0x00000001U
#define EXTI_EMR1_EM1                                       0x00000002U
#define EXTI_EMR1_EM2                                       0x00000004U
#define EXTI_EMR1_EM3                                       0x00000008U
#define EXTI_EMR1_EM4                                       0x00000010U
#define EXTI_EMR1_EM5                                       0x00000020U
#define EXTI_EMR1_EM6                                       0x00000040U
#define EXTI_EMR1_EM7                                       0x00000080U
#define EXTI_EMR1_EM8                                       0x00000100U
#define EXTI_EMR1_EM9                                       0x00000200U
#define EXTI_EMR1_EM10                                      0x00000400U
#define EXTI_EMR1_EM11                                      0x00000800U
#define EXTI_EMR1_EM12                                      0x00001000U
#define EXTI_EMR1_EM13                                      0x00002000U
#define EXTI_EMR1_EM14                                      0x00004000U
#define EXTI_EMR1_EM15                                      0x00008000U
#define EXTI_EMR1_EM16                                      0x00010000U
#define EXTI_EMR1_EM17                                      0x00020000U
#define EXTI_EMR1_EM18                                      0x00040000U
#define EXTI_EMR1_EM20                                      0x00100000U
#define EXTI_EMR1_EM21                                      0x00200000U
#define EXTI_EMR1_EM22                                      0x00400000U
#define EXTI_EMR1_EM23                                      0x00800000U
#define EXTI_EMR1_EM24                                      0x01000000U
#define EXTI_EMR1_EM25                                      0x02000000U
#define EXTI_EMR1_EM26                                      0x04000000U
#define EXTI_EMR1_EM27                                      0x08000000U
#define EXTI_EMR1_EM28                                      0x10000000U
#define EXTI_EMR1_EM29                                      0x20000000U
#define EXTI_EMR1_EM30                                      0x40000000U
#define EXTI_EMR1_EM31                                      0x80000000U

/*******************  Bit definition for EXTI_PR1 register  ********************/
#define EXTI_PR1_PR                                         0x003FFFFFU
#define EXTI_PR1_PR0                                        0x00000001U
#define EXTI_PR1_PR1                                        0x00000002U
#define EXTI_PR1_PR2                                        0x00000004U
#define EXTI_PR1_PR3                                        0x00000008U
#define EXTI_PR1_PR4                                        0x00000010U
#define EXTI_PR1_PR5                                        0x00000020U
#define EXTI_PR1_PR6                                        0x00000040U
#define EXTI_PR1_PR7                                        0x00000080U
#define EXTI_PR1_PR8                                        0x00000100U
#define EXTI_PR1_PR9                                        0x00000200U
#define EXTI_PR1_PR10                                       0x00000400U
#define EXTI_PR1_PR11                                       0x00000800U
#define EXTI_PR1_PR12                                       0x00001000U
#define EXTI_PR1_PR13                                       0x00002000U
#define EXTI_PR1_PR14                                       0x00004000U
#define EXTI_PR1_PR15                                       0x00008000U
#define EXTI_PR1_PR16                                       0x00010000U
#define EXTI_PR1_PR17                                       0x00020000U
#define EXTI_PR1_PR18                                       0x00040000U
#define EXTI_PR1_PR19                                       0x00080000U
#define EXTI_PR1_PR20                                       0x00100000U
#define EXTI_PR1_PR21                                       0x00200000U

/*******************  Bit definition for EXTI_IMR2 register  *******************/
#define EXTI_IMR2_IM                                        0xFFFFDFFFU
#define EXTI_IMR2_IM32                                      0x00000001U
#define EXTI_IMR2_IM33                                      0x00000002U
#define EXTI_IMR2_IM34                                      0x00000004U
#define EXTI_IMR2_IM35                                      0x00000008U
#define EXTI_IMR2_IM36                                      0x00000010U
#define EXTI_IMR2_IM37                                      0x00000020U
#define EXTI_IMR2_IM38                                      0x00000040U
#define EXTI_IMR2_IM39                                      0x00000080U
#define EXTI_IMR2_IM40                                      0x00000100U
#define EXTI_IMR2_IM41                                      0x00000200U
#define EXTI_IMR2_IM42                                      0x00000400U
#define EXTI_IMR2_IM43                                      0x00000800U
#define EXTI_IMR2_IM44                                      0x00001000U
#define EXTI_IMR2_IM46                                      0x00004000U
#define EXTI_IMR2_IM47                                      0x00008000U
#define EXTI_IMR2_IM48                                      0x00010000U
#define EXTI_IMR2_IM49                                      0x00020000U
#define EXTI_IMR2_IM50                                      0x00040000U
#define EXTI_IMR2_IM51                                      0x00080000U
#define EXTI_IMR2_IM52                                      0x00100000U
#define EXTI_IMR2_IM53                                      0x00200000U
#define EXTI_IMR2_IM54                                      0x00400000U
#define EXTI_IMR2_IM55                                      0x00800000U
#define EXTI_IMR2_IM56                                      0x01000000U
#define EXTI_IMR2_IM57                                      0x02000000U
#define EXTI_IMR2_IM58                                      0x04000000U
#define EXTI_IMR2_IM59                                      0x08000000U
#define EXTI_IMR2_IM60                                      0x10000000U
#define EXTI_IMR2_IM61                                      0x20000000U
#define EXTI_IMR2_IM62                                      0x40000000U
#define EXTI_IMR2_IM63                                      0x80000000U

/*******************  Bit definition for EXTI_EMR2 register  *******************/
#define EXTI_EMR2_EM                                        0xFFFFDFFFU
#define EXTI_EMR2_EM32                                      0x00000001U
#define EXTI_EMR2_EM33                                      0x00000002U
#define EXTI_EMR2_EM34                                      0x00000004U
#define EXTI_EMR2_EM35                                      0x00000008U
#define EXTI_EMR2_EM36                                      0x00000010U
#define EXTI_EMR2_EM37                                      0x00000020U
#define EXTI_EMR2_EM38                                      0x00000040U
#define EXTI_EMR2_EM39                                      0x00000080U
#define EXTI_EMR2_EM40                                      0x00000100U
#define EXTI_EMR2_EM41                                      0x00000200U
#define EXTI_EMR2_EM42                                      0x00000400U
#define EXTI_EMR2_EM43                                      0x00000800U
#define EXTI_EMR2_EM44                                      0x00001000U
#define EXTI_EMR2_EM46                                      0x00004000U
#define EXTI_EMR2_EM47                                      0x00008000U
#define EXTI_EMR2_EM48                                      0x00010000U
#define EXTI_EMR2_EM49                                      0x00020000U
#define EXTI_EMR2_EM50                                      0x00040000U
#define EXTI_EMR2_EM51                                      0x00080000U
#define EXTI_EMR2_EM52                                      0x00100000U
#define EXTI_EMR2_EM53                                      0x00200000U
#define EXTI_EMR2_EM54                                      0x00400000U
#define EXTI_EMR2_EM55                                      0x00800000U
#define EXTI_EMR2_EM56                                      0x01000000U
#define EXTI_EMR2_EM57                                      0x02000000U
#define EXTI_EMR2_EM58                                      0x04000000U
#define EXTI_EMR2_EM59                                      0x08000000U
#define EXTI_EMR2_EM60                                      0x10000000U
#define EXTI_EMR2_EM61                                      0x20000000U
#define EXTI_EMR2_EM62                                      0x40000000U
#define EXTI_EMR2_EM63                                      0x80000000U

/*******************  Bit definition for EXTI_PR2 register  ********************/
#define EXTI_PR2_PR                                         0x000A0000U
#define EXTI_PR2_PR49                                       0x00020000U
#define EXTI_PR2_PR51                                       0x00080000U

/*******************  Bit definition for EXTI_IMR3 register  *******************/
#define EXTI_IMR3_IM                                        0x00F5FFFFU
#define EXTI_IMR3_IM64                                      0x00000001U
#define EXTI_IMR3_IM65                                      0x00000002U
#define EXTI_IMR3_IM66                                      0x00000004U
#define EXTI_IMR3_IM67                                      0x00000008U
#define EXTI_IMR3_IM68                                      0x00000010U
#define EXTI_IMR3_IM69                                      0x00000020U
#define EXTI_IMR3_IM70                                      0x00000040U
#define EXTI_IMR3_IM71                                      0x00000080U
#define EXTI_IMR3_IM72                                      0x00000100U
#define EXTI_IMR3_IM73                                      0x00000200U
#define EXTI_IMR3_IM74                                      0x00000400U
#define EXTI_IMR3_IM75                                      0x00000800U
#define EXTI_IMR3_IM76                                      0x00001000U
#define EXTI_IMR3_IM77                                      0x00002000U
#define EXTI_IMR3_IM78                                      0x00004000U
#define EXTI_IMR3_IM79                                      0x00008000U
#define EXTI_IMR3_IM80                                      0x00010000U
#define EXTI_IMR3_IM82                                      0x00040000U
#define EXTI_IMR3_IM84                                      0x00100000U
#define EXTI_IMR3_IM85                                      0x00200000U
#define EXTI_IMR3_IM86                                      0x00400000U
#define EXTI_IMR3_IM87                                      0x00800000U

/*******************  Bit definition for EXTI_EMR3 register  *******************/
#define EXTI_EMR3_EM                                        0x00F5FFFFU
#define EXTI_EMR3_EM64                                      0x00000001U
#define EXTI_EMR3_EM65                                      0x00000002U
#define EXTI_EMR3_EM66                                      0x00000004U
#define EXTI_EMR3_EM67                                      0x00000008U
#define EXTI_EMR3_EM68                                      0x00000010U
#define EXTI_EMR3_EM69                                      0x00000020U
#define EXTI_EMR3_EM70                                      0x00000040U
#define EXTI_EMR3_EM71                                      0x00000080U
#define EXTI_EMR3_EM72                                      0x00000100U
#define EXTI_EMR3_EM73                                      0x00000200U
#define EXTI_EMR3_EM74                                      0x00000400U
#define EXTI_EMR3_EM75                                      0x00000800U
#define EXTI_EMR3_EM76                                      0x00001000U
#define EXTI_EMR3_EM77                                      0x00002000U
#define EXTI_EMR3_EM78                                      0x00004000U
#define EXTI_EMR3_EM79                                      0x00008000U
#define EXTI_EMR3_EM80                                      0x00010000U
#define EXTI_EMR3_EM81                                      0x00020000U
#define EXTI_EMR3_EM82                                      0x00040000U
#define EXTI_EMR3_EM84                                      0x00100000U
#define EXTI_EMR3_EM85                                      0x00200000U
#define EXTI_EMR3_EM86                                      0x00400000U
#define EXTI_EMR3_EM87                                      0x00800000U

/*******************  Bit definition for EXTI_PR3 register  ********************/
#define EXTI_PR3_PR                                         0x00740000U
#define EXTI_PR3_PR82                                       0x00040000U
#define EXTI_PR3_PR84                                       0x00100000U
#define EXTI_PR3_PR85                                       0x00200000U
#define EXTI_PR3_PR86                                       0x00400000U

#endif /* _STM32H743_EXTI_H */

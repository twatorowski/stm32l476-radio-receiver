/**
* @file adc.h
* 
* @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
* @date 2021-05-08
* 
* @brief STM32H743: ADC
*/
#ifndef _STM32H743_ADC_H
#define _STM32H743_ADC_H

#include "stm32h743/stm32h743.h"

/* instance base addresses */
#define ADC1_BASE                                           0x40022000
#define ADC2_BASE                                           0x40022100
#define ADC12_COMMON_BASE                                   0x40022300
#define ADC3_BASE                                           0x58006000
#define ADC3_COMMON_BASE                                    0x58006300

/* peripheral instances */
#define ADC1                                                ((adc_t *) ADC1_BASE)
#define ADC2                                                ((adc_t *) ADC2_BASE)
#define ADC3                                                ((adc_t *) ADC3_BASE)
#define ADC3_COMMON                                         ((adc_com_t *) ADC3_COMMON_BASE)
#define ADC12_COMMON                                        ((adc_com_t *) ADC12_COMMON_BASE)


/* register bank */
typedef struct {
    reg32_t ISR;              
    reg32_t IER;              
    reg32_t CR;               
    reg32_t CFGR;             
    reg32_t CFGR2;            
    reg32_t SMPR1;            
    reg32_t SMPR2;            
    reg32_t PCSEL;            
    reg32_t LTR1;             
    reg32_t HTR1;             
    reg32_t RESERVED1;        
    reg32_t RESERVED2;        
    reg32_t SQR1;             
    reg32_t SQR2;             
    reg32_t SQR3;             
    reg32_t SQR4;             
    reg32_t DR;               
    reg32_t RESERVED3;        
    reg32_t RESERVED4;        
    reg32_t JSQR;             
    reg32_t RESERVED5[4];     
    reg32_t OFR1;             
    reg32_t OFR2;             
    reg32_t OFR3;             
    reg32_t OFR4;             
    reg32_t RESERVED6[4];     
    reg32_t JDR1;             
    reg32_t JDR2;             
    reg32_t JDR3;             
    reg32_t JDR4;             
    reg32_t RESERVED7[4];     
    reg32_t AWD2CR;           
    reg32_t AWD3CR;           
    reg32_t RESERVED8;        
    reg32_t RESERVED9;        
    reg32_t LTR2;             
    reg32_t HTR2;             
    reg32_t LTR3;             
    reg32_t HTR3;             
    reg32_t DIFSEL;           
    reg32_t CALFACT;          
    reg32_t CALFACT2;  
} adc_t;

/****************  Bit definition for ADC_ISR register  ****************/
#define ADC_ISR_ADRDY                                       0x00000001U
#define ADC_ISR_EOSMP                                       0x00000002U
#define ADC_ISR_EOC                                         0x00000004U
#define ADC_ISR_EOS                                         0x00000008U
#define ADC_ISR_OVR                                         0x00000010U
#define ADC_ISR_JEOC                                        0x00000020U
#define ADC_ISR_JEOS                                        0x00000040U
#define ADC_ISR_AWD1                                        0x00000080U
#define ADC_ISR_AWD2                                        0x00000100U
#define ADC_ISR_AWD3                                        0x00000200U
#define ADC_ISR_JQOVF                                       0x00000400U

/****************  Bit definition for ADC_IER register  ****************/
#define ADC_IER_ADRDYIE                                     0x00000001U
#define ADC_IER_EOSMPIE                                     0x00000002U
#define ADC_IER_EOCIE                                       0x00000004U
#define ADC_IER_EOSIE                                       0x00000008U
#define ADC_IER_OVRIE                                       0x00000010U
#define ADC_IER_JEOCIE                                      0x00000020U
#define ADC_IER_JEOSIE                                      0x00000040U
#define ADC_IER_AWD1IE                                      0x00000080U
#define ADC_IER_AWD2IE                                      0x00000100U
#define ADC_IER_AWD3IE                                      0x00000200U
#define ADC_IER_JQOVFIE                                     0x00000400U

/****************  Bit definition for ADC_CR register  ****************/
#define ADC_CR_ADEN                                         0x00000001U
#define ADC_CR_ADDIS                                        0x00000002U
#define ADC_CR_ADSTART                                      0x00000004U
#define ADC_CR_JADSTART                                     0x00000008U
#define ADC_CR_ADSTP                                        0x00000010U
#define ADC_CR_JADSTP                                       0x00000020U
#define ADC_CR_BOOST                                        0x00000300U
#define ADC_CR_BOOST_0                                      0x00000100U
#define ADC_CR_BOOST_1                                      0x00000200U
#define ADC_CR_ADCALLIN                                     0x00010000U
#define ADC_CR_LINCALRDYW1                                  0x00400000U
#define ADC_CR_LINCALRDYW2                                  0x00800000U
#define ADC_CR_LINCALRDYW3                                  0x01000000U
#define ADC_CR_LINCALRDYW4                                  0x02000000U
#define ADC_CR_LINCALRDYW5                                  0x04000000U
#define ADC_CR_LINCALRDYW6                                  0x08000000U
#define ADC_CR_ADVREGEN                                     0x10000000U
#define ADC_CR_DEEPPWD                                      0x20000000U
#define ADC_CR_ADCALDIF                                     0x40000000U
#define ADC_CR_ADCAL                                        0x80000000U

/****************  Bit definition for ADC_CFGR register  ****************/
#define ADC_CFGR_DMNGT                                      0x00000003U
#define ADC_CFGR_DMNGT_0                                    0x00000001U
#define ADC_CFGR_DMNGT_1                                    0x00000002U
#define ADC_CFGR_RES                                        0x0000001CU
#define ADC_CFGR_RES_0                                      0x00000004U
#define ADC_CFGR_RES_1                                      0x00000008U
#define ADC_CFGR_RES_2                                      0x00000010U
#define ADC_CFGR_EXTSEL                                     0x000003E0U
#define ADC_CFGR_EXTSEL_0                                   0x00000020U
#define ADC_CFGR_EXTSEL_1                                   0x00000040U
#define ADC_CFGR_EXTSEL_2                                   0x00000080U
#define ADC_CFGR_EXTSEL_3                                   0x00000100U
#define ADC_CFGR_EXTSEL_4                                   0x00000200U
#define ADC_CFGR_EXTEN                                      0x00000C00U
#define ADC_CFGR_EXTEN_0                                    0x00000400U
#define ADC_CFGR_EXTEN_1                                    0x00000800U
#define ADC_CFGR_OVRMOD                                     0x00001000U
#define ADC_CFGR_CONT                                       0x00002000U
#define ADC_CFGR_AUTDLY                                     0x00004000U
#define ADC_CFGR_DISCEN                                     0x00010000U
#define ADC_CFGR_DISCNUM                                    0x000E0000U
#define ADC_CFGR_DISCNUM_0                                  0x00020000U
#define ADC_CFGR_DISCNUM_1                                  0x00040000U
#define ADC_CFGR_DISCNUM_2                                  0x00080000U
#define ADC_CFGR_JDISCEN                                    0x00100000U
#define ADC_CFGR_JQM                                        0x00200000U
#define ADC_CFGR_AWD1SGL                                    0x00400000U
#define ADC_CFGR_AWD1EN                                     0x00800000U
#define ADC_CFGR_JAWD1EN                                    0x01000000U
#define ADC_CFGR_JAUTO                                      0x02000000U
#define ADC_CFGR_AWD1CH                                     0x7C000000U
#define ADC_CFGR_AWD1CH_0                                   0x04000000U
#define ADC_CFGR_AWD1CH_1                                   0x08000000U
#define ADC_CFGR_AWD1CH_2                                   0x10000000U
#define ADC_CFGR_AWD1CH_3                                   0x20000000U
#define ADC_CFGR_AWD1CH_4                                   0x40000000U
#define ADC_CFGR_JQDIS                                      0x80000000U

/****************  Bit definition for ADC_CFGR2 register  ****************/
#define ADC_CFGR2_ROVSE                                     0x00000001U
#define ADC_CFGR2_JOVSE                                     0x00000002U
#define ADC_CFGR2_OVSS                                      0x000001E0U
#define ADC_CFGR2_OVSS_0                                    0x00000020U
#define ADC_CFGR2_OVSS_1                                    0x00000040U
#define ADC_CFGR2_OVSS_2                                    0x00000080U
#define ADC_CFGR2_OVSS_3                                    0x00000100U
#define ADC_CFGR2_TROVS                                     0x00000200U
#define ADC_CFGR2_ROVSM                                     0x00000400U
#define ADC_CFGR2_RSHIFT1                                   0x00000800U
#define ADC_CFGR2_RSHIFT2                                   0x00001000U
#define ADC_CFGR2_RSHIFT3                                   0x00002000U
#define ADC_CFGR2_RSHIFT4                                   0x00004000U
#define ADC_CFGR2_OVSR                                      0x03FF0000U
#define ADC_CFGR2_OVSR_0                                    0x00010000U
#define ADC_CFGR2_OVSR_1                                    0x00020000U
#define ADC_CFGR2_OVSR_2                                    0x00040000U
#define ADC_CFGR2_OVSR_3                                    0x00080000U
#define ADC_CFGR2_OVSR_4                                    0x00100000U
#define ADC_CFGR2_OVSR_5                                    0x00200000U
#define ADC_CFGR2_OVSR_6                                    0x00400000U
#define ADC_CFGR2_OVSR_7                                    0x00800000U
#define ADC_CFGR2_OVSR_8                                    0x01000000U
#define ADC_CFGR2_OVSR_9                                    0x02000000U
#define ADC_CFGR2_LSHIFT                                    0xF0000000U
#define ADC_CFGR2_LSHIFT_0                                  0x10000000U
#define ADC_CFGR2_LSHIFT_1                                  0x20000000U
#define ADC_CFGR2_LSHIFT_2                                  0x40000000U
#define ADC_CFGR2_LSHIFT_3                                  0x80000000U

/****************  Bit definition for ADC_SMPR1 register  ****************/
#define ADC_SMPR1_SMP0                                      0x00000007U
#define ADC_SMPR1_SMP0_0                                    0x00000001U
#define ADC_SMPR1_SMP0_1                                    0x00000002U
#define ADC_SMPR1_SMP0_2                                    0x00000004U
#define ADC_SMPR1_SMP1                                      0x00000038U
#define ADC_SMPR1_SMP1_0                                    0x00000008U
#define ADC_SMPR1_SMP1_1                                    0x00000010U
#define ADC_SMPR1_SMP1_2                                    0x00000020U
#define ADC_SMPR1_SMP2                                      0x000001C0U
#define ADC_SMPR1_SMP2_0                                    0x00000040U
#define ADC_SMPR1_SMP2_1                                    0x00000080U
#define ADC_SMPR1_SMP2_2                                    0x00000100U
#define ADC_SMPR1_SMP3                                      0x00000E00U
#define ADC_SMPR1_SMP3_0                                    0x00000200U
#define ADC_SMPR1_SMP3_1                                    0x00000400U
#define ADC_SMPR1_SMP3_2                                    0x00000800U
#define ADC_SMPR1_SMP4                                      0x00007000U
#define ADC_SMPR1_SMP4_0                                    0x00001000U
#define ADC_SMPR1_SMP4_1                                    0x00002000U
#define ADC_SMPR1_SMP4_2                                    0x00004000U
#define ADC_SMPR1_SMP5                                      0x00038000U
#define ADC_SMPR1_SMP5_0                                    0x00008000U
#define ADC_SMPR1_SMP5_1                                    0x00010000U
#define ADC_SMPR1_SMP5_2                                    0x00020000U
#define ADC_SMPR1_SMP6                                      0x001C0000U
#define ADC_SMPR1_SMP6_0                                    0x00040000U
#define ADC_SMPR1_SMP6_1                                    0x00080000U
#define ADC_SMPR1_SMP6_2                                    0x00100000U
#define ADC_SMPR1_SMP7                                      0x00E00000U
#define ADC_SMPR1_SMP7_0                                    0x00200000U
#define ADC_SMPR1_SMP7_1                                    0x00400000U
#define ADC_SMPR1_SMP7_2                                    0x00800000U
#define ADC_SMPR1_SMP8                                      0x07000000U
#define ADC_SMPR1_SMP8_0                                    0x01000000U
#define ADC_SMPR1_SMP8_1                                    0x02000000U
#define ADC_SMPR1_SMP8_2                                    0x04000000U
#define ADC_SMPR1_SMP9                                      0x38000000U
#define ADC_SMPR1_SMP9_0                                    0x08000000U
#define ADC_SMPR1_SMP9_1                                    0x10000000U
#define ADC_SMPR1_SMP9_2                                    0x20000000U

/****************  Bit definition for ADC_SMPR2 register  ****************/
#define ADC_SMPR2_SMP10                                     0x00000007U
#define ADC_SMPR2_SMP10_0                                   0x00000001U
#define ADC_SMPR2_SMP10_1                                   0x00000002U
#define ADC_SMPR2_SMP10_2                                   0x00000004U
#define ADC_SMPR2_SMP11                                     0x00000038U
#define ADC_SMPR2_SMP11_0                                   0x00000008U
#define ADC_SMPR2_SMP11_1                                   0x00000010U
#define ADC_SMPR2_SMP11_2                                   0x00000020U
#define ADC_SMPR2_SMP12                                     0x000001C0U
#define ADC_SMPR2_SMP12_0                                   0x00000040U
#define ADC_SMPR2_SMP12_1                                   0x00000080U
#define ADC_SMPR2_SMP12_2                                   0x00000100U
#define ADC_SMPR2_SMP13                                     0x00000E00U
#define ADC_SMPR2_SMP13_0                                   0x00000200U
#define ADC_SMPR2_SMP13_1                                   0x00000400U
#define ADC_SMPR2_SMP13_2                                   0x00000800U
#define ADC_SMPR2_SMP14                                     0x00007000U
#define ADC_SMPR2_SMP14_0                                   0x00001000U
#define ADC_SMPR2_SMP14_1                                   0x00002000U
#define ADC_SMPR2_SMP14_2                                   0x00004000U
#define ADC_SMPR2_SMP15                                     0x00038000U
#define ADC_SMPR2_SMP15_0                                   0x00008000U
#define ADC_SMPR2_SMP15_1                                   0x00010000U
#define ADC_SMPR2_SMP15_2                                   0x00020000U
#define ADC_SMPR2_SMP16                                     0x001C0000U
#define ADC_SMPR2_SMP16_0                                   0x00040000U
#define ADC_SMPR2_SMP16_1                                   0x00080000U
#define ADC_SMPR2_SMP16_2                                   0x00100000U
#define ADC_SMPR2_SMP17                                     0x00E00000U
#define ADC_SMPR2_SMP17_0                                   0x00200000U
#define ADC_SMPR2_SMP17_1                                   0x00400000U
#define ADC_SMPR2_SMP17_2                                   0x00800000U
#define ADC_SMPR2_SMP18                                     0x07000000U
#define ADC_SMPR2_SMP18_0                                   0x01000000U
#define ADC_SMPR2_SMP18_1                                   0x02000000U
#define ADC_SMPR2_SMP18_2                                   0x04000000U
#define ADC_SMPR2_SMP19                                     0x38000000U
#define ADC_SMPR2_SMP19_0                                   0x08000000U
#define ADC_SMPR2_SMP19_1                                   0x10000000U
#define ADC_SMPR2_SMP19_2                                   0x20000000U

/****************  Bit definition for ADC_PCSEL register  ****************/
#define ADC_PCSEL_PCSEL                                     0x000FFFFFU
#define ADC_PCSEL_PCSEL_0                                   0x00000001U
#define ADC_PCSEL_PCSEL_1                                   0x00000002U
#define ADC_PCSEL_PCSEL_2                                   0x00000004U
#define ADC_PCSEL_PCSEL_3                                   0x00000008U
#define ADC_PCSEL_PCSEL_4                                   0x00000010U
#define ADC_PCSEL_PCSEL_5                                   0x00000020U
#define ADC_PCSEL_PCSEL_6                                   0x00000040U
#define ADC_PCSEL_PCSEL_7                                   0x00000080U
#define ADC_PCSEL_PCSEL_8                                   0x00000100U
#define ADC_PCSEL_PCSEL_9                                   0x00000200U
#define ADC_PCSEL_PCSEL_10                                  0x00000400U
#define ADC_PCSEL_PCSEL_11                                  0x00000800U
#define ADC_PCSEL_PCSEL_12                                  0x00001000U
#define ADC_PCSEL_PCSEL_13                                  0x00002000U
#define ADC_PCSEL_PCSEL_14                                  0x00004000U
#define ADC_PCSEL_PCSEL_15                                  0x00008000U
#define ADC_PCSEL_PCSEL_16                                  0x00010000U
#define ADC_PCSEL_PCSEL_17                                  0x00020000U
#define ADC_PCSEL_PCSEL_18                                  0x00040000U
#define ADC_PCSEL_PCSEL_19                                  0x00080000U

/*************  Bit definition for ADC_LTR1, 2, 3 registers *************/
#define ADC_LTR_LT                                          0x03FFFFFFU

/*************  Bit definition for ADC_HTR1, 2, 3 registers  ************/
#define ADC_HTR_HT                                          0x03FFFFFFU

/****************  Bit definition for ADC_SQR1 register  ****************/
#define ADC_SQR1_L                                          0x0000000FU
#define ADC_SQR1_L_0                                        0x00000001U
#define ADC_SQR1_L_1                                        0x00000002U
#define ADC_SQR1_L_2                                        0x00000004U
#define ADC_SQR1_L_3                                        0x00000008U
#define ADC_SQR1_SQ1                                        0x000007C0U
#define ADC_SQR1_SQ1_0                                      0x00000040U
#define ADC_SQR1_SQ1_1                                      0x00000080U
#define ADC_SQR1_SQ1_2                                      0x00000100U
#define ADC_SQR1_SQ1_3                                      0x00000200U
#define ADC_SQR1_SQ1_4                                      0x00000400U
#define ADC_SQR1_SQ2                                        0x0001F000U
#define ADC_SQR1_SQ2_0                                      0x00001000U
#define ADC_SQR1_SQ2_1                                      0x00002000U
#define ADC_SQR1_SQ2_2                                      0x00004000U
#define ADC_SQR1_SQ2_3                                      0x00008000U
#define ADC_SQR1_SQ2_4                                      0x00010000U
#define ADC_SQR1_SQ3                                        0x007C0000U
#define ADC_SQR1_SQ3_0                                      0x00040000U
#define ADC_SQR1_SQ3_1                                      0x00080000U
#define ADC_SQR1_SQ3_2                                      0x00100000U
#define ADC_SQR1_SQ3_3                                      0x00200000U
#define ADC_SQR1_SQ3_4                                      0x00400000U
#define ADC_SQR1_SQ4                                        0x1F000000U
#define ADC_SQR1_SQ4_0                                      0x01000000U
#define ADC_SQR1_SQ4_1                                      0x02000000U
#define ADC_SQR1_SQ4_2                                      0x04000000U
#define ADC_SQR1_SQ4_3                                      0x08000000U
#define ADC_SQR1_SQ4_4                                      0x10000000U

/****************  Bit definition for ADC_SQR2 register  ****************/
#define ADC_SQR2_SQ5                                        0x0000001FU
#define ADC_SQR2_SQ5_0                                      0x00000001U
#define ADC_SQR2_SQ5_1                                      0x00000002U
#define ADC_SQR2_SQ5_2                                      0x00000004U
#define ADC_SQR2_SQ5_3                                      0x00000008U
#define ADC_SQR2_SQ5_4                                      0x00000010U
#define ADC_SQR2_SQ6                                        0x000007C0U
#define ADC_SQR2_SQ6_0                                      0x00000040U
#define ADC_SQR2_SQ6_1                                      0x00000080U
#define ADC_SQR2_SQ6_2                                      0x00000100U
#define ADC_SQR2_SQ6_3                                      0x00000200U
#define ADC_SQR2_SQ6_4                                      0x00000400U
#define ADC_SQR2_SQ7                                        0x0001F000U
#define ADC_SQR2_SQ7_0                                      0x00001000U
#define ADC_SQR2_SQ7_1                                      0x00002000U
#define ADC_SQR2_SQ7_2                                      0x00004000U
#define ADC_SQR2_SQ7_3                                      0x00008000U
#define ADC_SQR2_SQ7_4                                      0x00010000U
#define ADC_SQR2_SQ8                                        0x007C0000U
#define ADC_SQR2_SQ8_0                                      0x00040000U
#define ADC_SQR2_SQ8_1                                      0x00080000U
#define ADC_SQR2_SQ8_2                                      0x00100000U
#define ADC_SQR2_SQ8_3                                      0x00200000U
#define ADC_SQR2_SQ8_4                                      0x00400000U
#define ADC_SQR2_SQ9                                        0x1F000000U
#define ADC_SQR2_SQ9_0                                      0x01000000U
#define ADC_SQR2_SQ9_1                                      0x02000000U
#define ADC_SQR2_SQ9_2                                      0x04000000U
#define ADC_SQR2_SQ9_3                                      0x08000000U
#define ADC_SQR2_SQ9_4                                      0x10000000U

/****************  Bit definition for ADC_SQR3 register  ****************/
#define ADC_SQR3_SQ10                                       0x0000001FU
#define ADC_SQR3_SQ10_0                                     0x00000001U
#define ADC_SQR3_SQ10_1                                     0x00000002U
#define ADC_SQR3_SQ10_2                                     0x00000004U
#define ADC_SQR3_SQ10_3                                     0x00000008U
#define ADC_SQR3_SQ10_4                                     0x00000010U
#define ADC_SQR3_SQ11                                       0x000007C0U
#define ADC_SQR3_SQ11_0                                     0x00000040U
#define ADC_SQR3_SQ11_1                                     0x00000080U
#define ADC_SQR3_SQ11_2                                     0x00000100U
#define ADC_SQR3_SQ11_3                                     0x00000200U
#define ADC_SQR3_SQ11_4                                     0x00000400U
#define ADC_SQR3_SQ12                                       0x0001F000U
#define ADC_SQR3_SQ12_0                                     0x00001000U
#define ADC_SQR3_SQ12_1                                     0x00002000U
#define ADC_SQR3_SQ12_2                                     0x00004000U
#define ADC_SQR3_SQ12_3                                     0x00008000U
#define ADC_SQR3_SQ12_4                                     0x00010000U
#define ADC_SQR3_SQ13                                       0x007C0000U
#define ADC_SQR3_SQ13_0                                     0x00040000U
#define ADC_SQR3_SQ13_1                                     0x00080000U
#define ADC_SQR3_SQ13_2                                     0x00100000U
#define ADC_SQR3_SQ13_3                                     0x00200000U
#define ADC_SQR3_SQ13_4                                     0x00400000U
#define ADC_SQR3_SQ14                                       0x1F000000U
#define ADC_SQR3_SQ14_0                                     0x01000000U
#define ADC_SQR3_SQ14_1                                     0x02000000U
#define ADC_SQR3_SQ14_2                                     0x04000000U
#define ADC_SQR3_SQ14_3                                     0x08000000U
#define ADC_SQR3_SQ14_4                                     0x10000000U

/****************  Bit definition for ADC_SQR4 register  ****************/
#define ADC_SQR4_SQ15                                       0x0000001FU
#define ADC_SQR4_SQ15_0                                     0x00000001U
#define ADC_SQR4_SQ15_1                                     0x00000002U
#define ADC_SQR4_SQ15_2                                     0x00000004U
#define ADC_SQR4_SQ15_3                                     0x00000008U
#define ADC_SQR4_SQ15_4                                     0x00000010U
#define ADC_SQR4_SQ16                                       0x000007C0U
#define ADC_SQR4_SQ16_0                                     0x00000040U
#define ADC_SQR4_SQ16_1                                     0x00000080U
#define ADC_SQR4_SQ16_2                                     0x00000100U
#define ADC_SQR4_SQ16_3                                     0x00000200U
#define ADC_SQR4_SQ16_4                                     0x00000400U

/****************  Bit definition for ADC_DR register  ****************/
#define ADC_DR_RDATA                                        0xFFFFFFFFU

/****************  Bit definition for ADC_JSQR register  ****************/
#define ADC_JSQR_JL                                         0x00000003U
#define ADC_JSQR_JL_0                                       0x00000001U
#define ADC_JSQR_JL_1                                       0x00000002U
#define ADC_JSQR_JEXTSEL                                    0x0000007CU
#define ADC_JSQR_JEXTSEL_0                                  0x00000004U
#define ADC_JSQR_JEXTSEL_1                                  0x00000008U
#define ADC_JSQR_JEXTSEL_2                                  0x00000010U
#define ADC_JSQR_JEXTSEL_3                                  0x00000020U
#define ADC_JSQR_JEXTSEL_4                                  0x00000040U
#define ADC_JSQR_JEXTEN                                     0x00000180U
#define ADC_JSQR_JEXTEN_0                                   0x00000080U
#define ADC_JSQR_JEXTEN_1                                   0x00000100U
#define ADC_JSQR_JSQ1                                       0x00003E00U
#define ADC_JSQR_JSQ1_0                                     0x00000200U
#define ADC_JSQR_JSQ1_1                                     0x00000400U
#define ADC_JSQR_JSQ1_2                                     0x00000800U
#define ADC_JSQR_JSQ1_3                                     0x00001000U
#define ADC_JSQR_JSQ1_4                                     0x00002000U
#define ADC_JSQR_JSQ2                                       0x000F8000U
#define ADC_JSQR_JSQ2_0                                     0x00008000U
#define ADC_JSQR_JSQ2_1                                     0x00010000U
#define ADC_JSQR_JSQ2_2                                     0x00020000U
#define ADC_JSQR_JSQ2_3                                     0x00040000U
#define ADC_JSQR_JSQ2_4                                     0x00080000U
#define ADC_JSQR_JSQ3                                       0x03E00000U
#define ADC_JSQR_JSQ3_0                                     0x00200000U
#define ADC_JSQR_JSQ3_1                                     0x00400000U
#define ADC_JSQR_JSQ3_2                                     0x00800000U
#define ADC_JSQR_JSQ3_3                                     0x01000000U
#define ADC_JSQR_JSQ3_4                                     0x02000000U
#define ADC_JSQR_JSQ4                                       0xF8000000U
#define ADC_JSQR_JSQ4_0                                     0x08000000U
#define ADC_JSQR_JSQ4_1                                     0x10000000U
#define ADC_JSQR_JSQ4_2                                     0x20000000U
#define ADC_JSQR_JSQ4_3                                     0x40000000U
#define ADC_JSQR_JSQ4_4                                     0x80000000U

/****************  Bit definition for ADC_OFR1 register  ****************/
#define ADC_OFR1_OFFSET1                                    0x03FFFFFFU
#define ADC_OFR1_OFFSET1_0                                  0x00000001U
#define ADC_OFR1_OFFSET1_1                                  0x00000002U
#define ADC_OFR1_OFFSET1_2                                  0x00000004U
#define ADC_OFR1_OFFSET1_3                                  0x00000008U
#define ADC_OFR1_OFFSET1_4                                  0x00000010U
#define ADC_OFR1_OFFSET1_5                                  0x00000020U
#define ADC_OFR1_OFFSET1_6                                  0x00000040U
#define ADC_OFR1_OFFSET1_7                                  0x00000080U
#define ADC_OFR1_OFFSET1_8                                  0x00000100U
#define ADC_OFR1_OFFSET1_9                                  0x00000200U
#define ADC_OFR1_OFFSET1_10                                 0x00000400U
#define ADC_OFR1_OFFSET1_11                                 0x00000800U
#define ADC_OFR1_OFFSET1_12                                 0x00001000U
#define ADC_OFR1_OFFSET1_13                                 0x00002000U
#define ADC_OFR1_OFFSET1_14                                 0x00004000U
#define ADC_OFR1_OFFSET1_15                                 0x00008000U
#define ADC_OFR1_OFFSET1_16                                 0x00010000U
#define ADC_OFR1_OFFSET1_17                                 0x00020000U
#define ADC_OFR1_OFFSET1_18                                 0x00040000U
#define ADC_OFR1_OFFSET1_19                                 0x00080000U
#define ADC_OFR1_OFFSET1_20                                 0x00100000U
#define ADC_OFR1_OFFSET1_21                                 0x00200000U
#define ADC_OFR1_OFFSET1_22                                 0x00400000U
#define ADC_OFR1_OFFSET1_23                                 0x00800000U
#define ADC_OFR1_OFFSET1_24                                 0x01000000U
#define ADC_OFR1_OFFSET1_25                                 0x02000000U
#define ADC_OFR1_OFFSET1_CH                                 0x7C000000U
#define ADC_OFR1_OFFSET1_CH_0                               0x04000000U
#define ADC_OFR1_OFFSET1_CH_1                               0x08000000U
#define ADC_OFR1_OFFSET1_CH_2                               0x10000000U
#define ADC_OFR1_OFFSET1_CH_3                               0x20000000U
#define ADC_OFR1_OFFSET1_CH_4                               0x40000000U
#define ADC_OFR1_SSATE                                      0x80000000U

/****************  Bit definition for ADC_OFR2 register  ****************/
#define ADC_OFR2_OFFSET2                                    0x03FFFFFFU
#define ADC_OFR2_OFFSET2_0                                  0x00000001U
#define ADC_OFR2_OFFSET2_1                                  0x00000002U
#define ADC_OFR2_OFFSET2_2                                  0x00000004U
#define ADC_OFR2_OFFSET2_3                                  0x00000008U
#define ADC_OFR2_OFFSET2_4                                  0x00000010U
#define ADC_OFR2_OFFSET2_5                                  0x00000020U
#define ADC_OFR2_OFFSET2_6                                  0x00000040U
#define ADC_OFR2_OFFSET2_7                                  0x00000080U
#define ADC_OFR2_OFFSET2_8                                  0x00000100U
#define ADC_OFR2_OFFSET2_9                                  0x00000200U
#define ADC_OFR2_OFFSET2_10                                 0x00000400U
#define ADC_OFR2_OFFSET2_11                                 0x00000800U
#define ADC_OFR2_OFFSET2_12                                 0x00001000U
#define ADC_OFR2_OFFSET2_13                                 0x00002000U
#define ADC_OFR2_OFFSET2_14                                 0x00004000U
#define ADC_OFR2_OFFSET2_15                                 0x00008000U
#define ADC_OFR2_OFFSET2_16                                 0x00010000U
#define ADC_OFR2_OFFSET2_17                                 0x00020000U
#define ADC_OFR2_OFFSET2_18                                 0x00040000U
#define ADC_OFR2_OFFSET2_19                                 0x00080000U
#define ADC_OFR2_OFFSET2_20                                 0x00100000U
#define ADC_OFR2_OFFSET2_21                                 0x00200000U
#define ADC_OFR2_OFFSET2_22                                 0x00400000U
#define ADC_OFR2_OFFSET2_23                                 0x00800000U
#define ADC_OFR2_OFFSET2_24                                 0x01000000U
#define ADC_OFR2_OFFSET2_25                                 0x02000000U
#define ADC_OFR2_OFFSET2_CH                                 0x7C000000U
#define ADC_OFR2_OFFSET2_CH_0                               0x04000000U
#define ADC_OFR2_OFFSET2_CH_1                               0x08000000U
#define ADC_OFR2_OFFSET2_CH_2                               0x10000000U
#define ADC_OFR2_OFFSET2_CH_3                               0x20000000U
#define ADC_OFR2_OFFSET2_CH_4                               0x40000000U
#define ADC_OFR2_SSATE                                      0x80000000U

/****************  Bit definition for ADC_OFR3 register  ****************/
#define ADC_OFR3_OFFSET3                                    0x03FFFFFFU
#define ADC_OFR3_OFFSET3_0                                  0x00000001U
#define ADC_OFR3_OFFSET3_1                                  0x00000002U
#define ADC_OFR3_OFFSET3_2                                  0x00000004U
#define ADC_OFR3_OFFSET3_3                                  0x00000008U
#define ADC_OFR3_OFFSET3_4                                  0x00000010U
#define ADC_OFR3_OFFSET3_5                                  0x00000020U
#define ADC_OFR3_OFFSET3_6                                  0x00000040U
#define ADC_OFR3_OFFSET3_7                                  0x00000080U
#define ADC_OFR3_OFFSET3_8                                  0x00000100U
#define ADC_OFR3_OFFSET3_9                                  0x00000200U
#define ADC_OFR3_OFFSET3_10                                 0x00000400U
#define ADC_OFR3_OFFSET3_11                                 0x00000800U
#define ADC_OFR3_OFFSET3_12                                 0x00001000U
#define ADC_OFR3_OFFSET3_13                                 0x00002000U
#define ADC_OFR3_OFFSET3_14                                 0x00004000U
#define ADC_OFR3_OFFSET3_15                                 0x00008000U
#define ADC_OFR3_OFFSET3_16                                 0x00010000U
#define ADC_OFR3_OFFSET3_17                                 0x00020000U
#define ADC_OFR3_OFFSET3_18                                 0x00040000U
#define ADC_OFR3_OFFSET3_19                                 0x00080000U
#define ADC_OFR3_OFFSET3_20                                 0x00100000U
#define ADC_OFR3_OFFSET3_21                                 0x00200000U
#define ADC_OFR3_OFFSET3_22                                 0x00400000U
#define ADC_OFR3_OFFSET3_23                                 0x00800000U
#define ADC_OFR3_OFFSET3_24                                 0x01000000U
#define ADC_OFR3_OFFSET3_25                                 0x02000000U
#define ADC_OFR3_OFFSET3_CH                                 0x7C000000U
#define ADC_OFR3_OFFSET3_CH_0                               0x04000000U
#define ADC_OFR3_OFFSET3_CH_1                               0x08000000U
#define ADC_OFR3_OFFSET3_CH_2                               0x10000000U
#define ADC_OFR3_OFFSET3_CH_3                               0x20000000U
#define ADC_OFR3_OFFSET3_CH_4                               0x40000000U
#define ADC_OFR3_SSATE                                      0x80000000U

/****************  Bit definition for ADC_OFR4 register  ****************/
#define ADC_OFR4_OFFSET4                                    0x03FFFFFFU
#define ADC_OFR4_OFFSET4_0                                  0x00000001U
#define ADC_OFR4_OFFSET4_1                                  0x00000002U
#define ADC_OFR4_OFFSET4_2                                  0x00000004U
#define ADC_OFR4_OFFSET4_3                                  0x00000008U
#define ADC_OFR4_OFFSET4_4                                  0x00000010U
#define ADC_OFR4_OFFSET4_5                                  0x00000020U
#define ADC_OFR4_OFFSET4_6                                  0x00000040U
#define ADC_OFR4_OFFSET4_7                                  0x00000080U
#define ADC_OFR4_OFFSET4_8                                  0x00000100U
#define ADC_OFR4_OFFSET4_9                                  0x00000200U
#define ADC_OFR4_OFFSET4_10                                 0x00000400U
#define ADC_OFR4_OFFSET4_11                                 0x00000800U
#define ADC_OFR4_OFFSET4_12                                 0x00001000U
#define ADC_OFR4_OFFSET4_13                                 0x00002000U
#define ADC_OFR4_OFFSET4_14                                 0x00004000U
#define ADC_OFR4_OFFSET4_15                                 0x00008000U
#define ADC_OFR4_OFFSET4_16                                 0x00010000U
#define ADC_OFR4_OFFSET4_17                                 0x00020000U
#define ADC_OFR4_OFFSET4_18                                 0x00040000U
#define ADC_OFR4_OFFSET4_19                                 0x00080000U
#define ADC_OFR4_OFFSET4_20                                 0x00100000U
#define ADC_OFR4_OFFSET4_21                                 0x00200000U
#define ADC_OFR4_OFFSET4_22                                 0x00400000U
#define ADC_OFR4_OFFSET4_23                                 0x00800000U
#define ADC_OFR4_OFFSET4_24                                 0x01000000U
#define ADC_OFR4_OFFSET4_25                                 0x02000000U
#define ADC_OFR4_OFFSET4_CH                                 0x7C000000U
#define ADC_OFR4_OFFSET4_CH_0                               0x04000000U
#define ADC_OFR4_OFFSET4_CH_1                               0x08000000U
#define ADC_OFR4_OFFSET4_CH_2                               0x10000000U
#define ADC_OFR4_OFFSET4_CH_3                               0x20000000U
#define ADC_OFR4_OFFSET4_CH_4                               0x40000000U
#define ADC_OFR4_SSATE                                      0x80000000U

/****************  Bit definition for ADC_JDR1 register  ****************/
#define ADC_JDR1_JDATA                                      0xFFFFFFFFU
#define ADC_JDR1_JDATA_0                                    0x00000001U
#define ADC_JDR1_JDATA_1                                    0x00000002U
#define ADC_JDR1_JDATA_2                                    0x00000004U
#define ADC_JDR1_JDATA_3                                    0x00000008U
#define ADC_JDR1_JDATA_4                                    0x00000010U
#define ADC_JDR1_JDATA_5                                    0x00000020U
#define ADC_JDR1_JDATA_6                                    0x00000040U
#define ADC_JDR1_JDATA_7                                    0x00000080U
#define ADC_JDR1_JDATA_8                                    0x00000100U
#define ADC_JDR1_JDATA_9                                    0x00000200U
#define ADC_JDR1_JDATA_10                                   0x00000400U
#define ADC_JDR1_JDATA_11                                   0x00000800U
#define ADC_JDR1_JDATA_12                                   0x00001000U
#define ADC_JDR1_JDATA_13                                   0x00002000U
#define ADC_JDR1_JDATA_14                                   0x00004000U
#define ADC_JDR1_JDATA_15                                   0x00008000U
#define ADC_JDR1_JDATA_16                                   0x00010000U
#define ADC_JDR1_JDATA_17                                   0x00020000U
#define ADC_JDR1_JDATA_18                                   0x00040000U
#define ADC_JDR1_JDATA_19                                   0x00080000U
#define ADC_JDR1_JDATA_20                                   0x00100000U
#define ADC_JDR1_JDATA_21                                   0x00200000U
#define ADC_JDR1_JDATA_22                                   0x00400000U
#define ADC_JDR1_JDATA_23                                   0x00800000U
#define ADC_JDR1_JDATA_24                                   0x01000000U
#define ADC_JDR1_JDATA_25                                   0x02000000U
#define ADC_JDR1_JDATA_26                                   0x04000000U
#define ADC_JDR1_JDATA_27                                   0x08000000U
#define ADC_JDR1_JDATA_28                                   0x10000000U
#define ADC_JDR1_JDATA_29                                   0x20000000U
#define ADC_JDR1_JDATA_30                                   0x40000000U
#define ADC_JDR1_JDATA_31                                   0x80000000U

/****************  Bit definition for ADC_JDR2 register  ****************/
#define ADC_JDR2_JDATA                                      0xFFFFFFFFU
#define ADC_JDR2_JDATA_0                                    0x00000001U
#define ADC_JDR2_JDATA_1                                    0x00000002U
#define ADC_JDR2_JDATA_2                                    0x00000004U
#define ADC_JDR2_JDATA_3                                    0x00000008U
#define ADC_JDR2_JDATA_4                                    0x00000010U
#define ADC_JDR2_JDATA_5                                    0x00000020U
#define ADC_JDR2_JDATA_6                                    0x00000040U
#define ADC_JDR2_JDATA_7                                    0x00000080U
#define ADC_JDR2_JDATA_8                                    0x00000100U
#define ADC_JDR2_JDATA_9                                    0x00000200U
#define ADC_JDR2_JDATA_10                                   0x00000400U
#define ADC_JDR2_JDATA_11                                   0x00000800U
#define ADC_JDR2_JDATA_12                                   0x00001000U
#define ADC_JDR2_JDATA_13                                   0x00002000U
#define ADC_JDR2_JDATA_14                                   0x00004000U
#define ADC_JDR2_JDATA_15                                   0x00008000U
#define ADC_JDR2_JDATA_16                                   0x00010000U
#define ADC_JDR2_JDATA_17                                   0x00020000U
#define ADC_JDR2_JDATA_18                                   0x00040000U
#define ADC_JDR2_JDATA_19                                   0x00080000U
#define ADC_JDR2_JDATA_20                                   0x00100000U
#define ADC_JDR2_JDATA_21                                   0x00200000U
#define ADC_JDR2_JDATA_22                                   0x00400000U
#define ADC_JDR2_JDATA_23                                   0x00800000U
#define ADC_JDR2_JDATA_24                                   0x01000000U
#define ADC_JDR2_JDATA_25                                   0x02000000U
#define ADC_JDR2_JDATA_26                                   0x04000000U
#define ADC_JDR2_JDATA_27                                   0x08000000U
#define ADC_JDR2_JDATA_28                                   0x10000000U
#define ADC_JDR2_JDATA_29                                   0x20000000U
#define ADC_JDR2_JDATA_30                                   0x40000000U
#define ADC_JDR2_JDATA_31                                   0x80000000U

/****************  Bit definition for ADC_JDR3 register  ****************/
#define ADC_JDR3_JDATA                                      0xFFFFFFFFU
#define ADC_JDR3_JDATA_0                                    0x00000001U
#define ADC_JDR3_JDATA_1                                    0x00000002U
#define ADC_JDR3_JDATA_2                                    0x00000004U
#define ADC_JDR3_JDATA_3                                    0x00000008U
#define ADC_JDR3_JDATA_4                                    0x00000010U
#define ADC_JDR3_JDATA_5                                    0x00000020U
#define ADC_JDR3_JDATA_6                                    0x00000040U
#define ADC_JDR3_JDATA_7                                    0x00000080U
#define ADC_JDR3_JDATA_8                                    0x00000100U
#define ADC_JDR3_JDATA_9                                    0x00000200U
#define ADC_JDR3_JDATA_10                                   0x00000400U
#define ADC_JDR3_JDATA_11                                   0x00000800U
#define ADC_JDR3_JDATA_12                                   0x00001000U
#define ADC_JDR3_JDATA_13                                   0x00002000U
#define ADC_JDR3_JDATA_14                                   0x00004000U
#define ADC_JDR3_JDATA_15                                   0x00008000U
#define ADC_JDR3_JDATA_16                                   0x00010000U
#define ADC_JDR3_JDATA_17                                   0x00020000U
#define ADC_JDR3_JDATA_18                                   0x00040000U
#define ADC_JDR3_JDATA_19                                   0x00080000U
#define ADC_JDR3_JDATA_20                                   0x00100000U
#define ADC_JDR3_JDATA_21                                   0x00200000U
#define ADC_JDR3_JDATA_22                                   0x00400000U
#define ADC_JDR3_JDATA_23                                   0x00800000U
#define ADC_JDR3_JDATA_24                                   0x01000000U
#define ADC_JDR3_JDATA_25                                   0x02000000U
#define ADC_JDR3_JDATA_26                                   0x04000000U
#define ADC_JDR3_JDATA_27                                   0x08000000U
#define ADC_JDR3_JDATA_28                                   0x10000000U
#define ADC_JDR3_JDATA_29                                   0x20000000U
#define ADC_JDR3_JDATA_30                                   0x40000000U
#define ADC_JDR3_JDATA_31                                   0x80000000U

/****************  Bit definition for ADC_JDR4 register  ****************/
#define ADC_JDR4_JDATA                                      0xFFFFFFFFU
#define ADC_JDR4_JDATA_0                                    0x00000001U
#define ADC_JDR4_JDATA_1                                    0x00000002U
#define ADC_JDR4_JDATA_2                                    0x00000004U
#define ADC_JDR4_JDATA_3                                    0x00000008U
#define ADC_JDR4_JDATA_4                                    0x00000010U
#define ADC_JDR4_JDATA_5                                    0x00000020U
#define ADC_JDR4_JDATA_6                                    0x00000040U
#define ADC_JDR4_JDATA_7                                    0x00000080U
#define ADC_JDR4_JDATA_8                                    0x00000100U
#define ADC_JDR4_JDATA_9                                    0x00000200U
#define ADC_JDR4_JDATA_10                                   0x00000400U
#define ADC_JDR4_JDATA_11                                   0x00000800U
#define ADC_JDR4_JDATA_12                                   0x00001000U
#define ADC_JDR4_JDATA_13                                   0x00002000U
#define ADC_JDR4_JDATA_14                                   0x00004000U
#define ADC_JDR4_JDATA_15                                   0x00008000U
#define ADC_JDR4_JDATA_16                                   0x00010000U
#define ADC_JDR4_JDATA_17                                   0x00020000U
#define ADC_JDR4_JDATA_18                                   0x00040000U
#define ADC_JDR4_JDATA_19                                   0x00080000U
#define ADC_JDR4_JDATA_20                                   0x00100000U
#define ADC_JDR4_JDATA_21                                   0x00200000U
#define ADC_JDR4_JDATA_22                                   0x00400000U
#define ADC_JDR4_JDATA_23                                   0x00800000U
#define ADC_JDR4_JDATA_24                                   0x01000000U
#define ADC_JDR4_JDATA_25                                   0x02000000U
#define ADC_JDR4_JDATA_26                                   0x04000000U
#define ADC_JDR4_JDATA_27                                   0x08000000U
#define ADC_JDR4_JDATA_28                                   0x10000000U
#define ADC_JDR4_JDATA_29                                   0x20000000U
#define ADC_JDR4_JDATA_30                                   0x40000000U
#define ADC_JDR4_JDATA_31                                   0x80000000U

/****************  Bit definition for ADC_AWD2CR register  ****************/
#define ADC_AWD2CR_AWD2CH                                   0x000FFFFFU
#define ADC_AWD2CR_AWD2CH_0                                 0x00000001U
#define ADC_AWD2CR_AWD2CH_1                                 0x00000002U
#define ADC_AWD2CR_AWD2CH_2                                 0x00000004U
#define ADC_AWD2CR_AWD2CH_3                                 0x00000008U
#define ADC_AWD2CR_AWD2CH_4                                 0x00000010U
#define ADC_AWD2CR_AWD2CH_5                                 0x00000020U
#define ADC_AWD2CR_AWD2CH_6                                 0x00000040U
#define ADC_AWD2CR_AWD2CH_7                                 0x00000080U
#define ADC_AWD2CR_AWD2CH_8                                 0x00000100U
#define ADC_AWD2CR_AWD2CH_9                                 0x00000200U
#define ADC_AWD2CR_AWD2CH_10                                0x00000400U
#define ADC_AWD2CR_AWD2CH_11                                0x00000800U
#define ADC_AWD2CR_AWD2CH_12                                0x00001000U
#define ADC_AWD2CR_AWD2CH_13                                0x00002000U
#define ADC_AWD2CR_AWD2CH_14                                0x00004000U
#define ADC_AWD2CR_AWD2CH_15                                0x00008000U
#define ADC_AWD2CR_AWD2CH_16                                0x00010000U
#define ADC_AWD2CR_AWD2CH_17                                0x00020000U
#define ADC_AWD2CR_AWD2CH_18                                0x00040000U
#define ADC_AWD2CR_AWD2CH_19                                0x00080000U

/****************  Bit definition for ADC_AWD3CR register  ****************/
#define ADC_AWD3CR_AWD3CH                                   0x000FFFFFU
#define ADC_AWD3CR_AWD3CH_0                                 0x00000001U
#define ADC_AWD3CR_AWD3CH_1                                 0x00000002U
#define ADC_AWD3CR_AWD3CH_2                                 0x00000004U
#define ADC_AWD3CR_AWD3CH_3                                 0x00000008U
#define ADC_AWD3CR_AWD3CH_4                                 0x00000010U
#define ADC_AWD3CR_AWD3CH_5                                 0x00000020U
#define ADC_AWD3CR_AWD3CH_6                                 0x00000040U
#define ADC_AWD3CR_AWD3CH_7                                 0x00000080U
#define ADC_AWD3CR_AWD3CH_8                                 0x00000100U
#define ADC_AWD3CR_AWD3CH_9                                 0x00000200U
#define ADC_AWD3CR_AWD3CH_10                                0x00000400U
#define ADC_AWD3CR_AWD3CH_11                                0x00000800U
#define ADC_AWD3CR_AWD3CH_12                                0x00001000U
#define ADC_AWD3CR_AWD3CH_13                                0x00002000U
#define ADC_AWD3CR_AWD3CH_14                                0x00004000U
#define ADC_AWD3CR_AWD3CH_15                                0x00008000U
#define ADC_AWD3CR_AWD3CH_16                                0x00010000U
#define ADC_AWD3CR_AWD3CH_17                                0x00020000U
#define ADC_AWD3CR_AWD3CH_18                                0x00040000U
#define ADC_AWD3CR_AWD3CH_19                                0x00080000U

/****************  Bit definition for ADC_DIFSEL register  ****************/
#define ADC_DIFSEL_DIFSEL                                   0x000FFFFFU
#define ADC_DIFSEL_DIFSEL_0                                 0x00000001U
#define ADC_DIFSEL_DIFSEL_1                                 0x00000002U
#define ADC_DIFSEL_DIFSEL_2                                 0x00000004U
#define ADC_DIFSEL_DIFSEL_3                                 0x00000008U
#define ADC_DIFSEL_DIFSEL_4                                 0x00000010U
#define ADC_DIFSEL_DIFSEL_5                                 0x00000020U
#define ADC_DIFSEL_DIFSEL_6                                 0x00000040U
#define ADC_DIFSEL_DIFSEL_7                                 0x00000080U
#define ADC_DIFSEL_DIFSEL_8                                 0x00000100U
#define ADC_DIFSEL_DIFSEL_9                                 0x00000200U
#define ADC_DIFSEL_DIFSEL_10                                0x00000400U
#define ADC_DIFSEL_DIFSEL_11                                0x00000800U
#define ADC_DIFSEL_DIFSEL_12                                0x00001000U
#define ADC_DIFSEL_DIFSEL_13                                0x00002000U
#define ADC_DIFSEL_DIFSEL_14                                0x00004000U
#define ADC_DIFSEL_DIFSEL_15                                0x00008000U
#define ADC_DIFSEL_DIFSEL_16                                0x00010000U
#define ADC_DIFSEL_DIFSEL_17                                0x00020000U
#define ADC_DIFSEL_DIFSEL_18                                0x00040000U
#define ADC_DIFSEL_DIFSEL_19                                0x00080000U

/****************  Bit definition for ADC_CALFACT register  ****************/
#define ADC_CALFACT_CALFACT_S                               0x000007FFU
#define ADC_CALFACT_CALFACT_S_0                             0x00000001U
#define ADC_CALFACT_CALFACT_S_1                             0x00000002U
#define ADC_CALFACT_CALFACT_S_2                             0x00000004U
#define ADC_CALFACT_CALFACT_S_3                             0x00000008U
#define ADC_CALFACT_CALFACT_S_4                             0x00000010U
#define ADC_CALFACT_CALFACT_S_5                             0x00000020U
#define ADC_CALFACT_CALFACT_S_6                             0x00000040U
#define ADC_CALFACT_CALFACT_S_7                             0x00000080U
#define ADC_CALFACT_CALFACT_S_8                             0x00000100U
#define ADC_CALFACT_CALFACT_S_9                             0x00000200U
#define ADC_CALFACT_CALFACT_S_10                            0x00000400U
#define ADC_CALFACT_CALFACT_D                               0x07FF0000U
#define ADC_CALFACT_CALFACT_D_0                             0x00010000U
#define ADC_CALFACT_CALFACT_D_1                             0x00020000U
#define ADC_CALFACT_CALFACT_D_2                             0x00040000U
#define ADC_CALFACT_CALFACT_D_3                             0x00080000U
#define ADC_CALFACT_CALFACT_D_4                             0x00100000U
#define ADC_CALFACT_CALFACT_D_5                             0x00200000U
#define ADC_CALFACT_CALFACT_D_6                             0x00400000U
#define ADC_CALFACT_CALFACT_D_7                             0x00800000U
#define ADC_CALFACT_CALFACT_D_8                             0x01000000U
#define ADC_CALFACT_CALFACT_D_9                             0x02000000U
#define ADC_CALFACT_CALFACT_D_10                            0x04000000U

/****************  Bit definition for ADC_CALFACT2 register  ****************/
#define ADC_CALFACT2_LINCALFACT                             0x3FFFFFFFU
#define ADC_CALFACT2_LINCALFACT_0                           0x00000001U
#define ADC_CALFACT2_LINCALFACT_1                           0x00000002U
#define ADC_CALFACT2_LINCALFACT_2                           0x00000004U
#define ADC_CALFACT2_LINCALFACT_3                           0x00000008U
#define ADC_CALFACT2_LINCALFACT_4                           0x00000010U
#define ADC_CALFACT2_LINCALFACT_5                           0x00000020U
#define ADC_CALFACT2_LINCALFACT_6                           0x00000040U
#define ADC_CALFACT2_LINCALFACT_7                           0x00000080U
#define ADC_CALFACT2_LINCALFACT_8                           0x00000100U
#define ADC_CALFACT2_LINCALFACT_9                           0x00000200U
#define ADC_CALFACT2_LINCALFACT_10                          0x00000400U
#define ADC_CALFACT2_LINCALFACT_11                          0x00000800U
#define ADC_CALFACT2_LINCALFACT_12                          0x00001000U
#define ADC_CALFACT2_LINCALFACT_13                          0x00002000U
#define ADC_CALFACT2_LINCALFACT_14                          0x00004000U
#define ADC_CALFACT2_LINCALFACT_15                          0x00008000U
#define ADC_CALFACT2_LINCALFACT_16                          0x00010000U
#define ADC_CALFACT2_LINCALFACT_17                          0x00020000U
#define ADC_CALFACT2_LINCALFACT_18                          0x00040000U
#define ADC_CALFACT2_LINCALFACT_19                          0x00080000U
#define ADC_CALFACT2_LINCALFACT_20                          0x00100000U
#define ADC_CALFACT2_LINCALFACT_21                          0x00200000U
#define ADC_CALFACT2_LINCALFACT_22                          0x00400000U
#define ADC_CALFACT2_LINCALFACT_23                          0x00800000U
#define ADC_CALFACT2_LINCALFACT_24                          0x01000000U
#define ADC_CALFACT2_LINCALFACT_25                          0x02000000U
#define ADC_CALFACT2_LINCALFACT_26                          0x04000000U
#define ADC_CALFACT2_LINCALFACT_27                          0x08000000U
#define ADC_CALFACT2_LINCALFACT_28                          0x10000000U
#define ADC_CALFACT2_LINCALFACT_29                          0x20000000U

/* register bank */
typedef struct {
    reg32_t CSR; 
    reg32_t RESERVED; 
    reg32_t CCR; 
    reg32_t CDR; 
    reg32_t CDR2; 
} adc_com_t;

#define ADC_CSR_ADRDY_MST                                   0x00000001U
#define ADC_CSR_EOSMP_MST                                   0x00000002U
#define ADC_CSR_EOC_MST                                     0x00000004U
#define ADC_CSR_EOS_MST                                     0x00000008U
#define ADC_CSR_OVR_MST                                     0x00000010U
#define ADC_CSR_JEOC_MST                                    0x00000020U
#define ADC_CSR_JEOS_MST                                    0x00000040U
#define ADC_CSR_AWD1_MST                                    0x00000080U
#define ADC_CSR_AWD2_MST                                    0x00000100U
#define ADC_CSR_AWD3_MST                                    0x00000200U
#define ADC_CSR_JQOVF_MST                                   0x00000400U
#define ADC_CSR_ADRDY_SLV                                   0x00010000U
#define ADC_CSR_EOSMP_SLV                                   0x00020000U
#define ADC_CSR_EOC_SLV                                     0x00040000U
#define ADC_CSR_EOS_SLV                                     0x00080000U
#define ADC_CSR_OVR_SLV                                     0x00100000U
#define ADC_CSR_JEOC_SLV                                    0x00200000U
#define ADC_CSR_JEOS_SLV                                    0x00400000U
#define ADC_CSR_AWD1_SLV                                    0x00800000U
#define ADC_CSR_AWD2_SLV                                    0x01000000U
#define ADC_CSR_AWD3_SLV                                    0x02000000U
#define ADC_CSR_JQOVF_SLV                                   0x04000000U

/****************  Bit definition for ADC_CCR register  ****************/
#define ADC_CCR_DUAL                                        0x0000001FU
#define ADC_CCR_DUAL_0                                      0x00000001U
#define ADC_CCR_DUAL_1                                      0x00000002U
#define ADC_CCR_DUAL_2                                      0x00000004U
#define ADC_CCR_DUAL_3                                      0x00000008U
#define ADC_CCR_DUAL_4                                      0x00000010U
#define ADC_CCR_DELAY                                       0x00000F00U
#define ADC_CCR_DELAY_0                                     0x00000100U
#define ADC_CCR_DELAY_1                                     0x00000200U
#define ADC_CCR_DELAY_2                                     0x00000400U
#define ADC_CCR_DELAY_3                                     0x00000800U
#define ADC_CCR_DAMDF                                       0x0000C000U
#define ADC_CCR_DAMDF_0                                     0x00004000U
#define ADC_CCR_DAMDF_1                                     0x00008000U
#define ADC_CCR_CKMODE                                      0x00030000U
#define ADC_CCR_CKMODE_0                                    0x00010000U
#define ADC_CCR_CKMODE_1                                    0x00020000U
#define ADC_CCR_PRESC                                       0x003C0000U
#define ADC_CCR_PRESC_0                                     0x00040000U
#define ADC_CCR_PRESC_1                                     0x00080000U
#define ADC_CCR_PRESC_2                                     0x00100000U
#define ADC_CCR_PRESC_3                                     0x00200000U
#define ADC_CCR_VREFEN                                      0x00400000U
#define ADC_CCR_TSEN                                        0x00800000U
#define ADC_CCR_VBATEN                                      0x01000000U

/****************  Bit definition for ADC_CDR register  ***************/
#define ADC_CDR_RDATA_MST                                   0x0000FFFFU
#define ADC_CDR_RDATA_SLV                                   0xFFFF0000U

/****************  Bit definition for ADC_CDR2 register  **************/
#define ADC_CDR2_RDATA_ALT                                  0xFFFFFFFFU
#endif /* _STM32H743_ADC_H */

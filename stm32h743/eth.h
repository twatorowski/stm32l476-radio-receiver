/**
 * @file eth.h
 *
 * @date 2021-01-19
 * @author twatorowski
 *
 * @brief STM32H743: ETH
 */


#ifndef STM32H743_ETH_H
#define STM32H743_ETH_H

#include "stm32h743/stm32h743.h"

/* base addresses */
#define ETH_DMA_BASE                                        0x40029000U
#define ETH_MTL_BASE                                        0x40028c00U
#define ETH_MAC_BASE                                        0x40028000U

/* instances */
#define ETH_DMA                                             ((eth_dma_t *)ETH_DMA_BASE)
#define ETH_MTL                                             ((eth_mil_t *)ETH_MTL_BASE)
#define ETH_MAC                                             ((eth_mac_t *)ETH_MAC_BASE)


/* register bank */
typedef struct {
    reg32_t DMAMR;
    reg32_t DMASBMR;
    reg32_t DMAISR;
    reg32_t DMADSR;
    reg8_t RESERVED0[240];
    reg32_t DMACCR;
    reg32_t DMACTXCR;
    reg32_t DMACRXCR;
    reg8_t RESERVED1[8];
    reg32_t DMACTXDLAR;
    reg8_t RESERVED2[4];
    reg32_t DMACRXDLAR;
    reg32_t DMACTXDTPR;
    reg8_t RESERVED3[4];
    reg32_t DMACRXDTPR;
    reg32_t DMACTXRLR;
    reg32_t DMACRXRLR;
    reg32_t DMACIER;
    reg32_t DMACRXIWTR;
    reg8_t RESERVED4[8];
    reg32_t DMACCATxDR;
    reg8_t RESERVED5[4];
    reg32_t DMACCARXDR;
    reg8_t RESERVED6[4];
    reg32_t DMACCATXBR;
    reg8_t RESERVED7[4];
    reg32_t DMACCARXBR;
    reg32_t DMACSR;
    reg8_t RESERVED8[8];
    reg32_t DMACMFCR;
} eth_dma_t;

/****************** bit definitions for DMAMR register ******************/
#define ETH_DMAMR_SWR                                       0x00000001
#define ETH_DMAMR_DA                                        0x00000002
#define ETH_DMAMR_TXPR                                      0x00000800
#define ETH_DMAMR_PR                                        0x00007000
#define ETH_DMAMR_INTM                                      0x00010000

/***************** bit definitions for DMASBMR register *****************/
#define ETH_DMASBMR_FB                                      0x00000001
#define ETH_DMASBMR_AAL                                     0x00001000
#define ETH_DMASBMR_MB                                      0x00004000
#define ETH_DMASBMR_RB                                      0x00008000

/***************** bit definitions for DMAISR register ******************/
#define ETH_DMAISR_DC0IS                                    0x00000001
#define ETH_DMAISR_MTLIS                                    0x00010000
#define ETH_DMAISR_MACIS                                    0x00020000

/***************** bit definitions for DMADSR register ******************/
#define ETH_DMADSR_AXWHSTS                                  0x00000001
#define ETH_DMADSR_RPS0                                     0x00000f00
#define ETH_DMADSR_TPS0                                     0x0000f000

/***************** bit definitions for DMACCR register ******************/
#define ETH_DMACCR_MSS                                      0x00003fff
#define ETH_DMACCR_PBLX8                                    0x00010000
#define ETH_DMACCR_DSL                                      0x001c0000

/**************** bit definitions for DMACTxCR register *****************/
#define ETH_DMACTXCR_ST                                     0x00000001
#define ETH_DMACTXCR_OSF                                    0x00000010
#define ETH_DMACTXCR_TSE                                    0x00001000
#define ETH_DMACTXCR_TXPBL                                  0x003f0000

/**************** bit definitions for DMACRxCR register *****************/
#define ETH_DMACRXCR_SR                                     0x00000001
#define ETH_DMACRXCR_RBSZ                                   0x00007ffe
#define ETH_DMACRXCR_RXPBL                                  0x003f0000
#define ETH_DMACRXCR_RPF                                    0x80000000

/*************** bit definitions for DMACTxDLAR register ****************/
#define ETH_DMACTXDLAR_TDESLA                               0xfffffffc

/*************** bit definitions for DMACRxDLAR register ****************/
#define ETH_DMACRXDLAR_RDESLA                               0xfffffffc

/*************** bit definitions for DMACTxDTPR register ****************/
#define ETH_DMACTXDTPR_TDT                                  0xfffffffc

/*************** bit definitions for DMACRxDTPR register ****************/
#define ETH_DMACRXDTPR_RDT                                  0xfffffffc

/**************** bit definitions for DMACTxRLR register ****************/
#define ETH_DMACTXRLR_TDRL                                  0x000003ff

/**************** bit definitions for DMACRxRLR register ****************/
#define ETH_DMACRXRLR_RDRL                                  0x000003ff

/***************** bit definitions for DMACIER register *****************/
#define ETH_DMACIER_TIE                                     0x00000001
#define ETH_DMACIER_TXSE                                    0x00000002
#define ETH_DMACIER_TBUE                                    0x00000004
#define ETH_DMACIER_RIE                                     0x00000040
#define ETH_DMACIER_RBUE                                    0x00000080
#define ETH_DMACIER_RSE                                     0x00000100
#define ETH_DMACIER_RWTE                                    0x00000200
#define ETH_DMACIER_ETIE                                    0x00000400
#define ETH_DMACIER_ERIE                                    0x00000800
#define ETH_DMACIER_FBEE                                    0x00001000
#define ETH_DMACIER_CDEE                                    0x00002000
#define ETH_DMACIER_AIE                                     0x00004000
#define ETH_DMACIER_NIE                                     0x00008000

/*************** bit definitions for DMACRxIWTR register ****************/
#define ETH_DMACRXIWTR_RWT                                  0x000000ff

/*************** bit definitions for DMACCATxDR register ****************/
#define ETH_DMACCATXDR_CURTDESAPTR                          0xffffffff

/*************** bit definitions for DMACCARxDR register ****************/
#define ETH_DMACCARXDR_CURRDESAPTR                          0xffffffff

/*************** bit definitions for DMACCATxBR register ****************/
#define ETH_DMACCATXBR_CURTBUFAPTR                          0xffffffff

/*************** bit definitions for DMACCARxBR register ****************/
#define ETH_DMACCARXBR_CURRBUFAPTR                          0xffffffff

/***************** bit definitions for DMACSR register ******************/
#define ETH_DMACSR_TI                                       0x00000001
#define ETH_DMACSR_TPS                                      0x00000002
#define ETH_DMACSR_TBU                                      0x00000004
#define ETH_DMACSR_RI                                       0x00000040
#define ETH_DMACSR_RBU                                      0x00000080
#define ETH_DMACSR_RPS                                      0x00000100
#define ETH_DMACSR_RWT                                      0x00000200
#define ETH_DMACSR_ET                                       0x00000400
#define ETH_DMACSR_ER                                       0x00000800
#define ETH_DMACSR_FBE                                      0x00001000
#define ETH_DMACSR_CDE                                      0x00002000
#define ETH_DMACSR_AIS                                      0x00004000
#define ETH_DMACSR_NIS                                      0x00008000
#define ETH_DMACSR_TEB                                      0x00070000
#define ETH_DMACSR_REB                                      0x00380000

/**************** bit definitions for DMACMFCR register *****************/
#define ETH_DMACMFCR_MFC                                    0x000007ff
#define ETH_DMACMFCR_MFCO                                   0x00008000

/* register bank */
typedef struct {
    reg32_t MTLOMR;
    reg8_t RESERVED0[28];
    reg32_t MTLISR;
    reg8_t RESERVED1[220];
    reg32_t MTLTXQOMR;
    reg32_t MTLTXQUR;
    reg32_t MTLTXQDR;
    reg8_t RESERVED2[32];
    reg32_t MTLQICSR;
    reg32_t MTLRXQOMR;
    reg32_t MTLRXQMPOCR;
    reg32_t MTLRXQDR;
} eth_mil_t;

/***************** bit definitions for MTLOMR register ******************/
#define ETH_MTLOMR_DTXSTS                                   0x00000002
#define ETH_MTLOMR_CNTPRST                                  0x00000100
#define ETH_MTLOMR_CNTCLR                                   0x00000200

/***************** bit definitions for MTLISR register ******************/
#define ETH_MTLISR_Q0IS                                     0x00000001

/**************** bit definitions for MTLTXQOMR register ****************/
#define ETH_MTLTXQOMR_FTQ                                   0x00000001
#define ETH_MTLTXQOMR_TSF                                   0x00000002
#define ETH_MTLTXQOMR_TXQEN                                 0x0000000c
#define ETH_MTLTXQOMR_TTC                                   0x00000070
#define ETH_MTLTXQOMR_TQS                                   0x00070000

/**************** bit definitions for MTLTXQUR register *****************/
#define ETH_MTLTXQUR_UFFRMCNT                               0x000007ff
#define ETH_MTLTXQUR_UFCNTOVF                               0x00000800

/**************** bit definitions for MTLTXQDR register *****************/
#define ETH_MTLTXQDR_TXQPAUSED                              0x00000001
#define ETH_MTLTXQDR_TRCSTS                                 0x00000006
#define ETH_MTLTXQDR_TWCSTS                                 0x00000008
#define ETH_MTLTXQDR_TXQSTS                                 0x00000010
#define ETH_MTLTXQDR_TXSTSFSTS                              0x00000020
#define ETH_MTLTXQDR_PTXQ                                   0x00070000
#define ETH_MTLTXQDR_STXSTSF                                0x00700000

/**************** bit definitions for MTLQICSR register *****************/
#define ETH_MTLQICSR_TXUNFIS                                0x00000001
#define ETH_MTLQICSR_TXUIE                                  0x00000100
#define ETH_MTLQICSR_RXOVFIS                                0x00010000
#define ETH_MTLQICSR_RXOIE                                  0x01000000

/**************** bit definitions for MTLRXQOMR register ****************/
#define ETH_MTLRXQOMR_RTC                                   0x00000003
#define ETH_MTLRXQOMR_FUP                                   0x00000008
#define ETH_MTLRXQOMR_FEP                                   0x00000010
#define ETH_MTLRXQOMR_RSF                                   0x00000020
#define ETH_MTLRXQOMR_DIS_TCP_EF                            0x00000040
#define ETH_MTLRXQOMR_EHFC                                  0x00000080
#define ETH_MTLRXQOMR_RFA                                   0x00000700
#define ETH_MTLRXQOMR_RFD                                   0x0001c000
#define ETH_MTLRXQOMR_RQS                                   0x00700000

/*************** bit definitions for MTLRXQMPOCR register ***************/
#define ETH_MTLRXQMPOCR_OVFPKTCNT                           0x000007ff
#define ETH_MTLRXQMPOCR_OVFCNTOVF                           0x00000800
#define ETH_MTLRXQMPOCR_MISPKTCNT                           0x07ff0000
#define ETH_MTLRXQMPOCR_MISCNTOVF                           0x08000000

/**************** bit definitions for MTLRXQDR register *****************/
#define ETH_MTLRXQDR_RWCSTS                                 0x00000001
#define ETH_MTLRXQDR_RRCSTS                                 0x00000006
#define ETH_MTLRXQDR_RXQSTS                                 0x00000030
#define ETH_MTLRXQDR_PRXQ                                   0x3fff0000


/* register bank */
typedef struct {
    reg32_t MACCR;
    reg32_t MACECR;
    reg32_t MACPFR;
    reg32_t MACWTR;
    reg32_t MACHT0R;
    reg32_t MACHT1R;
    reg8_t RESERVED0[56];
    reg32_t MACVTR;
    reg8_t RESERVED1[4];
    reg32_t MACVHTR;
    reg8_t RESERVED2[4];
    reg32_t MACVIR;
    reg32_t MACIVIR;
    reg8_t RESERVED3[8];
    reg32_t MACQTFCR;
    reg8_t RESERVED4[28];
    reg32_t MACRFCR;
    reg8_t RESERVED5[28];
    reg32_t MACISR;
    reg32_t MACIER;
    reg32_t MACRXTXSR;
    reg8_t RESERVED6[4];
    reg32_t MACPCSR;
    reg32_t MACRWKPFR;
    reg8_t RESERVED7[8];
    reg32_t MACLCSR;
    reg32_t MACLTCR;
    reg32_t MACLETR;
    reg32_t MAC1USTCR;
    reg8_t RESERVED8[48];
    reg32_t MACVR;
    reg32_t MACDR;
    reg8_t RESERVED9[8];
    reg32_t MACHWF1R;
    reg32_t MACHWF2R;
    reg8_t RESERVED10[216];
    reg32_t MACMDIOAR;
    reg32_t MACMDIODR;
    reg8_t RESERVED11[248];
    reg32_t MACA0HR;
    reg32_t MACA0LR;
    reg32_t MACA1HR;
    reg32_t MACA1LR;
    reg32_t MACA2HR;
    reg32_t MACA2LR;
    reg32_t MACA3HR;
    reg32_t MACA3LR;
    reg8_t RESERVED12[992];
    reg32_t MMCCR;
    reg32_t MMCRIR;
    reg32_t MMCTIR;
    reg32_t MMCRIMR;
    reg32_t MMCTIMR;
    reg8_t RESERVED13[56];
    reg32_t MMCTSCGPR;
    reg32_t MMCTMCGPR;
    reg8_t RESERVED14[20];
    reg32_t MMCTPCGR;
    reg8_t RESERVED15[40];
    reg32_t MMCRCRCEPR;
    reg32_t MMCRAEPR;
    reg8_t RESERVED16[40];
    reg32_t MMCRUPGR;
    reg8_t RESERVED17[36];
    reg32_t MMCTLPIMSTR;
    reg32_t MMCTLPITCR;
    reg32_t MMCRLPIMSTR;
    reg32_t MMCRLPITCR;
    reg8_t RESERVED18[260];
    reg32_t MACL3L4C0R;
    reg32_t MACL4A0R;
    reg8_t RESERVED19[8];
    reg32_t MACL3A00R;
    reg32_t MACL3A10R;
    reg32_t MACL3A20;
    reg32_t MACL3A30;
    reg8_t RESERVED20[16];
    reg32_t MACL3L4C1R;
    reg32_t MACL4A1R;
    reg8_t RESERVED21[8];
    reg32_t MACL3A01R;
    reg32_t MACL3A11R;
    reg32_t MACL3A21R;
    reg32_t MACL3A31R;
    reg8_t RESERVED22[400];
    reg32_t MACARPAR;
    reg8_t RESERVED23[28];
    reg32_t MACTSCR;
    reg32_t MACSSIR;
    reg32_t MACSTSR;
    reg32_t MACSTNR;
    reg32_t MACSTSUR;
    reg32_t MACSTNUR;
    reg32_t MACTSAR;
    reg8_t RESERVED24[4];
    reg32_t MACTSSR;
    reg8_t RESERVED25[12];
    reg32_t MACTTSSNR;
    reg32_t MACTTSSSR;
    reg8_t RESERVED26[8];
    reg32_t MACACR;
    reg8_t RESERVED27[4];
    reg32_t MACATSNR;
    reg32_t MACATSSR;
    reg32_t MACTSIACR;
    reg32_t MACTSEACR;
    reg32_t MACTSICNR;
    reg32_t MACTSECNR;
    reg8_t RESERVED28[16];
    reg32_t MACPPSCR;
    reg8_t RESERVED29[12];
    reg32_t MACPPSTTSR;
    reg32_t MACPPSTTNR;
    reg32_t MACPPSIR;
    reg32_t MACPPSWR;
    reg8_t RESERVED30[48];
    reg32_t MACPOCR;
    reg32_t MACSPI0R;
    reg32_t MACSPI1R;
    reg32_t MACSPI2R;
    reg32_t MACLMIR;
} eth_mac_t;

/****************** bit definitions for MACCR register ******************/
#define ETH_MACCR_RE                                        0x00000001
#define ETH_MACCR_TE                                        0x00000002
#define ETH_MACCR_PRELEN                                    0x0000000c
#define ETH_MACCR_DC                                        0x00000010
#define ETH_MACCR_BL                                        0x00000060
#define ETH_MACCR_DR                                        0x00000100
#define ETH_MACCR_DCRS                                      0x00000200
#define ETH_MACCR_DO                                        0x00000400
#define ETH_MACCR_ECRSFD                                    0x00000800
#define ETH_MACCR_LM                                        0x00001000
#define ETH_MACCR_DM                                        0x00002000
#define ETH_MACCR_FES                                       0x00004000
#define ETH_MACCR_JE                                        0x00010000
#define ETH_MACCR_JD                                        0x00020000
#define ETH_MACCR_WD                                        0x00080000
#define ETH_MACCR_ACS                                       0x00100000
#define ETH_MACCR_CST                                       0x00200000
#define ETH_MACCR_S2KP                                      0x00400000
#define ETH_MACCR_GPSLCE                                    0x00800000
#define ETH_MACCR_IPG                                       0x07000000
#define ETH_MACCR_IPC                                       0x08000000
#define ETH_MACCR_SARC                                      0x70000000
#define ETH_MACCR_ARPEN                                     0x80000000

/***************** bit definitions for MACECR register ******************/
#define ETH_MACECR_GPSL                                     0x00003fff
#define ETH_MACECR_DCRCC                                    0x00010000
#define ETH_MACECR_SPEN                                     0x00020000
#define ETH_MACECR_USP                                      0x00040000
#define ETH_MACECR_EIPGEN                                   0x01000000
#define ETH_MACECR_EIPG                                     0x3e000000

/***************** bit definitions for MACPFR register ******************/
#define ETH_MACPFR_PR                                       0x00000001
#define ETH_MACPFR_HUC                                      0x00000002
#define ETH_MACPFR_HMC                                      0x00000004
#define ETH_MACPFR_DAIF                                     0x00000008
#define ETH_MACPFR_PM                                       0x00000010
#define ETH_MACPFR_DBF                                      0x00000020
#define ETH_MACPFR_PCF                                      0x000000c0
#define ETH_MACPFR_SAIF                                     0x00000100
#define ETH_MACPFR_SAF                                      0x00000200
#define ETH_MACPFR_HPF                                      0x00000400
#define ETH_MACPFR_VTFE                                     0x00010000
#define ETH_MACPFR_IPFE                                     0x00100000
#define ETH_MACPFR_DNTU                                     0x00200000
#define ETH_MACPFR_RA                                       0x80000000

/***************** bit definitions for MACWTR register ******************/
#define ETH_MACWTR_WTO                                      0x0000000f
#define ETH_MACWTR_PWE                                      0x00000100

/***************** bit definitions for MACHT0R register *****************/
#define ETH_MACHT0R_HT31T0                                  0xffffffff

/***************** bit definitions for MACHT1R register *****************/
#define ETH_MACHT1R_HT63T32                                 0xffffffff

/***************** bit definitions for MACVTR register ******************/
#define ETH_MACVTR_VL                                       0x0000ffff
#define ETH_MACVTR_ETV                                      0x00010000
#define ETH_MACVTR_VTIM                                     0x00020000
#define ETH_MACVTR_ESVL                                     0x00040000
#define ETH_MACVTR_ERSVLM                                   0x00080000
#define ETH_MACVTR_DOVLTC                                   0x00100000
#define ETH_MACVTR_EVLS                                     0x00600000
#define ETH_MACVTR_EVLRXS                                   0x01000000
#define ETH_MACVTR_VTHM                                     0x02000000
#define ETH_MACVTR_EDVLP                                    0x04000000
#define ETH_MACVTR_ERIVLT                                   0x08000000
#define ETH_MACVTR_EIVLS                                    0x30000000
#define ETH_MACVTR_EIVLRXS                                  0x80000000

/***************** bit definitions for MACVHTR register *****************/
#define ETH_MACVHTR_VLHT                                    0x0000ffff

/***************** bit definitions for MACVIR register ******************/
#define ETH_MACVIR_VLT                                      0x0000ffff
#define ETH_MACVIR_VLC                                      0x00030000
#define ETH_MACVIR_VLP                                      0x00040000
#define ETH_MACVIR_CSVL                                     0x00080000
#define ETH_MACVIR_VLTI                                     0x00100000

/***************** bit definitions for MACIVIR register *****************/
#define ETH_MACIVIR_VLT                                     0x0000ffff
#define ETH_MACIVIR_VLC                                     0x00030000
#define ETH_MACIVIR_VLP                                     0x00040000
#define ETH_MACIVIR_CSVL                                    0x00080000
#define ETH_MACIVIR_VLTI                                    0x00100000

/**************** bit definitions for MACQTxFCR register ****************/
#define ETH_MACQTFCR_FCB_BPA                                0x00000001
#define ETH_MACQTFCR_TFE                                    0x00000002
#define ETH_MACQTFCR_PLT                                    0x00000070
#define ETH_MACQTFCR_DZPQ                                   0x00000080
#define ETH_MACQTFCR_PT                                     0xffff0000

/**************** bit definitions for MACRxFCR register *****************/
#define ETH_MACRFCR_RFE                                     0x00000001
#define ETH_MACRFCR_UP                                      0x00000002

/***************** bit definitions for MACISR register ******************/
#define ETH_MACISR_PHYIS                                    0x00000008
#define ETH_MACISR_PMTIS                                    0x00000010
#define ETH_MACISR_LPIIS                                    0x00000020
#define ETH_MACISR_MMCIS                                    0x00000100
#define ETH_MACISR_MMCRXIS                                  0x00000200
#define ETH_MACISR_MMCTXIS                                  0x00000400
#define ETH_MACISR_TSIS                                     0x00001000
#define ETH_MACISR_TXSTSIS                                  0x00002000
#define ETH_MACISR_RXSTSIS                                  0x00004000

/***************** bit definitions for MACIER register ******************/
#define ETH_MACIER_PHYIE                                    0x00000008
#define ETH_MACIER_PMTIE                                    0x00000010
#define ETH_MACIER_LPIIE                                    0x00000020
#define ETH_MACIER_TSIE                                     0x00001000
#define ETH_MACIER_TXSTSIE                                  0x00002000
#define ETH_MACIER_RXSTSIE                                  0x00004000

/**************** bit definitions for MACRxTxSR register ****************/
#define ETH_MACRXTXSR_TJT                                   0x00000001
#define ETH_MACRXTXSR_NCARR                                 0x00000002
#define ETH_MACRXTXSR_LCARR                                 0x00000004
#define ETH_MACRXTXSR_EXDEF                                 0x00000008
#define ETH_MACRXTXSR_LCOL                                  0x00000010
#define ETH_MACRXTXSR_EXCOL                                 0x00000020
#define ETH_MACRXTXSR_RWT                                   0x00000100

/***************** bit definitions for MACPCSR register *****************/
#define ETH_MACPCSR_PWRDWN                                  0x00000001
#define ETH_MACPCSR_MGKPKTEN                                0x00000002
#define ETH_MACPCSR_RWKPKTEN                                0x00000004
#define ETH_MACPCSR_MGKPRCVD                                0x00000020
#define ETH_MACPCSR_RWKPRCVD                                0x00000040
#define ETH_MACPCSR_GLBLUCAST                               0x00000200
#define ETH_MACPCSR_RWKPFE                                  0x00000400
#define ETH_MACPCSR_RWKPTR                                  0x1f000000
#define ETH_MACPCSR_RWKFILTRST                              0x80000000

/**************** bit definitions for MACRWKPFR register ****************/
#define ETH_MACRWKPFR_MACRWKPFR                             0xffffffff

/***************** bit definitions for MACLCSR register *****************/
#define ETH_MACLCSR_TLPIEN                                  0x00000001
#define ETH_MACLCSR_TLPIEX                                  0x00000002
#define ETH_MACLCSR_RLPIEN                                  0x00000004
#define ETH_MACLCSR_RLPIEX                                  0x00000008
#define ETH_MACLCSR_TLPIST                                  0x00000100
#define ETH_MACLCSR_RLPIST                                  0x00000200
#define ETH_MACLCSR_LPIEN                                   0x00010000
#define ETH_MACLCSR_PLS                                     0x00020000
#define ETH_MACLCSR_PLSEN                                   0x00040000
#define ETH_MACLCSR_LPITXA                                  0x00080000
#define ETH_MACLCSR_LPITE                                   0x00100000

/***************** bit definitions for MACLTCR register *****************/
#define ETH_MACLTCR_TWT                                     0x0000ffff
#define ETH_MACLTCR_LST                                     0x03ff0000

/***************** bit definitions for MACLETR register *****************/
#define ETH_MACLETR_LPIET                                   0x0001ffff

/**************** bit definitions for MAC1USTCR register ****************/
#define ETH_MAC1USTCR_TIC_1US_CNTR                          0x00000fff

/****************** bit definitions for MACVR register ******************/
#define ETH_MACVR_SNPSVER                                   0x000000ff
#define ETH_MACVR_USERVER                                   0x0000ff00

/****************** bit definitions for MACDR register ******************/
#define ETH_MACDR_RPESTS                                    0x00000001
#define ETH_MACDR_RFCFCSTS                                  0x00000006
#define ETH_MACDR_TPESTS                                    0x00010000
#define ETH_MACDR_TFCSTS                                    0x00060000

/**************** bit definitions for MACHWF1R register *****************/
#define ETH_MACHWF1R_RXFIFOSIZE                             0x0000001f
#define ETH_MACHWF1R_TXFIFOSIZE                             0x000007c0
#define ETH_MACHWF1R_OSTEN                                  0x00000800
#define ETH_MACHWF1R_PTOEN                                  0x00001000
#define ETH_MACHWF1R_ADVTHWORD                              0x00002000
#define ETH_MACHWF1R_ADDR64                                 0x0000c000
#define ETH_MACHWF1R_DCBEN                                  0x00010000
#define ETH_MACHWF1R_SPHEN                                  0x00020000
#define ETH_MACHWF1R_TSOEN                                  0x00040000
#define ETH_MACHWF1R_DBGMEMA                                0x00080000
#define ETH_MACHWF1R_AVSEL                                  0x00100000
#define ETH_MACHWF1R_HASHTBLSZ                              0x03000000
#define ETH_MACHWF1R_L3L4FNUM                               0x78000000

/**************** bit definitions for MACHWF2R register *****************/
#define ETH_MACHWF2R_RXQCNT                                 0x0000000f
#define ETH_MACHWF2R_TXQCNT                                 0x000003c0
#define ETH_MACHWF2R_RXCHCNT                                0x0000f000
#define ETH_MACHWF2R_TXCHCNT                                0x003c0000
#define ETH_MACHWF2R_PPSOUTNUM                              0x07000000
#define ETH_MACHWF2R_AUXSNAPNUM                             0x70000000

/**************** bit definitions for MACMDIOAR register ****************/
#define ETH_MACMDIOAR_MB                                    0x00000001
#define ETH_MACMDIOAR_C45E                                  0x00000002
#define ETH_MACMDIOAR_GOC                                   0x0000000c
#define ETH_MACMDIOAR_SKAP                                  0x00000010
#define ETH_MACMDIOAR_CR                                    0x00000f00
#define ETH_MACMDIOAR_NTC                                   0x00007000
#define ETH_MACMDIOAR_RDA                                   0x001f0000
#define ETH_MACMDIOAR_PA                                    0x03e00000
#define ETH_MACMDIOAR_BTB                                   0x04000000
#define ETH_MACMDIOAR_PSE                                   0x08000000

/**************** bit definitions for MACMDIODR register ****************/
#define ETH_MACMDIODR_MD                                    0x0000ffff
#define ETH_MACMDIODR_RA                                    0xffff0000

/***************** bit definitions for MACA0HR register *****************/
#define ETH_MACA0HR_ADDRHI                                  0x0000ffff
#define ETH_MACA0HR_AE                                      0x80000000

/***************** bit definitions for MACA0LR register *****************/
#define ETH_MACA0LR_ADDRLO                                  0xffffffff

/***************** bit definitions for MACA1HR register *****************/
#define ETH_MACA1HR_ADDRHI                                  0x0000ffff
#define ETH_MACA1HR_MBC                                     0x3f000000
#define ETH_MACA1HR_SA                                      0x40000000
#define ETH_MACA1HR_AE                                      0x80000000

/***************** bit definitions for MACA1LR register *****************/
#define ETH_MACA1LR_ADDRLO                                  0xffffffff

/***************** bit definitions for MACA2HR register *****************/
#define ETH_MACA2HR_ADDRHI                                  0x0000ffff
#define ETH_MACA2HR_MBC                                     0x3f000000
#define ETH_MACA2HR_SA                                      0x40000000
#define ETH_MACA2HR_AE                                      0x80000000

/***************** bit definitions for MACA2LR register *****************/
#define ETH_MACA2LR_ADDRLO                                  0xffffffff

/***************** bit definitions for MACA3HR register *****************/
#define ETH_MACA3HR_ADDRHI                                  0x0000ffff
#define ETH_MACA3HR_MBC                                     0x3f000000
#define ETH_MACA3HR_SA                                      0x40000000
#define ETH_MACA3HR_AE                                      0x80000000

/***************** bit definitions for MACA3LR register *****************/
#define ETH_MACA3LR_ADDRLO                                  0xffffffff

/*************** bit definitions for MMCCR register ***************/
#define ETH_MMCCR_CNTRST                                    0x00000001
#define ETH_MMCCR_CNTSTOPRO                                 0x00000002
#define ETH_MMCCR_RSTONRD                                   0x00000004
#define ETH_MMCCR_CNTFREEZ                                  0x00000008
#define ETH_MMCCR_CNTPRST                                   0x00000010
#define ETH_MMCCR_CNTPRSTLVL                                0x00000020
#define ETH_MMCCR_UCDBC                                     0x00000100

/************ bit definitions for MMCRIR register *************/
#define ETH_MMCRIR_RXCRCERPIS                               0x00000020
#define ETH_MMCRIR_RXALGNERPIS                              0x00000040
#define ETH_MMCRIR_RXUCGPIS                                 0x00020000
#define ETH_MMCRIR_RXLPIUSCIS                               0x04000000
#define ETH_MMCRIR_RXLPITRCIS                               0x08000000

/************ bit definitions for MMCTIR register *************/
#define ETH_MMCTIR_TXSCOLGPIS                               0x00004000
#define ETH_MMCTIR_TXMCOLGPIS                               0x00008000
#define ETH_MMCTIR_TXGPKTIS                                 0x00200000
#define ETH_MMCTIR_TXLPIUSCIS                               0x04000000
#define ETH_MMCTIR_TXLPITRCIS                               0x08000000

/********** bit definitions for MMCRIMR register **********/
#define ETH_MMCRIMR_RXCRCERPIM                              0x00000020
#define ETH_MMCRIMR_RXALGNERPIM                             0x00000040
#define ETH_MMCRIMR_RXUCGPIM                                0x00020000
#define ETH_MMCRIMR_RXLPIUSCIM                              0x04000000
#define ETH_MMCRIMR_RXLPITRCIM                              0x08000000

/********** bit definitions for MMCTIMR register **********/
#define ETH_MMCTIMR_TXSCOLGPIM                              0x00004000
#define ETH_MMCTIMR_TXMCOLGPIM                              0x00008000
#define ETH_MMCTIMR_TXGPKTIM                                0x00200000
#define ETH_MMCTIMR_TXLPIUSCIM                              0x04000000
#define ETH_MMCTIMR_TXLPITRCIM                              0x08000000

/**** bit definitions for MMCTSCGPR register *****/
#define ETH_MMCTSCGPR_TXSNGLCOLG                            0xffffffff

/*** bit definitions for MMCTMCGPR register ****/
#define ETH_MMCTMCGPR_TXMULTCOLG                            0xffffffff

/********** bit definitions for MMCTPCGR register ***********/
#define ETH_MMCTPCGR_TXPKTG                                 0xffffffff

/********** bit definitions for MMCRCRCEPR register ***********/
#define ETH_MMCRCRCEPR_RXCRCERR                             0xffffffff

/******* bit definitions for MMCRAEPR register ********/
#define ETH_MMCRAEPR_RXALGNERR                              0xffffffff

/********* bit definitions for MMCRUPGR register *********/
#define ETH_MMCRUPGR_RXUCASTG                               0xffffffff

/************ bit definitions for MMCTLPIMSTR register *************/
#define ETH_MMCTLPIMSTR_TXLPIUSC                            0xffffffff

/************ bit definitions for MMCTLPITCR register *************/
#define ETH_MMCTLPITCR_TXLPITRC                             0xffffffff

/************ bit definitions for MMCRLPIMSTR register *************/
#define ETH_MMCRLPIMSTR_RXLPIUSC                            0xffffffff

/************ bit definitions for MMCRLPITCR register *************/
#define ETH_MMCRLPITCR_RXLPITRC                             0xffffffff

/*************** bit definitions for MACL3L4C0R register ****************/
#define ETH_MACL3L4C0R_L3PEN0                               0x00000001
#define ETH_MACL3L4C0R_L3SAM0                               0x00000004
#define ETH_MACL3L4C0R_L3SAIM0                              0x00000008
#define ETH_MACL3L4C0R_L3DAM0                               0x00000010
#define ETH_MACL3L4C0R_L3DAIM0                              0x00000020
#define ETH_MACL3L4C0R_L3HSBM0                              0x000007c0
#define ETH_MACL3L4C0R_L3HDBM0                              0x0000f800
#define ETH_MACL3L4C0R_L4PEN0                               0x00010000
#define ETH_MACL3L4C0R_L4SPM0                               0x00040000
#define ETH_MACL3L4C0R_L4SPIM0                              0x00080000
#define ETH_MACL3L4C0R_L4DPM0                               0x00100000
#define ETH_MACL3L4C0R_L4DPIM0                              0x00200000

/**************** bit definitions for MACL4A0R register *****************/
#define ETH_MACL4A0R_L4SP0                                  0x0000ffff
#define ETH_MACL4A0R_L4DP0                                  0xffff0000

/**************** bit definitions for MACL3A00R register ****************/
#define ETH_MACL3A00R_L3A00                                 0xffffffff

/**************** bit definitions for MACL3A10R register ****************/
#define ETH_MACL3A10R_L3A10                                 0xffffffff

/**************** bit definitions for MACL3A20 register *****************/
#define ETH_MACL3A20_L3A20                                  0xffffffff

/**************** bit definitions for MACL3A30 register *****************/
#define ETH_MACL3A30_L3A30                                  0xffffffff

/*************** bit definitions for MACL3L4C1R register ****************/
#define ETH_MACL3L4C1R_L3PEN1                               0x00000001
#define ETH_MACL3L4C1R_L3SAM1                               0x00000004
#define ETH_MACL3L4C1R_L3SAIM1                              0x00000008
#define ETH_MACL3L4C1R_L3DAM1                               0x00000010
#define ETH_MACL3L4C1R_L3DAIM1                              0x00000020
#define ETH_MACL3L4C1R_L3HSBM1                              0x000007c0
#define ETH_MACL3L4C1R_L3HDBM1                              0x0000f800
#define ETH_MACL3L4C1R_L4PEN1                               0x00010000
#define ETH_MACL3L4C1R_L4SPM1                               0x00040000
#define ETH_MACL3L4C1R_L4SPIM1                              0x00080000
#define ETH_MACL3L4C1R_L4DPM1                               0x00100000
#define ETH_MACL3L4C1R_L4DPIM1                              0x00200000

/**************** bit definitions for MACL4A1R register *****************/
#define ETH_MACL4A1R_L4SP1                                  0x0000ffff
#define ETH_MACL4A1R_L4DP1                                  0xffff0000

/**************** bit definitions for MACL3A01R register ****************/
#define ETH_MACL3A01R_L3A01                                 0xffffffff

/**************** bit definitions for MACL3A11R register ****************/
#define ETH_MACL3A11R_L3A11                                 0xffffffff

/**************** bit definitions for MACL3A21R register ****************/
#define ETH_MACL3A21R_L3A21                                 0xffffffff

/**************** bit definitions for MACL3A31R register ****************/
#define ETH_MACL3A31R_L3A31                                 0xffffffff

/**************** bit definitions for MACARPAR register *****************/
#define ETH_MACARPAR_ARPPA                                  0xffffffff

/***************** bit definitions for MACTSCR register *****************/
#define ETH_MACTSCR_TSENA                                   0x00000001
#define ETH_MACTSCR_TSCFUPDT                                0x00000002
#define ETH_MACTSCR_TSINIT                                  0x00000004
#define ETH_MACTSCR_TSUPDT                                  0x00000008
#define ETH_MACTSCR_TSADDREG                                0x00000020
#define ETH_MACTSCR_TSENALL                                 0x00000100
#define ETH_MACTSCR_TSCTRLSSR                               0x00000200
#define ETH_MACTSCR_TSVER2ENA                               0x00000400
#define ETH_MACTSCR_TSIPENA                                 0x00000800
#define ETH_MACTSCR_TSIPV6ENA                               0x00001000
#define ETH_MACTSCR_TSIPV4ENA                               0x00002000
#define ETH_MACTSCR_TSEVNTENA                               0x00004000
#define ETH_MACTSCR_TSMSTRENA                               0x00008000
#define ETH_MACTSCR_SNAPTYPSEL                              0x00030000
#define ETH_MACTSCR_TSENMACADDR                             0x00040000
#define ETH_MACTSCR_CSC                                     0x00080000
#define ETH_MACTSCR_TXTSSTSM                                0x01000000

/***************** bit definitions for MACSSIR register *****************/
#define ETH_MACSSIR_SNSINC                                  0x0000ff00
#define ETH_MACSSIR_SSINC                                   0x00ff0000

/***************** bit definitions for MACSTSR register *****************/
#define ETH_MACSTSR_TSS                                     0xffffffff

/***************** bit definitions for MACSTNR register *****************/
#define ETH_MACSTNR_TSSS                                    0x7fffffff

/**************** bit definitions for MACSTSUR register *****************/
#define ETH_MACSTSUR_TSS                                    0xffffffff

/**************** bit definitions for MACSTNUR register *****************/
#define ETH_MACSTNUR_TSSS                                   0x7fffffff
#define ETH_MACSTNUR_ADDSUB                                 0x80000000

/***************** bit definitions for MACTSAR register *****************/
#define ETH_MACTSAR_TSAR                                    0xffffffff

/***************** bit definitions for MACTSSR register *****************/
#define ETH_MACTSSR_TSSOVF                                  0x00000001
#define ETH_MACTSSR_TSTARGT0                                0x00000002
#define ETH_MACTSSR_AUXTSTRIG                               0x00000004
#define ETH_MACTSSR_TSTRGTERR0                              0x00000008
#define ETH_MACTSSR_TXTSSIS                                 0x00008000
#define ETH_MACTSSR_ATSSTN                                  0x000f0000
#define ETH_MACTSSR_ATSSTM                                  0x01000000
#define ETH_MACTSSR_ATSNS                                   0x3e000000

/*************** bit definitions for MACTTSSNR register ****************/
#define ETH_MACTTSSNR_TXTSSLO                               0x7fffffff
#define ETH_MACTTSSNR_TXTSSMIS                              0x80000000

/*************** bit definitions for MACTTSSSR register ****************/
#define ETH_MACTTSSSR_TXTSSHI                               0xffffffff

/***************** bit definitions for MACACR register ******************/
#define ETH_MACACR_ATSFC                                    0x00000001
#define ETH_MACACR_ATSEN0                                   0x00000010
#define ETH_MACACR_ATSEN1                                   0x00000020
#define ETH_MACACR_ATSEN2                                   0x00000040
#define ETH_MACACR_ATSEN3                                   0x00000080

/**************** bit definitions for MACATSNR register *****************/
#define ETH_MACATSNR_AUXTSLO                                0x7fffffff

/**************** bit definitions for MACATSSR register *****************/
#define ETH_MACATSSR_AUXTSHI                                0xffffffff

/**************** bit definitions for MACTSIACR register ****************/
#define ETH_MACTSIACR_OSTIAC                                0xffffffff

/**************** bit definitions for MACTSEACR register ****************/
#define ETH_MACTSEACR_OSTEAC                                0xffffffff

/**************** bit definitions for MACTSICNR register ****************/
#define ETH_MACTSICNR_TSIC                                  0xffffffff

/**************** bit definitions for MACTSECNR register ****************/
#define ETH_MACTSECNR_TSEC                                  0xffffffff

/**************** bit definitions for MACPPSCR register *****************/
#define ETH_MACPPSCR_PPSCTRL                                0x0000000f
#define ETH_MACPPSCR_PPSEN0                                 0x00000010
#define ETH_MACPPSCR_TRGTMODSEL0                            0x00000060

/*************** bit definitions for MACPPSTTSR register ****************/
#define ETH_MACPPSTTSR_TSTRH0                               0x7fffffff

/*************** bit definitions for MACPPSTTNR register ****************/
#define ETH_MACPPSTTNR_TTSL0                                0x7fffffff
#define ETH_MACPPSTTNR_TRGTBUSY0                            0x80000000

/**************** bit definitions for MACPPSIR register *****************/
#define ETH_MACPPSIR_PPSINT0                                0xffffffff

/**************** bit definitions for MACPPSWR register *****************/
#define ETH_MACPPSWR_PPSWIDTH0                              0xffffffff

/***************** bit definitions for MACPOCR register *****************/
#define ETH_MACPOCR_PTOEN                                   0x00000001
#define ETH_MACPOCR_ASYNCEN                                 0x00000002
#define ETH_MACPOCR_APDREQEN                                0x00000004
#define ETH_MACPOCR_ASYNCTRIG                               0x00000010
#define ETH_MACPOCR_APDREQTRIG                              0x00000020
#define ETH_MACPOCR_DRRDIS                                  0x00000040
#define ETH_MACPOCR_DN                                      0x0000ff00

/**************** bit definitions for MACSPI0R register *****************/
#define ETH_MACSPI0R_SPI0                                   0xffffffff

/**************** bit definitions for MACSPI1R register *****************/
#define ETH_MACSPI1R_SPI1                                   0xffffffff

/**************** bit definitions for MACSPI2R register *****************/
#define ETH_MACSPI2R_SPI2                                   0x0000ffff

/***************** bit definitions for MACLMIR register *****************/
#define ETH_MACLMIR_LSI                                     0x000000ff
#define ETH_MACLMIR_DRSYNCR                                 0x00000700
#define ETH_MACLMIR_LMPDRI                                  0xff000000


/* register bank for the ethernet descriptor */
typedef struct {
    reg32_t DESC0;
    reg32_t DESC1;
    reg32_t DESC2;
    reg32_t DESC3;
} eth_dma_desc_t;

/***************** bit definitions for TDES0 RF register ****************/
#define ETH_DMATXNDESC0RF_B1AP                              0xFFFFFFFF

/***************** bit definitions for TDES1 RF register ****************/
#define ETH_DMATXNDESC1RF_B2AP                              0xFFFFFFFF

/***************** bit definitions for TDES2 RF register ****************/
#define ETH_DMATXNDESC2RF_IOC                               0x80000000
#define ETH_DMATXNDESC2RF_TTSE                              0x40000000
#define ETH_DMATXNDESC2RF_B2L                               0x3FFF0000
#define ETH_DMATXNDESC2RF_VTIR                              0x0000C000
#define ETH_DMATXNDESC2RF_VTIR_DISABLE                      0x00000000
#define ETH_DMATXNDESC2RF_VTIR_REMOVE                       0x00004000
#define ETH_DMATXNDESC2RF_VTIR_INSERT                       0x00008000
#define ETH_DMATXNDESC2RF_VTIR_REPLACE                      0x0000C000
#define ETH_DMATXNDESC2RF_B1L                               0x00003FFF
#define ETH_DMATXNDESC2RF_HL                                0x000003FF

/***************** bit definitions for TDES3 RF register ****************/
#define ETH_DMATXNDESC3RF_OWN                               0x80000000
#define ETH_DMATXNDESC3RF_CTXT                              0x40000000
#define ETH_DMATXNDESC3RF_FD                                0x20000000
#define ETH_DMATXNDESC3RF_LD                                0x10000000
#define ETH_DMATXNDESC3RF_CPC                               0x0C000000
#define ETH_DMATXNDESC3RF_CPC_CRCPAD_INSERT                 0x00000000
#define ETH_DMATXNDESC3RF_CPC_CRC_INSERT                    0x04000000
#define ETH_DMATXNDESC3RF_CPC_DISABLE                       0x08000000
#define ETH_DMATXNDESC3RF_CPC_CRC_REPLACE                   0x0C000000
#define ETH_DMATXNDESC3RF_SAIC                              0x03800000
#define ETH_DMATXNDESC3RF_SAIC_DISABLE                      0x00000000
#define ETH_DMATXNDESC3RF_SAIC_INSERT                       0x00800000
#define ETH_DMATXNDESC3RF_SAIC_REPLACE                      0x01000000
#define ETH_DMATXNDESC3RF_THL                               0x00780000
#define ETH_DMATXNDESC3RF_TSE                               0x00040000
#define ETH_DMATXNDESC3RF_CIC                               0x00030000
#define ETH_DMATXNDESC3RF_CIC_DISABLE                       0x00000000
#define ETH_DMATXNDESC3RF_CIC_IPHDR_INSERT                  0x00010000
#define ETH_DMATXNDESC3RF_CIC_IPHDR_PAYLOAD_INSERT          0x00020000
#define ETH_DMATXNDESC3RF_CIC_IPHDR_PAYLOAD_INSERT_PHDR_CALC 0x00030000
#define ETH_DMATXNDESC3RF_TPL                               0x0003FFFF
#define ETH_DMATXNDESC3RF_FL                                0x00007FFF

/**************** bit definitions for TDES0 WBF register ****************/
#define ETH_DMATXNDESC0WBF_TTSL                             0xFFFFFFFF

/**************** bit definitions for TDES1 WBF register ****************/
#define ETH_DMATXNDESC1WBF_TTSH                             0xFFFFFFFF

/**************** bit definitions for TDES3 WBF register ****************/
#define ETH_DMATXNDESC3WBF_OWN                              0x80000000
#define ETH_DMATXNDESC3WBF_CTXT                             0x40000000
#define ETH_DMATXNDESC3WBF_FD                               0x20000000
#define ETH_DMATXNDESC3WBF_LD                               0x10000000
#define ETH_DMATXNDESC3WBF_TTSS                             0x00020000
#define ETH_DMATXNDESC3WBF_DP                               0x04000000
#define ETH_DMATXNDESC3WBF_TTSE                             0x02000000
#define ETH_DMATXNDESC3WBF_ES                               0x00008000
#define ETH_DMATXNDESC3WBF_JT                               0x00004000
#define ETH_DMATXNDESC3WBF_FF                               0x00002000
#define ETH_DMATXNDESC3WBF_PCE                              0x00001000
#define ETH_DMATXNDESC3WBF_LCA                              0x00000800
#define ETH_DMATXNDESC3WBF_NC                               0x00000400
#define ETH_DMATXNDESC3WBF_LCO                              0x00000200
#define ETH_DMATXNDESC3WBF_EC                               0x00000100
#define ETH_DMATXNDESC3WBF_CC                               0x000000F0
#define ETH_DMATXNDESC3WBF_ED                               0x00000008
#define ETH_DMATXNDESC3WBF_UF                               0x00000004
#define ETH_DMATXNDESC3WBF_DB                               0x00000002
#define ETH_DMATXNDESC3WBF_IHE                              0x00000004

/**************** bit definitions for TDES0 TXC register ****************/
#define ETH_DMATXCDESC0_TTSL                                0xFFFFFFFF

/**************** bit definitions for TDES1 TXC register ****************/
#define ETH_DMATXCDESC1_TTSH                                0xFFFFFFFF

/**************** bit definitions for TDES2 TXC register ****************/
#define ETH_DMATXCDESC2_IVT                                 0xFFFF0000
#define ETH_DMATXCDESC2_MSS                                 0x00003FFF

/**************** bit definitions for TDES3 TXC register ****************/
#define ETH_DMATXCDESC3_OWN                                 0x80000000
#define ETH_DMATXCDESC3_CTXT                                0x40000000
#define ETH_DMATXCDESC3_OSTC                                0x08000000
#define ETH_DMATXCDESC3_TCMSSV                              0x04000000
#define ETH_DMATXCDESC3_CDE                                 0x00800000
#define ETH_DMATXCDESC3_IVTIR                               0x000C0000
#define ETH_DMATXCDESC3_IVTIR_DISABLE                       0x00000000
#define ETH_DMATXCDESC3_IVTIR_REMOVE                        0x00040000
#define ETH_DMATXCDESC3_IVTIR_INSERT                        0x00080000
#define ETH_DMATXCDESC3_IVTIR_REPLACE                       0x000C0000
#define ETH_DMATXCDESC3_IVLTV                               0x00020000
#define ETH_DMATXCDESC3_VLTV                                0x00010000
#define ETH_DMATXCDESC3_VT                                  0x0000FFFF

/***************** bit definitions for RDES0 RF register ****************/
#define ETH_DMARXNDESC0RF_BUF1AP                            0xFFFFFFFF

/***************** bit definitions for RDES2 RF register ****************/
#define ETH_DMARXNDESC2RF_BUF2AP                            0xFFFFFFFF

/***************** bit definitions for RDES3 RF register ****************/
#define ETH_DMARXNDESC3RF_OWN                               0x80000000
#define ETH_DMARXNDESC3RF_IOC                               0x40000000
#define ETH_DMARXNDESC3RF_BUF2V                             0x02000000
#define ETH_DMARXNDESC3RF_BUF1V                             0x01000000

/***************** bit definitions for RDES0 WRF register ****************/
#define ETH_DMARXNDESC0WBF_IVT                              0xFFFF0000
#define ETH_DMARXNDESC0WBF_OVT                              0x0000FFFF

/***************** bit definitions for RDES1 WRF register ****************/
#define ETH_DMARXNDESC1WBF_OPC                              0xFFFF0000
#define ETH_DMARXNDESC1WBF_TD                               0x00008000
#define ETH_DMARXNDESC1WBF_TSA                              0x00004000
#define ETH_DMARXNDESC1WBF_PV                               0x00002000
#define ETH_DMARXNDESC1WBF_PFT                              0x00001000
#define ETH_DMARXNDESC1WBF_PMT_NO                           0x00000000
#define ETH_DMARXNDESC1WBF_PMT_SYNC                         0x00000100
#define ETH_DMARXNDESC1WBF_PMT_FUP                          0x00000200
#define ETH_DMARXNDESC1WBF_PMT_DREQ                         0x00000300
#define ETH_DMARXNDESC1WBF_PMT_DRESP                        0x00000400
#define ETH_DMARXNDESC1WBF_PMT_PDREQ                        0x00000500
#define ETH_DMARXNDESC1WBF_PMT_PDRESP                       0x00000600
#define ETH_DMARXNDESC1WBF_PMT_PDRESPFUP                    0x00000700
#define ETH_DMARXNDESC1WBF_PMT_ANNOUNCE                     0x00000800
#define ETH_DMARXNDESC1WBF_PMT_MANAG                        0x00000900
#define ETH_DMARXNDESC1WBF_PMT_SIGN                         0x00000A00
#define ETH_DMARXNDESC1WBF_PMT_RESERVED                     0x00000F00
#define ETH_DMARXNDESC1WBF_IPCE                             0x00000080
#define ETH_DMARXNDESC1WBF_IPCB                             0x00000040
#define ETH_DMARXNDESC1WBF_IPV6                             0x00000020
#define ETH_DMARXNDESC1WBF_IPV4                             0x00000010
#define ETH_DMARXNDESC1WBF_IPHE                             0x00000008
#define ETH_DMARXNDESC1WBF_PT                               0x00000003
#define ETH_DMARXNDESC1WBF_PT_UNKNOWN                       0x00000000
#define ETH_DMARXNDESC1WBF_PT_UDP                           0x00000001
#define ETH_DMARXNDESC1WBF_PT_TCP                           0x00000002
#define ETH_DMARXNDESC1WBF_PT_ICMP                          0x00000003

/***************** bit definitions for RDES2 WRF register ****************/
#define ETH_DMARXNDESC2WBF_L3L4FM                           0x20000000
#define ETH_DMARXNDESC2WBF_L4FM                             0x10000000
#define ETH_DMARXNDESC2WBF_L3FM                             0x08000000
#define ETH_DMARXNDESC2WBF_MADRM                            0x07F80000
#define ETH_DMARXNDESC2WBF_HF                               0x00040000
#define ETH_DMARXNDESC2WBF_DAF                              0x00020000
#define ETH_DMARXNDESC2WBF_SAF                              0x00010000
#define ETH_DMARXNDESC2WBF_VF                               0x00008000
#define ETH_DMARXNDESC2WBF_ARPNR                            0x00000400

/***************** bit definitions for RDES3 WRF register ****************/
#define ETH_DMARXNDESC3WBF_OWN                              0x80000000
#define ETH_DMARXNDESC3WBF_CTXT                             0x40000000
#define ETH_DMARXNDESC3WBF_FD                               0x20000000
#define ETH_DMARXNDESC3WBF_LD                               0x10000000
#define ETH_DMARXNDESC3WBF_RS2V                             0x08000000
#define ETH_DMARXNDESC3WBF_RS1V                             0x04000000
#define ETH_DMARXNDESC3WBF_RS0V                             0x02000000
#define ETH_DMARXNDESC3WBF_CE                               0x01000000
#define ETH_DMARXNDESC3WBF_GP                               0x00800000
#define ETH_DMARXNDESC3WBF_RWT                              0x00400000
#define ETH_DMARXNDESC3WBF_OE                               0x00200000
#define ETH_DMARXNDESC3WBF_RE                               0x00100000
#define ETH_DMARXNDESC3WBF_DE                               0x00080000
#define ETH_DMARXNDESC3WBF_LT                               0x00070000
#define ETH_DMARXNDESC3WBF_LT_LP                            0x00000000
#define ETH_DMARXNDESC3WBF_LT_TP                            0x00010000
#define ETH_DMARXNDESC3WBF_LT_ARP                           0x00030000
#define ETH_DMARXNDESC3WBF_LT_VLAN                          0x00040000
#define ETH_DMARXNDESC3WBF_LT_DVLAN                         0x00050000
#define ETH_DMARXNDESC3WBF_LT_MAC                           0x00060000
#define ETH_DMARXNDESC3WBF_LT_OAM                           0x00070000
#define ETH_DMARXNDESC3WBF_ES                               0x00008000
#define ETH_DMARXNDESC3WBF_PL                               0x00007FFF

/***************** bit definitions for RDES0 RF register ****************/
#define ETH_DMARXCDESC0_RTSL                                0xFFFFFFFF

/***************** bit definitions for RDES1 RF register ****************/
#define ETH_DMARXCDESC1_RTSH                                0xFFFFFFFF

/***************** bit definitions for RDES3 RF register ****************/
#define ETH_DMARXCDESC3_OWN                                 0x80000000
#define ETH_DMARXCDESC3_CTXT                                0x40000000


/* ethenret buffer type */
typedef struct {
    /* data pointer */
    void *ptr;
    /* buffer length */
    uint32_t length;
} eth_dma_buf_t;



#endif /* STM32H743_ETH_H */

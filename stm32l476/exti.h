/**
 * @file exti.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: EXTI
 */


#ifndef STM32L476_EXTI_H_
#define STM32L476_EXTI_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define EXTI_BASE							(0x40010400)
/* registers */
#define EXTI								((exti_t *) EXTI_BASE)

/* registers */
typedef struct {
  reg32_t IMR1;
  reg32_t EMR1;
  reg32_t RTSR1;
  reg32_t FTSR1;
  reg32_t SWIER1;
  reg32_t PR1;
  reg32_t RESERVED1;
  reg32_t RESERVED2;
  reg32_t IMR2;
  reg32_t EMR2;
  reg32_t RTSR2;
  reg32_t FTSR2;
  reg32_t SWIER2;
  reg32_t PR2;
} __attribute__((packed, aligned(4))) exti_t;

/*	Bit definition for EXTI_IMR1 register  */
#define EXTI_IMR1_IM0						(0x00000001)
#define EXTI_IMR1_IM1						(0x00000002)
#define EXTI_IMR1_IM2						(0x00000004)
#define EXTI_IMR1_IM3						(0x00000008)
#define EXTI_IMR1_IM4						(0x00000010)
#define EXTI_IMR1_IM5						(0x00000020)
#define EXTI_IMR1_IM6						(0x00000040)
#define EXTI_IMR1_IM7						(0x00000080)
#define EXTI_IMR1_IM8						(0x00000100)
#define EXTI_IMR1_IM9						(0x00000200)
#define EXTI_IMR1_IM10						(0x00000400)
#define EXTI_IMR1_IM11						(0x00000800)
#define EXTI_IMR1_IM12						(0x00001000)
#define EXTI_IMR1_IM13						(0x00002000)
#define EXTI_IMR1_IM14						(0x00004000)
#define EXTI_IMR1_IM15						(0x00008000)
#define EXTI_IMR1_IM16						(0x00010000)
#define EXTI_IMR1_IM17						(0x00020000)
#define EXTI_IMR1_IM18						(0x00040000)
#define EXTI_IMR1_IM19						(0x00080000)
#define EXTI_IMR1_IM20						(0x00100000)
#define EXTI_IMR1_IM21						(0x00200000)
#define EXTI_IMR1_IM22						(0x00400000)
#define EXTI_IMR1_IM23						(0x00800000)
#define EXTI_IMR1_IM24						(0x01000000)
#define EXTI_IMR1_IM25						(0x02000000)
#define EXTI_IMR1_IM26						(0x04000000)
#define EXTI_IMR1_IM27						(0x08000000)
#define EXTI_IMR1_IM28						(0x10000000)
#define EXTI_IMR1_IM29						(0x20000000)
#define EXTI_IMR1_IM30						(0x40000000)
#define EXTI_IMR1_IM31						(0x80000000)
#define EXTI_IMR1_IM						(0xFFFFFFFF)

/*	Bit definition for EXTI_EMR1 register  */
#define EXTI_EMR1_EM0						(0x00000001)
#define EXTI_EMR1_EM1						(0x00000002)
#define EXTI_EMR1_EM2						(0x00000004)
#define EXTI_EMR1_EM3						(0x00000008)
#define EXTI_EMR1_EM4						(0x00000010)
#define EXTI_EMR1_EM5						(0x00000020)
#define EXTI_EMR1_EM6						(0x00000040)
#define EXTI_EMR1_EM7						(0x00000080)
#define EXTI_EMR1_EM8						(0x00000100)
#define EXTI_EMR1_EM9						(0x00000200)
#define EXTI_EMR1_EM10						(0x00000400)
#define EXTI_EMR1_EM11						(0x00000800)
#define EXTI_EMR1_EM12						(0x00001000)
#define EXTI_EMR1_EM13						(0x00002000)
#define EXTI_EMR1_EM14						(0x00004000)
#define EXTI_EMR1_EM15						(0x00008000)
#define EXTI_EMR1_EM16						(0x00010000)
#define EXTI_EMR1_EM17						(0x00020000)
#define EXTI_EMR1_EM18						(0x00040000)
#define EXTI_EMR1_EM19						(0x00080000)
#define EXTI_EMR1_EM20						(0x00100000)
#define EXTI_EMR1_EM21						(0x00200000)
#define EXTI_EMR1_EM22						(0x00400000)
#define EXTI_EMR1_EM23						(0x00800000)
#define EXTI_EMR1_EM24						(0x01000000)
#define EXTI_EMR1_EM25						(0x02000000)
#define EXTI_EMR1_EM26						(0x04000000)
#define EXTI_EMR1_EM27						(0x08000000)
#define EXTI_EMR1_EM28						(0x10000000)
#define EXTI_EMR1_EM29						(0x20000000)
#define EXTI_EMR1_EM30						(0x40000000)
#define EXTI_EMR1_EM31						(0x80000000)

/*	Bit definition for EXTI_RTSR1 register	*/
#define EXTI_RTSR1_RT0						(0x00000001)
#define EXTI_RTSR1_RT1						(0x00000002)
#define EXTI_RTSR1_RT2						(0x00000004)
#define EXTI_RTSR1_RT3						(0x00000008)
#define EXTI_RTSR1_RT4						(0x00000010)
#define EXTI_RTSR1_RT5						(0x00000020)
#define EXTI_RTSR1_RT6						(0x00000040)
#define EXTI_RTSR1_RT7						(0x00000080)
#define EXTI_RTSR1_RT8						(0x00000100)
#define EXTI_RTSR1_RT9						(0x00000200)
#define EXTI_RTSR1_RT10						(0x00000400)
#define EXTI_RTSR1_RT11						(0x00000800)
#define EXTI_RTSR1_RT12						(0x00001000)
#define EXTI_RTSR1_RT13						(0x00002000)
#define EXTI_RTSR1_RT14						(0x00004000)
#define EXTI_RTSR1_RT15						(0x00008000)
#define EXTI_RTSR1_RT16						(0x00010000)
#define EXTI_RTSR1_RT18						(0x00040000)
#define EXTI_RTSR1_RT19						(0x00080000)
#define EXTI_RTSR1_RT20						(0x00100000)
#define EXTI_RTSR1_RT21						(0x00200000)
#define EXTI_RTSR1_RT22						(0x00400000)

/*	Bit definition for EXTI_FTSR1 register	*/
#define EXTI_FTSR1_FT0						(0x00000001)
#define EXTI_FTSR1_FT1						(0x00000002)
#define EXTI_FTSR1_FT2						(0x00000004)
#define EXTI_FTSR1_FT3						(0x00000008)
#define EXTI_FTSR1_FT4						(0x00000010)
#define EXTI_FTSR1_FT5						(0x00000020)
#define EXTI_FTSR1_FT6						(0x00000040)
#define EXTI_FTSR1_FT7						(0x00000080)
#define EXTI_FTSR1_FT8						(0x00000100)
#define EXTI_FTSR1_FT9						(0x00000200)
#define EXTI_FTSR1_FT10						(0x00000400)
#define EXTI_FTSR1_FT11						(0x00000800)
#define EXTI_FTSR1_FT12						(0x00001000)
#define EXTI_FTSR1_FT13						(0x00002000)
#define EXTI_FTSR1_FT14						(0x00004000)
#define EXTI_FTSR1_FT15						(0x00008000)
#define EXTI_FTSR1_FT16						(0x00010000)
#define EXTI_FTSR1_FT18						(0x00040000)
#define EXTI_FTSR1_FT19						(0x00080000)
#define EXTI_FTSR1_FT20						(0x00100000)
#define EXTI_FTSR1_FT21						(0x00200000)
#define EXTI_FTSR1_FT22						(0x00400000)

/*	Bit definition for EXTI_SWIER1 register  */
#define EXTI_SWIER1_SWI0					(0x00000001)
#define EXTI_SWIER1_SWI1					(0x00000002)
#define EXTI_SWIER1_SWI2					(0x00000004)
#define EXTI_SWIER1_SWI3					(0x00000008)
#define EXTI_SWIER1_SWI4					(0x00000010)
#define EXTI_SWIER1_SWI5					(0x00000020)
#define EXTI_SWIER1_SWI6					(0x00000040)
#define EXTI_SWIER1_SWI7					(0x00000080)
#define EXTI_SWIER1_SWI8					(0x00000100)
#define EXTI_SWIER1_SWI9					(0x00000200)
#define EXTI_SWIER1_SWI10					(0x00000400)
#define EXTI_SWIER1_SWI11					(0x00000800)
#define EXTI_SWIER1_SWI12					(0x00001000)
#define EXTI_SWIER1_SWI13					(0x00002000)
#define EXTI_SWIER1_SWI14					(0x00004000)
#define EXTI_SWIER1_SWI15					(0x00008000)
#define EXTI_SWIER1_SWI16					(0x00010000)
#define EXTI_SWIER1_SWI18					(0x00040000)
#define EXTI_SWIER1_SWI19					(0x00080000)
#define EXTI_SWIER1_SWI20					(0x00100000)
#define EXTI_SWIER1_SWI21					(0x00200000)
#define EXTI_SWIER1_SWI22					(0x00400000)

/*	Bit definition for EXTI_PR1 register  */
#define EXTI_PR1_PIF0						(0x00000001)
#define EXTI_PR1_PIF1						(0x00000002)
#define EXTI_PR1_PIF2						(0x00000004)
#define EXTI_PR1_PIF3						(0x00000008)
#define EXTI_PR1_PIF4						(0x00000010)
#define EXTI_PR1_PIF5						(0x00000020)
#define EXTI_PR1_PIF6						(0x00000040)
#define EXTI_PR1_PIF7						(0x00000080)
#define EXTI_PR1_PIF8						(0x00000100)
#define EXTI_PR1_PIF9						(0x00000200)
#define EXTI_PR1_PIF10						(0x00000400)
#define EXTI_PR1_PIF11						(0x00000800)
#define EXTI_PR1_PIF12						(0x00001000)
#define EXTI_PR1_PIF13						(0x00002000)
#define EXTI_PR1_PIF14						(0x00004000)
#define EXTI_PR1_PIF15						(0x00008000)
#define EXTI_PR1_PIF16						(0x00010000)
#define EXTI_PR1_PIF18						(0x00040000)
#define EXTI_PR1_PIF19						(0x00080000)
#define EXTI_PR1_PIF20						(0x00100000)
#define EXTI_PR1_PIF21						(0x00200000)
#define EXTI_PR1_PIF22						(0x00400000)

/*	Bit definition for EXTI_IMR2 register  */
#define EXTI_IMR2_IM32						(0x00000001)
#define EXTI_IMR2_IM33						(0x00000002)
#define EXTI_IMR2_IM34						(0x00000004)
#define EXTI_IMR2_IM35						(0x00000008)
#define EXTI_IMR2_IM36						(0x00000010)
#define EXTI_IMR2_IM37						(0x00000020)
#define EXTI_IMR2_IM38						(0x00000040)
#define EXTI_IMR2_IM39						(0x00000080)
#define EXTI_IMR2_IM						(0x000000FF)

/*	Bit definition for EXTI_EMR2 register  */
#define EXTI_EMR2_EM32						(0x00000001)
#define EXTI_EMR2_EM33						(0x00000002)
#define EXTI_EMR2_EM34						(0x00000004)
#define EXTI_EMR2_EM35						(0x00000008)
#define EXTI_EMR2_EM36						(0x00000010)
#define EXTI_EMR2_EM37						(0x00000020)
#define EXTI_EMR2_EM38						(0x00000040)
#define EXTI_EMR2_EM39						(0x00000080)

/*	Bit definition for EXTI_RTSR2 register	*/
#define EXTI_RTSR2_RT35						(0x00000008)
#define EXTI_RTSR2_RT36						(0x00000010)
#define EXTI_RTSR2_RT37						(0x00000020)
#define EXTI_RTSR2_RT38						(0x00000040)

/*	Bit definition for EXTI_FTSR2 register	*/
#define EXTI_FTSR2_FT35						(0x00000008)
#define EXTI_FTSR2_FT36						(0x00000010)
#define EXTI_FTSR2_FT37						(0x00000020)
#define EXTI_FTSR2_FT38						(0x00000040)

/*	Bit definition for EXTI_SWIER2 register  */
#define EXTI_SWIER2_SWI35					(0x00000008)
#define EXTI_SWIER2_SWI36					(0x00000010)
#define EXTI_SWIER2_SWI37					(0x00000020)
#define EXTI_SWIER2_SWI38					(0x00000040)

/*	Bit definition for EXTI_PR2 register  */
#define EXTI_PR2_PIF35						(0x00000008)
#define EXTI_PR2_PIF36						(0x00000010)
#define EXTI_PR2_PIF37						(0x00000020)
#define EXTI_PR2_PIF38						(0x00000040)

#endif /* STM32L476_EXTI_H_ */

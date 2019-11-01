/**
 * @file flash.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: FLASH
 */


#ifndef STM32L476_FLASH_H_
#define STM32L476_FLASH_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define FLASH_BASE							(0x40022000)
/* registers */
#define FLASH								((flash_t *) FLASH_BASE)

/* registers */
typedef struct {
	reg32_t ACR;
	reg32_t PDKEYR;
	reg32_t KEYR;
	reg32_t OPTKEYR;
	reg32_t SR;
	reg32_t CR;
	reg32_t ECCR;
	reg32_t RESERVED1;
	reg32_t OPTR;
	reg32_t PCROP1SR;
	reg32_t PCROP1ER;
	reg32_t WRP1AR;
	reg32_t WRP1BR;
	reg32_t RESERVED2[4];
	reg32_t PCROP2SR;
	reg32_t PCROP2ER;
	reg32_t WRP2AR;
	reg32_t WRP2BR;
} __attribute__((packed, aligned(4))) flash_t;

/*	Bits definition for FLASH_ACR register	*/
#define FLASH_ACR_LATENCY					(0x00000007)
#define FLASH_ACR_LATENCY_0WS				(0x00000000)
#define FLASH_ACR_LATENCY_1WS				(0x00000001)
#define FLASH_ACR_LATENCY_2WS				(0x00000002)
#define FLASH_ACR_LATENCY_3WS				(0x00000003)
#define FLASH_ACR_LATENCY_4WS				(0x00000004)
#define FLASH_ACR_PRFTEN					(0x00000100)
#define FLASH_ACR_ICEN						(0x00000200)
#define FLASH_ACR_DCEN						(0x00000400)
#define FLASH_ACR_ICRST						(0x00000800)
#define FLASH_ACR_DCRST						(0x00001000)
#define FLASH_ACR_RUN_PD					(0x00002000)
#define FLASH_ACR_SLEEP_PD					(0x00004000)

/*	Bits definition for FLASH_SR register  */
#define FLASH_SR_EOP						(0x00000001)
#define FLASH_SR_OPERR						(0x00000002)
#define FLASH_SR_PROGERR					(0x00000008)
#define FLASH_SR_WRPERR						(0x00000010)
#define FLASH_SR_PGAERR						(0x00000020)
#define FLASH_SR_SIZERR						(0x00000040)
#define FLASH_SR_PGSERR						(0x00000080)
#define FLASH_SR_MISERR						(0x00000100)
#define FLASH_SR_FASTERR					(0x00000200)
#define FLASH_SR_RDERR						(0x00004000)
#define FLASH_SR_OPTVERR					(0x00008000)
#define FLASH_SR_BSY						(0x00010000)

/*	Bits definition for FLASH_CR register  */
#define FLASH_CR_PG							(0x00000001)
#define FLASH_CR_PER						(0x00000002)
#define FLASH_CR_MER1						(0x00000004)
#define FLASH_CR_PNB						(0x000007F8)
#define FLASH_CR_BKER						(0x00000800)
#define FLASH_CR_MER2						(0x00008000)
#define FLASH_CR_STRT						(0x00010000)
#define FLASH_CR_OPTSTRT					(0x00020000)
#define FLASH_CR_FSTPG						(0x00040000)
#define FLASH_CR_EOPIE						(0x01000000)
#define FLASH_CR_ERRIE						(0x02000000)
#define FLASH_CR_RDERRIE					(0x04000000)
#define FLASH_CR_OBL_LAUNCH					(0x08000000)
#define FLASH_CR_OPTLOCK					(0x40000000)
#define FLASH_CR_LOCK						(0x80000000)

/*	Bits definition for FLASH_ECCR register  */
#define FLASH_ECCR_ADDR_ECC					(0x0007FFFF)
#define FLASH_ECCR_BK_ECC					(0x00080000)
#define FLASH_ECCR_SYSF_ECC					(0x00100000)
#define FLASH_ECCR_ECCIE					(0x01000000)
#define FLASH_ECCR_ECCC						(0x40000000)
#define FLASH_ECCR_ECCD						(0x80000000)

/*	Bits definition for FLASH_OPTR register  */
#define FLASH_OPTR_RDP						(0x000000FF)
#define FLASH_OPTR_BOR_LEV					(0x00000700)
#define FLASH_OPTR_BOR_LEV_0				(0x00000000)
#define FLASH_OPTR_BOR_LEV_1				(0x00000100)
#define FLASH_OPTR_BOR_LEV_2				(0x00000200)
#define FLASH_OPTR_BOR_LEV_3				(0x00000300)
#define FLASH_OPTR_BOR_LEV_4				(0x00000400)
#define FLASH_OPTR_nRST_STOP				(0x00001000)
#define FLASH_OPTR_nRST_STDBY				(0x00002000)
#define FLASH_OPTR_nRST_SHDW				(0x00004000)
#define FLASH_OPTR_IWDG_SW					(0x00010000)
#define FLASH_OPTR_IWDG_STOP				(0x00020000)
#define FLASH_OPTR_IWDG_STDBY				(0x00040000)
#define FLASH_OPTR_WWDG_SW					(0x00080000)
#define FLASH_OPTR_BFB2						(0x00100000)
#define FLASH_OPTR_DUALBANK					(0x00200000)
#define FLASH_OPTR_nBOOT1					(0x00800000)
#define FLASH_OPTR_SRAM2_PE					(0x01000000)
#define FLASH_OPTR_SRAM2_RST				(0x02000000)

/*	Bits definition for FLASH_PCROP1SR register  */
#define FLASH_PCROP1SR_PCROP1_STRT			(0x0000FFFF)

/*	Bits definition for FLASH_PCROP1ER register  */
#define FLASH_PCROP1ER_PCROP1_END			(0x0000FFFF)
#define FLASH_PCROP1ER_PCROP_RDP			(0x80000000)

/*	Bits definition for FLASH_WRP1AR register  */
#define FLASH_WRP1AR_WRP1A_STRT				(0x000000FF)
#define FLASH_WRP1AR_WRP1A_END				(0x00FF0000)

/*	Bits definition for FLASH_WRPB1R register  */
#define FLASH_WRP1BR_WRP1B_STRT				(0x000000FF)
#define FLASH_WRP1BR_WRP1B_END				(0x00FF0000)

/*	Bits definition for FLASH_PCROP2SR register  */
#define FLASH_PCROP2SR_PCROP2_STRT			(0x0000FFFF)

/*	Bits definition for FLASH_PCROP2ER register  */
 #define FLASH_PCROP2ER_PCROP2_END			(0x0000FFFF)

/*	Bits definition for FLASH_WRP2AR register  */
#define FLASH_WRP2AR_WRP2A_STRT				(0x000000FF)
#define FLASH_WRP2AR_WRP2A_END				(0x00FF0000)

/*	Bits definition for FLASH_WRP2BR register  */
#define FLASH_WRP2BR_WRP2B_STRT				(0x000000FF)
#define FLASH_WRP2BR_WRP2B_END				(0x00FF0000)

/* flash keys */
#define FLASH_KEYR_KEY1						(0x45670123)
#define FLASH_KEYR_KEY2						(0xCDEF89AB)

/* option bytes keys */
#define FLASH_OPTKEY_KEY1					(0x08192A3B)
#define FLASH_OPTKEY_KEY2					(0x4C5D6E7F)


#endif /* STM32L476_FLASH_H_ */

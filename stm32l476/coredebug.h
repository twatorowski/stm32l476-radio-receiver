/**
 * @file coredebug.h
 * 
 * @date 2019-09-12
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief STM32 Headers: COREDEBUG
 */

#ifndef STM32L476_COREDEBUG_H_
#define STM32L476_COREDEBUG_H_

#include "stm32l476/stm32l476.h"

/* register base */
#define COREDEBUG_BASE						(0xE000EDF0)
/* registers*/
#define COREDEBUG							((core_debug_t *) COREDEBUG_BASE)

/* core debug registers */
typedef struct {
	reg32_t DHCSR;
	reg32_t DCRSR;
	reg32_t DCRDR;
	reg32_t DEMCR;
} __attribute__((packed, aligned(4))) core_debug_t;

/* Debug Halting Control and Status Register Definitions */
#define COREDEBUG_DHCSR_DBGKEY					0xFFFF0000											  /*!< CoreDebug DHCSR: DBGKEY Position */
#define COREDEBUG_DHCSR_S_RESET_ST				0x02000000											  /*!< CoreDebug DHCSR: S_RESET_ST Position */
#define COREDEBUG_DHCSR_S_RETIRE_ST				0x01000000											  /*!< CoreDebug DHCSR: S_RETIRE_ST Position */
#define COREDEBUG_DHCSR_S_LOCKUP				0x00080000											  /*!< CoreDebug DHCSR: S_LOCKUP Position */
#define COREDEBUG_DHCSR_S_SLEEP					0x00040000											  /*!< CoreDebug DHCSR: S_SLEEP Position */
#define COREDEBUG_DHCSR_S_HALT					0x00020000											  /*!< CoreDebug DHCSR: S_HALT Position */
#define COREDEBUG_DHCSR_S_REGRDY				0x00010000											  /*!< CoreDebug DHCSR: S_REGRDY Position */
#define COREDEBUG_DHCSR_C_SNAPSTALL				0x00000020											  /*!< CoreDebug DHCSR: C_SNAPSTALL Position */
#define COREDEBUG_DHCSR_C_MASKINTS				0x00000008											 /*!< CoreDebug DHCSR: C_MASKINTS Position */
#define COREDEBUG_DHCSR_C_STEP					0x00000004											  /*!< CoreDebug DHCSR: C_STEP Position */
#define COREDEBUG_DHCSR_C_HALT					0x00000002											  /*!< CoreDebug DHCSR: C_HALT Position */
#define COREDEBUG_DHCSR_C_DEBUGEN				0x00000001											  /*!< CoreDebug DHCSR: C_DEBUGEN Position */

/* Debug Core Register Selector Register Definitions */
#define COREDEBUG_DCRSR_REGWnR					0x00010000											  /*!< CoreDebug DCRSR: REGWnR Position */
#define COREDEBUG_DCRSR_REGSEL					0x0000001F											  /*!< CoreDebug DCRSR: REGSEL Position */

/* Debug Exception and Monitor Control Register Definitions */
#define COREDEBUG_DEMCR_TRCENA					0x01000000											  /*!< CoreDebug DEMCR: TRCENA Position */
#define COREDEBUG_DEMCR_MON_REQ					0x00080000											  /*!< CoreDebug DEMCR: MON_REQ Position */
#define COREDEBUG_DEMCR_MON_STEP				0x00040000											  /*!< CoreDebug DEMCR: MON_STEP Position */
#define COREDEBUG_DEMCR_MON_PEND				0x00020000											  /*!< CoreDebug DEMCR: MON_PEND Position */
#define COREDEBUG_DEMCR_MON_EN					0x00010000											  /*!< CoreDebug DEMCR: MON_EN Position */
#define COREDEBUG_DEMCR_VC_HARDERR				0x00000400											  /*!< CoreDebug DEMCR: VC_HARDERR Position */
#define COREDEBUG_DEMCR_VC_INTERR				0x00000200											  /*!< CoreDebug DEMCR: VC_INTERR Position */
#define COREDEBUG_DEMCR_VC_BUSERR				0x00000100
#define COREDEBUG_DEMCR_VC_STATERR				0x00000080											  /*!< CoreDebug DEMCR: VC_STATERR Position */
#define COREDEBUG_DEMCR_VC_CHKERR				0x00000040											  /*!< CoreDebug DEMCR: VC_CHKERR Position */
#define COREDEBUG_DEMCR_VC_NOCPERR				0x00000020											  /*!< CoreDebug DEMCR: VC_NOCPERR Position */
#define COREDEBUG_DEMCR_VC_MMERR				0x00000010											  /*!< CoreDebug DEMCR: VC_MMERR Position */
#define COREDEBUG_DEMCR_VC_CORERESET			0x00000001											  /*!< CoreDebug DEMCR: VC_CORERESET Position */


#endif /* STM32L476_COREDEBUG_H_ */

/**
 * @file debug_dump.h
 * 
 * @date 2019-11-14
 * @author twatorowski 
 * 
 * @brief 
 */

#ifndef DEBUG_DUMP_H_
#define DEBUG_DUMP_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "config.h"

/** @brief valid entry marker */
#define DEBUG_VALID_ENTRY               0xdeadbeef

/** @brief debugger stack frame for further display */
typedef struct debug_stack_frame {
    /** valid entry */
    uint32_t valid;
    /* general purpose registers */
    uint32_t r0, r1, r2, r3; 
    /* other registers */
    uint32_t r12, lr, pc, xpsr;
} PACKED debug_stack_frame_t;

/** @brief additional exception information */
typedef struct debug_exc_info {
    /** valid entry */
    uint32_t valid;
    /** interrupt program status register */
    uint32_t ipsr;
    /* active interrupts */
    uint32_t iabr[DEBUG_NUM_IABR_ISBR];
    /* pending interrupts */
    uint32_t ispr[DEBUG_NUM_IABR_ISBR];
} PACKED debug_exc_info_t;

/** @brief additional system control block information */
typedef struct debug_scb_info {
    /** valid entry */
    uint32_t valid;
    /** Configurable Fault Status Register */
    uint32_t cfsr;
    /** HardFault Status Register */
    uint32_t hfsr;
    /** MemManage Fault Address Register */
    uint32_t mmar;
    /** BusFault Address Register */
    uint32_t bfar;
    /** System Handler Control and State Register */
    uint32_t shcsr;
} PACKED debug_scb_info_t;

/** @brief last assert information */
typedef struct debug_assert_info {
    /** valid entry */
    uint32_t valid;
    /** assert message pointer */
    const char *message;
    /** additional info (may be used as pointer or value) */
    uintptr_t additional_info;
} PACKED debug_assert_info_t;

/** @brief storage space for storing mcu state during critical failures */
extern debug_scb_info_t debug_scb_info;
extern debug_exc_info_t debug_exc_info;
extern debug_stack_frame_t debug_stack_frame;
extern debug_assert_info_t debug_assert_info;

#endif /* DEBUG_DUMP_H_ */

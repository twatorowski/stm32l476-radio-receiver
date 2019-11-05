/**
 * @file debug.h
 *
 * @date 29.06.2019
 * @author twatorowski
 *
 * @brief Debugging macros
 */

#ifndef DEV_DEBUG_H_
#define DEV_DEBUG_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "config.h"
#include "at/ntfy/debug.h"
#include "sys/sem.h"
#include "util/stdio.h"
#include "util/concatstr.h"

/* disables debug globally */
#if !(DEVELOPMENT)
	#undef DEBUG
#endif

/** @brief valid entry marker */
#define DEBUG_VALID_ENTRY               0xdeadbeef

/** @brief debugger stack frame for further display */
typedef struct debug_stack_frame {
    /**< valid entry */
    uint32_t valid;
    /* general purpose registers */
    uint32_t r0, r1, r2, r3; 
    /* other registers */
    uint32_t r12, lr, pc, xpsr;
} PACKED debug_stack_frame_t;

/** @brief additional exception information */
typedef struct debug_exc_info {
    /**< valid entry */
    uint32_t valid;
    /* interrupt program status register */
    uint32_t ipsr;
} PACKED debug_exc_info_t;

/** @brief additional system control block information */
typedef struct debug_scb_info {
    /**< valid entry */
    uint32_t valid;
    /**< Configurable Fault Status Register */
    uint32_t cfsr;
    /**< HardFault Status Register */
    uint32_t hfsr;
    /**< MemManage Fault Address Register */
    uint32_t mmar;
    /**< BusFault Address Register */
    uint32_t bfar;
    /**< System Handler Control and State Register */
    uint32_t shcsr;
} PACKED debug_scb_info_t;

/** @brief last assert information */
typedef struct {
    /**< valid entry */
    uint32_t valid;
    /**< assert message */
    const char *message;
} PACKED debug_assert_info_t;

/** @brief storage space for storing scb state during critical exeptions */
extern debug_scb_info_t debug_scb_info;
extern debug_exc_info_t debug_exc_info;
extern debug_stack_frame_t debug_stack_frame;
extern debug_assert_info_t debug_assert_info;

/* debug enabled? */
#ifdef DEBUG

/* debug message prefix */
#define DBG_MSG_PRFX                                                        \
    "+D: [" __FILE__ ":" CONCATSTR(__LINE__) "]"

/**
 * @brief non-blocking debug routine. To be used like printf()
 */
#define dprintf(fmt, ...)													\
	/* encapsulated in a loop, to make it compiler-proof :) */				\
	do {																	\
		/* buffer */														\
		char __debug_buf[AT_RES_MAX_LINE_LEN];								\
		/* produce string */												\
		int __l = snprintf(__debug_buf, sizeof(__debug_buf),                \
            DBG_MSG_PRFX fmt, ## __VA_ARGS__);			                    \
		/* try to send debug over the tp */									\
		ATNtfyDebug_PutDebugData(__debug_buf, __l);							\
	} while (0)

#else
#warning "HERE"
/**
 * @brief non-blocking debug routine. To be used like printf()
 */
#define dprintf(fmt, ...)													\
	/* encapsulated in a loop, to make it compiler-proof :) */				\
	do {																	\
	} while (0)

#endif


/**
 * @brief Initialize debug module, print last fatal exception information.
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int Debug_Init(void);

#endif /* DEV_DEBUG_H_ */

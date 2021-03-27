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
#include "sys/sem.h"
#include "util/stdio.h"
#include "util/concatstr.h"

/* disables debug globally */
#if !(DEVELOPMENT)
    #undef DEBUG
#endif

/* debug enabled? */
#ifdef DEBUG

/* debug message prefix */
#define DBG_MSG_PRFX                                                        \
    "+D: [" __FILE__ ":" CONCATSTR(__LINE__) "]"

/**
 * @brief non-blocking debug routine. To be used like printf()
 */
#define dprintf(fmt, ...)                                                   \
    /* encapsulated in a loop, to make it compiler-proof :) */              \
    do {                                                                    \
        /* buffer */                                                        \
        char __debug_buf[AT_MAX_LINE_LEN];                                  \
        /* produce string */                                                \
        int __l = snprintf(__debug_buf, sizeof(__debug_buf),                \
            DBG_MSG_PRFX fmt, ## __VA_ARGS__);                              \
        /* try to send debug over the tp */                                 \
        ATNtfDebug_PutDebugData(__debug_buf, __l);                          \
    } while (0)

#else
/**
 * @brief non-blocking debug routine. To be used like printf()
 */
#define dprintf(fmt, ...)                                                   \
    /* encapsulated in a loop, to make it compiler-proof :) */              \
    do {                                                                    \
    } while (0)

#endif

/**
 * @brief Initialize debug module, print last fatal exception information.
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int Debug_Init(void);

#endif /* DEV_DEBUG_H_ */

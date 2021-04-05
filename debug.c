/**
 * @file debug.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-05
 * 
 * @brief Printf Debugging
 */

#include <stdint.h>
#include <stddef.h>

#include "err.h"
#include "config.h"

/* debug line buffer */
char debug_buf[DEBUG_MAX_LINE_LEN];
/* current debug buffer contents length */
size_t debug_buf_len;
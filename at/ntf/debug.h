/**
 * @file debug.h
 * 
 * @date 2019-09-13
 * @author twatorowski
 * 
 * @brief AT Notifications: Debug.
 */

#ifndef AT_NTFY_DEBUG_H_
#define AT_NTFY_DEBUG_H_

#include <stddef.h>

#include "at/ntf.h"

/** @name Notification mask bit fields definitions */
/** @{ */
/** @brief debug notifications */
#define AT_NTF_MASK_DEBUG                               (0x00000001)
/** @brief radio data notifications */
#define AT_NTF_MASK_RADIO_DATA                          (0x00000002)
/** @} */


/**
 * @brief Initialize debug notifications submodule
 * 
 * @return int error code (@ref ERR_ERROR_CODES)
 */
int ATNtfDebug_Init(void);

/**
 * @brief poll debug notifications submodule 
 */
void ATNtfDebug_Poll(void);

/**
 * @brief Sends debug strings (printfs) as AT notifications. All debug strings must
 * follow the format: "+D: (actual_debug_string + newline)"
 *
 * @param str string pointer
 * @param len string length
 *
 * @return status code (@ref ERR_ERROR_CODES)
 */
int ATNtfDebug_PutDebugData(const char *str, size_t len);


#endif /* AT_NTFY_DEBUG_H_ */

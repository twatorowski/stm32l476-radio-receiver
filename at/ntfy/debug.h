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

/**
 * @brief Initialize debug notifications submodule
 * 
 * @return int error code (@ref ERR_ERROR_CODES)
 */
int ATNtfyDebug_Init(void);

/**
 * @brief poll debug notifications submodule 
 */
void ATNtfyDebug_Poll(void);

/**
 * @brief Sends debug strings (printfs) as AT notifications. All debug strings must
 * follow the format: "+D: (actual_debug_string + newline)"
 *
 * @param str string pointer
 * @param len string length
 *
 * @return status code (@ref ERR_ERROR_CODES)
 */
int ATNtfyDebug_PutDebugData(const char *str, size_t len);


#endif /* AT_NTFY_DEBUG_H_ */

/**
 * @file cmd.h
 *
 * @date 28.06.2019
 * @author twatorowski
 *
 * @brief Commands part of the AT protocol
 */

#ifndef AT_CMD_H_
#define AT_CMD_H_

#include <stddef.h>

/** @brief at command descriptor. if you want to implement a set of commands for 
 * controlling some functionality group these within the array that ends with 
 * entry for empty command {.cmd = ""} */
typedef struct at_cmd {
    /**< command string, like 'AT' or 'AT+SET=' or 'AT+TEST=?' or 
     * 'AT+READ?', you get the idea */
    const char *cmd;
    /**< processing routine pointer: iface - interface id from which the 
     * command came, *cmd - command line itself, len - length, shall return the 
     * error code (@ref ERR_ERROR_CODES) */
    int (*func) (int iface, const char *cmd, size_t len);
} at_cmd_t;

/**
 * @brief Initialize command parser module
 *
 * @return initialization status error code @ref ERR_ERROR_CODES
 */
int ATCmd_Init(void);

/**
 * @brief Command parser module polling function. To be put into program main loop.
 */
void ATCmd_Poll(void);

/**
 * @brief Process the command that is contained within a string pointer by @p line
 * and came from the interface @p iface. WILL ALTER the @p line contents.
 *
 * @param iface interface id, needed to generate the response to the proper 
 * interface
 * @param line string pointer that holds the command itself
 *
 * @return processing status @ref ERR_ERROR_CODES
 */
int ATCmd_Input(int iface, char *line);

/**
 * @brief Sends the trailing response in form of OK or 'ERROR: (error_msg)' 
 * depending on the command result code
 * 
 * @param iface interface id over which to send the response
 * @param rc error code to report
 * 
 * @return int error code @ref ERR_ERROR_CODES
 */
int ATCmd_SendGeneralResponse(int iface, int rc);

/**
 * @brief Sends a response over given interface
 * 
 * @param iface interface is @ref AT_RXTX_IFACE
 * @param str response string
 * @param len length of the string
 * 
 * @return int status code (@ref ERR_ERROR_CODES)
 */
int ATCmd_SendResponse(int iface, const char *str, size_t len);

#endif /* AT_CMD_H_ */

/**
 * @file strerr.c
 * 
 * @date 2019-09-09
 * @author twatorowski
 * 
 * @brief Translate error code to human readable form
 */

#include "err.h"
#include "util/elems.h"

/* error string prefixes */
/* at parser */
#define PRFX_AT                                 "at: "
/* i2c interface */
#define PRFX_I2C                                "i2c: "

/* error strings */
static const char *err_str[] = {
    /* general errors */
    [-EOK] =
        "success",
    [-EFATAL] = 
        "fatal error",
    [-EBUSY] = 
        "resource busy",
    
    /* at parses errors */
    [-EAT_UNKNOWN_CMD] =
        PRFX_AT "unknown command",
    [-EAT_SYNTAX] =
        PRFX_AT "command syntax invalid",
    [-EAT_EXEC] =
        PRFX_AT "command execution failed",

    
    /* i2c interface errors */
    [-EI2C_SWD] = 
        PRFX_I2C "pins controlled by swd",
    [-EI2C_ADDR_NACK] = 
        PRFX_I2C "device did not respond to it's address",
    [-EI2C_TRANSFER_ERROR] = 
        PRFX_I2C "error during transfer",

};

/* return the error string for given error code (or empty string 
 * if not found) */
const char * strerr(int ec) 
{   
    /* we use negative error codes in the system, so lets negate */
    ec = -ec;
    /* outside the boundaries? */
    if (ec < 0 || ec > (int)elems(err_str))
        return "";
    /* no valid error string? */
    if (!err_str[ec])
        return "";
    /* got valid error string */
    return err_str[ec];
}

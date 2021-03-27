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
/* can errors */
#define PRFX_CAN                                "can: "
/* i2c errors */
#define PRFX_I2C                                "i2c: "
/* max31865 sensor errors */
#define PRFX_MAX31865                           "max31865: "
/* max31856 sensor errors */
#define PRFX_MAX31856                           "max31856: "
/* cnc errors */
#define PRFX_CNC                                "cnc: "
/* gcode parser & executor */
#define PRFX_GCODE                              "gcode: "

/* error strings */
static const char *err_str[] = {
    /* general errors */
    [-EOK] =
        "success",
    [-EFATAL] = 
        "fatal error",
    [-EBUSY] = 
        "resource busy",
    [-EARGVAL] = 
        "invalid argument value",
};

/* return the error string for given error code (or empty string 
 * if not found) */
const char * strerr(err_t ec) 
{   
    /* we use negative error codes in the system, so lets negate */
    ec = -ec;
    /* outside the boundaries? */
    if (ec < 0 || ec >= (int)elems(err_str))
        return "unknown error";
    /* no valid error string? */
    if (!err_str[ec])
        return "unknown error";
    /* got valid error string */
    return err_str[ec];
}

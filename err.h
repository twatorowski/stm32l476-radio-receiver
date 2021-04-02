/**
 * @file err.h
 * 
 * @date 2020-03-12
 * @author twatorowski 
 * 
 * @brief Error codes definitions
 */

#ifndef ERR_H
#define ERR_H

#include <stdint.h>

/** error codes present in system */
typedef enum err {
    /** secure the size of enum */
    _MAX_VAL = INT_FAST32_MAX,
    /* general errors */
    /** no error */
    EOK = 0,
    /** fatal error */
    EFATAL = -1,
    /** resource busy */
    EBUSY = -2,
    /** argument value error */
    EARGVAL = -3,
    /** routine is to be called again (polled upon) */
    EAGAIN = -4,
    /** task cancelled */
    ETIMEOUT = -5,

    /** operating system errors */
    /** task cancelled */
    ECANCEL = -10
} err_t;


#endif /** ERR_H */

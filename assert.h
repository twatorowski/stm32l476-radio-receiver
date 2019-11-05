/**
 * @file assert.h
 * 
 * @date 2019-10-09
 * @author your name (you@domain.com)
 * 
 * @brief 
 */

#ifndef ASSERT_H_
#define ASSERT_H_

#include "util/concatstr.h"

#define DEBUG
#include "debug.h"

/* assert message prefix */
#define ASSERT_MSG_PRFX                                         \
    "[" __FILE__ ":" CONCATSTR(__LINE__) "] "

/** @brief assert check implementation. If condition is not met then an endless 
 * loop will be executed
 * 
 * @param x condition to be checked
 * */
#define assert(x, msg)                                          \
    /* protect from compilers */                                \
    do {                                                        \
        /* check condition */                                   \
        if (!(x)) {                                             \
            /* set the assert message */                        \
            debug_assert_info.message = ASSERT_MSG_PRFX msg;    \
            /* set the debug information as valid */            \
            debug_assert_info.valid = DEBUG_VALID_ENTRY;        \
            /* endless loop */                                  \
            while(1);                                           \
        }                                                       \
    } while(0)                                 


#endif /* ASSERT_H_ */
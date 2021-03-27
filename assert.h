/**
 * @file assert.h
 * 
 * @date 2019-10-09
 * @author your name (you@domain.com)
 * 
 * @brief Assertion
 */

#ifndef ASSERT_H_
#define ASSERT_H_

#include "compiler.h"
#include "reset.h"
#include "util/concatstr.h"

/** @brief assert message prefix */
#define ASSERT_MSG_PRFX                                         \
    "[" __FILE__ ":" CONCATSTR(__LINE__) "] "

/** @brief assert check implementation. If condition is not met then an endless 
 * loop will be executed
 * 
 * @param x condition to be checked
 * @param msg constant message pointer to be stored in the within error 
 * reporting placeholder
 * @param info additional pointer info 
 * */
#define assert(x, msg, info)                                    \
    /* protect from compilers */                                \
    do {                                                        \
        /* check condition */                                   \
        if (!(x)) {                                             \
            /* reset the mcu */                                 \
            Reset_ResetMCU();                                   \
        }                                                       \
    } while (0)


#endif /* ASSERT_H_ */
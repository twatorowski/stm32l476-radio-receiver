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

/** @brief assert check implementation. If condition is not met then an endless 
 * loop will be executed
 * 
 * @param x condition to be checked
 * */
#define assert(x)                               \
    /* protect from compilers */                \
    do {                                        \
        /* check condition */                   \
        if (!(x))                               \
            /* endless loop */                  \
            while(1);                           \
    } while(0);                                 


#endif /* ASSERT_H_ */
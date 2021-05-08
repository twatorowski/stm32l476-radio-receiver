/**
 * @file delay.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief simple delay function
 */
#ifndef _SYS_DELAY_H
#define _SYS_DELAY_H

#include <stdint.h>

/**
 * @brief Block execution for us microseconds
 * 
 * @param us number of microseconds to block for
 */
void Delay(uint32_t us);


#endif /* _SYS_DELAY_H */

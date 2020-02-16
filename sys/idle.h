/**
 * @file idle.h
 * 
 * @date 2020-02-15
 * @author twatorowski 
 * 
 * @brief Idle mode support
 */

#ifndef SYS_IDLE_H
#define SYS_IDLE_H

/* initialize idle mode monitor */
int Idle_Init(void);

/* polling in idle mode */
void Idle_Poll(void);

#endif /* SYS_IDLE_H */

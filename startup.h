/**
 * @file startup.h
 * 
 * @date 2019-09-19
 * @author twatorowski (tw@mightydevices.com)
 * 
 * @brief MCU startup routines. This is where the story starts
 */

#ifndef STARTUP_H_
#define STARTUP_H_

/**
 * @brief first function to be executed after the reset. Shall initialize the 
 * chip to it's default state
 */
void Startup_ResetHandler(void);

#endif /* STARTUP_H_ */

/**
 * @file display.h
 * 
 * @date 2019-11-06
 * @author twatorowski 
 * 
 * @brief CD Multi-segment display driver. Drives the stm32l4-discover on-board 
 * display. Uses LSE clock.
 */

#ifndef DEV_DISPLAY_H_
#define DEV_DISPLAY_H_

/**
 * @brief Initialize the display module
 * 
 * @return int status (@ref ERR_ERROR_CODES)
 */
int Display_Init(void);

/**
 * @brief Sets the display to ekhm... display a character at given position. 
 * The display contents will get updated after the Display_Update() gets called.
 * 
 * @param pos position that is about to get changed
 * @param c character value
 */
void Display_SetCharacter(int pos, char c);

/**
 * @brief Transfers the LCD RAM contents to the Display itself
 */
void Display_Update(void);

#endif /* DEV_DISPLAY_H_ */

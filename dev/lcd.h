/**
 * @file lcd.h
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-17
 * 
 * @brief 
 */

#ifndef _DEV_LCD_H
#define _DEV_LCD_H

#include <stdint.h>
#include <stddef.h>

#include "err.h"

/** 8 rows of pixels of character data*/
typedef struct { 
    /* row data, encoded in least significant 5 bits per row */
    uint8_t data[8];
} lcd_char_data_t;

/**
 * @brief initialize the communication interface
 * 
 * @return err_t 
 */
err_t LCD_Init(void);

/**
 * @brief Enters 4 bit mode, setups auto-increment cursor mode
 * 
 * @return err_t status
 */
err_t LCD_Initialize(void);

/**
 * @brief Enable the display
 * 
 * @return err_t status
 */
err_t LCD_SetDisplayOn(void);

/**
 * @brief Clears display data
 * 
 * @return err_t status
 */
err_t LCD_Clear(void);

/**
 * @brief Sets current position of the cursor
 * 
 * @param row row number (0-1)
 * @param col column number (0-15)
 * 
 * @return err_t 
 */
err_t LCD_SetCursorPos(int row, int col);

/**
 * @brief write characters to display memory
 * 
 * @param ptr character array
 * @param size size of the data array
 * 
 * @return err_t status
 */
err_t LCD_WriteData(const void *ptr, size_t size);

/**
 * @brief Store new character within the displays cg ram
 * 
 * @param pos position to store to
 * @param cd character data
 *  
 * @return err_t status code
 */
err_t LCD_StoreCustomCharacter(int pos, const lcd_char_data_t *cd);


#endif /* _DEV_LCD_H */

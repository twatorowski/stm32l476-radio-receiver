/**
 * @file lcd_keypad.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-18
 * 
 * @brief Test for lcd and keys module
 */

#include "err.h"
#include "dev/lcd.h"
#include "dev/keypad.h"
#include "sys/yield.h"
#include "sys/sleep.h"
#include "util/string.h"

/* test for the lcd keypad module */
static void TestLCDKeypad_Test(void *arg)
{
    /* mask of the keys being pressed */
    keypad_key_mask_t keys;
    /* string to be displayed */
    const char *str;

    /* endless update loop */
    while (1) {
        /* read the key status */
        Keypad_GetKeyStatus(&keys);
        /* determine the string to be displayed */
        switch (keys) {
        case KEYPAD_KEY_MASK_DOWN : str = "down"; break;
        case KEYPAD_KEY_MASK_UP : str = "up"; break;
        case KEYPAD_KEY_MASK_LEFT : str = "left"; break;
        case KEYPAD_KEY_MASK_RIGHT : str = "right"; break;
        case KEYPAD_KEY_MASK_SELECT : str = "select"; break; 
        default : str = "unknown/none"; break;
        }
        /* put the data onto the display */
        LCD_Clear();
        LCD_SetCursorPos(0, 0);
        LCD_WriteData(str, strlen(str));
        /* sleep before the next update */
        Sleep(200);
    }
}

/* initialize test */
err_t TestLCDKeypad_Init(void)
{
    /* create the task */
    Yield_CreateTask(TestLCDKeypad_Test, 0, 1024);
    /* report status */
    return EOK;
}

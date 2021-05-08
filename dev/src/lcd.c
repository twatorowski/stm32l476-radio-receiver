/**
 * @file lcd.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-04-17
 * 
 * @brief Driver for the  lcd that comes with the LCD Keypad Shield
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "compiler.h"
#include "err.h"
#include "dev/lcd.h"
#include "dev/gpio.h"
#include "sys/critical.h"
#include "sys/delay.h"
#include "sys/sleep.h"
#include "util/elems.h"

/* pin definitions */
static const struct {
    gpio_t *gpio; gpio_pin_t pin;
/* specifications for the pins */
} E = {GPIOD, 15}, RS = {GPIOF, 3}, D4 = {GPIOE, 14}, D5 = {GPIOE, 11}, 
    D6 = {GPIOE, 9}, D7 = {GPIOG, 12};

/* pulse the enable signal */
static void LCD_PulseEnable(void)
{
    /* wait */
    Delay(25); GPIO_Set(E.gpio, E.pin, 1);
    /* wait */
    Delay(25); GPIO_Set(E.gpio, E.pin, 0);
}

/* sets the data lines in given state */
static void LCD_SetDataLines(int value)
{
    /* d4-d6 are located on port b */
    GPIO_Set(D4.gpio, D4.pin, value & 1);
    GPIO_Set(D5.gpio, D5.pin, value & 2);
    GPIO_Set(D6.gpio, D6.pin, value & 4);
    /* d7 is located as port a */
    GPIO_Set(D7.gpio, D7.pin, value & 8);
}

/* send a single nibble of data through the lcd interface */
static void LCD_WriteNibble(int value)
{
    LCD_SetDataLines(value);
    LCD_PulseEnable();
}

/* send a byte of data through the lcd interface */
static void LCD_WriteByte(int value)
{
    /* upper nibble goes first */
    LCD_WriteNibble((value & 0xf0) >> 4);
    LCD_WriteNibble((value & 0x0f) >> 0);
}

/* enable/disable writing to command register */
static void LCD_CmdMode(int enable)
{
    /* additional delay for the line to settle */
    GPIO_Set(RS.gpio, RS.pin, !enable); Delay(25);
}

/* initialize the lcd driver */
err_t LCD_Init(void)
{
    /* enter critical section */
    Critical_Enter();

    /* data lines: d7, d6, d5, d4 */
    GPIO_CfgOutput(D4.gpio, D4.pin, GPIO_OTYPE_PP, 0);
    GPIO_CfgOutput(D5.gpio, D5.pin, GPIO_OTYPE_PP, 0);
    GPIO_CfgOutput(D6.gpio, D6.pin, GPIO_OTYPE_PP, 0);
    GPIO_CfgOutput(D7.gpio, D7.pin, GPIO_OTYPE_PP, 0);
    /* rs */
    GPIO_CfgOutput(RS.gpio, RS.pin, GPIO_OTYPE_PP, 1);
    /* e */
    GPIO_CfgOutput(E.gpio, E.pin, GPIO_OTYPE_PP, 0);

    /* exit critical section */
    Critical_Exit();

    /* initialize the display */
    LCD_Initialize();
    /* clear display contents */
    LCD_Clear();
    /* enable the display */
    LCD_SetDisplayOn();

    /* return status */
    return EOK;
}

/* enter 4-bit mode */
err_t LCD_Initialize(void)
{
    /* enter command mode */
    LCD_CmdMode(1);
    /* setup 4 bit mode */
    LCD_WriteByte(0x33);
    // /* setup 4 bit mode */
    LCD_WriteByte(0x32);
    /* delay of 5 ms is needed */
    Sleep(5);

    /* 4-bit mode - 2 line - 5x7 font. */
    LCD_WriteByte(0x28);
    /* automatic cursor increment */
    LCD_WriteByte(0x06);

    /* report status */
    return EOK;
}

/* set the display on */
err_t LCD_SetDisplayOn(void)
{
    /* enter command mode */
    LCD_CmdMode(1);
    /* display on, cursor: no blink*/
    LCD_WriteByte(0x0c);
    /* exit command mode */
    LCD_CmdMode(0);

    /* delay of 2ms is needed for this command to be processed */
    Sleep(2);

    /* return status */
    return EOK;
}

/* clear the display */
err_t LCD_Clear(void)
{
    /* enter command mode */
    LCD_CmdMode(1);
    /* setup 4 bit mode */
    LCD_WriteByte(0x01);
    /* exit command mode */
    LCD_CmdMode(0);

    /* delay of 2ms us is needed for this command to be processed */
    Sleep(2);

    /* return status */
    return EOK;
}

/* set the cursor position */
err_t LCD_SetCursorPos(int row, int col)
{
    /* sanity check */
    if (row < 0 || row > 2 || col < 0 || col > 15)
        return EFATAL;

    /* enter command mode */
    LCD_CmdMode(1);
    /* setup 4 bit mode */
    LCD_WriteByte(0x80 + 0x40 * row + col);
    /* exit command mode */
    LCD_CmdMode(0);

    /* delay of 220 us is needed for this command to be processed */
    Delay(220);

    /* return status */
    return EOK;
}

/* write character data to display memory */
err_t LCD_WriteData(const void *ptr, size_t size)
{
    /* byte-wise pointer */
    const uint8_t *p8 = ptr;

    /* exit command mode */
    LCD_CmdMode(0);
    /* upload bytes */
    for (size_t i = 0; i < size; i++)
        LCD_WriteByte(p8[i]);

    /* report status */
    return EOK;
}

/* store custom character within character memory */
err_t LCD_StoreCustomCharacter(int pos, const lcd_char_data_t *cd)
{
    /* sanity check */
    if (pos < 0 || pos > 7)
        return EARGVAL;

    /* enter command mode */
    LCD_CmdMode(1);
    /* set the character position */
    LCD_WriteByte(0x40 + pos * 8);
    /* exit command mode */
    LCD_CmdMode(0);

    /* delay of 220 us is needed for this command to be processed */
    Delay(220);

    /* store character data */
    for (int i = 0; i < elems(cd->data); i++)
        LCD_WriteByte(cd->data[i]);

    /* return status */
    return EOK;
}
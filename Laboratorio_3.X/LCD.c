/*
 * File:   LCD.c
 * Author: Daniel
 *
 * Created on 4 de febrero de 2021, 04:27 PM
 */

#define _XTAL_FREQ 4000000
#include <xc.h>

uint8_t initialLCD(void * iodata, uint8_t cols, uint8_t rows) {
    // Initialize IO pins
    lcdrows = rows;
    lcdcolumns = cols;

    // Initial delay after power-up
    __delay_ms(100);
    // Begin LCD controller Initialization (HD44780 page 45-46)
    lcd_command(E_FUNCTION_SET);
    __delay_ms(5);
    lcd_command(E_FUNCTION_SET);
    __delay_us(120);
    lcd_command(E_FUNCTION_SET);
    __delay_us(120);
    lcd_command(E_FUNCTION_SET | BIT_DL_DATALENGTH_8 | BIT_N_DISP_LINES_2 | BIT_F_FONT_5_10);
    __delay_us(50);
    // Configure display after power up
    lcd_command(E_DISPLAY_ON_OFF_CTRL | BIT_D_DISPLAY_OFF);
    delay_us(50);
    lcd_command(E_CLEAR_DISPLAY);
    delay_ms(2);
    lcd_command(E_ENTRY_MODE_SET | BIT_S_AUTOSCROLL_OFF | BIT_ID_INCREMENT_CURSOR);
    delay_us(50);

    return TRUE;
}

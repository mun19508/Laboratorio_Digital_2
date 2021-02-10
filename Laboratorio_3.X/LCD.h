/* 
 * File: LCD.h 
 * Author: electroSome & Embedded life
 * Bibliogra:
 * //https://electrosome.com/lcd-pic-mplab-xc8/
 * //https://embeddedlifehelp.blogspot.com/2015/03/c-code-to-convert-floating-point-value.html
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
//Se definen los puertos de la LCD
#define RS PORTDbits.RD0
#define EN PORTDbits.RD1
#define RW PORTDbits.RD2
#define D0 PORTAbits.RA0
#define D1 PORTAbits.RA1
#define D2 PORTAbits.RA2
#define D3 PORTAbits.RA3
#define D4 PORTAbits.RA4
#define D5 PORTAbits.RA5
#define D6 PORTAbits.RA6
#define D7 PORTAbits.RA7
//Autor electrosome
void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);
//Autor embedded life
void convert(char *data,float a, int place);

#endif	/* LCD_H */


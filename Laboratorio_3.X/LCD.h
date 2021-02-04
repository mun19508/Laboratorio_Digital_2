/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#define lcd_command( x ) lcd_send( x, FALSE )
uint8_t initialLCD(void);
#endif	/* XC_HEADER_TEMPLATE_H */


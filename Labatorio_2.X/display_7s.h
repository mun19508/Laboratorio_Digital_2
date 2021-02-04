/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef DISPLAY_7S_H
#define	DISPLAY_7S_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void separar_nibbles(uint8_t lectura, uint8_t nibble_deseado);
void tabla_7s(uint8_t nibbles);
void multiplex(uint8_t port, uint8_t cantidad_D7S);

#endif	/* DISPLAY_7S_H */


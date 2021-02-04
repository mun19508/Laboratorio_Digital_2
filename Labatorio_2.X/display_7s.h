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

void Nibbles_L(uint8_t datoL);
void Nibbles_H(uint8_t datoH);
void tabla7segmentos(uint8_t valor);
//uint8_t multiplex(uint8_t port, uint8_t cantidad_D7S);

#endif	/* DISPLAY_7S_H */


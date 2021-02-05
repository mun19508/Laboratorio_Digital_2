/*
 * File:   display_7s.h
 * Author: Daniel Mundo
 *Descripcion: Se definen los prototipos de funciones a emplear por la libreria.
 */

#ifndef DISPLAY_7S_H
#define	DISPLAY_7S_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void NibbleMS(uint8_t);
void NibbleLS(uint8_t );
void tabla7segmentos(uint8_t valor);

#endif	/* DISPLAY_7S_H */


/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_LIB_H
#define	ADC_LIB_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
void start_adc(uint8_t frec);
void Select_ch(uint8_t channel);

#endif	/* ADC_LIB_H */


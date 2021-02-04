#include "ADC_LIB.h"
void start_adc(uint8_t frec){
    ADCON0bits.ADON = 1;
    switch(frec){
        case 1: // Fosc/2
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 0;
        break;
        case 2: // Fosc/8
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 0;
        break;
        case 3: // Fosc/32
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 1;
        break;
        case 4: // FRC 
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 1;
        break;
    }
}
void Select_ch(uint8_t channel){
        switch(channel){
        case 0: // AN0
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;          
        break;
        case 1: // AN1
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;          
        break;
        case 2: // AN2
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;          
        break;
        case 3: // AN3
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;          
        break;
        case 4: // AN4
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;          
        break;
        case 5: // AN5
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;          
        break;
        case 6: // AN6
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;          
        break;
        case 7: // AN7
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;          
        break;
        case 8: // AN8
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;          
        break;
        case 9: // AN9
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;          
        break;
        case 10: // AN10
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;          
        break;
        case 11: // AN11
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;          
        break;
        case 12: // AN12
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;          
        break;
        case 13: // AN13
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;          
        break;
        case 14: // CVref
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;          
        break;
        case 15: // Fixed ref
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;          
        break;
    }
}
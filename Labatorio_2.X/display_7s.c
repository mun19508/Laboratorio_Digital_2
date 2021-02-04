/*
 * File:   display_7S.c
 * Author: Daniel
 *
 * Created on 3 de febrero de 2021, 10:09 PM
 */


#include "display_7s.h"



void tabla7segmentos(uint8_t valor) {
    switch (valor) {
        case 0:
            PORTC = 0b01110111;
            break;
        case 1:
            PORTC = 0b01000001;
            break;
        case 2:
            PORTC = 0b00111011;
            break;
        case 3:
            PORTC = 0b01101011;
            break;
        case 4:
            PORTC = 0b01001101;
            break;
        case 5:
            PORTC = 0b01101110;
            break;
        case 6:
            PORTC = 0b01111110;
            break;
        case 7:
            PORTC = 0b01000011;
            break;
        case 8:
            PORTC = 0b01111111;
            break;
        case 9:
            PORTC = 0b01101111;
            break;
        case 10:
            PORTC = 0b01011111;
            break;
        case 11:
            PORTC = 0b01111100;
            break;
        case 12:
            PORTC = 0b00110110;
            break;
        case 13:
            PORTC = 0b01111001;
            break;
        case 14:
            PORTC = 0b00111110;
            break;
        case 15:
            PORTC = 0b00011110;
            break;
    }
}

void derecho(uint8_t adcHs) {
    uint8_t temp = adcHs;
    temp = (temp >> 4);
    uint8_t nlh = (temp & 0b00001111);
    tabla7segmentos(nlh);
    return;
}
void izquierdo(uint8_t adcLs) {
    uint8_t nsl = (adcLs & 0b00001111);
    tabla7segmentos(nsl);
    return;
}




/*uint8_t multiplex(uint8_t port, uint8_t cantidad_D7S) {
    static uint8_t contador[] = {0x00,
        0x01,
        0x02,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80};
    if (port == contador[cantidad_D7S]) {
        port = 0;
    }
    if (port > 0) {
        port = (port << 1);
    }
    if (port == 0) {
        port++;
    }
    return port;
}*/
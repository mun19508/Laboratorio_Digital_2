/*
 * File:   display_7S.c
 * Author: Daniel
 *
 * Created on 3 de febrero de 2021, 10:09 PM
 */

#include <xc.h>
#include <stdint.h>
#include "display_7s.h"

void separar_nibbles(uint8_t lectura, uint8_t nibble_deseado) {
    uint8_t valor_D7S = 0;
    if (nibble_deseado == 0) {
        valor_D7S = (lectura && 0x0F);
    } else {
        valor_D7S = (lectura >> 4);
    }
    return valor_D7S;
}

void tabla_7s(uint8_t nibbles) {
    static uint8_t tabla_D7S[] = {0b01110111,
        0b01000001,
        0b00111011,
        0b01101011,
        0b01001101,
        0b01101110,
        0b01111110,
        0b01000011,
        0b01111111,
        0b01101111,
        0b01011111,
        0b01111100,
        0b00110110,
        0b01111001,
        0b00111110,
        0b00011110};
    return tabla_D7S[nibbles];
}

void multiplex(uint8_t port, uint8_t cantidad_D7S) {
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
        contador++;
    }
    if (port == 0) {
        port++;
    }
    return port;
}
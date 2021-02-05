/*
 * File:   display_7S.c
 * Author: Daniel Mundo
 *Descripcion: Se definen la operaciones a realizar por las funciones previamente
 *             definidas en el archivo display_7.h
 */

#include "display_7s.h"

void tabla7segmentos(uint8_t valor) {//en este case se obtiene el valor que debe de
    switch (valor) {                //tener el puerto para mostrar los numeros en los display
        case 0: //0
            PORTC = 0b01110111;
            break;
        case 1: //1
            PORTC = 0b01000001;
            break;
        case 2: //2
            PORTC = 0b00111011;
            break;
        case 3: //3
            PORTC = 0b01101011;
            break;
        case 4: //4
            PORTC = 0b01001101;
            break;
        case 5: //5
            PORTC = 0b01101110;
            break;
        case 6: //6
            PORTC = 0b01111110;
            break;
        case 7: //7
            PORTC = 0b01000011;
            break;
        case 8: //8
            PORTC = 0b01111111;
            break;
        case 9: //9
            PORTC = 0b01101111;
            break;
        case 10: //A
            PORTC = 0b01011111;
            break;
        case 11: //b
            PORTC = 0b01111100;
            break; //C
        case 12:
            PORTC = 0b00110110;
            break;
        case 13: //d
            PORTC = 0b01111001;
            break;
        case 14: //E
            PORTC = 0b00111110;
            break;
        case 15: //F
            PORTC = 0b00011110;
            break;
    }
}

void NibbleMS(uint8_t adcMs) { //Se recupera el nibble mas significativo 
    uint8_t temp = adcMs;
    temp = (temp >> 4); //se realiza una especie de swap entre los nibbles
    uint8_t nlh = (temp & 0b00001111); //se realiza lo mismo que NibbleLS
    tabla7segmentos(nlh);
    return;
}
void NibbleLS(uint8_t adcLs) { //Se recupera el nibble menos significativo
    uint8_t nsl = (adcLs & 0b00001111);//se hace un "and" para mantener unicamente 
    tabla7segmentos(nsl);             //el nibble menos significativo
    return;
}

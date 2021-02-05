/*
 * File:   lab_2.c
 * Author: Daniel
 *
 * Created on 28 de enero de 2021, 05:36 PM
 */
//**********************************Librerias***********************************
#include <xc.h>
#include <stdint.h>
#include "ADC_LIB.h"
#include "display_7s.h"
//******************************************************************************
//***************************Bits de ConFig*************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
//******************************************************************************
//**************************Prototipos de Funciones*****************************
void configuracion(void);

//********************************Variables*************************************
volatile uint8_t display_adc;
uint8_t count;
uint8_t toogle = 0;
uint8_t antireb = 0;
uint8_t antireb_ant = 0;
//******************************************************************************
//******************************Interrupciones**********************************

void __interrupt() ISR(void) {
    if (PIR1bits.ADIF == 1) { //si la bandera del ADC se enciende
        PIR1bits.ADIF = 0;
        display_adc = ADRESH; //se guarda el valor convertido en la variable
        ADCON0bits.GO = 1;
    }
    if (INTCONbits.T0IF == 1) {// si la bandera del Timer 0 es 1
        PORTC = 0; 
        PORTE = 0; //Se asegura que los puertos esten limpios

        if (toogle == 0) { //debido a que solo hay dos Displays el contador solo puede
            NibbleMS(display_adc); //0 o 1.
            PORTEbits.RE0 = 1;
            toogle++; //se aumentar el contador para que en la sig ISR muestre el otro nibble
        } else {
            NibbleLS(display_adc);
            toogle--; //misma logica de la linea 56 de este archivo.
            PORTEbits.RE1 = 1;
        }
        TMR0 = 177; //se vuelve a iniciar el timer
        INTCONbits.T0IF = 0; 
    }
    if (INTCONbits.RBIF == 1) { //Se trabaja con botones en config. pull-up
        antireb = antireb_ant; 
        antireb_ant = PORTB;
        if ((antireb_ant & 0b00000011) == 3) { //Se asegura que B0 y B1 fueron soltados.
            if ((antireb & 0b00000011) == 2) {//Compruba si en la anterior interrupción B0 fue presionado.
                count++; 
                PORTD++; //Aumenta el valor del contador y del puerto
            }
            if ((antireb & 0b00000011) == 1) {//Compruba si en la anterior interrupción B1 fue presionado.
                count--;
                PORTD--; //Disminuye el valor del contador y del puerto
            }
        }
        INTCONbits.RBIF = 0;
    }
}
//******************************************************************************

void main(void) {
    //-----------------------Interrupciones---------------------------------
    INTCONbits.GIE = 1; //Se habilitan ISR globales.
    INTCONbits.PEIE = 1; //Se habilitan ISR perifericas.
    INTCONbits.T0IE = 1; //Se habilita la ISR del Timer 0.
    INTCONbits.T0IF = 0;
    INTCONbits.RBIE = 1; //Se habilita la ISR del por cambios.
    INTCONbits.RBIF = 0;
    IOCBbits.IOCB0 = 1; 
    IOCBbits.IOCB1 = 1; //Se habilita individualmente la lectura de los cambios.
    OPTION_REGbits.T0CS = 0;//Reloj interno
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 1;// Se configura un prescaler de 1/64
    TMR0 = 177;
    //--------------------------Canal Analogico---------------------------------
    ANSEL = 0;
    ANSELH = 0; //Puerto A y B como digitales
    start_adc(2, 1, 0, 0); //Fosc/8, Si ISR de ADC, Ref Vdd y Vcc, a la izquierda
    start_ch(8); //Habilita el pin del Puerto.
    Select_ch(8); //Selecciona el canal e inicia la conversion.
    //--------------------------Puerto Entrada/salida---------------------------
    TRISA = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0; //Puerto A, C, D & E como salidas 
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1; //Pines B0, B1 & B2 como entrada
    //-------------------------------Limpieza de puertos------------------------   
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0; //Se limpian los puertos
    while (1) {
        if (display_adc >= count) { // se comprueba si el valor del ADC es mayor o igual al del contador
            PORTEbits.RE2 = 1; //se enciende la alarma.
        } else {
            PORTEbits.RE2 = 0; //sino se apaga.
        }
    }
}

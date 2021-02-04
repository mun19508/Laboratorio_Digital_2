/*
 * File:   lab_2.c
 * Author: Daniel
 *
 * Created on 28 de enero de 2021, 05:36 PM
 */
#include <xc.h>
#include <stdint.h>
#include "ADC_LIB.h"

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

//**************************Prototipos de Funciones*****************************
void configuracion(void);

//********************************Variables*************************************
int start;
int J1 = 0;
int J2 = 0;
//******************************************************************************
//******************************Interrupciones**********************************
void __interrupt() ISR(void){

}
//******************************************************************************
void main(void) {
    configuracion();
}
void configuracion(void){
//--------------------------Canal Analogico-------------------------------------
    ANSEL = 0;   
    ANSELH = 0; //Puerto A y B como digitales
    ANSELHbits.ANS8 = 0;
    Select_ch(8);
//--------------------------Puerto Entrada/salida-------------------------------
    TRISA = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0; //Puerto A, C, D & E como salidas 
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1; //Pines B0, B1 & B2 como entrada
//-------------------------------Limpieza de puertos----------------------------    
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0; //Se limpian los puertos
}
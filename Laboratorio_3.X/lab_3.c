/*
 * File:   lab_3.c
 * Author: Daniel
 *
 * Created on 4 de febrero de 2021, 03:05 PM
 */
//**********************************Librerias***********************************
#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "ADC_LIB.h"
#define _XTAL_FREQ 4000000
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
//********************************Variable**************************************
uint8_t canal_act = 0;
volatile uint8_t var_adc0 = 0;
volatile uint8_t var_adc1 = 0;
char adc0[10];
char adc1[10];
float conv0 = 0;
float conv1 = 0;
//******************************************************************************
//**************************Prototipos de Funciones*****************************

//*****************************************************************************

void __interrupt() ISR(void) {

}

void main(void) {
    //-----------------------Interrupciones---------------------------------
    INTCONbits.GIE = 1; //Se habilitan ISR globales.
    INTCONbits.PEIE = 1; //Se habilitan ISR perifericas.
    INTCONbits.RBIF = 0;
    //--------------------------Canal Analogico---------------------------------
    ANSEL = 0;
    ANSELH = 0; //Puerto A y B como digitales
    start_adc(2, 0, 0, 0); //Fosc/8, No ISR de ADC, Ref Vdd y Vcc, a la izquierda
    start_ch(12); //Habilita el pin del Puerto RB0.
    start_ch(10); //Habilita el pin del Puerto RB1.
    Select_ch(12); //Selecciona el canal e inicia la conversion.
    //--------------------------Puerto Entrada/salida---------------------------
    TRISA = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0; //Puerto A, C, D & E como salidas 
    TRISB = 255;
    //-------------------------------Limpieza de puertos------------------------   
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0; //Se limpian los puertos
    //-------------------------------LCD----------------------------------------
    Lcd_Init(); //se inicia la configuración de la LCD
    Lcd_Clear();

    //--------------------------Loop principal----------------------------------
    while (1) {
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("P1");
        Lcd_Set_Cursor(1, 8);
        Lcd_Write_String("P2");
        Lcd_Set_Cursor(1, 15);
        Lcd_Write_String("PC");
        if (PIR1bits.ADIF == 1) {
            if (canal_act == 0) {
                var_adc0 = ADRESH; //se guarda el valor convertido en la variable
                Select_ch(10);
                canal_act++;
            } else {
                var_adc1 = ADRESH; //se guarda el valor convertido en la variable
                Select_ch(12);
                canal_act--;
            }
            PIR1bits.ADIF = 0;
        }
        conv0 = 0;
        conv1 = 0;

        conv0 = (var_adc0 / (float) 255)*5;
        convert(adc0, conv0, 2);

        conv1 = (var_adc1 / (float) 255)*5;
        convert(adc1, conv1, 2);

        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(adc0);

        Lcd_Set_Cursor(2, 8);
        Lcd_Write_String(adc1);
        __delay_ms(20);
 
    }
}


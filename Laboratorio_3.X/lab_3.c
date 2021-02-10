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
#include "UART.h"
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
float cont_uart = 0;
char string_uart[10];
char valor_uart = 0;
char adc0[10];
char adc1[10];
float conv0 = 0;
float conv1 = 0;
//******************************************************************************
void main(void) {
    //--------------------------Canal Analogico---------------------------------
    ANSEL = 0;
    ANSELH = 0; //Puerto A y B como digitales
    start_adc(2, 0, 0, 0); //Fosc/8, No ISR de ADC, Ref Vdd y Vcc, a la izquierda
    start_ch(12); //Habilita el pin del Puerto RB0.
    start_ch(10); //Habilita el pin del Puerto RB1.
    Select_ch(12); //Selecciona el canal e inicia la conversion.
    //--------------------------Comunicacion UART-------------------------------
    UARTInit(9600, 1);
    //--------------------------Puerto Entrada/salida---------------------------
    TRISA = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
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
        Lcd_Write_String("S1:");
        Lcd_Set_Cursor(1, 8);
        Lcd_Write_String("S2:");
        Lcd_Set_Cursor(1, 15);
        Lcd_Write_String("S3:");
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
        if (UARTDataReady()) { //se comprueba si el valor ingresado hace que el contador
            valor_uart = UARTReadChar();
            if (valor_uart == '+') { //aumente si es el caracter "+"
                cont_uart++; 
            } else if (valor_uart == '-') {//disminuya si es el caracter "-"
                cont_uart--;
            }
        }

        conv0 = 0;//se reinicia las cada ves que se inicia el proceso de enviar datos
        conv1 = 0;//tanto para la LCD como por UART.
//------------------------Mostrar datos via UART--------------------------------
        //-----------------------------Sensor 1---------------------------------
        conv0 = (var_adc0 / (float) 255)*5; //Se consigue el porcentaje con respecto al valor 
       //maximo que un puerto puede tener, despues se multiplica por 5 para conocer el voltaje actual del puerto                                          
        convert(adc0, conv0, 2);//se convierte el valor actual a un valor ASCII.
        UARTSendString("|", 3);
        UARTSendString("S1", 6);
        UARTSendString(":", 3);
        UARTSendString(" ", 3);
        UARTSendString(adc0, 6);
        UARTSendString("V", 3);
        UARTSendString(",", 3);
        UARTSendString(" ", 3);
        //-----------------------------Sensor 2---------------------------------
        conv1 = (var_adc1 / (float) 255)*5; //misma logica que conv0
        convert(adc1, conv1, 2);
        UARTSendString("S2", 6);
        UARTSendString(":", 3);
        UARTSendString(" ", 3);
        UARTSendString(adc1, 6);
        UARTSendString("V", 3);
        UARTSendString("|", 3);
        UARTSendString(" ", 3);
        //---------------------Sensor 3(contador)-------------------------------
        convert(string_uart, cont_uart, 1);
//-----------------------Mostrar datos en la LCD--------------------------------
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(adc0);
        Lcd_Set_Cursor(2, 5);
        Lcd_Write_String("V");

        Lcd_Set_Cursor(2, 7);
        Lcd_Write_String(adc1);
        Lcd_Set_Cursor(2, 11);
        Lcd_Write_String("V");

        Lcd_Set_Cursor(2, 15);
        Lcd_Write_String(string_uart);
        __delay_ms(20);

    }
}


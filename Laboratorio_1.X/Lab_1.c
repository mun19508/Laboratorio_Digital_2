/*
 * File:   Lab_1.c
 * Author: Daniel Mundo
 *
 * Created on 21 de enero de 2021, 06:08 PM
 */


#include <xc.h>
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
//****************************Frecuencia***************************************
#define _XTAL_FREQ 4000000
//**************************Prototipos de Funciones*****************************
void config(void);
void semaforo(void);
//********************************Variables*************************************
int start = 0; //Utilizada para indicar si la carrera comenzo.
int J1 = 0; //Es el contador del jugador 1.
int J2 = 0; //Es contador del jugador 2.
//******************************************************************************

void main(void) {
    config();
    while (1) {
        if (PORTBbits.RB0 == 0 && start == 0) { //Se comprueba si el boton fue 
            __delay_us(150); //presionado.
            if (PORTBbits.RB0 == 1) { //Se asegura que el boton se solto
                PORTE = 0; //Se asegura que el LED que indica al ganador este apagado 
                J1 = 0;
                J2 = 0; //se asegura que los contadores esten en 0.
                semaforo();
                start = 1; //se indica que la carrera comenzo.
            }
        }
        if (PORTBbits.RB1 == 0 && start == 1) { //Misma logica que el boton que
            __delay_us(150); //esta en RB0
            if (PORTBbits.RB1 == 1) {
                if (J1 == 0) { //Al momento de comenzar la carrera unicamente 
                    J1++; //se incrementa el puerto y el contador.
                    PORTAbits.RA0 = 1;
                } else { //En caso sea la segunda vez que se presiona el boton
                    PORTA = (PORTA << 1); //tras iniciada la carrera, se incrementa
                    J1++; //el contador y se rota a la izquierda el
                } //valor del puerto.
            }
        }
        if (PORTBbits.RB2 == 0 && start == 1) {//La logica es la misma que el boton
            __delay_us(150); //que esta en RB0.
            if (PORTBbits.RB2 == 1) {//Es la misma logica que el boton de RB1.
                if (J2 == 0) {
                    J2++;
                    PORTCbits.RC0 = 1;
                } else {
                    PORTC = (PORTC << 1);
                    J2++;
                }
            }
        }
        if (J1 == 8 || J2 == 8) {//Si alguno de los contadores llega a 8
            if (J1 == 8) { //se enciende el Led correspondiente a quien haya llegado  
                PORTEbits.RE0 = 1; //primero.
            } else {//Esta rutina unicamente se realiza si uno de los contadores 
                PORTEbits.RE1 = 1; //igual a 8, por ello si J1 no llega a 8 J2 fue
            }//el que llego.
            PORTA = 0;
            PORTC = 0;
            start = 0; //Se regresa al estado inicial
        }
    }
}

void semaforo(void) {
    PORTDbits.RD0 = 1; //Al momento de que la funcion es llamada
    PORTDbits.RD1 = 0; //empieza la cuenta regresiva enciendo primero
    PORTDbits.RD2 = 0; //el LED color rojo.
    __delay_ms(250); //se espera una cierta cantidad de tiempo.
    PORTDbits.RD0 = 0; //Despues encendiendo el LED color amarillo.
    PORTDbits.RD1 = 1;
    PORTDbits.RD2 = 0;
    __delay_ms(250);
    PORTDbits.RD0 = 0; //Por ultimo se enciende el led color verde.
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 1;
    __delay_ms(250);
}

void config(void) {
    ANSEL = 0;
    ANSELH = 0; //Puerto A & B como digitales
    TRISA = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0; //Puerto A, C, D & E como salidas 
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1; //Pines B0, B1 & B2 como entrada
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0; //Se limpian los puertos
}
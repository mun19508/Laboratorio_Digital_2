/********************************************
 *Autor: Daniel Mundo                       *
 *Carnet:19508                              *
 *Nombre del archivo: main.c                *
 *Archivo compilable                        *
 ********************************************
 *              Librerias                   *
 ********************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
/********************************************
 *           Prototipo de funciones         *
 ********************************************/
void toggle1Hz(void);

/********************************************
 *                  Variables               *
 ********************************************/
uint32_t LoadTime;
uint32_t Option;
uint32_t LedR = 0;
uint32_t LedB = 0;
uint32_t LedG = 0;
uint32_t FlagR = 0;
uint32_t FlagB = 0;
uint32_t FlagG = 0;
/********************************************/
int main(void)
{   /*************Parte 2:******************/
    /*Config. del reloj para freq. de 40MHz*/
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    LoadTime = SysCtlClockGet();
    /*Habilita puerto F*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    /*Habilita Timer 0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    /*Se config. los pines de los leds como salidas*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);
    /*Se config. el timer 0 como timer de 32 bits*/
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    /*************Parte 4:******************/
    /*Se carga el valor para que la interrupcion suceda cada 1s*/
    TimerLoadSet(TIMER0_BASE, TIMER_A, LoadTime - 1);
    /*Se habilita la interrupcion del timer0*/
    IntEnable(INT_TIMER0A);
    /*Se config. la interrupcion para que suceda cada vez que haya desborde en el timer0*/
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    /*Se inicia el timer*/
    TimerEnable(TIMER0_BASE, TIMER_A);
    /*************Parte 5:******************/
    /*Habilita puerto A*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    /*Habilita el modulo de UART0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    /* Hacer que el modulo UART0 controle los pines del puerto A*/
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    /* Config. el modulo UART0*/
    UARTConfigSetExpClk(
            UART0_BASE, LoadTime, 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    /*Se habilita el UART0*/
    UARTEnable(UART0_BASE);
    /*Se habilita la interrupcion del UART0*/
    IntEnable(INT_UART0);
    /*Se config. la interrupcion para que suceda cada vez que entran datos*/
    UARTIntEnable(UART0_BASE, UART_INT_RX);
    /*Se inician todas las interrupciones*/
    IntMasterEnable();
    while (1)
    {   /*Se revisa si desde la terminal se recibio una 'r'*/
        if (FlagR == 1)
        {/*Se habilita el toogle del led rojo*/
            LedR = 1;
        }/*Se revisa si nuevamente se recibio una 'r'*/
        if (FlagR > 1)
        {/*Se inhabilita el toogle del led rojo*/
            LedR = 0;
            FlagR = 0;
        }/*Se revisa si desde la terminal se recibio una 'b'*/
        if (FlagB == 1)
        {/*Se habilita el toogle del led azul*/
            LedB = 1;
        }/*Se revisa si nuevamente se recibio una 'b'*/
        if (FlagB > 1)
        {/*Se inhabilita el toogle del led azul*/
            LedB = 0;
            FlagB = 0;
        }/*Se revisa si desde la terminal se recibio una 'g'*/
        if (FlagG == 1)
        {/*Se habilita el toogle del led verde*/
            LedG = 1;
        }/*Se revisa si nuevamente se recibio una 'g'*/
        if (FlagG > 1)
        {/*Se inhabilita el toogle del led verde*/
            LedG = 0;
            FlagG = 0;
        }
    }
}
void Timer0IntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    /*Se realizan los toogles a los leds que los tenga habilitados*/
    if (LedR == 1)
    {/*Cada vez que sucede una interrupcion se invierte la señal*/
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,
                     ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
    }
    if (LedB == 1)
    {/*Misma logica de arriba*/
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,
                     ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2));
    }
    if (LedG == 1)
    {/*Misma logica de arriba*/
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,
                     ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3));
    }
}
void UARTIntHandler(void)
{
    UARTIntClear(UART0_BASE, UART_INT_RX);
    Option = UARTCharGetNonBlocking(UART0_BASE);
    /*Se revisa que caracter se recibio*/
    if (Option == 'r')
    {
        FlagR++;
    }
    if (Option == 'b')
    {
        FlagB++;
    }
    if (Option == 'g')
    {
        FlagG++;
    }
}

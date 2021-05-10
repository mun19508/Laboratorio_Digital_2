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
/********************************************
 *           Prototipo de funciones         *
 ********************************************/
void toggle1Hz(void);
/********************************************/
int main(void)
{   //Parte 2:
    SysCtlClockSet(
            SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN); //Config. del reloj a 40 MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF|SYSCTL_PERIPH_TIMER0);   //Habilita el puerto F & el timer 0
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
                          GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1); //Los pines de los habilitados como salidas
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
}
/********************************************
 *              Subrutinas                  *
 ********************************************/

/*UVG
 *Autor: Daniel Mundo
 *Carnet:19508
 *Nombre del archivo: main.c
 */
/**************************
 * Librerias              *
 **************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
/**************************
 * Prototipo de funciones *
 **************************/
int main(void)
{
//Parte 2: Configuración del reloj
    //Setting divider 5
    //Se utiliza PLL
    //La frecuencia del cristal es de 16MHz
    //Se asigna el reloj al sistema
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}

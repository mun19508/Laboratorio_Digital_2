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
void semaforo(void);
void delayManual(void);
/**************************/
int main(void)
{
//Parte 2: Configuración del reloj
    //Setting divider 5
    //Se utiliza PLL
    //La frecuencia del cristal es de 16MHz
    //Se asigna el reloj al sistema
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //Parte 3: Configuracion de Puertos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);   //habilita el puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1); //se habilitan como salida los pines de los leds (ledG|ledB|ledR)
    semaforo();//funcion de semaforo version 1
}
/*******Subrutinas*******/
void semaforo(void){
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 2); //enciende led rojo
    delayManual();
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
    delayManual();
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 10); //enciende led amarillo
    delayManual();
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
    delayManual();
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 8); //enciende led verde
    delayManual();
    int i;
    for(i = 0; i < 8; i++){
        delayManual();
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
        delayManual();
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 8); //enciende led verde
    }
}
void delayManual(void){
    uint32_t j;
    for(j=0; j<2000000; j++){}
}


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
/*Parte 2: Configuración del reloj
  Setting divider 5
  Se utiliza PLL
  La frecuencia del cristal es de 16MHz
  Se asigna el reloj al sistema*/
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //Parte 3: Configuracion de Puertos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);   //habilita el puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1); //se habilitan como salida los pines de los leds (ledG|ledB|ledR)
    /*********************Parte 4: Configuracion de botones**********************/
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); //se configura el pin SW1 de la TivaC como entrada
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU); //con pull-upp
    uint32_t actual = 16;
    uint32_t anterior = 16;

    while(1){
    anterior = actual;
    actual= GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4); //la funcion puede devolver 0 o 16, ya que 2**4=16
    if(anterior == 0 && actual == 16)semaforo();//funcion de semaforo, v2.0
    }
}
/********************************Subrutinas************************************************/
void semaforo(void){
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 8); //enciende led verde
    SysCtlDelay(20000000); //delay aprox. 1.5s
    int i;
    for(i = 0; i < 8; i++){
        SysCtlDelay(2000000); //delay aprox 0.15s
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
        SysCtlDelay(2000000); //delay aprox 0.15s
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 8); //enciende led verde
    }
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
    SysCtlDelay(20000000); //delay aprox. 1.5s
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 10); //enciende led amarillo
    SysCtlDelay(20000000); //delay aprox. 1.5s
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
    SysCtlDelay(20000000); //delay aprox. 1.5s
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 2); //enciende led rojo
    SysCtlDelay(20000000); //delay aprox. 1.5s
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0); //apaga led
}
void delayManual(void){
    uint32_t j;
    for(j=0; j<2000000; j++){} //el delay es de aprox. 50ms
}

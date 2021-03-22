/*Autor: Daniel Mundo
   Carnet
*/
#define BotonJ1 PF_4 //Pin 31
#define BotonJ2 PF_0 //Pin 17
#define StartRace PD_7 //Pin 32

int LED_J1[] = {PB_5, PB_0, PB_1, PE_4, PE_5, PB_4, PA_5, PA_6}; //Arreglo con el fin de simular un puerto

void setup() {
  // put your setup code here, to run once:
  //------------LED's del semaforo---------------------------
  pinMode(GREEN_LED, OUTPUT); //Pin 39
  pinMode(RED_LED, OUTPUT);  //Pin 30
  pinMode(BLUE_LED, OUTPUT); //Pin 40
  //-------------------Botones-------------------------------
  pinMode(StartRace, INPUT_PULLUP); //Boton para inicio de carrera en la proto
  pinMode(BotonJ1, INPUT_PULLUP); //Boton para J1 en la tiva
  pinMode(BotonJ2, INPUT_PULLUP); //Boton para J2 en la tiva
  //------------Contodor del J1-----------------------------
  for(int i= 0; i<9; i++){
    pinMode(LED_J1[i], OUTPUT); //Se habilita toda el arreglo como salida
    }
  /*pinMode(); //Pin
    pinMode(); //Pin
    pinMode(); //Pin
    pinMode(); //Pin
    pinMode(); //Pin
    pinMode(); //Pin
    pinMode(); //Pin
    pinMode(); //Pin*/
}

void loop() {
  // put your main code here, to run repeatedly:
  semaforo();
}
void semaforo(void){
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  }

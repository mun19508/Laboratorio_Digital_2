/*
   Autor: Daniel Mundo
   Carnet: 19508
   Titulo: Juego de Carreras
   Descripcion: Hay dos botenes con los cuales se aumentan un contador de decadas, además ambos botones
   de la Tiva C pueden comenzar la carrera. 
*/
#define BotonJ1 PD_7 //Pin 32
#define BotonJ2 PA_2 //Pin 12
#define antirebDelay 10

//-----------------------------Puertos-------------------------------
int LED_J1[] = {PB_5, PB_0, PB_1, PE_4, PE_5, PB_4, PA_5, PA_6, PA_7}; //Arreglo con el fin de simular un puerto
int LED_J2[] = {PA_3, PE_3, PE_2, PE_1, PD_3, PD_2, PD_0, PD_1, PD_6}; //Arreglo con el fin de simular un puerto
//------------------------Antirebote---------------------------------
int AntiRebRace[] = {1, 1, 1, 1}; //{estado_anterior_SW1, estado_actual_SW1, estado_anterior_SW2, estado_actual_SW2}
int AntiRebPlayer[] = {1, 1, 1, 1}; //{estado_anterior_J1, estado_actual_J1, estado_anterior_J2, estado_actual_J2}
unsigned long timePush[] = {0, 0};
unsigned long timeJ12[] = {0, 0};
int debounceRace[] = {1, 1, 1, 1};//Para los debounceRace... la posicion 0 y 2 sirven para comprobar si se presiono el boton,
int debouncePlayer[] = {1, 1, 1, 1}; //mientras que la pos. 1 y 3 son para comprobar que el boton se haya soltado
//-----------------------Contadores-------------------------
int count[] = {0, 0}; //la pos. 0 es para J1 y la pos. 1 para J2

void setup() {
  // put your setup code here, to run once:
  //------------LED's del semaforo---------------------------
  pinMode(GREEN_LED, OUTPUT); //Pin 39
  pinMode(RED_LED, OUTPUT);  //Pin 30
  pinMode(BLUE_LED, OUTPUT); //Pin 40
  //-------------------Botones-------------------------------
  // pinMode(StartRace, INPUT_PULLUP); //Boton para inicio de carrera en la proto
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(BotonJ1, INPUT_PULLUP); //Boton para J1
  pinMode(BotonJ2, INPUT_PULLUP); //Boton para J2
  //------------Contodor del J1-----------------------------
  for (int i = 0; i < 9; i++) {
    pinMode(LED_J1[i], OUTPUT); //Se habilita toda el arreglo como salida
    pinMode(LED_J2[i], OUTPUT); //Se habilita toda el arreglo como salida
  }
}

void loop() {
  //Se guarda el valor leido anteriormente en el pin del boton
  AntiRebRace[0] = AntiRebRace[1];
  AntiRebRace[1] = digitalRead(PUSH1);
  AntiRebRace[2] = AntiRebRace[3];
  AntiRebRace[3] = digitalRead(PUSH2);

  //Se comprueba si hubo algun cambio con respecto al valor del anterior
  if (AntiRebRace[0] != AntiRebRace[1]) timePush[0] = millis();
  if (AntiRebRace[2] != AntiRebRace[3]) timePush[1] = millis();

  //Se espera un tiempo y se guarda el valor obtenido en el anterior loop
  if ((millis() - timePush[0]) > antirebDelay) {
    debounceRace[0] =  debounceRace[1];
    debounceRace[1] = AntiRebRace[1];
  }
  if ((millis() - timePush[1]) > antirebDelay) {
    debounceRace[2] =  debounceRace[3];
    debounceRace[3] = AntiRebRace[3];
  }

  //Se comprueba si ya se solto el boton, de ser asi se espera que el pin del boton lea 1
  if ((debounceRace[0] != debounceRace[1]) && debounceRace[1] == 1 || (debounceRace[2] != debounceRace[3]) && debounceRace[3] == 1) {
    //Se inicia la funcion de semaforo, se reinician los puertos y contadores
    semaforo();
    for (int j = 0; j < 9; j++) {
      digitalWrite(LED_J1[j], LOW);
      digitalWrite(LED_J2[j], LOW);
    }
    count[0] = count[1] = 0;
    //-----------Comienza la carrera-------------------
    while (count[0] < 9 && count[1] < 9) {
      race();
    }
  }
}
//------------Definicion de Funciones----------------
void contadorLedJ1(int c) {
  int a = c - 1;
  if (a >= 0) {
    for (int i = 0; i < 9; i++) {
      digitalWrite(LED_J1[i], LOW); //Se apagan todas las Leds
    }
    digitalWrite(LED_J1[a], HIGH); //se enciende unicamente la que se requiere
  }
}

void contadorLedJ2(int c) {
  int a = c - 1;
  if (a >= 0) {
    for (int i = 0; i < 9; i++) {
      digitalWrite(LED_J2[i], LOW); //Se habilita toda el arreglo como salida
    }
    digitalWrite(LED_J2[a], HIGH);
  }
}

void race(void) {
  //Se guarda el valor leido anteriormente en el pin del boton
  AntiRebPlayer[0] = AntiRebPlayer[1];
  AntiRebPlayer[1] = digitalRead(BotonJ1);
  AntiRebPlayer[2] = AntiRebPlayer[3];
  AntiRebPlayer[3] = digitalRead(BotonJ2);

  //Se comprueba si hubo algun cambio con respecto al valor del anterior
  if (AntiRebPlayer[0] != AntiRebPlayer[1]) timeJ12[0] = millis();
  if (AntiRebPlayer[2] != AntiRebPlayer[3]) timeJ12[1] = millis();

  //Se espera un tiempo y se guarda el valor obtenido en el anterior loop
  if ((millis() - timeJ12[0]) > antirebDelay) {
    debouncePlayer[0] =  debouncePlayer[1];
    debouncePlayer[1] = AntiRebPlayer[1];
  }
  if ((millis() - timeJ12[1]) > antirebDelay) {
    debouncePlayer[2] =  debouncePlayer[3];
    debouncePlayer[3] = AntiRebPlayer[3];
  }

  //Se comprueba si ya se solto el boton, de ser asi se espera que el pin del boton lea 1
  if ((debouncePlayer[0] != debouncePlayer[1]) && debouncePlayer[1] == 1) {
    count[0]++; //se incrementa el contador del jugador 1
  }

  if ((debouncePlayer[2] != debouncePlayer[3]) && debouncePlayer[3] == 1) {
    count[1]++; //se incrementa el contador del jugador 2
  }

  //Se llama a la funcion para encender el Led correspondiente
  contadorLedJ1(count[0]);
  contadorLedJ2(count[1]);
}

void semaforo(void) {
  digitalWrite(RED_LED, HIGH); //Se enciende el led rojo para marcar el comienzo de la cuenta regresiva. 
  digitalWrite(GREEN_LED, LOW); //Se asegura que el led verde este apagado.
  delay(1000);
  digitalWrite(GREEN_LED, HIGH); //Al encenderse el verde y rojo al mismo tiempo se obtiene el color amarillo.
  delay(1500);
  digitalWrite(RED_LED, LOW);//Unicamente se deja encendido el led verde.
}

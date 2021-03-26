
#include <SPI.h>
#include <SD.h>

File root;
char opcion = '0';
uint8_t control = 0;
char inByte;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  SPI.setModule(0);


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");



  Serial.println("done!");
}

void loop()
{
  if (control == 0) {
    root = SD.open("/");
    printDirectory(root, 0);
    Serial.println("Escriba la posicion del archivo que desea ver: ");
    control++;
  }
  if (Serial.available()) {
    inByte = Serial.read();
  }
  if (inByte == '1') {
    opcion = '1';
    control--;
  }
  if (inByte == '2') {
    opcion = '2';
    control--;
  }
  if (inByte == '3') {
    opcion = '3';
    control--;
  }
  readText(opcion);
  opcion = '0';
}


//laboratorio parte 2
void readText(char dir) {
  uint8_t seleccion;
  File archivo;
  switch (dir) {
    case '1':
      archivo = SD.open("ghost.txt");
      seleccion = 1;
      break;
    case '2':
      archivo = SD.open("pacman.txt");
      seleccion = 1;
      break;
    case '3':
      archivo = SD.open("spider.txt");
      seleccion = 1;
      break;
    default:
      seleccion = 0;
      break;
  }
  if (seleccion == 1) {
    if (archivo) {
      Serial.println(archivo.name());

      // read from the file until there's nothing else in it:
      while (archivo.available()) {
        Serial.write(archivo.read());
      }
      // close the file:
      archivo.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
  }
}

//Laboratorio 5 parte 1
void printDirectory(File dir, int numTabs) {
  dir.rewindDirectory();
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

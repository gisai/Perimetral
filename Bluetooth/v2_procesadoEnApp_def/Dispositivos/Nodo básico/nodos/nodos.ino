
/*
* Programa para configurar los nodos Bluetooth
* Borja Bordel
* PERIMETER SECURITY
* 2017
*/

//Librerías necesarias
#include <SoftwareSerial.h>

// CONNECT BT RX PIN TO ARDUINO 11 PIN 
//CONNECT BT TX PIN TO ARDUINO 10 PIN
SoftwareSerial BTSerial(10, 11); 

//Configuración
void setup() 
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH); 
  Serial.begin(9600);
  Serial.println("Comenzamos:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}

//Bucle principal
void loop()
{
  
  //Primero comprobamos que todo funciona correctamente
  BTSerial.println("AT\r");
  Serial.println("AT");
  delay(300);
  while (BTSerial.available())
    Serial.write(BTSerial.read());
  delay(10000);
  
  //Cambiamos el nombre como identificador de grupo
  BTSerial.println("AT+NAME=HC-05");
  Serial.println("AT+NAME=HC-05");
  delay(300);
  while (BTSerial.available())
    Serial.write(BTSerial.read());
  delay(10000);
  
  //Imprimimos la dirección MAC asignada para poder conocer el número de usuario
  BTSerial.println("AT+ADDR?");
  Serial.println("AT+ADDR?");
  delay(300);
  while (BTSerial.available())
    Serial.write(BTSerial.read());
  delay(10000);
}



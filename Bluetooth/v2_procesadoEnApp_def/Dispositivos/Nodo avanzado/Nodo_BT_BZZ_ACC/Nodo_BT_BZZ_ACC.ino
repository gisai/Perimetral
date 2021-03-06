/**************************************************************************/
/*!
 *  NODO BT AVANZADO INCLUYENDO ACC Y BUZZER PARA AVISO DE CAÍDAS
 *  PROYECTO PERIMETER SECURITY
    GISAI UPM  BORJA BORDEL 
    2017
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

#define max_error 1.5
#define pin_bzz 2

SoftwareSerial mySerial(11, 12); //RX, TX

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("Adafruit MMA8451 test!");
  

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); 
  Serial.print(2 << mma.getRange());  
  Serial.println("G");
}

void loop() {

  /* EVENTO DE LECTURA */ 
  sensors_event_t event; 
  mma.getEvent(&event);

  /* 
   *  Por como se ha dispuesto el sensor y el nodo, la ecleración debe ser 9,8 m/s^2 en el eje Y y cero en los demás ejes
   *  Si no fuera así ha habido una caída
  */
  if (abs(event.acceleration.x) > max_error || abs(event.acceleration.z) > max_error || event.acceleration.y > -max_error) {
    //se ha producido una caída
     Serial.println("caida");
     mySerial.println("caida");
     tone(pin_bzz, 1000);
  } else {
     noTone(pin_bzz);
  }
  mySerial.println();
  Serial.println();
  delay(1000);
}

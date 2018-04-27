/**************************************************************************/
/*!
 *  NODO WiFi AVANZADO INCLUYENDO ACC Y BUZZER PARA AVISO DE CAÍDAS
 *  PROYECTO PERIMETER SECURITY
    GISAI UPM  BORJA BORDEL 
    2017
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#define max_error 1.5
#define pin_bzz A0

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);
  
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
  if (abs(event.acceleration.x) > max_error) {
    //se ha producido una caída
    Serial.println(event.acceleration.y);
     Serial.println("caida");
     tone(pin_bzz, 10000, 1000);
  } 
  Serial.println();
  delay(500);
}

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  pinMode (_pin, OUTPUT );
  analogWriteFreq(frequency);
  analogWrite(_pin,500);
  delay(duration);
  analogWrite(_pin,0);
}

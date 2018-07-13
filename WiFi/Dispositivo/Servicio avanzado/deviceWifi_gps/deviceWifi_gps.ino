/*
 * NodeMCU Access Point 
 * PERIMETER SECURITY
 * GISAI 2017
 */
 
#include <ESP8266WiFi.h>                  //Incluye la librerÃ­a ESP8266WiFi
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h> 
 
const char ssid[] = "NodeMCU-CUADRILLA#1";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red- 
const char password[] = "12345678";       //Definimos la contraseÃ±a de nuestro servidor 
WiFiServer server(80);                    //Definimos el puerto de comunicaciones

//Definimos el pin de salida - GPIO2 / D4
int PinLED = 2;       

Adafruit_MMA8451 mma = Adafruit_MMA8451();
double max_error = 1.5;
int pin_bzz = 3;
int bateria;

SoftwareSerial GPS_Serial(7, 8); // RX, TX


/* 
 *  CONFIGURACIÃ“N
 */
void setup() {
  Serial.begin(115200);
 
  pinMode(PinLED, OUTPUT);                //Inicializamos el GPIO2 como salida
  digitalWrite(PinLED, HIGH);              //Dejamos inicialmente el GPIO2 apagado

  server.begin();                         //inicializamos el servidor
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);            //Red con clave, en el canal 1 y visible
  //WiFi.softAP(ssid, password,3,1);      //Red con clave, en el canal 3 y visible 
  //WiFi.softAP(ssid);                    //Red abierta
 
  Serial.println();
 
  Serial.print("Direccion IP Access Point - por defecto: ");      //Imprime la direcciÃ³n IP
  Serial.println(WiFi.softAPIP()); 
  Serial.print("Direccion MAC Access Point: ");                   //Imprime la direcciÃ³n MAC
  Serial.println(WiFi.softAPmacAddress()); 
 
  //IPAddress local_ip(192, 168, 1, 1);                           //Modifica la direcciÃ³n IP 
  //IPAddress gateway(192, 168, 1, 1);   
  //IPAddress subnet(255, 255, 255, 0);
  //WiFi.softAPConfig(local_ip, gateway, subnet);
  //Serial.println();
  //Serial.print("Access Point - Nueva direccion IP: ");
  //Serial.println(WiFi.softAPIP());

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

  GPS_Serial.begin(9600); 
}

 
/* 
 *  BUCLE PRINCIPAL
 */
void loop() 
{
  // Comprueba si el cliente ha conectado
  WiFiClient client = server.available();  
  if (!client) {
    return;
  }

  Serial.println("Conectado a red");
 
  // Espera hasta que el cliente envÃ­a alguna peticiÃ³n
  /*while(!client.available()){
    delay(1);
  }
 
  // Lee la peticiÃ³n
  String peticion = client.readStringUntil('r');
  */
   client.flush(); 

   //EnvÃ­o avanzado de datos si procede
   client.print("{bateria:");
   bateria = analogRead(A0);  
   client.print(bateria);
   client.print(",");

  /* EVENTO DE LECTURA */ 
  sensors_event_t event; 
  mma.getEvent(&event);

  /* 
   *  Por como se ha dispuesto el sensor y el nodo, la ecleraciÃ³n debe ser 9,8 m/s^2 en el eje Y y cero en los demÃ¡s ejes
   *  Si no fuera asÃ­ ha habido una caÃ­da
  */
  client.print("acc:{x:");
  client.print(event.acceleration.x);
  client.print(",y:");
  client.print(event.acceleration.y);
  client.print(",z:");
  client.print(event.acceleration.z);
  client.print("},");
  if (abs(event.acceleration.x) > max_error || abs(event.acceleration.z) > max_error) {
    //se ha producido una caÃ­da
     tone(pin_bzz, 1000);
  } else {
    noTone(pin_bzz);    
  }

  char rc;
   if (GPS_Serial.available()){
        rc = GPS_Serial.read();
        client.print("position:");
        client.print(rc);
   }
  client.println("}");
  // Se finaliza la peticiÃ³n al cliente. Se inicaliza la espera de una nueva peticiÃ³n.
  //DesconexiÃ³n de los clientes
  //WiFi.softAPdisconnect();
}


/*
 * NodeMCU Access Point 
 * PERIMETER SECURITY
 * GISAI 2017
 */
 
#include <ESP8266WiFi.h>                  //Incluye la librería ESP8266WiFi
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#define POWER 0  //Potencia en dBm
 
const char ap_ssid[] = "NodeMCU-CUADRILLA#1";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red- 
const char ap_password[] = "12345678";       //Definimos la contraseña de nuestro servidor 

const char ssid[] = "Antena_Wifi";   
const char password[] = "1234567890";

const char* host = "192.168.1.1";                 

//Definimos el pin de salida - GPIO2 / D4
int PinLED = 2;       

Adafruit_MMA8451 mma = Adafruit_MMA8451();
double max_error = 1.5;
int pin_bzz = 3;
int bateria;


/* 
 *  CONFIGURACIÓN
 */
void setup() {
  Serial.begin(115200);
 
  pinMode(PinLED, OUTPUT);                //Inicializamos el GPIO2 como salida
  digitalWrite(PinLED, HIGH);              //Dejamos inicialmente el GPIO2 apagado
 
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);            //Red con clave, en el canal 1 y visible

  WiFi.setOutputPower(POWER);
  //WiFi.softAP(ssid, password,3,1);      //Red con clave, en el canal 3 y visible 
  //WiFi.softAP(ssid);                    //Red abierta

  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //mientras que no estes conectado, no sale de aqui
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado al wifi");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
  
  Serial.println();
 
  Serial.print("Direccion IP Access Point - por defecto: ");      //Imprime la dirección IP
  Serial.println(WiFi.softAPIP()); 
  Serial.print("Direccion MAC Access Point: ");                   //Imprime la dirección MAC
  Serial.println(WiFi.softAPmacAddress()); 
 
  //IPAddress local_ip(192, 168, 1, 1);                           //Modifica la dirección IP 
  //IPAddress gateway(192, 168, 1, 1);   
  //IPAddress subnet(255, 255, 255, 0);
  //WiFi.softAPConfig(local_ip, gateway, subnet);
  //Serial.println();
  //Serial.print("Access Point - Nueva direccion IP: ");
  //Serial.println(WiFi.softAPIP());

  Serial.println("Adafruit MMA8451 test!");
  

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    //while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); 
  Serial.print(2 << mma.getRange());  
  Serial.println("G");
}

 
/* 
 *  BUCLE PRINCIPAL
 */
void loop() 
{
  // Comprueba si el cliente ha conectado
  WiFiClient client;      //creo el cliente
  const int httpPort = 3000; // antes 80 y he cambiado l 3000 a ver si va
   if (!client.connect(host, httpPort)) { //si no me conecto
    Serial.println("conexion fallida");
    return;     //empiezo el loop de nuevo
  }



  //Envío avanzado de datos si procede
String body="ID=tech: wifi, ID: {PERIMETER,NodeMCU-CUADRILLA#1,";
body+=WiFi.softAPmacAddress();
body+="}";
body+=",sensor=options:{bateria:";
bateria = analogRead(A0);  
body+=bateria;
body+=",";

 /* EVENTO DE LECTURA */ 
sensors_event_t event; 
mma.getEvent(&event);

  /* 
   *  Por como se ha dispuesto el sensor y el nodo, la ecleración debe ser 9,8 m/s^2 en el eje Y y cero en los demás ejes
   *  Si no fuera así ha habido una caída
  */
  body+="acc:{x:";
  body+=event.acceleration.x;
  body+=",y:";
  body+=event.acceleration.y;
  body+=",z:";  
  body+=event.acceleration.z;
  body+="}";
  if (abs(event.acceleration.x) > max_error || abs(event.acceleration.z) > max_error) {
    //se ha producido una caída
     tone(pin_bzz, 1000);
  } else {
    noTone(pin_bzz);    
  }
  body+="}";

  String url = "/";  

  Serial.println(body);
  client.print(String("POST ") + url + " HTTP/1.1\r\n"
  "Host: " + host + "\r\n" +
  "Content-Type: application/x-www-form-urlencoded\r\n"+
  "Content-Length:");
  client.println(body.length());
  client.print("Connection: close \r\n\r\n"+
  body ); // terminar la petecion 
}

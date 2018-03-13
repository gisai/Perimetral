/*
 * NodeMCU Access Point 
 * PERIMETER SECURITY
 * GISAI 2017
 */
 
#include <ESP8266WiFi.h>                  //Incluye la librería ESP8266WiFi
 
const char ssid[] = "NodeMCU-CUADRILLA#1";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red- 
const char password[] = "12345678";       //Definimos la contraseña de nuestro servidor 
WiFiServer server(80);                    //Definimos el puerto de comunicaciones

//Definimos el pin de salida - GPIO2 / D4
int PinLED = 2;         

/* 
 *  CONFIGURACIÓN
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
 
  // Espera hasta que el cliente envía alguna petición
  while(!client.available()){
    delay(1);
  }
 
  // Lee la petición
  String peticion = client.readStringUntil('r');
  client.flush();  

  //Envío avanzado de datos si procede
 
  //Desconexión de los clientes
  //WiFi.softAPdisconnect();
}

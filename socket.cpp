#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"

extern WiFiClient client;

void establish_socket(){
  char message[255];
  IPAddress gateway = WiFi.gatewayIP();
  sprintf(message, "Establishing socket to server : %s, at port : %d", gateway.toString(), PORT_NUMBER);
  Serial.println(message);

  if(client.connect(gateway, PORT_NUMBER)){
    Serial.println("Connected to server !");
  }else{
    Serial.println("Can't connect ...");
  }
}
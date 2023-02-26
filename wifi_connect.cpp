#include <stdlib.h>
#include "WString.h"
#include <Arduino.h>
#include <WiFi.h>
#include "wifi_connect.h"


void connect_to_access_point(){
  WiFi.begin(SSID, PASSWORD);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void check_wifi_connection(){
  int status = WiFi.status();
  if(status == WL_CONNECTION_LOST || status == WL_DISCONNECTED){
    Serial.println("Connection lost, trying to reconnect");
    connect_to_access_point();
  }
}

char* get_mac_address(){
  uint8_t mac_address_array[6];
  WiFi.macAddress(mac_address_array);
  char * mac_address = (char *)malloc(12*sizeof(char));
  for(int i=0; i<6; i++){
    sprintf(&mac_address[i*2], "%02X", mac_address_array[i]);
  }
  return mac_address;
}

IPAddress get_ip_address(){
  return WiFi.localIP();
}
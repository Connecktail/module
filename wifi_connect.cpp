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

String get_mac_address(){
  return WiFi.macAddress();
}

IPAddress get_ip_address(){
  return WiFi.localIP();
}
#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"
#include "wifi_connect.h"

void establish_socket(){
  char message[255];
  IPAddress gateway = WiFi.gatewayIP();
  sprintf(message, "Establishing socket to server : %s, at port : %d", gateway.toString(), PORT_NUMBER);
  Serial.println(message);

  while (!client.connect("192.168.1.14", 5000)) {
    delay(500);
    Serial.println("Can't connect");
  }
  Serial.println("Connected to server !");

}

char *construct_pair_message(){
  char *pair_message = (char *)malloc(64 * sizeof(char));
  IPAddress ip_address = get_ip_address();
  char* mac_address = get_mac_address();

  sprintf(pair_message, "{\"action\":\"pair\",\"ip_address\":\"%s\",\"id\":\"%s\"}",ip_address.toString(), mac_address);
  return pair_message;
}

bool check_protocol(){
   char check = client.read();
    if(check == PROTOCOL_CHECK)
      return true;
    else{
      // The message is not processed
      while (client.available()) client.read();
      return false;
    }
}

char *get_response_data(){
  char carac;
  char length_as_string[5];
  int i = 0;

  // Get the length of the data
  while((carac = client.read()) != ' ') length_as_string[i++] = carac;
  length_as_string[i] = '\0';
  int length = atoi(length_as_string);

  // Retrieve data
  char *content = (char*)malloc((length+1) * sizeof(char));
  for(int i = 0; i < length; i++){
    content[i] = client.read();
  }
  content[length]= '\0';
  return content;
}
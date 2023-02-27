#include <WiFi.h>
#include "pair.h"
#include "socket.h"

void IRAM_ATTR pair_button_action()
{
  pair_button.pressed = true;
  detachInterrupt(pair_button.pin);
}

void pair(){
  pair_button.pressed = false;
  waiting_to_pair = true;
  Serial.println("pair button pressed");

  char *pair_message = construct_pair_message();
  Serial.println("Sending message to pair...");
  client.write(pair_message);
}

void waiting_ack_pair(){
  if(client.available() && check_protocol()){
    char *response = get_response_data();
    if(strcmp(response, PAIR_RESPONSE) == 0){
      Serial.println("module paired !");
      waiting_to_pair = false;
    }
  }
}
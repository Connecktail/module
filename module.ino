#include "types.h"
#include "pair.h"
#include "wifi_connect.h"
#include "socket.h"

button_t pair_button = {PAIR_BUTTON_PIN, false};
bool waiting_to_pair = false;
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  pinMode(pair_button.pin, INPUT);
  connect_to_access_point();
  delay(3000);
  establish_socket();
  attachInterrupt(pair_button.pin, pair_button_action, FALLING);
}

void loop()
{
  check_wifi_connection();
  if(pair_button.pressed){
    pair_button.pressed = false;
    waiting_to_pair = true;
    Serial.println("pair button pressed");

    char *pair_message = construct_pair_message();
    Serial.println("Sending message to pair...");
    client.write(pair_message);
    free(pair_message);
  }
  else if(waiting_to_pair){
    if(client.available() && check_protocol()){
      char *response = get_response_data();
      if(strcmp(response, "OK") == 0){
        Serial.println("module paired !");
        waiting_to_pair = false;
      }
    }
  }
  else{
    if(client.available() && check_protocol()){
      char *response = get_response_data();
      Serial.println("response from server : ");
      Serial.println(response);      
    }
  }

  delay(100);
}

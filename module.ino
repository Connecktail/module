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
  if(pair_button.pressed) pair();
  else if(waiting_to_pair) waiting_ack_pair();  
  else{
    if(client.available() && check_protocol()){
      char *response = get_response_data();
      Serial.println("response from server : ");
      Serial.println(response);    

      //TODO: Implement listening for actions  
    }
  }

  delay(100);
}

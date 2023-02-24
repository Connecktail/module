#include "types.h"
#include "pair.h"
#include "wifi_connect.h"
#include "socket.h"

button_t pair_button = {PAIR_BUTTON_PIN, false};
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  pinMode(pair_button.pin, INPUT);
  connect_to_access_point();
  establish_socket();
  attachInterrupt(pair_button.pin, pair_button_action, FALLING);
}

void loop()
{
  check_wifi_connection();
  if(pair_button.pressed){
    pair_button.pressed = false;
    Serial.println("pair button pressed");
  }
  delay(100);
}

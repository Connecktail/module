#include "types.h"
#include "pair.h"
#include "wifi_connect.h"
#include "socket.h"
#include "actions.h"

button_t pair_button = {PAIR_BUTTON_PIN, false};
bool waiting_to_pair = false;
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  pinMode(pair_button.pin, INPUT_PULLDOWN);
  connect_to_access_point();
  delay(3000);
  attachInterrupt(pair_button.pin, pair_button_action, FALLING);
}

void loop()
{
  check_wifi_connection();
  if (pair_button.pressed)
    pair();
  else if (waiting_to_pair)
    waiting_ack_pair();
  else
  {
    if (client.available() && check_protocol())
    {
      char *response = get_response_data();
      char *action = get_action(response);

      if (strcmp(action, ENABLE_LED))
      {
        Serial.println("action enable_led");
        // TODO
      }
      else if (strcmp(action, DISABLE_LED))
      {
        Serial.println("action disable_led");
        // TODO
      }
      else if (strcmp(action, ENABLE_SOUND))
      {
        Serial.println("action enable_sound");
        // TODO
      }
      else if (strcmp(action, DISABLE_SOUND))
      {
        Serial.println("action disable_sound");
        // TODO
      }
      else
        Serial.println("action not recognized");
    }
  }
  delay(100);
}

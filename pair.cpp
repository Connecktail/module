#include <WiFi.h>
#include "pair.h"
#include "socket.h"

void IRAM_ATTR pair_button_action()
{
  pair_button.pressed = true;
  detachInterrupt(pair_button.pin);
}
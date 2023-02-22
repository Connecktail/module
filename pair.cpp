#include "esp32-hal-gpio.h"
#include "pair.h"

void IRAM_ATTR pair_button_action()
{
  pair_button.pressed = true;
  //send info to pair
  detachInterrupt(pair_button.pin);
}
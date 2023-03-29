#include "esp32-hal-gpio.h"
#include "actions.h"

void enable_led(rgb_led_t rgb_led){
  digitalWrite(rgb_led.red.pin, rgb_led.red.value);
  digitalWrite(rgb_led.green.pin, rgb_led.green.value);
  digitalWrite(rgb_led.blue.pin, rgb_led.blue.value);
}
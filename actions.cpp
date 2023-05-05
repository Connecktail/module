#include "esp32-hal-gpio.h"
#include "actions.h"

void enable_led(rgb_led_t rgb_led){
  _switch_led(rgb_led, true);
}

void _switch_led(rgb_led_t rgb_led, bool state){
  digitalWrite(rgb_led.red.pin, state ? rgb_led.red.value : 0);
  digitalWrite(rgb_led.green.pin, state ? rgb_led.green.value : 0);
  digitalWrite(rgb_led.blue.pin, state ? rgb_led.blue.value : 0); 
}

void disable_led(rgb_led_t rgb_led){
  _switch_led(rgb_led, false);
}
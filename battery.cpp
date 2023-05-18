#include "esp32-hal-gpio.h"
#include "battery.h"
#include "Arduino.h"
#include "actions.h"
#include <WiFi.h>
#include "socket.h"

extern bool low_battery;
extern rgb_led_t rgb_led;
extern WiFiClient client;

int get_battery_level(){
  int analog_value = analogRead(BATTERY_LEVEL_PIN);
  int battery_level = (analog_value - CONVERT_ANALOG(ESP_MIN_VOLTAGE)) / (CONVERT_ANALOG(ESP_BASE_VOLTAGE) - CONVERT_ANALOG(ESP_MIN_VOLTAGE)) * 100; 
  return ROUND_UP(battery_level);
} 

bool is_low_battery(int battery_level){
  return battery_level < BATTERY_LEVEL_THRESHOLD;
}

void set_battery_level(){
  int battery_level = get_battery_level();

  low_battery = is_low_battery(battery_level);
  if (low_battery){
    rgb_led.red.value = 255;
    rgb_led.blue.value = 0;
    rgb_led.green.value = 0;
  }else{
    rgb_led.red.value = RED_VALUE;
    rgb_led.blue.value = BLUE_VALUE;
    rgb_led.green.value = GREEN_VALUE;
  }

  char *set_battery_message = construct_set_battery_message(battery_level);
  // send the set_battery message
  Serial.println("Sending set_battery message...");
  client.write(set_battery_message);
}
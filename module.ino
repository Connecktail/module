#include <Wire.h>
#include "types.h"
#include "pair.h"
#include "wifi_connect.h"
#include "socket.h"
#include "actions.h"
#include "gyroscope.h"
#include "battery.h"
#include <TimeAlarms.h>

button_t pair_button = {PAIR_BUTTON_PIN, false};
bool waiting_to_pair = false;
bool waiting_to_take_bottle = false;
bool low_battery = false;

rgb_led_t rgb_led = {
    {RED_PIN, RED_VALUE},
    {GREEN_PIN, GREEN_VALUE},
    {BLUE_PIN, BLUE_VALUE}};

WiFiClient client;
ITG3200 gyro;

buzzer_t buzzer = {BUZZER_PIN, BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION};

void setup()
{
  Serial.begin(9600);
  Alarm.timerRepeat(SET_BATTERY_INTERVAL, set_battery_level);
  setup_gyroscope();
  pinMode(pair_button.pin, INPUT_PULLDOWN);
  pinMode(rgb_led.red.pin, OUTPUT);
  pinMode(rgb_led.green.pin, OUTPUT);
  pinMode(rgb_led.blue.pin, OUTPUT);
  pinMode(BATTERY_LEVEL_PIN, INPUT);
  connect_to_access_point();
  delay(3000);
  attachInterrupt(pair_button.pin, pair_button_action, FALLING);
  ledcSetup(buzzer.channel, buzzer.freq, buzzer.resolution);
  ledcAttachPin(buzzer.pin, buzzer.channel);
}

void loop()
{
  if(low_battery){
    enable_led(rgb_led);
    delay(1000);
    disable_led(rgb_led);
    delay(1000);
  }else{
    check_wifi_connection();

    if (waiting_to_take_bottle && is_moving())
      take_bottle();

    if (pair_button.pressed)
      pair();
    else if (waiting_to_pair){
      waiting_ack_pair();
      enable_led(rgb_led);
      delay(2000);
      disable_led(rgb_led);
    }else{
      if (client.available() && check_protocol())
      {
        char *response = get_response_data();
        char *action = get_action(response);

        if (!strcmp(action, ENABLE_LED))
        {
          Serial.println("action enable_led");
          enable_led(rgb_led);
          waiting_to_take_bottle = true;
        }
        else if (!strcmp(action, DISABLE_LED))
        {
          Serial.println("action disable_led");
          disable_led(rgb_led);
          waiting_to_take_bottle = false;
        }
        else if (!strcmp(action, ENABLE_SOUND))
        {
          Serial.println("action enable_sound");
          enable_buzzer(buzzer, 25);
          waiting_to_take_bottle = true;
        }
        else if (!strcmp(action, DISABLE_SOUND))
        {
          Serial.println("action disable_sound");
          disable_buzzer(buzzer);
          waiting_to_take_bottle = false;
        }
        else
          Serial.println("action not recognized");
      }
    }
    delay(500);
  }
  Alarm.delay(0);
}

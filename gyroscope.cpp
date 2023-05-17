#include "gyroscope.h"
#include "socket.h"
#include <WiFi.h>
#include "actions.h"

extern ITG3200 gyro;
extern bool waiting_to_take_bottle;
extern WiFiClient client;
extern rgb_led_t rgb_led;
extern buzzer_t buzzer;

void setup_gyroscope(){
  gyro.init();
  gyro.zeroCalibrate(200, 10);
}

void take_bottle(){
  char *bottle_taken_message = construct_bottle_taken_message();
  // send the bottle_taken message
  Serial.println("Sending bottle_taken message...");
  client.write(bottle_taken_message);
  waiting_to_take_bottle = false;
  disable_led(rgb_led);
  disable_buzzer(buzzer);
}

bool is_moving(){
  float ax, ay, az;

  gyro.getAngularVelocity(&ax, &ay, &az);

  bool ax_condition = ax > ACCELERATION_THRESHOLD || ax < -ACCELERATION_THRESHOLD;
  bool ay_condition = ay > ACCELERATION_THRESHOLD || ay < -ACCELERATION_THRESHOLD;
  bool az_condition = az > ACCELERATION_THRESHOLD || az < -ACCELERATION_THRESHOLD;
  
  return ax_condition || ay_condition || az_condition;
}

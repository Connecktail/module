#include "gyroscope.h"
#include "socket.h"
#include <WiFi.h>

extern ITG3200 gyro;
extern bool waiting_to_take_bottle;
extern WiFiClient client;;

void setup_gyroscope(){
  gyro.init();
  gyro.zeroCalibrate(200, 10);
}

void take_bottle(){
  // wait until the bottle is taken
  while (!is_moving()) delay(200);
  char *bottle_taken_message = construct_bottle_taken_message();
  // send the bottle_taken message
  Serial.println("Sending bottle_taken message...");
  client.write(bottle_taken_message);
  waiting_to_take_bottle = false;
}

bool is_moving(){
  float ax, ay, az;

  gyro.getAngularVelocity(&ax, &ay, &az);

  bool ax_condition = ax > ACCELERATION_THRESHOLD || ax < -ACCELERATION_THRESHOLD;
  bool ay_condition = ay > ACCELERATION_THRESHOLD || ay < -ACCELERATION_THRESHOLD;
  bool az_condition = az > ACCELERATION_THRESHOLD || az < -ACCELERATION_THRESHOLD;
  
  return ax_condition || ay_condition || az_condition;
}

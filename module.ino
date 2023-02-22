#include "types.h"
#include "pair.h"

button_t pair_button = {PAIR_BUTTON_PIN, false};

void setup()
{
  Serial.begin(9600);
  pinMode(pair_button.pin, INPUT);
  attachInterrupt(pair_button.pin, pair_button_action, FALLING);
}

void loop()
{
  if(pair_button.pressed){
    pair_button.pressed = false;
    Serial.println("pair button pressed");
  }
  delay(100);
}

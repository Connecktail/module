#ifndef ACTIONS_H
#define ACTIONS_H

#define RED_PIN D4
#define GREEN_PIN D5
#define BLUE_PIN D6

#define RED_VALUE 125
#define GREEN_VALUE 200
#define BLUE_VALUE 125

#define BUZZER_PIN D2
#define BUZZER_CHANNEL 0
#define BUZZER_FREQ 200
#define BUZZER_RESOLUTION 8

typedef struct{
  uint8_t pin;
  uint8_t value;
}rgb_led_pin_t;

typedef struct{
  rgb_led_pin_t red;
  rgb_led_pin_t green;
  rgb_led_pin_t blue;
}rgb_led_t;

typedef struct{
  uint8_t pin;
  int channel;
  int freq;
  int resolution;
}buzzer_t;

#define ENABLE_LED "enable_led"
#define DISABLE_LED "disable_led"
#define ENABLE_SOUND "enable_sound"
#define DISABLE_SOUND "disable_sound"

void enable_led(rgb_led_t rgb_led);
void _switch_led(rgb_led_t rgb_led, bool state);
void disable_led(rgb_led_t rgb_led);
void enable_buzzer(buzzer_t buzzer, int value);
void disable_buzzer(buzzer_t buzzer);

#endif

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

/**
 * @brief Enable the led
 * @param rgb_led The led to enable
 * @note the color of the led is defined by the constants RED_VALUE, GREEN_VALUE and BLUE_VALUE
 * @note uses _switch_led function
 */
void enable_led(rgb_led_t rgb_led);

/**
 * @brief Disable the led
 * @param rgb_led The led to disable
 * @note uses _switch_led function
 */
void disable_led(rgb_led_t rgb_led);

/**
 * @brief toggle the led
 * @param rgb_led The led to set the state
 * @param state The state of the led : true for on, false for off
 */
void _switch_led(rgb_led_t rgb_led, bool state);

/**
 * @brief Play a sound on the buzzer
 * @param buzzer The buzzer to play the sound with
 * @param value The value of the duty cycle to apply
 */
void enable_buzzer(buzzer_t buzzer, int value);

/**
 * @brief Stop the sound on the buzzer
 * @param buzzer The buzzer to stop the sound
 */
void disable_buzzer(buzzer_t buzzer);

#endif

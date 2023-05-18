#ifndef BATTERY_H
#define BATTERY_H

#define BATTERY_LEVEL_PIN A0
#define ESP_BASE_VOLTAGE 5
#define ESP_MIN_VOLTAGE 2.55
#define CONVERT_ANALOG(voltage) (ADC_MAX_VALUE * voltage / ESP_BASE_VOLTAGE)
#define BATTERY_LEVEL_THRESHOLD 25
#define ROUND_UP(value) (value < 0 ? 0 : (value > 100 ? 100 : value))

#define SET_BATTERY_INTERVAL 5

#define ADC_MAX_VALUE 4095
#define ADC_MIN_VALUE 0

int get_battery_level();
bool is_low_battery(int battery_level);
void set_battery_level();

#endif
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

/**
 * @brief Get the battery level
 * @return The battery level in percent
 * @note The battery level is calculated with the formula : (battery_voltage - min_voltage) * 100 / (max_voltage - min_voltage)
 */
int get_battery_level();

/**
 * @brief Check if the battery level is low
 * @param battery_level The battery level to check
 * @return true if the battery level is low, false otherwise
 * @note The battery level is considered low if it is below the threshold defined by BATTERY_LEVEL_THRESHOLD
 */
bool is_low_battery(int battery_level);

/**
 * @brief Set the battery level
 * @note Send a message to the server with the battery level
 */
void set_battery_level();

#endif
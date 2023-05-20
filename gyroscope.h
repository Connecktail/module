#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <WiFi.h>
#include "ITG3200.h"

#define ACCELERATION_THRESHOLD 150

/**
 * @brief Setup the gyroscope
*/
void setup_gyroscope();

/**
 * @brief function called when the bottle is taken
 * @note Send a message to the server with the bottle taken message and disable the led and the buzzer
*/
void take_bottle();

/**
 * @brief Check if the bottle is moving
 * @return true if the bottle is moving, false otherwise
 * @note The bottle is considered moving if the acceleration on one of the axis is above the threshold defined by ACCELERATION_THRESHOLD
*/
bool is_moving();

#endif
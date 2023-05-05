#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <WiFi.h>
#include "ITG3200.h"

#define ACCELERATION_THRESHOLD 150

void setup_gyroscope();
void take_bottle();
bool is_moving();

#endif
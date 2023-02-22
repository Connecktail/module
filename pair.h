#ifndef PAIR_H
#define PAIR_H

#include <Arduino.h>
#include "types.h"

#define PAIR_BUTTON_PIN 15

extern button_t pair_button;

void IRAM_ATTR pair_button_action();

#endif
#ifndef PAIR_H
#define PAIR_H

#include <Arduino.h>
#include "types.h"

#define PAIR_BUTTON_PIN D3
#define PAIR_RESPONSE "OK"

extern button_t pair_button;
extern bool waiting_to_pair;

void IRAM_ATTR pair_button_action();
void pair();
void waiting_ack_pair();

#endif
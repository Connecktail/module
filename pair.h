#ifndef PAIR_H
#define PAIR_H

#include <Arduino.h>
#include "types.h"

#define PAIR_BUTTON_PIN D3
#define PAIR_RESPONSE "OK"

extern button_t pair_button;
extern bool waiting_to_pair;

/**
 * @brief interruption function called when the pair button is pressed
 * @note set the pair_button.pressed to true and detach the interruption
*/
void IRAM_ATTR pair_button_action();

/**
 * @brief Pair the module with the server
 * @note Send a message to the server with the pair message
*/
void pair();

/**
 * @brief Wait for the server to send the pair response
 * @note If the response is PAIR_RESPONSE, set waiting_to_pair to false
*/
void waiting_ack_pair();

#endif
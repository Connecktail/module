#ifndef SOCKET_H
#define SOCKET_H

#define PORT_NUMBER 5000
#define PROTOCOL_CHECK 0x2a

extern WiFiClient client;

/**
 * @brief Establish the socket with the server
 * @note Connect to the server and enable the led to notice the connection
 * @note If the connection fails, try again every 500ms
 * @note the module connects to the gateway at port defined by PORT_NUMBER
*/
void establish_socket();

/**
 * @brief Construct the pair message
 * @return the pair message
 * @note The pair message is a JSON object with the action pair, the ip address and the mac address of the module
*/
char *construct_pair_message();

/**
 * @brief Construct the bottle taken message
 * @return the bottle taken message
 * @note The bottle taken message is a JSON object with the action bottle_taken
*/
char *construct_bottle_taken_message();

/**
 * @brief Construct the set battery message
 * @param battery_level the battery level of the module
 * @return the set battery message
 * @note The set battery message is a JSON object with the action set_battery and the battery level of the module
*/
char *construct_set_battery_message(int battery_level);

/**
 * @brief Check if the protocol is correct
 * @return true if the protocol is correct, false otherwise
 * @note The protocol is correct if the first byte received is PROTOCOL_CHECK
 * @note If the protocol is not correct, all data received is discarded
*/
bool check_protocol();

/**
 * @brief Retrieve the json data received from the server by parsing it
 * @note The data is parsed according to the protocol
*/
char *get_response_data();

/**
 * @brief Retrieve the action from the json data
 * @param data the json data as string
 * @return the action
 * @note The action is the first key of the json data
*/
char *get_action(char *data);

#endif
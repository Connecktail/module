#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H

#include <WiFi.h>

#define SSID "Jsuis une formule1"
#define PASSWORD "totototo"

/**
 * @brief Connect to the access point
 * @note Connect to the access point defined by SSID and PASSWORD
 * @note Enable the led for 2 seconds if the connection is successful
 * @note if the connection failed try every 100ms
*/
void connect_to_access_point();

/**
 * @brief Check if the connection is still active
 * @note If the connection is lost, try to reconnect
*/
void check_wifi_connection();

/**
 * @brief Retrieve the mac address of the module
 * @return the mac address of the module
*/
char* get_mac_address();

/**
 * @brief Retrieve the ip address of the module
 * @return the ip address of the module
*/
IPAddress get_ip_address();

#endif
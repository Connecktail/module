#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H

#include <WiFi.h>

#define SSID "ssid"
#define PASSWORD "password"

void connect_to_access_point();
void check_connection();

String get_mac_address();
IPAddress get_ip_address();


#endif
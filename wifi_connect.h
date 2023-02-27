#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H

#include <WiFi.h>

#define SSID "SSID"
#define PASSWORD "PASSWORD"

void connect_to_access_point();
void check_wifi_connection();

char* get_mac_address();
IPAddress get_ip_address();

#endif
#ifndef SOCKET_H
#define SOCKET_H

#define PORT_NUMBER 5000
#define PROTOCOL_CHECK 0x2a

extern WiFiClient client;

void establish_socket();
char *construct_pair_message();
char *construct_bottle_taken_message();
char *construct_set_battery_message(int battery_level);

bool check_protocol();
char *get_response_data();
char *get_action(char *data);

#endif
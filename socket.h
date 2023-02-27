#ifndef SOCKET_H
#define SOCKET_H

#define PORT_NUMBER 5000
#define PROTOCOL_CHECK 0x2a

extern WiFiClient client;

void establish_socket();
char *construct_pair_message();

bool check_protocol();
char *get_response_data();

#endif
#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"
#include "wifi_connect.h"

void establish_socket()
{
  char message[255];
  IPAddress gateway = WiFi.gatewayIP();
  sprintf(message, "Establishing socket to server : %s, at port : %d", gateway.toString(), PORT_NUMBER);
  Serial.println(message);

  while (!client.connect("192.168.1.14", PORT_NUMBER))
  {
    delay(500);
    Serial.println("Can't connect");
  }
  Serial.println("Connected to server !");
}

char *construct_pair_message()
{
  IPAddress ip_address = get_ip_address();
  String ip_address_string = ip_address.toString();
  unsigned int ip_address_length = ip_address_string.length() + 1;
  unsigned int nb = ip_address_length > 0 ? (int)log10((double)ip_address_length) + 1 : 1;

  char *pair_message = (char *)malloc((63 + nb + ip_address_length) * sizeof(char));
  char *mac_address = get_mac_address();

  sprintf(pair_message, "*%d {\"action\":\"pair\",\"ip_address\":\"%s\",\"mac_address\":\"%s\"}", 61 + ip_address_length, ip_address_string, mac_address);
  return pair_message;
}

char *construct_bottle_taken_message(){
  char *bottle_taken_message = (char *)malloc((29) * sizeof(char));
  
  strcpy(bottle_taken_message, "*25 {\"action\":\"bottle_taken\"}");
  return bottle_taken_message;
}

bool check_protocol()
{
  char check = client.read();
  if (check == PROTOCOL_CHECK)
    return true;
  else
  {
    // The message is not processed
    while (client.available())
      client.read();
    return false;
  }
}

char *get_response_data()
{
  char carac;
  char length_as_string[5];
  int i = 0;

  // Get the length of the data
  while ((carac = client.read()) != ' ')
    length_as_string[i++] = carac;
  length_as_string[i] = '\0';
  int length = atoi(length_as_string);

  // Retrieve data
  char *content = (char *)malloc((length + 1) * sizeof(char));
  for (int i = 0; i < length; i++)
  {
    content[i] = client.read();
  }
  content[length] = '\0';
  return content;
}

char *get_action(char *data)
{
  int i = 11, j = 0;
  while (data[i] != '"')
    i++;
  char *action = (char *)malloc((i - 11) * sizeof(char));
  for (j = 0; j < i - 11; j++)
    action[j] = data[11 + j];
  action[j] = '\0';
  return action;
}
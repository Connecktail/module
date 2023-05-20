# Module

## Purpose of the process :

Be able to light a led and play a sound meaning the bottle has to be taken. Detect the taking of the bottle. Pair with a server and communicate via TCP with it using a defined protocol.

## How to use it :

### Prerequisites :

In order to compile and upload the code on the esp32 you need to add the url : https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json into File/preferences/Additional boards manager URLs.

- boards manager : esp32
- library Time
- library TimeAlarms
- library Grove 3-Axis Digital Gyro

Make sure you have the permissions to read and write on /dev/ttyUSB when you plug you device in the computer

## How it works :

The module tries first to connect to the access point emitted by the server. After that he waits for the user to press the pairing button. When pressed, the module tries to establish a connection with the server then send the pair message. After sending it he waits the acknoledgment.

When all of that is set up, the module waits for new data, and check if the flag of the mdata recieved correspond to the one defined for the protocol. In that case, the module process the data depending of the action recieved : 
- if the action is enable_led then it light the led
- if the action is disable_led the it turn off the led
- if the action is enable_sound then it plays the sound
- if the action is disable_sound the it stops playing the sound

After lighting the led, the module waits the user to take the bottle then its disable the led and the buzzer and send that information to the server.
At a certain rate, the module check its battery level and send it to the server. If the level is under a threshold then the light is blinking in red to indicate its low level.

## Data structures :

Structs have been define in order so that is easier to deal with pins and state of a sensor or actuator :

- Structs to deal with an rgb led

```c
typedef struct{
  rgb_led_pin_t red;
  rgb_led_pin_t green;
  rgb_led_pin_t blue;
}rgb_led_t;
```

```c
typedef struct{
  uint8_t pin;
  uint8_t value;
}rgb_led_pin_t;
```

- Struct to deal with a buzzer

```c
typedef struct{
  uint8_t pin;
  int channel;
  int freq;
  int resolution;
}buzzer_t;
```

- Struct to deal with a button

```c
typedef struct
{
    const char pin;
    bool pressed;
} button_t;
```

## Functions :

### Wifi connection

- Connection to the access point :

```c
void connect_to_access_point()
```

- Check if the connection is still established :

```c
void check_wifi_connection()
```

- Retrieve the mac address of the module

```c
char* get_mac_address()
```

- Retrieve the ip address of the module

```c
IPAddress get_ip_address()
```

### Socket processing

- Establish the socket with the server :

```c
void establish_socket()
```

- Check the protocol of the data received :

```c
bool check_protocol()
```

- Get the json data according to the protocol :

```c
char *get_response_data()
```

- Retrieve the action from json data :

```c
char *get_action(char *data)
```

- Construct the pair message : 

```c
char *construct_pair_message()
```

- Construct the bottle_taken message :

```c
char *construct_bottle_taken_message()
```

- Construct the set_battery message : 

```c
char *construct_set_battery_message(int battery_level)
```

### Pairing process

- Interruption called when pressing the pairing button :

```c
void IRAM_ATTR pair_button_action()
```

- Function to pair the module with the server :

```c
void pair()
```

- Function to wait the ack from server :

```c
void waiting_ack_pair()
```

### Gyroscope handling

- Function to setup the gyroscope :

```c
void setup_gyroscope()
```

- Know if the gyroscope is moving :

```c
bool is_moving()
```

- Action to do when the bottle has been taken :

```c
void take_bottle()
```

### Battery handling

- Function to get the battery level :

```c
int get_battery_level()
```

- Know if the battery level is low : 

```c
bool is_low_battery(int battery_level)
```

- Send the battery level to the server :

```c
void set_battery_level()
```

### Actions

- Enable the led

```c
void enable_led(rgb_led_t rgb_led)
```

- Disable the led

```c
void disable_led(rgb_led_t rgb_led)
```

- Play a sound

```c
void enable_buzzer(buzzer_t buzzer, int value)
```

- Stop the sound

```c
void disable_buzzer(buzzer_t buzzer)
```
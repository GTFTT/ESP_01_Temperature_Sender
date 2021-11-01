# ESP_01_Temperature_Sender
This project is creted for a new IoT device - Temperature Sensore. It aims to provide server with data about environment state inside of a house.
Here is used ESP-01 for WiFi requests to the server. Basically idea is to create a sensor without Arduino UNO and nRF24L01.



# How to make this sh**t work

1. Make all required connections for your ESP-01(I use ESP-01 Breakout board and Arduino without microcontroller to make connection easier).
2. Open serial monitor
3. Select 115200 baud rate
4. Select “Both NL & CL”(new and carriage line in serial monitor setting)
5. Change ESP01 mode: AT+CWMODE=3
6. Type: “AT+CWLAP” To see list of available networks

# Some useful commands
- `AT+CWMODE=3` - required to connect to WiFi
- `AT+CWLAP` - list of available networks
- `AT+CWJAP=”SSID”,”PASSWORD”` - connect to WIFI
- `AT+CWJAP="Nataliya","0806XXXX"` - REMINDER FOR ME
- `AT+CWJAP="U3H","12345678"` - REMINDER FOR ME

# Issues
1. If you can’t send or receive messages: Check connection, use step down logic converters if needed, use correct version of Arduino IDE(2.0.X Beta is UNSTABLE!!!)
2. 2.	If you receive error when send `AT+CWLAP` then try this `AT+CWMODE=3`. [Link](https://medium.com/@deduardopineda/the-correc-command-is-at-cwlap-wifi-name-wifi-password-d642b301c6ec).

# ESP_01_Temperature_Sender
This project is creted for a new IoT device - Temperature Sensore. It aims to provide server with data about environment state inside of a house.
Here is used ESP-01 for WiFi requests to the server. Basically idea is to create a sensor without Arduino UNO and nRF24L01.



# How to make this sh**t work

<div>
  <img src="https://user-images.githubusercontent.com/48696470/139743871-36d4f821-8e6a-4bcd-8e18-a4a71903e9e6.png" alt="My connection" height="200px"/>
  <img src="https://user-images.githubusercontent.com/48696470/139743683-5fbc1c17-9092-4dfb-9eaa-3837965f1c32.png" alt="Connection example" height="200px"/>
</div>

1. Make all required connections for your ESP-01(I use ESP-01 Breakout board, Arduino without microcontroller and logic level step down converter).
<!-- Images are replaced with HTML because they were too big, if there are any issues you can set it as before -->
<!--   ![image](https://user-images.githubusercontent.com/48696470/139743683-5fbc1c17-9092-4dfb-9eaa-3837965f1c32.png) -->
<!--   ![image](https://user-images.githubusercontent.com/48696470/139743871-36d4f821-8e6a-4bcd-8e18-a4a71903e9e6.png) -->
2. Open serial monitor
3. Select 115200 baud rate
4. Select “Both NL & CL”(new and carriage line in serial monitor setting)
5. Change ESP01 mode: `AT+CWMODE=3`
6. Type: `AT+CWLAP` To see list of available networks

# Some useful commands
- `AT+CWMODE=3` - required to connect to WiFi
- `AT+CWLAP` - list of available networks
- `AT+CWJAP="SSID","PASSWORD"` - connect to WIFI
- `AT+CWJAP="Nataliya","0806XXXX"` - REMINDER FOR ME
- `AT+CWJAP="U3H","12345678"` - REMINDER FOR ME

# Issues
1. If you can’t send or receive messages: Check connection, use step down logic converters if needed, use correct version of Arduino IDE(2.0.X Beta is UNSTABLE!!!)
2. 2.	If you receive error when send `AT+CWLAP` then try this `AT+CWMODE=3`. [Link](https://medium.com/@deduardopineda/the-correc-command-is-at-cwlap-wifi-name-wifi-password-d642b301c6ec).
3. If you can not connect to the  network via `AT+CWJAP=”SSID”,”PASSWORD”` it can be because you have wrong quoutation(“)mark craracter code, use plain standard ASKI quotation mark. Ithink something like that `AT+CWJAP="SSID","PASSWORD"`.

# Sources
- [Commands list](https://wiki.iteadstudio.com/images/5/53/Esp8266_at_instruction_set_en_v1.5.4_0.pdf)
- [Good tutorial](https://www.geekstips.com/esp8266-arduino-tutorial-iot-code-example/)
- [Types of ESP](https://blog.squix.org/2015/03/esp8266-module-comparison-esp-01-esp-05.html)(ESP-01, ESP-05, ESP-12...)

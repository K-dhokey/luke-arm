# luke-arm
# human emulating robotic hand
# Tasks :

  Task0 : hello world 

  Task1 : led blink

  Task2 : control servo from Esp32 , from 0 to 90, can add loop also
  
  Task3 : establish communication between two esps and send data between them


#  wifi communication between two esps

# how to establish a Wi-Fi communication (HTTP) between two esps boards to exchange data without the need to connect to the internet (you don’t need a router).
You’re going to set one ESP as an Access Point (Server) and another ESP as a Station (Client). Then, the server and the client will exchange data (sensor readings) via HTTP requests. 
here, server esp creates its own wireless network( so that other wifi devices can connect to that network) and client esp is set as a station, connecting the server esp
The client can make HTTP GET requests to the server to request sensor data or any other information. It just needs to use the IP address of the server to make a request on a certain route: /temperature, /humidity or /pressure.
The server listens for incoming requests and sends an appropriate response with the readings.
The client receives the readings and displays them on the OLED display.

# you need the following parts:

    2x ESP8266 Development boards – read Best ESP8266 Boards Comparison
    BME280 sensor
    I2C SSD1306 OLED display
    Jumper Wires
    Breaboard
    
    resource : https://randomnerdtutorials.com/esp8266-nodemcu-client-server-wi-fi/

# ESP-NOW Two-Way Communication Between ESP32 Boards

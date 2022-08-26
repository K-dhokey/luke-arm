# establishing communication between two esps
### [resource]:(https://esp32io.com/tutorials/communication-between-two-esp32)
#  wifi communication between two esps

## how to establish a Wi-Fi communication (HTTP) between two esps boards to exchange data without the need to connect to the internet (you don’t need a router).
You’re going to set one ESP as an Access Point (Server) and another ESP as a Station (Client). Then, the server and the client will exchange data (sensor readings) via HTTP requests. 
here, server esp creates its own wireless network( so that other wifi devices can connect to that network) and client esp is set as a station, connecting the server esp
The client can make HTTP GET requests to the server to request sensor data or any other information. It just needs to use the IP address of the server to make a request on a certain route: /temperature, /humidity or /pressure.
The server listens for incoming requests and sends an appropriate response with the readings.
The client receives the readings and displays them on the OLED display.

## you need the following parts:

    2x ESP Development boards 
    BME280 sensor
    I2C SSD1306 OLED display
    Jumper Wires
    Breaboard
    
 ### [resource]:(https://randomnerdtutorials.com/esp8266-nodemcu-client-server-wi-fi/)

# ESP-NOW Two-Way Communication Between ESP32 Boards
## ESP-NOW is a connectionless communication protocol developed by Espressif that features short packet transmission. This protocol enables multiple devices to talk to each other without using Wi-Fi.

### [resource]:(https://randomnerdtutorials.com/esp-now-two-way-communication-esp32/)

# Communication between two ESP8266 via WiFi
### [resource]:(https://www.aranacorp.com/en/communication-between-two-esp8266-via-wifi/)

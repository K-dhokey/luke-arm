# establishing communication between two esps
### [resource]:(https://esp32io.com/tutorials/communication-between-two-esp32)
#  wifi communication between two esps

## how to establish a Wi-Fi communication (HTTP) between two esps boards to exchange data without the need to connect to the internet (you don’t need a router).
You’re going to set one ESP as an Access Point (Server) and another ESP as a Station (Client). Then, the server and the client will exchange data (sensor readings) via HTTP requests. 
here, server esp creates its own wireless network( so that other wifi devices can connect to that network) and client esp is set as a station, connecting the server esp
The client can make HTTP GET requests to the server to request sensor data or any other information. It just needs to use the IP address of the server to make a request on a certain route: /temperature, /humidity or /pressure.
The server listens for incoming requests and sends an appropriate response with the readings.
The client receives the readings and displays them on the OLED display.

    
 ### [resource]:(https://randomnerdtutorials.com/esp8266-nodemcu-client-server-wi-fi/)

# ESP-NOW Two-Way Communication Between ESP32 Boards
## ESP-NOW is a connectionless communication protocol developed by Espressif that features short packet transmission. This protocol enables multiple devices to talk to each other without using Wi-Fi.

### [resource]:(https://randomnerdtutorials.com/esp-now-two-way-communication-esp32/)
### [resource]:(https://microcontrollerslab.com/esp-now-one-to-many-esp32-esp8266/)
# Communication between two ESP8266 via WiFi
### [resource]:(https://www.aranacorp.com/en/communication-between-two-esp8266-via-wifi/)

# youtube resources i refered
## ESP IDF WIFI Client connection of the esp32 and GET request from the internet site
### [resource]:(https://youtu.be/AvJAg9m0x1E)
## ESP-NOW - Peer to Peer ESP32 Network
### [resource]:(https://youtu.be/bEKjCDDUPaU)
## ESP32: How to setup ESP NOW for One Way Wireless Communication
### [resource]: (https://youtu.be/CbcnxGJkY-Q)


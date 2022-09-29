
# Luke Arm

### human emulating robotic hand

- Designing a cost effective arm housing 5 servos controlled by one slave esp-32 taking commands from a remote esp-32 by establishing wifi communication between the two,essentially one acting as a server and the other as a client.The user will have to relay finger flex data to the arm and control the servos using client esp accordingly.
- Communication protocol used is ESP-NOW as:
  - It overcomes the drawbacks of traditonal wifi connection.
  - The pairing between devices is needed prior to their communication. After the pairing is done, the connection is secure and peer-to-peer.
  - ESP NOW does not require a router for the connection,Thus this project can be used anywhere,at any remote places.
  - If suddenly one of the boards loses power or resets, when it restarts, it will automatically connect to its peers.
  
##### To read more about the project refer this documentation

## Table of contents
- #### About the project
  - Tech stack
  - file structure
- #### Getting Started
  - prerequisites
- #### Usage
- #### Connections
- #### Theory and Approach
- #### Results and Demo
- #### Code Flowchart
- #### Future Work
- #### Troubleshooting
- #### Contributors
- #### Acknowledgements and Resources
- #### License

## About the project
## Tech stack 
##### The following technologies were used for this project:
- ESP-IDF
- FreeRTOS
- Esp-now
## File structure

## Getting started 
### Prerequisites
##### To flash this project install ESP-IDF(ESP-IDF v4.0 and above): https://github.com/espressif/esp-idf. You can visit the ESP-IDF Programmming Guide for the installation steps.

## Cloning the repository
##### Clone the project by typing the following command in your Terminal/CommandPrompt

## Hardware
### Connections
##### Connect both ESP-32 to your device via USB to flash the code in it. flash the

## Usage

##### After following the above steps , use the following commands to:
##### build

```
idf.py build
```
##### Configuration

```
idf.py menuconfig
```
##### Flash and monitor : 
##### Connect two esp32 through ports and run the following command on two seprate terminals.The terminals will act as user interface.

```
idf.py -p (PORT) flash monitor
```
## contributors

- Kamakshi Dhokey
- Vaidic Gupta

## Acknowledgements and Resources
  
   - SRA VJTI Eklavya 2022
   - Refered FreeRTOS for FreeRTOS API.
   - Refered ESP_NOW for ESP-NOW API.



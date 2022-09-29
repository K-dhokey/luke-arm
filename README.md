
# Luke Arm

### human emulating robotic hand

Designing a cost effective arm housing 5 servos controlled by one slave esp-32 taking commands from a remote esp-32 by establishing wifi communication between the two,essentially one acting as a server and the other as a client.The user will have to relay finger flex data to the arm and control the servos using client esp accordingly.

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
##### To flash this project install ESP-IDF: https://github.com/espressif/esp-idf

## Cloning the repository
##### Clone the project by typing the following command in your Terminal/CommandPrompt

## Hardware
### Connections
##### Connect the ESP32 to your device via USB to flash the code in it.

## Usage

##### After following the above steps , use the following commands to: Build

'''
idf.py build
'''

##### Flash
...
idf.py -p (PORT) flash monitor
...

##### Configuration

...
idf.py menuconfig
...
       

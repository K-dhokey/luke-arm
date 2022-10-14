
# Luke Arm

### human emulating robotic hand

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Tech Stack](#tech-stack)
  * [File Structure](#file-structure)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Results and Demo](#results-and-demo)
* [Future Work](#future-work)
* [Troubleshooting](#troubleshooting)
* [Contributors](#contributors)
* [Acknowledgements and Resources](#acknowledgements-and-resources)
* [License](#license)


<!-- ABOUT THE PROJECT -->
## About The Project


* Aim of the project is designing a cost effective arm housing 5 servos controlled by one slave esp-32 taking commands from a remote esp-32 by establishing wifi communication between the two,essentially one acting as a server and the other as a client.The user will have to relay finger flex data to the arm and control the servos using client esp accordingly.

* Communication protocol used is ESP-NOW as
  * It overcomes the drawbacks of traditonal wifi connection.
  * The pairing between devices is needed prior to their communication. After the pairing is done, the connection is secure and peer-to-peer.
  * ESP NOW does not require a router for the connection,Thus this project can be used anywhere,at any remote places.
  * If suddenly one of the boards loses power or resets, when it restarts, it will automatically connect to its peers.

To read more about the project refer this [documentation](https://github.com/K-dhokey/luke-arm/blob/main/Docs/Documentation%20.pdf)

### Tech Stack

* [FreeRTOS](https://www.freertos.org/openrtos.html)
* [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)


### File Structure
     .
    ├── Components              # Contains files of specific library of functions or Hardware used
    │    ├──esp_now             # Contains the code to setup connection using ESP-NOW. 
    │    ├──CMakeLists.txt      # To include this component in a esp-idf 
    ├── docs                    # Documentation files 
    │   ├── report.pdf          # Project report
    │   └── results             # Folder containing the video, gifs of the result
    ├── main                    # Source files of project
    │   ├──main.c               # Main Source code.
    │   ├──kconfig.projbuild    # Shows the menu of project configuration
    │   ├──CMakeLists.txt       # To include source code files in esp-idf.
    ├── CmakeLists.txt          # To include components and main folder while executing
    ├── LICENSE
    └── README.md 
    

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* **ESP-IDF v4.0 and above**

  You can visit the [ESP-IDF Programmming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#installation-step-by-step) for the installation steps.

### Installation
clone the repo
```sh
https://github.com/K-dhokey/luke-arm.git
```

<!-- USAGE EXAMPLES -->
## Usage
### Configuration

```
idf.py menuconfig
```

### Build
```
idf.py build
```
### Flash and Monitor
* Connect two esp32 through ports and run the following command on two seprate terminals.
* The terminals will act as user interface. 
```
idf.py -p /dev/ttyUSB0 flash monitor

```
```
idf.py -p /dev/ttyUSB1 flash monitor

```
<!-- CODE  -->
## Code
* The input of finger flex data is taken from the user connected to master esp32.
* This data is sent through espnow and is sent to other slave esp32 board.
* the slave esp32 controls the servos based on the data sent from master esp32.
* When the data is received,the servos pull the fingers leading to hand movements.



<!-- RESULTS AND DEMO -->
## Results and Demo
![**Setup**](https://github.com/K-dhokey/luke-arm/blob/main/assets/IMG-20221014-WA0003.jpg)


<!-- CONTRIBUTORS -->
## Contributors
* [Kamakshi Dhokey](https://github.com/K-dhokey)
* [Vaidic Gupta](https://github.com/Vaidicgupta)


<!-- ACKNOWLEDGEMENTS AND REFERENCES -->
## Acknowledgements and Resources
* [SRA VJTI](http://sra.vjti.info/) Eklavya 2020
* Special thanks 
  [om sheladia](https://github.com/omsheladia) ,[rishikesh donadkar](https://github.com/RISHI27-dot) 
* Refered [FreeRTOS](https://www.freertos.org/) for FreeRTOS API.
* Refered [ESP_NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html) for ESP-NOW API.



<!-- LICENSE -->
## License
Describe your [License](LICENSE) for your project. 

# Driver
## About
Firmware for the pan tilt device of the project using arm processors. The two boards considered for this project are the KL25Z because of the large amount of tutorials and support available and the K82F because of it's onboard magnetometer and flex IO and similarity with the KL25Z. 

Some code of this project is based off the Alexander G Dean's Serial-Demo 

## Desired Features
### Magnetometer
* Read magnetometer raw values via ADC
* Communication with sensor via I^2C

### Onboard Light
* turn on

### Light
* send signal to turn on/off light via some GPIO port
* send completion status over serial

### Serial Communication
* Send magnetometer values
* recieve commands sent by GUI
* send status of commands sent by GUI

## Scheduling
Type: Non premptive
### Window
#### Event Driven Tasks

#### Periodic Tasks

### General Application structure/ Architecture
![System Diagram](https://github.com/MiguelAmaro/baboom_Driver/blob/master/docs/diagram_EmbeddedSystem.png)
![Modules and Dependencies Diagram](https://github.com/MiguelAmaro/baboom_Driver/blob/master/docs/diagram_Modules%26Dependencies.png)

### Device Info
Clock Speed: 48Mhz

## Portability
Intended to run on any Desktop PC

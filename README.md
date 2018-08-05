# Autopilot
Generic autopilot and 'Remote' control of boats
Consists of Android application, RPI3 application a stepper motor
and a driver


## Equipment 
Raspberry pi3
23 Nema Stepper motor
M542T Motor driver


### Wiring
Later


## Software 
### Simulator
#### Android part
Open a terminal
cd AndroidModule
qmake Autopilot.pro
make
./debug/Autopilot

### Microcontroller part
Open a new terminal
cd MicrocontrollerModule/Application/
edit Makefile to have CXX = g++ (comment out CXX = arm-linux g++ with #)
make
./build/Application


### Overview
#### AndroidModule
The androidmodule runs on a phone (Or the pc during simulation)
It is responsible for showing the map, the location of the android device running It,
as well as taking user input to send to the uC.
The user input can be either rotate the motor,
setting a desired heading (not implemented on uC side)
or setting waypoints to follow (not implemented on uC side).
From the uC it receives the heading from a magnetometer (not implemented)
The androidmodule consits of the following parts

#### Main.cpp
Starts the networkmodule and guimodule as well as defining the objects (Outbox
and inbox) that are shared between them.

#### GUIModule
Responsible for all that is drawn to screen. Most of the code is written in main.qml.
Input to main.qml are pointers to the Inbox and Outbox handled by the NetworkModule.


#### NetworkModule
Sets up a TCP server and starts an endless loop reading and sending messages to
the connected client. The loop is started in a thread in main.cpp
When messages are received they are written to the Inbox. The member of the Inbox
is currently the measured heading
The Outbox class consists of the desired State (Off, Hold, Clockwiseturn,CounterClockwiseTurn, 
Autopilot) and the desired heading. The later is only used when the desired state = Autopilot














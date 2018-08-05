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

## Running Simulation
### Android part
```
Open a terminal
cd AndroidModule
qmake Autopilot.pro
make
./debug/Autopilot


Qt linux can be installed by following the guide here
http://doc.qt.io/qt-5/linux.html
```

### Microcontroller part
```
Open a new terminal
cd MicrocontrollerModule/Application/
edit Makefile to have CXX = g++ (comment out CXX = arm-linux g++ with #)
make
./build/Application
```
## Runnng on Hardware
Later

## Software 

### AndroidModule
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


### MicrocontrollerModule/Application
The MicrocontrollerModule should connect to the TCPserver created
by the androidmodule, receive messages from the Android phone and
turn the stepper motor accordingly. Also it should read and filter data
from a magnetometer to calculate the heading (not implemented)


#### Main.cpp
Creates the Inbox and Outbox and networkmanager objects.
Starts the networkmanager task which communicates with the android.
Starts the controlTask which uses the messages received to carry out 
commands on the stepper motor



#### NetworkModule
Sets up a TCPClient which connects to the TCPServer created by the android module.
IF simulation is set in the makefile (CXX=g++) then the ip it connects to is
the 127.0.0.1 (local ip), else it is Android hotspot default ip (192.168.43.1).
In case of a disconnection it will try to reconneect until succeeded. 
Sends Outbox which consists of the calculated heading (Not yet implemented)
and reads the task and desired heading and writes it to the Inbox.


#### MotorModule
Uses the WiringPi library to initialise the GPIO on the raspberry pi.
By toggling the pulse pin the stepper motor moves one step. For now only 
turnign is implemented. Ie. the module does not remember how many steps it has taken 
(most be implemnted for an autoplot)


#### SimulatorModule
The wiringPi library speaks directly to the Hardware on the rpi.
This is done by the commands pinMode, digitaWrite and wiringPiSetup.
IF simulator is defined theese functiosn are overloaded to basic print
functions so the program can be tested on a computer which doesn't have the necessary hardware






















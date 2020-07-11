# :computer_mouse: Mouse Control with Arduino joystick :computer_mouse:
---
# C++ Library to control your mouse, using [SerialPort](https://github.com/manashmandal/SerialPort) library.

## Circuit Diagram

Just a common 5 pin joystick, USB cable and jumper wires:

<img src="https://exploreembedded.com/wiki/images/5/5f/0_Joystick_with_Arduino_bb.png" width="400">

## How to build and use

### CMake and Visual Studio

Cmake:

> **Where is the source code:**  YourDirectory/MouseControlWithArduinoJoystick

> **Where to build the binaries:** YourDirectory/MouseControlWithArduinoJoystick/build

 Create the directory if applicable, configure then generate. Build all in Visual Studio.
 
 Execute **SerialPortExecutable.exe** then uppload **joystickSendData.ino** to your Arduino.
 
 Move the joystick to control the mouse cursor and push it to press right click button!
 
## Issues
### - C++ executable must be opened before connecting Arduino (crash otherwise)

Just a beginner, this is probably due to my lack of telecommunications concepts.

### - Disconecting Arduino causes runtime crash

Maybe better ``` arduino->isConnected()```  checks can solve this problem.

### - Random crashes are few and far between, but there are

Serial buffer issue?

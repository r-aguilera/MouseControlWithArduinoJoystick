#include <iostream>
#include "SerialPort.hpp"
#include <stdio.h>
#include <string.h>
#include <WinUser.h>

#define MAX_DATA_LENGTH 255
#define REDUCTION_FACTOR 20

char *portName = "\\\\.\\COM3";
char incomingData[MAX_DATA_LENGTH];

// Arduino SerialPort global object
SerialPort *arduino;

// String data from joystick to int variables
void readData(int& X, int& Y, int& SW) {
    int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
    char *tokenX = strtok(incomingData, ",");
    char *tokenY = strtok(NULL, ",");
    char *tokenSW = strtok(NULL, ",");
    sscanf(tokenX, "%d", &X);
    sscanf(tokenY, "%d", &Y);
    sscanf(tokenSW, "%d", &SW);
}

int main() {
    arduino = new SerialPort(portName);

    while (1) {
        // Wait for Arduino connection
        while (!arduino->isConnected()) {
            Sleep(100);
            arduino = new SerialPort(portName);
        }

        // Message when Arduino is connected
        if (arduino->isConnected()) {
            std::cout << std::endl << "Connection established at port " << portName << std::endl;
        }
        
        for (int i = 0; arduino->isConnected() && i < 2; ++i) { // Toss the two first readings
            arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
            Sleep(20);
        }

        int Xpos, Ypos, SWstate, Xpos_i, Ypos_i, SWstate_i;

        readData(Xpos_i, Ypos_i, SWstate_i);    // First reading, taken as reference (DON'T MOVE THE JOYSTICK!)
        Sleep(20);

        while (arduino->isConnected()) {
            readData(Xpos, Ypos, SWstate);
            std::cout << Xpos << "\t" << Ypos << "\t" << SWstate << std::endl;
           
            INPUT input;
            input.type = INPUT_MOUSE;
            input.mi.dx = (LONG)((Xpos - Xpos_i) / REDUCTION_FACTOR);
            input.mi.dy = (LONG)((Ypos - Ypos_i) / REDUCTION_FACTOR);
            input.mi.dwFlags = (MOUSEEVENTF_MOVE);// | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
            input.mi.mouseData = 0;
            input.mi.dwExtraInfo = NULL;
            input.mi.time = 0;
            SendInput(1, &input, sizeof(INPUT));

            Sleep(20);
        }
    }
}

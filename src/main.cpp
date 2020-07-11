#include <iostream>
#include "SerialPort.hpp"
#include <stdio.h>
#include <string.h>
#include <WinUser.h>

#define MAX_DATA_LENGTH 255
#define JOSTICK_DELAY 20
#define REDUCTION_FACTOR 35

char *portName = "\\\\.\\COM3";
char incomingData[MAX_DATA_LENGTH];

// Arduino SerialPort global object
SerialPort *arduino;

// Joystick variables: X and Y position and switch (push button) state
int Xpos    =   0,  Ypos    =   0,  SWstate         =   0,  // Current readings, used to simulate a mouse
    Xpos_i  =   0,  Ypos_i  =   0,  SWstate_i       =   0,  // First readings, used as reference
                                    SWstate_last    =   0;  // Last switch reading, used to properly simulate left clicks

// String data from joystick to int variables
int readData(int& X, int& Y, int& SW) {
    int bytesCount = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
    char *tokenX = strtok(incomingData, ",");
    char *tokenY = strtok(NULL, ",");
    char *tokenSW = strtok(NULL, ",");
    sscanf(tokenX, "%d", &X);
    sscanf(tokenY, "%d", &Y);
    sscanf(tokenSW, "%d", &SW);
    return bytesCount;
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

        // Toss the two first readings
        for (int i = 0; arduino->isConnected() && i < 2; ++i) { 
            arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
            Sleep(JOSTICK_DELAY);
        }

        // First reading, taken as reference (DON'T MOVE THE JOYSTICK!)
        if (arduino->isConnected()) {
            readData(Xpos_i, Ypos_i, SWstate_i);    
            Sleep(JOSTICK_DELAY);
        }

        SWstate_last = SWstate_i;

        while (arduino->isConnected()) {
            readData(Xpos, Ypos, SWstate);
            std::cout << Xpos << "\t" << Ypos << "\t" << SWstate << std::endl;
                       
            INPUT input;
            input.type = INPUT_MOUSE;
            input.mi.dx = (LONG)((Xpos - Xpos_i) / REDUCTION_FACTOR);
            input.mi.dy = (LONG)((Ypos - Ypos_i) / REDUCTION_FACTOR);
            input.mi.dwFlags = (MOUSEEVENTF_MOVE);
            if (SWstate != SWstate_last && SWstate != SWstate_i)
                input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN);
            else if (SWstate != SWstate_last && SWstate == SWstate_i)
                input.mi.dwFlags = (MOUSEEVENTF_LEFTUP);
            input.mi.mouseData = 0;
            input.mi.dwExtraInfo = NULL;
            input.mi.time = 0;
            SendInput(1, &input, sizeof(INPUT));

            SWstate_last = SWstate;
            Sleep(JOSTICK_DELAY);
        }
    }
}

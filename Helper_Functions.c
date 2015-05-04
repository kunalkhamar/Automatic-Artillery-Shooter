// This file contains all miscellaneous helper functions
// used throughout the code

#define _HELPER_FUNCTIONS_C
#include "Helper_Functions.h"
#include "Variable_Declarations.c"
#include "Base_Functions.c"

void initialize() {
    SensorType[COLOR] = sensorCOLORFULL;
    SensorType[US] = sensorSONAR;

    nMotorEncoder[FEEDER] = 0;
    nMotorEncoder[BASE] = 0;

    nMotorPIDSpeedCtrl[WHEELS] = mtrSpeedReg;
    nMotorPIDSpeedCtrl[BASE] = mtrSpeedReg;

    nxtDisplayString(0, "Press orange");
    nxtDisplayString(1, "to begin");
    while (nNxtButtonPressed != 3);
    while (nNxtButtonPressed == 3);
    eraseDisplay();
    time1[0] = 0;       // main program timer
}

void terminate() {
    motor[WHEELS] = 0;
    resetAngle();
    running = false;

    nxtDisplayString(2, "Runtime:");
    nxtDisplayString(3, "%.2f s", time1[0]/1000.0); // Display runtime on screen
    wait1Msec(2000);

    StopAllTasks();
}

int getColor() {
    return SensorValue[COLOR];
}

bool isValidColor(int col) {
    return col == COLOR_BLUE || col == COLOR_GREEN ||
           col == COLOR_RED;
}

int baseAngle() {
    return nMotorEncoder[BASE];
}

int distance() {
    return SensorValue[US];
}

bool inRange(int reading) {
    return reading >= MIN_DIST && reading <= MAX_DIST;
}

float roundFloat(float num) {
    if (num - (int) num < 0.5)
        return floor(num);
    else
        return ceil(num);
}

// Display the ultrasonic sensor reading live on the
// NXT screen
// This runs as a separate task, i.e. different thread
task displaySONAR() {
    while (running) {
        nxtDisplayString(0, "US:%d", distance());
        wait1Msec(25);
    }
}

// This file contains all functions to control the shooter and
// feeder sub-systems of the robot

#define _SHOOTER_FUNCTIONS_C
#include "Shooter_Functions.h"
#include "Variable_Declarations.c"
#include "Helper_Functions.c"

void feed() {
    time1[1] = 0;

    nMotorEncoder[FEEDER] = 0;

    nMotorEncoderTarget[FEEDER] = ONE_ROTATION;
    motor[FEEDER] = MAX_FEEDER_POWER;
    while(nMotorRunState[FEEDER] != runStateIdle);
    motor[FEEDER] = 0;

    while (time1[1] < 1000); // the process is given 1 second
}

int calcWheelPower(int distRaw, int color) {
    float dist = distRaw - DIST_OFFSET;

    // Equations are cubic polynomials determined through experimental data and curve fitting.
    if(distRaw>=0 && distRaw<=MAX_DIST){
        switch(color) {
            case COLOR_BLUE:
                wheelPower = 0.000003*(pow(dist,3)) - 0.0021*(dist*dist) + 0.6219*dist + 13;
                break;
            case COLOR_GREEN:
                wheelPower = 0.000006*(pow(dist,3)) - 0.0034*(dist*dist) + 0.6802*dist + 18.828;
                break;
            case COLOR_RED:
                wheelPower = -0.00002*(pow(dist,3)) - 0.0005*(dist*dist) + 0.4849*dist + 30.232;
                break;
            default:
                wheelPower = 0;
                break;
        }
    } else
        wheelPower = 0;

    #ifdef DEBUG
        nxtDisplayString(4, "P:%d  C:%s", wheelPower, COLORS[color]);
    #endif

    return wheelPower;
}

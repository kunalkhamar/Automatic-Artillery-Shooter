// This file contains all functions to control the
// sub-systems of the rotating base of the robot

#define _BASE_FUNCTIONS_C

#include "Base_Functions.h"
#include "Variable_Declarations.c"
#include "Helper_Functions.c"


bool resetAngle() {
    nMotorEncoder[BASE] = 0;
    nMotorEncoderTarget[BASE] = rotation;

    motor[BASE] = BASE_POWER_RESET;
    while (nMotorRunState[BASE] != runStateIdle);
    motor[BASE] = 0;

    return nMotorEncoder[BASE] == rotation;
}

int calcOffsetFromDist(int dist) {
    dist -= DIST_OFFSET;
    if (dist < 10 || dist > 65)
        return 0;

    for (int i = 0; i < 8; i++)
        if (specialOffsets[i][0] == dist)
            return specialOffsets[i][1];

    dist = (int) ((dist+2)/ 5.0) * 5;
    return distToOffset[dist/5 - 2][1];
}

int detectBox() {
    if (baseAngle() >= MAX_ANGLE)
        return -1;

    int leftDist = 0;                   // distance (approx) of box
    int firstEdge = 0, secondEdge = 0;  // angle of first and second edges

    motor[BASE] = BASE_POWER;
    while (baseAngle() < MAX_ANGLE && !inRange(distance())) {
        // while angle < max angle and target is not detected
        #ifdef DEBUG
	        nxtDisplayString(1, "bA:%d", baseAngle());
	        nxtDisplayString(2, "D:%d", distance());
        #endif
    }

    if (baseAngle() >= MAX_ANGLE)   // No target found
        return -1;

    leftDist = distance();
    firstEdge = baseAngle();        // record angular position
    while(inRange(distance()));     // while target is detected
    secondEdge = baseAngle();       // record angular position
    motor[BASE] = 0;
    wait1Msec(500);                 // wait for motor to stop

    int inertialError = baseAngle() - secondEdge;   // since the motor cannot stop instantly
    float actualDist = cosDegrees((firstEdge-secondEdge)/4.5 - 19)*leftDist;
                                    // division by 2 * 2.25, because geared up
                                    // -19 was found to work by trial-and-error
    int offset = calcOffsetFromDist((int) roundFloat(actualDist)) - 7;
                                    // 7 was found to work by trial-and-error
    int degreesBackWall = (int) ((secondEdge - firstEdge)/2.0 - offset + inertialError);

    #ifdef DEBUG
        nxtDisplayString(1, "bA:%d", baseAngle());
        nxtDisplayString(6, "DBW:%d", degreesBackWall);
    #endif

    rotation += nMotorEncoder[BASE] - degreesBackWall;  // add angle rotated to total rotation
    nMotorEncoder[BASE] = 0;
    nMotorEncoderTarget[BASE] = degreesBackWall;
    motor[BASE] = BASE_POWER_RESET;
    while (nMotorRunState[BASE] != runStateIdle);       // while motor is not stationary/idle
    motor[BASE] = 0;
    int timeElapsed = time1[0];
    wait1Msec(100);

    nxtDisplayString(0, "Time elapsed to");
    nxtDisplayString(1, "locate: %.2f s", timeElapsed/1000.0);

    #ifdef DEBUG
	    nxtDisplayString(1, "bAf:%d T:%.2f", baseAngle(), timeElapsed/1000.0);
	    nxtDisplayString(2, "Off:%d Ad:%f", offset, actualDist);
	    nxtDisplayString(3, "fE:%d sE:%d", firstEdge, secondEdge);
	    nxtDisplayString(7, "Df:%d", baseAngle(), distance());
    #endif

    return distance();
}

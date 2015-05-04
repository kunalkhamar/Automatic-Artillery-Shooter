// Function prototypes for the rotating base of the robot

#ifndef _BASE_FUNCTIONS_H
#define _BASE_FUNCTIONS_H

// Return base to angle it started from at the beginning of program
bool resetAngle();

// Calculate offset (deviance from calculated value) of the
// angle the base should turn, to point the shooter towards
// the center of the target.
// Some values were tested and stored in an array
// The value that is closest to the parameter passed to the
// function is returned
int calcOffsetFromDist(int dist);

// Scan circular perimeter around the robot clockwise
// Use the angular position (encoder count) of left and right
// edges to approximately align the robot so that
// it faces the center of the target
// Returns distance to the target
int detectBox();

#endif

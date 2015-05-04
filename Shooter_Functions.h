// Function prototypes for the shooter

#ifndef _SHOOTER_FUNCTIONS_H
#define _SHOOTER_FUNCTIONS_H

// Rotate the feeder motor 360 degrees to feed one ball into the shooter.
// There is a timeout of 1 second (function will exit after that time).
// Average error of 1-2 degrees.
void feed();

// Calculate motor power of shooter wheels for a specified target
// distance and ball colour.
int calcWheelPower(int distRaw, int color);

#endif

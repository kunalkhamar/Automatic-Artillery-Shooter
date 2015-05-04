// Function prototypes for helper functions

#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

// Configure sensors, reset encoders, enable speed PID and
// wait for button press from user to start program.
void initialize();

// Turn off shooter, turn turret back to original angle,
// display total runtime on screen and end program.
void terminate();

// Return the integer value corresponding to the colour sensed.
int getColor();

// Return true if colour sensed is blue, green or red (valid ball
// in robot).
bool isValidColor(int col);

// Return encoder count for base motor.
int baseAngle();

// Return ultrasonic reading (distance to backboard of target).
int distance();

// Return true if distance reading is within the defined
// minimum and maximum distances.
bool inRange(int reading);

// Round a float to the nearest integer.
float roundFloat(float num);

#endif

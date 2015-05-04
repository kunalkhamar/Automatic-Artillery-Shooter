// This file contains all of the variable declarations
// and definitions to be used in the rest of the code

#define _VARIABLE_DECLARATIONS_C

//#define DEBUG // Pre-processor directive that switches between 'debug' and 'functional' mode

// Variable declarations

const tMotor WHEELS = motorA;  // Motor for shooter/wheels
const tMotor FEEDER = motorB;  // Motor for feeder/poker
const tMotor BASE = motorC;    // Motor for rotation/base

const tSensors COLOR = S1;     // Color sensor
const tSensors US = S4;        // Ultrasonic sensor

const int MAX_FEEDER_POWER = 80;        // Motor power for feeder mechanism
const int BASE_POWER = -15;             // Motor power for regular base movement
const int BASE_POWER_RESET = -(BASE_POWER - 4); //Motor power for resetting base movement

const int ONE_ROTATION = 360;
const int MAX_ANGLE = 270;               // Maximum angle that base can safely turn
const int MIN_DIST = 10, MAX_DIST = 100; // Minimum and maximum distance that ultrasonic should detect
const float DIST_OFFSET = 31.5; // 31.5 cm is the length of entire target + dist from front of base to US sensor.

const string COLORS [7] = { "","BLACK","BLUE","GREEN","YELLOW","RED","WHITE" };
const int COLOR_BLUE = 2, COLOR_GREEN = 3, COLOR_RED = 5;

bool running = true;    // State of program
int wheelPower = 0;     // Shooter wheel motor power
int rotation = 0;       // Angle that robot turned from starting position to center of target

// Arrays that contain angle offset data for specific target distances
const int distToOffset [12][2] = { {10,11},{15,11},{20,11},{25,9},{30,9},{35,7},{40,7},{45,5},{50,5},{55,3},{60,2},{65,3} };
const int specialOffsets[8][2] = { {22,10},{23,10},{32,8},{33,8},{42,6},{43,6},{52,4},{53,4} };

#ifndef _VARIABLE_DECLARATIONS_C
#include "Variable_Declarations.c"
#endif

#ifndef _HELPER_FUNCTIONS_C
#include "Helper_Functions.c"
#endif

#ifndef _BASE_FUNCTIONS_C
#include "Base_Functions.c"
#endif

#ifndef _SHOOTER_FUNCTIONS_C
#include "Shooter_Functions.c"
#endif

// Main loop that executes program for robot
task main() {
    initialize();

    #ifdef DEBUG
        StartTask(displaySONAR);    // acquire and display sensor readings from a different thread
    #endif

    int dist = detectBox();
    bool firstSpinUp = true;
    int col = getColor();

    while (isValidColor(col)) {
	    int power = calcWheelPower(dist, col);
	    motor[WHEELS] = -power;

	    if (firstSpinUp) {
	        wait1Msec(5000);
	        firstSpinUp = false;
	    } else
	        wait1Msec(3000);

	    feed();
	    wait1Msec(1000); // Pause so next ball can get aligned
	    col = getColor();
    }

    #ifdef DEBUG
        nxtDisplayString(5, "TERMINATED");
    #endif
    terminate();
}

#ifndef __CONFIG__
#define __CONFIG__

/**DEBUG options
 * WARNING: It gets a bit messy if both are enabled
 */

// #define __LOG         //for explicit messages from tasks.
// #define __DEBUG       //for "cryptic" messages from the scheduler and few other things.

// LED
#define L1_PIN 7 // Green diode led
#define L2_PIN 6 // Red diode led
#define L3_PIN 5 // Green diode led

// BUTTON
#define BUTTON_PIN 4

// Termometer
#define TMP_PIN A0
#define TMP_READ_DELAY 500 // read temperature once per second/2 (500 ms)

// PIR
#define PIR_PIN 2

// SONAR
#define SONAR_TRIG_PIN 11
#define SONAR_ECHO_PIN 12
#define SONAR_MAX_TIME 30000 // 30 ms

// SERVO
#define SERVO_PIN 9

/**
 * TODO: TIMING, time constants for example N4.... etc
 */
#define N1 2
// Time for the gate to open after car presence (in seconds)
#define MINDIST 10.0f  // Minimum distance for car fully entering (in cm)
#define N2 10          // Time to consider car fully entered (in seconds)
#define N3 15          // Time for the washing process (in seconds)
#define MAXDIST 30     // Maximum distance to consider car leaving (in cm)
#define N4_FOR_DIST 10 // Time to consider car fully left (in seconds)
#define N5 5           // Time to check for critical temperature (in seconds) then it goes in error state
#define MAXTEMP 30     // Maximum temperature before maintenance required (in Celsius)

#endif

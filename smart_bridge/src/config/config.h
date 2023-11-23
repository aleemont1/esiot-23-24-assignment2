#ifndef __CONFIG__
#define __CONFIG__

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

// SERVO
#define SERVO_PIN 9

/**
 * TODO: TIMING, time constants for example N4.... etc
 */
#define N1 10      // Time for the gate to open after car presence (in seconds)
#define MINDIST 10 // Minimum distance for car fully entering (in cm)
#define N2 10      // Time to consider car fully entered (in seconds)
#define N3 15      // Time for the washing process (in seconds)
#define MAXDIST 30 // Maximum distance to consider car leaving (in cm)
#define N4 10      // Time to consider car fully left (in seconds)
#define MAXTEMP 50 // Maximum temperature before maintenance required (in Celsius)

#endif

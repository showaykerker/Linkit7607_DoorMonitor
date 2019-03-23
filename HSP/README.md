# HSP.ino

## Settings
TODO

``` C++

// HSP_defines.h

#ifndef HSP_DEFINES_H
#define HSP_DEFINES_H

/* ========== User Settings ========== */
#include "HSP_CallsAndPswd.h"
// Define WIFI_SSID, WIFI_PSWD, ENTER_PSWD, TRIGGER_START, TRIGGER_ALERT in it.


// Wait for how many seconds after launching the system
#define WAIT_FOR_GO_OUT 1
// Wait for how many seconds to turn off lcd
#define TURN_OFF_SEC 5 


/* ========== Advanced Settings ========== */
// Threshold of Hall Effect Sensor
#define HALL_UPPER_THRESH 700
#define HALL_LOWER_THRESH 300



/* ========== Code Definitions ========== */
// DONT TOUCH ANY OF THIS 
// IF YOU DONT KNOW WHAT YOU'RE DOING
#define COUNT_FREQ 10 // Counting Frequency of t
// Pin Definitions
#define Hall 6
#define SCL 8
#define SDA 9
#define Buzzer 15
#define LED_Yellow 16
#define LED_Orange 17


enum LEDIND{
	// Blink Pattern 1 (Regular Blink)
	NONE = 0,
	BLINK = 8,
	FAST_BLINK = 3,
	SLOW_BLINK = 16,
	// Blink Pattern 2
	STAND_BY = 50,
	ALERT = 5,
};

#endif


```
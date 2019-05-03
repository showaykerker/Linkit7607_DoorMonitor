# HSP.ino

## Settings
TODO

``` C++

#ifndef HSP_DEFINES_H
#define HSP_DEFINES_H

/* ========== Server Settings ========== */
// These need to be set according to the server.
#define RPI_SERVER "192.168.0.102"
#define RPI_PORT 8008

/* ========== User Settings ========== */
#include "HSP_CallsAndPswd.h"
// Define WIFI_SSID, WIFI_PSWD, ENTER_PSWD, TRIGGER_START, TRIGGER_ALERT in it.

// WONT sent GET request to server if this is set to 0
#define ENABLE_ALERT 1
#define ENABLE_BUZZER 0

// Wait for how many seconds after launching the system
#define WAIT_FOR_GO_OUT 1
// Wait for how many seconds to turn off lcd
#define TURN_OFF_SEC 5


/* ========== Advanced Settings ========== */
// Threshold of Hall Effect Sensor
#define HALL_UPPER_THRESH 2500
#define HALL_LOWER_THRESH 1000


/* ========== Code Definitions ========== */
// DONT TOUCH ANY OF THIS 
// IF YOU DONT KNOW WHAT YOU'RE DOING
#define COUNT_FREQ 10 // Counting Frequency of t
// Pin Definitions
#define Hall 17
#define SCL 8
#define SDA 9
#define Buzzer 3
#define LED_Yellow 4
#define LED_Orange 5


enum LEDIND{
	// Blink Pattern 1 (Regular Blink)
	NONE = 0,
	BLINK = 8,
	FAST_BLINK = 3,
	SLOW_BLINK = 16,
	// Blink Pattern 2
	STAND_BY = 50,
	ALERT = 2,
};

#endif




```
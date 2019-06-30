#ifndef HSP_DEFINES_H
#define HSP_DEFINES_H

/* ========== User Settings ========== */
#include "HSP_CallsAndPswd.h"
// Define WIFI_SSID, WIFI_PSWD, ENTER_PSWD, TRIGGER_START, TRIGGER_ALERT in it.

// WONT sent GET request to server if this is set to 0
#define ENABLE_ALERT 1
#define ENABLE_BUZZER 1

// Wait for how many seconds after launching the system
#define WAIT_FOR_GO_OUT 10
// Wait for how many seconds to turn off lcd
#define TURN_OFF_SEC 5


/* ========== Advanced Settings ========== */
// Threshold of Hall Effect Sensor
#define HALL_UPPER_THRESH 3000
#define HALL_LOWER_THRESH 1000
#define RPI_SERVER "192.168.0.18"
#define RPI_PORT 8008

/* ========== Advanced Settings ========== */
// Trigger to be sent to RPi
#define TRIGGER_START "GET /0"
#define TRIGGER_ALERT "GET /1"
#define TRIGGER_CLEAR "GET /2"
#define TRIGGER_USER_DEFINE1_1 "GET /601"
#define TRIGGER_USER_DEFINE1_2 "GET /602"
#define TRIGGER_USER_DEFINE1_3 "GET /603"
#define TRIGGER_USER_DEFINE1_4 "GET /604"
#define TRIGGER_USER_DEFINE1_5 "GET /605"
#define TRIGGER_USER_DEFINE2_1 "GET /801"
#define TRIGGER_USER_DEFINE2_2 "GET /802"
#define TRIGGER_USER_DEFINE2_3 "GET /803"
#define TRIGGER_USER_DEFINE2_4 "GET /804"
#define TRIGGER_USER_DEFINE2_5 "GET /805"

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

#ifndef HSP_DEFINES_H
#define HSP_DEFINES_H


/* ========== User Settings ========== */
#include "HSP_CallsAndPswd.h"
// Define WIFI_SSID, WIFI_PSWD, ENTER_PSWD, TRIGGER_START, TRIGGER_ALERT in it.

// Wait for how many seconds after launching the system
#define WAIT_FOR_GO_OUT 1

/* ========== Advanced Settings ========== */
// Wait for how many seconds to turn off lcd
#define TURN_OFF_SEC 5 


/* ========== Code Definitions ========== */
// DONT TOUCH ANY OF THIS 
// IF YOU DONT KNOW WHAT YOU'RE DOING
#define COUNT_FREQ 10 // Counting Frequency of t
// Pin Definitions
#define Hall 6
#define Buzz 14
#define SCL 8
#define SDA 9
#define LED 7

enum LEDIND{
	// Regular Blink
	NONE = 0,
	BLINK = 8,
	FAST_BLINK = 3,
	SLOW_BLINK = 16,
	// 
	STAND_BY = 50,
	ALERT = 5,
};

#endif

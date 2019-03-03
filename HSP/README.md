# HSP.ino

## Settings
TODO

``` C++

// HSP_defines.h

// Wait for how many seconds after launching the system
#define WAIT_FOR_GO_OUT 1
// Wait for how many seconds to turn off lcd
#define TURN_OFF_SEC 5 


/* ========== Advanced Settings ========== */
// Threshold of Hall Effect Sensor
#define HALL_UPPER_THRESH 700
#define HALL_LOWER_THRESH 300


/* ========== Code Definitions ========== */
// DONT TOUCH ANY OF THESE IF YOU DONT KNOW WHAT IT IS.
#define COUNT_FREQ 10 // Counting Frequency of t
// Pin Definitions
#define Hall 6
#define Buzzer 14
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

```
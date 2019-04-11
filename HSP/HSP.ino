#include "LTimer.h"
#include "HSP_WiFi.h"
#include "HSP_KEYPAD.hpp"
#include "HSP_defines.h"
#include "HSP_LCD_Wrapper.hpp"
#include "HSP_Buzzer.hpp"
#include <string.h>
using namespace std;

HSP_KeyPad kp;
HSP_WiFi client(WIFI_SSID, WIFI_PSWD);
HSP_LCD_Wrapper lcd(0x27);
HSP_Buzzer bz;

LTimer timer0(LTIMER_0);

// Timer
unsigned long int t = 0; // 0 ~ 4294697295/COUNT_FREQ second
unsigned long int start_t; 
unsigned long int last_press_t = 0;

// For LED
bool TurnOn = false;
LEDIND LEDI = NONE;
bool LED_ON = false;

// Alert
bool TRIGGERED = false;


void setup() {
	Serial.begin(9600);
	
	// timer
	timer0.begin();
	timer0.start( int(1000/COUNT_FREQ), LTIMER_REPEAT_MODE, _callback0, NULL );
	
	pinMode(LED_Yellow, OUTPUT); digitalWrite(LED_Yellow, HIGH);
	pinMode(LED_Orange, OUTPUT); digitalWrite(LED_Orange, HIGH);
	pinMode(Hall, INPUT);
	
	bz.start(); // Block for 3.5 quarter note, speed 120
	lcd.start(1000); // Block for 1000 ms
	LEDI = BLINK;
	client.connect_WiFi();
	if(LAUNCH_ALERT) client.trig(TRIG_START);
	lcd.wifi_connected(2500);

}

void loop() {
	digitalWrite(LED_Yellow, LOW); digitalWrite(LED_Orange, LOW);
	LEDI = STAND_BY;
	last_press_t = t;
	String enter_pswd = "";
	while(true){
		// if over TURN_OFF_SEC then turn lcd off
		if ( (t - last_press_t)/COUNT_FREQ >= TURN_OFF_SEC){
			LEDI = STAND_BY;
			lcd.noBacklight();
			enter_pswd = "";
		}
		if (!TurnOn){
			char key = kp.getKey();
      
			if (key){
				bz.beep(key); // Block for 50ms (*5 for special key)
				LEDI = BLINK;
				lcd.setBacklight(128);
				if (key=='#'){
					lcd.start_monitor();
					TurnOn = !TurnOn;
					start_t = t;
					lcd.count_down(WAIT_FOR_GO_OUT);
				}
				last_press_t = t;
			}
		}
		else{ // Turn On
			
			int HES = analogRead(Hall); // Hall Effect Sensor Reading.
			if ((HES<HALL_LOWER_THRESH or HES>HALL_UPPER_THRESH) and TRIGGERED == false){ 
				// Trigger Alert Event
				lcd.setBacklight(255);
				TRIGGERED = true;
				if(LAUNCH_ALERT) client.trig(1);
				LEDI = FAST_BLINK;
				lcd.show_triggered();
				last_press_t = t;
			}
			else{
				char key = kp.getKey();
				if(key){
					bz.beep(key); // Block for 50 ms (*5 for special key)
					if (TRIGGERED == false) LEDI = FAST_BLINK;
					lcd.setBacklight(128);
					if (key == '*'){ // Cancel
						enter_pswd = "";
						lcd.show_pswd(enter_pswd.c_str());
					}
					else{
						enter_pswd += key;
						lcd.show_pswd(enter_pswd.c_str());
						if (enter_pswd.length()>16){
              bz.wrong(); // Block for 8 quarter note, speed 180
							lcd.Wrong_PSWD();
							enter_pswd = "";
						}
						else if(enter_pswd == ENTER_PSWD){
              enter_pswd = "";
							LEDI = BLINK;
              bz.pass(); // Block for 2.25 quarter note, speed 120
							lcd.Welcome_Home(); // Block for 3500 ms
							TurnOn = !TurnOn;
							TRIGGERED = false;
						}

					}
					last_press_t = t;
				}
			}
			if (TRIGGERED){
				last_press_t = t;
        LEDI = ALERT;
        if (t % 25) lcd.show_triggered();
				bz.Alert(t); // No Block
        delay(20);
			}
		}
	}
}

void _callback0(void *usr_data){
	t++;
  
	if (LEDI == NONE);
	else{
		float tick = float(t)*10/float(COUNT_FREQ);
		if (LEDI == BLINK or LEDI == FAST_BLINK or LEDI == SLOW_BLINK){
			if ( int(tick) % LEDI == 0 and ceilf(tick) == tick ){
				LED_ON = !LED_ON;
				digitalWrite(LED_Yellow, LED_ON);
				digitalWrite(LED_Orange, LED_ON);
			}
		}
		else if (LEDI == STAND_BY or LEDI == ALERT){
			if ( int(tick) % LEDI == 0 and ceilf(tick) == tick ) LED_ON = true;
			else if( int(tick) % LEDI == 1 and ceilf(tick) == tick ) LED_ON = false;
			digitalWrite(LED_Yellow, LED_ON);
			digitalWrite(LED_Orange, LED_ON);
		}
	}
}

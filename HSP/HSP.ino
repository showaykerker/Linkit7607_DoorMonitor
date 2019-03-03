#include "LTimer.h"
#include "HSP_WiFi.h"
#include "HSP_KEYPAD.hpp"
#include "HSP_defines.h"
#include "HSP_LCD_Wrapper.hpp"
#include <string.h>
using namespace std;

HSP_KeyPad kp;
HSP_WiFi client(WIFI_SSID, WIFI_PSWD);
HSP_LCD_Wrapper lcd(0x27);

LTimer timer0(LTIMER_0);

unsigned long int t = 0; // 0 ~ 4294697295/COUNT_FREQ second
unsigned long int start_t;
unsigned long int last_press_t = 0;
bool TurnOn = false;
LEDIND LEDI = NONE;
bool LED_ON = false;

void setup() {
	Serial.begin(9600);
	
	// timer
	timer0.begin();
	timer0.start( int(1000/COUNT_FREQ), LTIMER_REPEAT_MODE, _callback0, NULL );
	
	pinMode(LED, OUTPUT); digitalWrite(LED, HIGH);
	pinMode(Buzz, OUTPUT); 
	pinMode(Hall, INPUT);
	lcd.start();
	lcd.setBacklight(255);
	LEDI = BLINK;
	client.connect_WiFi();
	//client.trig(TRIG_START);
	lcd.wifi_connected();

}

void loop() {
	digitalWrite(LED, LOW);
	LEDI = STAND_BY;
	last_press_t = t;
	String enter_pswd = "";
	while(true){
		// if over TURN_OFF_SEC
		if ( (t - last_press_t)/COUNT_FREQ >= TURN_OFF_SEC){
			LEDI = STAND_BY;
			lcd.noBacklight();
			enter_pswd = "";
		}
		if (!TurnOn){
			char key = kp.getKey();
			if (key){
				LEDI = BLINK;
				lcd.setBacklight(128);
				if (key=='*'){
					lcd.start_monitor();
					TurnOn = !TurnOn;
					start_t = t;
					lcd.count_down(WAIT_FOR_GO_OUT);
				}
				last_press_t = t;
			}
		}
		else{ // Turn On
			char key = kp.getKey();
			if(key){
				LEDI = FAST_BLINK;
				lcd.setBacklight(128);
				if (key == 'C'){ // Cancel
					enter_pswd = "";
					lcd.show_pswd(enter_pswd.c_str());
				}
				else if (key == 'D'){ // Enter
					if (enter_pswd == ENTER_PSWD){
						LEDI = BLINK;
						lcd.Welcome_Home();
						TurnOn = !TurnOn;
					}
					else{
						lcd.Wrong_PSWD();
						enter_pswd = "";
					}
				}
				else{
					enter_pswd += key;
					if (enter_pswd.length()>16) enter_pswd = "";
					lcd.show_pswd(enter_pswd.c_str());
				}
				last_press_t = t;
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
				digitalWrite(LED, LED_ON);
			}
		}
		else if (LEDI == STAND_BY or LEDI == ALERT){
			if ( int(tick) % LEDI == 0 and ceilf(tick) == tick ) LED_ON = true;
			else if( int(tick) % LEDI == 1 and ceilf(tick) == tick ) LED_ON = false;
			digitalWrite(LED, LED_ON);
		}
	}
}

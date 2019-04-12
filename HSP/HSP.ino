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

// Sensor
unsigned short int HLT = HALL_LOWER_THRESH; 
unsigned short int HUT = HALL_UPPER_THRESH;


void setup() {
	Serial.begin(9600);
	
	// timer
	timer0.begin();
	timer0.start( int(1000/COUNT_FREQ), LTIMER_REPEAT_MODE, _callback0, NULL );
	
	pinMode(LED_Yellow, OUTPUT); digitalWrite(LED_Yellow, HIGH);
	pinMode(LED_Orange, OUTPUT); digitalWrite(LED_Orange, HIGH);
	pinMode(Hall, INPUT);
	
	bz.start(); // Blocks for 3.5 quarter note, speed 120
	lcd.start(1000); // Blocks for 1000 ms
	LEDI = BLINK;
	client.connect_WiFi();
	if(ENABLE_ALERT) client.trig(TRIG_START);
	lcd.wifi_connected(2500);

}

void ToggleBuzzerEnable(){
	bz.toggleEnable();
	bool isEnable = bz.isEnable();
	if (isEnable) lcd.show_word(String("Buzzer Enabled.").c_str(), 1000);
	else lcd.show_word(String("Buzzer Disabled.").c_str(), 1000);
	
}

void HallMonitorMode(){
	unsigned short int last_val = 0;
	while (true){
		char key = kp.getKey();
		if (key) break;
		unsigned short int now_val = analogRead(Hall);
		String val = String(now_val);
		if (t%10==0) lcd.show_word(String("Reading: " + val).c_str(), String( "U: "+String(HUT) + ", L: "+String(HLT) ).c_str());
		last_val = now_val;
	}
	bz.beep('*');
	lcd.standby();
}

void HallThreshModifyMode(){
	String enter_word = "", last_enter_word="";
	unsigned short int mode = 0;
	lcd.show_word(String("Modify Thresholds.").c_str(), 1200);
	lcd.show_word( String( "U: " + String(HUT) ).c_str(), String( "L: " + String(HLT) ).c_str() );
	while (true){
		char key = kp.getKey();
		if (mode == 0){ // Blink for HUT
			if (t%20==0) lcd.show_word( String( "U: " + String(HUT) ).c_str(), String( "L: " + String(HLT) ).c_str() );
			else if (t%20==10) lcd.show_word( String( "U: " + String(HUT) + " <- " ).c_str(), String( "L: " + String(HLT) ).c_str() );
		}
		else if (mode == 1){ // Modify HUT
			if (t%10==0) lcd.show_word( String( "Current: " + String(HUT) ).c_str(), String( " -> New: " + enter_word ).c_str() );
			else if (t%10==5) lcd.show_word( String( "Current: " + String(HUT) ).c_str(), String( "    New: " + enter_word ).c_str() );
		}
		else if (mode == 2){ // Blink for HLT
			unsigned short int v = (last_enter_word.toInt()>0)?(last_enter_word.toInt()):(HUT);
			v = (v>9999) ? 9999 : v;
			if (last_enter_word!="") HUT = v;
			if (t%20==0) lcd.show_word( String( "U: " + String(HUT) ).c_str(), String( "L: " + String(HLT) ).c_str() );
			else if (t%20==10) lcd.show_word( String( "U: " + String(HUT) ).c_str(), String( "L: " + String(HLT) + " <- " ).c_str() );
		}
		else if (mode == 3){ // Modify HUT
			if (t%10==0) lcd.show_word( String( "Current: " + String(HLT) ).c_str(), String( " -> New: " + enter_word ).c_str() );
			else if (t%10==5) lcd.show_word( String( "Current: " + String(HLT) ).c_str(), String( "    New: " + enter_word ).c_str() );
		}
		else if (mode == 4){ // End
			unsigned short int v = (last_enter_word.toInt()>0)?(last_enter_word.toInt()):(0);
			if (last_enter_word!="" and v < HUT) HLT = v;
			HallMonitorMode();
			break;
		}
		if (key){
			bz.beep(key);
			if (key == '#'){ // Enter
				mode++;
				last_enter_word = enter_word;
				enter_word = "";
			}
			else if (key=='*'){ // Cancel
				enter_word = "";
				if (mode==0 or mode==2) mode += 2;
				else if (mode==1 or mode==3) mode += 1;
			}
			else enter_word += key;
		}
	}
}

bool check_reset(){
	// if over TURN_OFF_SEC then turn lcd off
	if ( (t - last_press_t)/COUNT_FREQ >= TURN_OFF_SEC){
		LEDI = STAND_BY;
		lcd.noBacklight();
		lcd.reset();
		return true;
	}
	return false;
}

void loop() {
	digitalWrite(LED_Yellow, LOW); digitalWrite(LED_Orange, LOW);
	LEDI = STAND_BY;
	last_press_t = t;
	String enter_word = "";
	while(true){
		if (check_reset()) enter_word = "";
		if (!TurnOn){ // Turn Off
			char key = kp.getKey();
			if (key){
				bz.beep(key); // Blocks for 50ms (*5 for special key)
				LEDI = BLINK;
				lcd.setBacklight(128);
				if (key=='#'){ // Enter
					if (enter_word==""){ // Start Monitor
						lcd.start_monitor();
						TurnOn = !TurnOn;
						lcd.count_down(WAIT_FOR_GO_OUT); // Block
						start_t = t;
					}
					else{ // Special Mode
						if (enter_word=="0") HallMonitorMode(); // HALL Monitor Mode
						else if (enter_word=="1") HallThreshModifyMode(); // Adjust Threshold Mode
						else if (enter_word=="8") ToggleBuzzerEnable(); // Toggle Buzzer Output, Blocks for 1 seconds
						else lcd.show_word(String("Entering:").c_str(), String("").c_str());
					}
					enter_word = "";
				}
				else if (key=='*'){ // Cancel
					enter_word = "";  
					lcd.show_word(String("Entering:").c_str(), String("").c_str());
				}
				else{
					enter_word += key;
					lcd.show_word(String("Entering:").c_str(), enter_word.c_str());
				}
				last_press_t = t;
			}
		}
		else{ // Turn On
			
			int HES = analogRead(Hall); // Hall Effect Sensor Reading.
			if ((HES<HLT or HES>HUT) and TRIGGERED == false){ 
				// Trigger Alert Event
				lcd.setBacklight(255);
				TRIGGERED = true;
				if(ENABLE_ALERT) client.trig(1);
				LEDI = FAST_BLINK;
				lcd.show_triggered();
				last_press_t = t;
			}
			else{
				char key = kp.getKey();
				if(key){
					bz.beep(key); // Blocks for 50 ms (*5 for special key)
					if (TRIGGERED == false) LEDI = FAST_BLINK;
					lcd.setBacklight(128);
					if (key == '*'){ // Cancel
						enter_word = "";
						lcd.show_word(String("Password:").c_str(), enter_word.c_str());
					}
					else{
						enter_word += key;
						lcd.show_word(String("Password:").c_str(), enter_word.c_str());
						if (enter_word.length()>16){
							bz.wrong(); // Blocks for 8 quarter note, speed 180
							lcd.Wrong_PSWD();
							enter_word = "";
						}
						else if(enter_word == ENTER_PSWD){
							enter_word = "";
							LEDI = BLINK;
							bz.pass(); // Blocks for 2.25 quarter note, speed 120
							lcd.Welcome_Home(); // Blocks for 3500 ms
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
				if (t % 25 == 0) lcd.show_triggered();
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

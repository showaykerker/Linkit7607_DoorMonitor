#ifndef HSP_BUZZER_HPP
#define HSP_BUZZER_HPP

#include<Arduino.h>
#include"HSP_defines.h"
#include"Buzzer_Pitches.h"

class HSP_Buzzer{
	public:
		HSP_Buzzer(){
			pinMode(Buzzer, OUTPUT);
			pin = Buzzer;
			t_times = 1 / COUNT_FREQ;
		}
		
		void beep(char type_){
			int f, delay_;
			if (type_ == '*' or type_ == 'C' or type_ == 'D'){
				f = NOTE_C7; 
				delay_ = delay_time * 5;
			}
			else{
				f = NOTE_G7; // Normal
				delay_ = delay_time;
			}
			tone(pin, f);
			delay(delay_);
			noTone(pin);
		}
		
		void Alert(unsigned long int t){
			
		}
		
		void pass(void){
			tone(pin, NOTE_C2); delay(240);
			noTone(pin); delay(10);
			tone(pin, NOTE_C2); delay(240);
			noTone(pin); delay(10);
			tone(pin, NOTE_C2); delay(115);
			noTone(pin); delay(10);
			tone(pin, NOTE_E2); delay(115);
			noTone(pin); delay(10);
			tone(pin, NOTE_G2); delay(115);
			noTone(pin); delay(10);
			tone(pin, NOTE_C3); delay(240);
			noTone(pin); delay(10);
		}
		
		void wrong(void){
			for(int i = 0; i<= 3; i++){
				tone(pin, NOTE_C2); delay(63);
				tone(pin, NOTE_C3); delay(63);
			}
			noTone(pin);
		}
		
	private:
		int pin;
		int delay_time = 50;
		float t_times;
		
		
};


#endif
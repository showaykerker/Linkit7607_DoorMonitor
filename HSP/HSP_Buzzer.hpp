#ifndef HSP_BUZZER_HPP
#define HSP_BUZZER_HPP

#include<Arduino.h>
#include"HSP_defines.h"
#include"Buzzer_Pitches.h"

float tempo_d(float spd, float div, float len){
	// 60 4 = 1000
	float ori = 1000.;
	ori /= ((spd/60.) * (div/4.));
	int ans = int(ori*len - 10);
	if (ans<0) ans = 0;
	return ans;
}

class HSP_Buzzer{
	public:
		HSP_Buzzer(){
			pinMode(Buzzer, OUTPUT);
			pin = Buzzer;
			t_times = 1 / COUNT_FREQ;
		}
		
		void beep(char type_){
			int f, delay_;
			if (type_ == '*' or type_ == '#'){
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
		
		void start(void){
			tone(pin, NOTE_G2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_F2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_E2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_D2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_C2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_C3); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
		}
		
		void Alert(unsigned long int t){
			int hint = t%12;
			if (t<3) tone(pin, NOTE_G4);
			else if (t<6) tone(pin, NOTE_FS4);
			else if (t<9) tone(pin, NOTE_F4);
			else if (t<12) tone(pin, NOTE_FS4);
		}
		
		void pass(void){
			tone(pin, NOTE_C2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_C2); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_C2); delay(tempo_d(120, 16, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_E2); delay(tempo_d(120, 16, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_G2); delay(tempo_d(120, 16, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_C3); delay(tempo_d(120, 8, 1));
			noTone(pin); delay(10);
		}
		
		void wrong(void){
			tone(pin, NOTE_A3); delay(tempo_d(180, 4, 1));
			noTone(pin); delay(10);
			tone(pin, NOTE_D4); delay( tempo_d(180, 4, 3.5) );
			noTone(pin); delay(10);
			tone(pin, NOTE_CS4); delay( tempo_d(180, 8, 1) );
			noTone(pin); delay(10);
			tone(pin, NOTE_C4); delay( tempo_d(180, 8, 1) );
			noTone(pin); delay(10);
			tone(pin, NOTE_B3); delay( tempo_d(180, 8, 1) );
			noTone(pin); delay(10);
			tone(pin, NOTE_AS4); delay( tempo_d(180, 8, 1) );
			noTone(pin); delay(10);
			tone(pin, NOTE_A4); delay( tempo_d(180, 8, 1) );
			noTone(pin); delay(10);
			tone(pin, NOTE_GS4); delay( tempo_d(180, 8, 2) );
			noTone(pin); delay(10);
			
		}
		
		void stop(void){
			noTone(pin);
		}
		
	private:
		int pin;
		int delay_time = 50;
		float t_times;
		
		
};


#endif
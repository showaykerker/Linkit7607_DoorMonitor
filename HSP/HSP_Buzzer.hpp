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
			this->pin = Buzzer;
			this->_enable = ENABLE_BUZZER;
			this->t_times = 1 / COUNT_FREQ;
		}
		
		void beep(char type_){
			if (!this->_enable) return;
			int f, delay_;
			if (type_ == '*' or type_ == '#'){
				f = NOTE_DS8; 
				delay_ = this->delay_time*5;
			}
			else if (type_=='x'){
				f = NOTE_C9;
				delay_ = this->delay_time;
			}
			else{
				f = NOTE_C8; // Normal
				delay_ = this->delay_time;
			}
			tone(this->pin, f);
			delay(delay_);
			noTone(this->pin);
		}
		
		void start(void){
			if (!this->_enable) return;
			tone(this->pin, NOTE_G6); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_F6); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_E6); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_D6); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_C6); delay(tempo_d(120, 4, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_C7); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			this->beep('x');
			this->beep('*');
			
		}
		
		void Alert(unsigned long int t){
			if (!this->_enable) return;
			int hint = t%12;
			if (hint<3) tone(this->pin, NOTE_G6);
			else if (hint<6) tone(this->pin, NOTE_FS6);
			else if (hint<9) tone(this->pin, NOTE_F6);
			else if (hint<12) tone(this->pin, NOTE_FS6);
		}
		
		void pass(void){
			if (!this->_enable) return;
			tone(this->pin, NOTE_C6); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_C6); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_C6); delay(tempo_d(120, 16, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_E6); delay(tempo_d(120, 16, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_G6); delay(tempo_d(120, 16, 1));
			noTone(this->pin);        delay(10);
			tone(this->pin, NOTE_C7); delay(tempo_d(120, 8, 1));
			noTone(this->pin);        delay(10);
			this->beep('x');
		}
		
		void wrong(void){
			if (!this->_enable) return;
			tone(this->pin, NOTE_A6);  delay(tempo_d(180, 4, 1));
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_D7);  delay( tempo_d(180, 4, 3.5) );
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_CS7); delay( tempo_d(180, 8, 1) );
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_C7);  delay( tempo_d(180, 8, 1) );
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_B7);  delay( tempo_d(180, 8, 1) );
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_AS7); delay( tempo_d(180, 8, 1) );
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_A7);  delay( tempo_d(180, 8, 1) );
			noTone(this->pin);         delay(10);
			tone(this->pin, NOTE_GS7); delay( tempo_d(180, 8, 2) );
			noTone(this->pin);         delay(10);
			this->beep('x');
		}
		
		
		void stop(void){
			if (!this->_enable) return;
			noTone(this->pin);
		}
		
		bool isEnable(void){
			return this->_enable;
		}
		
		void toggleEnable(void){
			this->_enable = !this->_enable;
		}
		
	private:
		int pin;
		int delay_time = 50;
		float t_times;
		bool _enable;
		
		
};


#endif
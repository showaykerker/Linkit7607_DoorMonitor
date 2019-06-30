#ifndef HSP_LCD_WRAPPER_HPP
#define HSP_LCD_WRAPPER_HPP
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "HSP_defines.h"

class HSP_LCD_Wrapper: public LiquidCrystal_I2C{
	public: 
		HSP_LCD_Wrapper(int n):LiquidCrystal_I2C(n){};
		void start(int block_for){
			setBacklight(255);
			begin(16,2);
			reset();
			print("Hello!"); 
			delay(block_for);
			reset(); 
			print("Connecting ");
			setCursor(0, 1); 
			print("        to WiFi.");
		}

		void wifi_connected(int block_for){
			reset(); 
			print("WiFi Connected. ");
			setCursor(0, 1); 
			print("ssid: ");
			setCursor(6, 1); 
			print(WIFI_SSID);
			delay(block_for);
			this->standby();
			
		}

		void reset(void){
			clear(); 
			home(); 
		}

		void start_monitor(void){
			reset();
			print("  Start Monitor!"); 
			delay(1000);
			this->monitoring();
		}
		
		void count_down(int t){
			reset();
			for (int i = t; i>=0; i--){
				if (i>=100) setCursor(12,1);
				else if (i>=10) setCursor(13, 1);
				else setCursor(14, 1);
				print(i);
				delay(1000);
				reset();
			}
			this->show_word(String("Start Monitor!").c_str());
		}
		
		void standby(void){
			reset();
			print("Stand By.       ");
		}
		
		void monitoring(void){
			reset();
			print("Monitoring");
		}
		
		void show_word(const char *line1, const char *line2, int delay_time){
			reset(); print(line1);
			setCursor(0, 1); print(line2);
			delay(delay_time);
		}
		
		void show_word(const char *line1){
			this->show_word(line1, String("").c_str(), 0);
		}
		
		void show_word(const char *line1, int delay_time){
			this->show_word(line1, String("").c_str(), delay_time);
		}
		
		void show_word(const char *line1, const char *line2){
			this->show_word(line1, line2, 0);
			//reset(); print(line1);
			//setCursor(0, 1); print(line2);
		}
		
		void show_reading(int val){
			reset(); print("HES Reading:");
			setCursor(0, 12); print(val);
		}
		
		void show_triggered(void){
			reset(); print("TRIGGERED!!!");
		}
		
		void Welcome_Home(void){
			reset(); print(" Welcome Home ! ");
			delay(2500);
			reset();
			print("Stand By.       ");
			delay(1000);
		}
		
		void Wrong_PSWD(void){
			reset();
			setCursor(0, 0); print(" Wrong Password ");
		}
		
	private:
		void _scroll_left(int n, int d_time1, int d_time2){
			for(int i = 0; i < n; i++){
				scrollDisplayLeft();
				delay(d_time1);
			}
			delay(d_time2);
		}
};

#endif

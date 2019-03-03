#ifndef HSP_KEYPAD_HPP
#define HSP_KEYPAD_HPP

#include<Arduino.h>
#include<Keypad.h>

#define KEY_ROWS 4 
#define KEY_COLS 4 

class HSP_KeyPad{
	public:
		char getKey(void){
			return myKeypad.getKey();
		}
	private:
		Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);
		char keymap[KEY_ROWS][KEY_COLS] = {
			{'1', '2', '3', 'A'},
			{'4', '5', '6', 'B'},
			{'7', '8', '9', 'C'},
			{'*', '0', '#', 'D'}
		};
		byte colPins[KEY_COLS] = {5, 4, 3, 2};
		byte rowPins[KEY_ROWS] = {13, 12, 11, 10};
};


#endif
# HSP

## Home Security Project
This project is made for monitoring the door if it is opened before entering the correct password.

The unauthorized entering will trigger the event service provided by [IFTTT](https://ifttt.com/maker_webhooks) and send a Line message to my mobile phone in my case.

## Features
### Keys
* '#': Enter
* '*': Delete

### Modes
#### AlertMode
Press Enter without typing anything will enter the AlertMode.

In AlertMode, the Hall Effect Sensor will be monitored. Once the value is out of threshold range, an alert will be triggered and a noisy sound will be played.

To leave AlertMode, simply type the password without pressing enter needed.


#### HallMonitorMode
Enter "0" to go to this mode.

Monitor current reading of the Hall Effect Sensor and show the current threshold.


#### HallThreshModifyMode
Enter "1" to go to this mode.

Modify thresholds through keypad.

At the end of HallThreshModifyMode, HallMonitorMode is called.


#### Toggle Buzzer
Enter "8" to toggle buzzer enabling.


## Note
Two extra files "HSP/HSP_CallsAndPswd.h" and "server/Keys.py" have to be added since it was ignored.

It should be something looks like the following, 


``` C++

// HSP/HSP_CallsAndPswd.h

// The Arduino script will read this file to set wifi, passwords and send proper request to the server.
// Alternatively, the TRIGGER can be IFTTT requests if there is no server envolved.

#ifndef CALLS_AND_PSWD_H
#define CALLS_AND_PSWD_H

#define WIFI_SSID "[wifi_ssid]"
#define WIFI_PSWD "[wifi_password]"
#define ENTER_PSWD "[password]" // for opening the door without sending an alert

#define TRIGGER_START "[ServerIP]:[ServerPort]/0"
#define TRIGGER_ALERT "[ServerIP]:[ServerPort]/1"
#define TRIGGER_CLEAR "[ServerIP]:[ServerPort]/2"

#endif

```

``` python

// server/Keys.py

// These will be passed to IFTTT 
//   as "GET https://maker.ifttt.com/trigger/[start_event_name]/with/key/[key]"
//   with a json file that contains {value1, value2}.

EventName ='[IFTTT Event Name]'
Key = '[IFTTT Key]'

```

## Hardware 
TODO

## Extra Libraries
* [Keypad Library for Arduino](https://playground.arduino.cc/Code/Keypad/)

## TODO
* Can Do More Buzzer Inticator Music
* Camera Event for RPi.
* ~~Check function for Hall Effect Sensor Readings.~~ (done @ 190413)
* ~~Modify through a RA. (requires hardware modifications.)~~ (del @ 190412)
* ~~Buzzer Part~~ (done @ 190322)


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
An extra file "HSP_CallsAndPswd.h" has to be added since it was ignored.
It should be something looks like the following, 

``` C++

// HSP_CallsAndPswd.h

#ifndef CALLS_AND_PSWD_H
#define CALLS_AND_PSWD_H

#define WIFI_SSID "[wifi_ssid]"
#define WIFI_PSWD "[wifi_password]"
#define ENTER_PSWD "[password]" // for opening the door without sending an alert

#define TRIGGER_START "GET https://maker.ifttt.com/trigger/[start_event_name]/with/key/[key]"
#define TRIGGER_ALERT "GET https://maker.ifttt.com/trigger/[alert_event_name]/with/key/[key]"

#endif

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


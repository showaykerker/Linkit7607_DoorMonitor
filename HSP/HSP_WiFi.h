#ifndef HSP_WIFI_H
#define HSP_WIFI_H

#include<LWiFi.h>

#define TRIG_START 0
#define TRIG_ALERT 1

class HSP_WiFi{
	public:
		HSP_WiFi(char* ssid_, char* pswd_);
		void connect_WiFi(void);
		void trig(int type);
		WiFiClient client;
	private:
		void printWiFiStatus(void);
		int status = WL_IDLE_STATUS;
		char *server; 
		char *ssid, *pswd;
		char *trigger_Start, *trigger_Alert;
		
};



#endif
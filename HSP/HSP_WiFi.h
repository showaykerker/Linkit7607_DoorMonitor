#ifndef HSP_WIFI_H
#define HSP_WIFI_H

#include<LWiFi.h>

#define TRIG_START 0
#define TRIG_ALERT 1

class HSP_WiFi{
	public:
		HSP_WiFi(char* ssid_, char* pswd_);
		void connect_WiFi(void);
		bool trig(int type); // type0: Start, type1: Alert, type2: Clear
		WiFiClient client;
	private:
		void printWiFiStatus(void);
		int status = WL_IDLE_STATUS;
		char *server; 
		char *ssid, *pswd;

};



#endif

#ifndef HSP_WIFI_CPP
#define HSP_WIFI_CPP

#include<Arduino.h>
#include"HSP_WiFi.h"
#include"HSP_defines.h"
#include<LWiFi.h>


HSP_WiFi::HSP_WiFi(char* ssid_, char* pswd_){
	server = "maker.ifttt.com";
	ssid = ssid_;
	pswd = pswd_;
}

void HSP_WiFi::connect_WiFi(void){
	while (status!=WL_CONNECTED){
		Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
		status = WiFi.begin(ssid, pswd);
	}
	Serial.println("Connected to wifi");
	printWiFiStatus();
}

bool HSP_WiFi::trig(int type){ // type0: Start, type1: Alert, type3: Clear
	if (client.connect(RPI_SERVER, RPI_PORT)){
		Serial.println("connected to server (GET)");
        // Make a HTTP request:
		if (type==0) client.println(TRIGGER_START);
	    else if (type==1) client.println(TRIGGER_ALERT);
		else if (type==2) client.println(TRIGGER_CLEAR);
		else if (type==601) client.println(TRIGGER_USER_DEFINE1_1); // Under Alarm Off State
		else if (type==602) client.println(TRIGGER_USER_DEFINE1_2);
		else if (type==603) client.println(TRIGGER_USER_DEFINE1_3);
		else if (type==604) client.println(TRIGGER_USER_DEFINE1_4);
		else if (type==605) client.println(TRIGGER_USER_DEFINE1_5);
		else if (type==801) client.println(TRIGGER_USER_DEFINE2_1); // Under Alarm On State
		else if (type==802) client.println(TRIGGER_USER_DEFINE2_2);
		else if (type==803) client.println(TRIGGER_USER_DEFINE2_3);
		else if (type==804) client.println(TRIGGER_USER_DEFINE2_4);
		else if (type==805) client.println(TRIGGER_USER_DEFINE2_5);
		client.println("Host: " + String(RPI_SERVER));
        client.println("Accept: */*");
        client.println("Connection: close");
        client.println();
		delay(100);
	}
	else{
		return false;
	}
	while (client.available()) {
        char c = client.read();
        Serial.write(c);
    }
	return true;
}


void HSP_WiFi::printWiFiStatus(void){
	// print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}


#endif

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
	trigger_Start = TRIGGER_START;
	trigger_Alert = TRIGGER_ALERT;
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

void HSP_WiFi::trig(int type){ // type0: Start, type1: Alert
	if (client.connect(server, 80)){
		Serial.println("connected to server (GET)");
        // Make a HTTP request:
		if (type==0) client.println(trigger_Start);
        else client.println(trigger_Alert);
        client.println("Host: maker.ifttt.com");
        client.println("Accept: */*");
        client.println("Connection: close");
        //client.println();
        delay(100);
	}
	while (client.available()) {
        char c = client.read();
        Serial.write(c);
    }
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
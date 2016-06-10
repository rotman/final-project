#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <message.h>
#include <ArduinoJson.h>



class Wifi : public ICommunicationable<String, JsonObject>{
private:
	WiFiClient client;
public:	
	 void initCommunication(T&, int, int) = 0;
	 void sendMessage(T&, E&) = 0;
	 E receiveMessage(T&) = 0;
//dudi:
	void init(String ssid, String password);
	String post(JsonObject& json, String url);
	String get(String url);

};


#endif

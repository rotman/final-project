#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <message.h>
#include <ArduinoJson.h>



class Wifi {
private:
	WiFiClient client;
public:
	void init(String ssid, String password);
	String post(JsonObject& json, String url);
	String get(String url);

};


#endif

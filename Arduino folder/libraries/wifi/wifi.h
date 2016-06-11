#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <message.h>
#include <ArduinoJson.h>



class Wifi : public ICommunicationable<String, JsonObject>{
private:
	WiFiClient client;
	String url;
public:
	 void initCommunication(String, String);
	 void sendMessage(JsonObject&);
	 String receiveMessage();
	 String getUrl();
	 void setUrl(String);

};


#endif

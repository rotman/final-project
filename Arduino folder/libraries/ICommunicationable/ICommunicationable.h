#ifndef ICOMMUNICATIONABLE
#define ICOMMUNICATIONABLE

#include <Arduino.h>
#include <Message.h>
#include <ArduinoJson.h>

class ICommunicationable {
	public:
		virtual ~ICommunicationable() {}
		virtual void initCommunication(int, int) {};
		virtual void initCommunication(const char*, const char*) {};
		virtual bool sendMessage(Message&) {};
		virtual String sendMessage(JsonObject&,String) {return "";};
		virtual Message receiveMessage() {Message message ; return message;};
		virtual String receiveMessage(String) {return "";};
};

#endif

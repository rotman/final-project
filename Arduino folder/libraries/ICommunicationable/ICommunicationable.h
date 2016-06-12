#ifndef ICOMMUNICATIONABLE
#define ICOMMUNICATIONABLE

#include <Arduino.h>

class ICommunicationable {
	public:
		virtual ~ICommunicationable() {}
		virtual void initCommunication(int, int) = 0;
		virtual void initCommunication(String, String) = 0;
		virtual void sendMessage(Message&) = 0;
		virtual String sendMessage(JsonObject&) = 0;
		virtual Message receiveMessage() = 0;
		virtual String receiveMessage(String) = 0;

};

#endif

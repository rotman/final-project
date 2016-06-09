#ifndef ICOMMUNICATIONABLE
#define ICOMMUNICATIONABLE

#include <Arduino.h>

template <class T, class E>
class ICommunicationable {
	public:
		virtual ~ICommunicationable() {}
		virtual void initCommunication(T&, int, int) = 0;
		virtual void sendMessage(T&, E&) = 0;
		virtual E receiveMessage(T&) = 0;
};

#endif
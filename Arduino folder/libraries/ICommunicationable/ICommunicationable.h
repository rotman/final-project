#ifndef ICOMMUNICATIONABLE
#define ICOMMUNICATIONABLE

#include <Arduino.h>


template <class T, class E>
class ICommunicationable {
	public:
		virtual ~ICommunicationable() {}
		virtual void initCommunication(T, T) = 0;
		virtual void sendMessage(E&) = 0;
		virtual E receiveMessage() = 0;

};

#endif
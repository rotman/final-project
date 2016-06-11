#ifndef ICOMMUNICATIONABLE
#define ICOMMUNICATIONABLE

#include <Arduino.h>


template <class T, class E>
class ICommunicationable {
	public:
		virtual ~ICommunicationable() {}
		virtual void initCommunication(E, E) = 0;
		virtual E sendMessage(T&) = 0;
		virtual T receiveMessage() = 0;

};

#endif

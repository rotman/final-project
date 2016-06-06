#ifndef COMMUNICATIONABLE
#define COMMUNICATIONABLE

#include <Arduino.h>

template <class T, class E>
class Communicationable {
	public:
		virtual ~Communicationable() {}
		virtual void initCommunication(T&, byte*, byte*) = 0;
		virtual void sendMessage(T&, E&) = 0;
		virtual E receiveMessage(T&) = 0;
};

#endif
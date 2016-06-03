#ifndef RADIO_H
#define RADIO_H
#include <Arduino.h>
#include <RF24.h>
#include <message.h>


class Radio {
public:
	void init(RF24&, byte[6], byte[6]);
	void sendMessage(RF24&, Message&);
	Message receiveMessage(RF24&);

};


#endif
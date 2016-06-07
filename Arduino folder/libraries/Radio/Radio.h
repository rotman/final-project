#ifndef RADIO_H
#define RADIO_H
#include <Arduino.h>
#include <RF24.h>
#include <message.h>
#include <ExponentialBackoff.h>


class Radio {
public:
	void init(RF24&, int, int);
	void sendMessage(RF24&, Message&);
	Message receiveMessage(RF24&);

};


#endif
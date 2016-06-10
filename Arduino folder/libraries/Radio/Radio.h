#ifndef RADIO_H
#define RADIO_H
#include <Arduino.h>
#include <RF24.h>
#include <message.h>
#include <ExponentialBackoff.h>
#include <CommonValues.h>

class Radio {
public:
	void init (int, int);
	void sendMessage(RF24&, Message&);
	Message receiveMessage(RF24&);
private:
	RF24* radio;
};


#endif
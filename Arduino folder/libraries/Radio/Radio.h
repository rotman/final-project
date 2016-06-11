#ifndef RADIO_H
#define RADIO_H
#include <Arduino.h>
#include <RF24.h>
#include <message.h>
#include <ExponentialBackoff.h>
#include <CommonValues.h>
#include <ICommunicationable.h>


class Radio :public ICommunicationable<Message,int>{
public:
	void initCommunication (int, int);
	int sendMessage(Message&);
	Message receiveMessage();
private:
	RF24* radio;
};

#endif

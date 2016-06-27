#ifndef RADIO_H
#define RADIO_H
#include <Arduino.h>
#include <RF24.h>
#include <Message.h>
#include <ExponentialBackoff.h>
#include <CommonValues.h>
#include <ICommunicationable.h>


class Radio : public ICommunicationable{
public:
	Radio(int, int);
	void initCommunication (int, int);
	bool sendMessage(Message);
	void receiveMessage(Message& message);
private:
	RF24* radio;

};

#endif

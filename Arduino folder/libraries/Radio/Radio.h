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
	void initCommunication (int, int);
	bool sendMessage(Message&);
	void receiveMessage(Message&);
private:
	RF24* radio = new RF24(7,8);

};

#endif

#ifndef GREENHOUSEPLATFORM_H
#define GREENHOUSEPLATFORM_H

#include <Radio.h>
#include <ISensorNetworkPlatform.h>
#include <LinkedList.h>
#include <Actuator.h>

class GreenHousePlatform : public ISensorNetworkPlatform<RF24, Message, Actuator> {
	
	public:
		void init(RF24&, byte[6], byte[6]);
		void addSensor(Sensor*);
		void removeSensor(Sensor*);
		LinkedList<Message> readSensorsData();
		void sendMessage(RF24&, Message&);
		Message receiveMessage(RF24&);
		void actuate(Actuator*, bool);
		void onSensorFail();
		
	private:
		Radio radioHelper;
		LinkedList<Sensor*> sensors;
		
};

#endif
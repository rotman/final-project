#ifndef MIDDLELAYER
#define MIDDLELAYER

#include <Communicationable.h>
#include <IMiddleLayer.h>
#include <Actuator.h>
#include <Radio.h>
#include <Sensor.h>

class MiddleLayer : public Communicationable<RF24, Message>, public IMiddleLayer<Actuator> {
	
	public:
		//Communicationable implementation
		void initCommunication(RF24&, byte[6], byte[6]);
		void sendMessage(RF24&, Message&);
		Message receiveMessage(RF24&);
		
		//IMiddleLayer implementation
		void initLayer();
		void actuate(Actuator*, bool);
		
	private:
		Radio radioHelper;
		LinkedList<Actuator*> actuators;
		
};

#endif
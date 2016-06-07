#ifndef MIDDLELAYER
#define MIDDLELAYER

#include <Communicationable.h>
#include <IMiddleLayer.h>
#include <Radio.h>
#include <Sensor.h>
#include <Clock.h>


class MiddleLayer : public Communicationable<RF24, Message>, public IMiddleLayer<Actuator> {
	
	public:
		//Communicationable implementation
		void initCommunication(RF24&, byte[6], byte[6]);
		void sendMessage(RF24&, Message&);
		Message receiveMessage(RF24&);
		
		//IMiddleLayer implementation
		void initLayer(int);
		void addActuator(Actuator*);
		void removeActuator(int);
		void actuate(Actuator*, bool);
		
		void startClock();
		void getTime();
		
	private:
		int address;
		Radio radioHelper;
		LinkedList<Actuator*> actuators;
		Clock clock;
		
};

#endif
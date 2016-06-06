#ifndef LOWERLAYER
#define LOWERLAYER

#include <Communicationable.h>
#include <ILowerLayer.h>
#include <Actuator.h>
#include <Radio.h>
#include <Sensor.h>

class LowerLayer : public Communicationable<RF24, Message>, public ILowerLayer<Message, Actuator> {
	
	public:
		//Communicationable implementation
		void initCommunication(RF24&, byte[6], byte[6]);
		void sendMessage(RF24&, Message&);
		Message receiveMessage(RF24&);
		
		//ILowerLayer implementation
		void initLayer();
		void addSensor(Sensor*);
		void removeSensor(Sensor*);
		LinkedList<Message> readSensorsData();
		void actuate(Actuator*, bool);
		void onSensorFail();
		
	private:
		Radio radioHelper;
		LinkedList<Sensor*> sensors;
		LinkedList<Actuator*> actuators;
		
};

#endif
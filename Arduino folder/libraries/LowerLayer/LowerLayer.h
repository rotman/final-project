#ifndef LOWERLAYER
#define LOWERLAYER

#include <Communicationable.h>
#include <ILowerLayer.h>
#include <Radio.h>
#include <CommonValues.h>

class LowerLayer : public Communicationable<RF24, Message>, public ILowerLayer<Message, Actuator> {
	
	public:
		//Communicationable implementation
		void initCommunication(RF24&, int, int);
		void sendMessage(RF24&, Message&);
		Message receiveMessage(RF24&);
		
		//ILowerLayer implementation
		void initLayer(int);
		void addSensor(Sensor*);
		void removeSensor(int);
		void addActuator(Actuator*);
		void removeActuator(int);
		LinkedList<Message> readSensorsData();
		void actuate(Actuator*, bool);
		void onSensorFail();
		
	private:
		int address;
		Radio radioHelper;
		LinkedList<Sensor*> sensors;
		LinkedList<Actuator*> actuators;
		
};

#endif
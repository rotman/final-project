#ifndef LOWERLAYER
#define LOWERLAYER

#include <ILowerLayer.h>
#include <Radio.h>
#include <CommonValues.h>
#include <Message.h>

class LowerLayer : public ILowerLayer<RF24, Message>{
	
	public:
		/*ILowerLayer methods*/
		virtual ~ILayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage() = 0;
		virtual Message prepareMessage(Message, int) = 0;
		virtual void initCommunication(RF24 &, int, int) = 0;
		virtual void sendMessage(RF24 &, Message&) = 0;
		virtual Message receiveMessage(RF24 &) = 0;
		virtual void addActuator(Actuator*) = 0;
		virtual void removeActuator(int) = 0;
		virtual void actuate(int, bool) = 0;
		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(int) = 0;
		virtual LinkedList<Message> readSensorsData() = 0;
		virtual void onSensorFail() = 0;
	
	private:
		int address;
		Radio radioHelper;



		/*
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
		*/
};

#endif
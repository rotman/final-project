#ifndef GREEN_HOUSE_LOWER_LAYER
#define GREEN_HOUSE_LOWER_LAYER

#include <LowerLayer.h>
#include <Radio.h>
#include <CommonValues.h>
#include <Message.h>

class GreenHouseLowerLayer : public LowerLayer<Message,Message,int>{

	public:
		/*LowerLayer methods*/
		~GreenHouseLowerLayer(){}
		 void initLayer(int);
		 void analyze();
		 void decodeMessage(Message);
		 Message prepareMessage(Message, int);

		 void addActuator(Actuator*);
		 void removeActuator(int);
		 Actuator* findActuatorById(int);
		 void addSensor(Sensor*);
		 void removeSensor(int);
		 LinkedList<Message> readSensorsData();
		 void onSensorFail();

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

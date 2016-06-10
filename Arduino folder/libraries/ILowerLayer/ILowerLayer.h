#ifndef ILOWERLAYER
#define ILOWERLAYER

#include <Sensor.h>
#include <Actuator.h>
#include <ILayer.h>
#include <Actuatorable.h>
#include <Sensorable.h>


template <class E, class S>
//in green house project,'S' stands for Message, 'E' stands for communication type
class ILowerLayer :public ILayer<E,S>,public Actuatorable,public Sensorable<S>{
	public:
		/*ILayer methods*/
		virtual ~ILowerLayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage() = 0;
		virtual S prepareMessage(S, int) = 0;
		virtual void initCommunication(E&, int, int) = 0;
		virtual void sendMessage(E&, S&) = 0;
		virtual S receiveMessage(E&) = 0;

		/*Actuatorable methods*/

		virtual void addActuator(Actuator*) = 0;
		virtual void removeActuator(int) = 0;
		virtual Actuator* findActuatorById(int) = 0;

		/*Sensorable methods*/

		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(int) = 0;
		virtual LinkedList<S> readSensorsData() = 0;
		virtual void onSensorFail() = 0;




		//virtual void initLayer(int) = 0;
	//	virtual void addSensor(Sensor*) = 0;
	//	virtual void removeSensor(int) = 0;
	//	virtual LinkedList<E> readSensorsData() = 0;
	//	virtual void onSensorFail() = 0;

//		virtual void addActuator(Actuator*) = 0;
//		virtual void removeActuator(int) = 0;
//		virtual void actuate(S*, bool) = 0;
		
};

#endif
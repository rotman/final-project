#ifndef LOWERLAYER
#define LOWERLAYER

#include <Sensor.h>
#include <Actuator.h>
#include <Layer.h>
#include <Actuatorable.h>
#include <Sensorable.h>


template <class T,class E, class S>
//in green house project,'T' stands for Message
class LowerLayer :public Layer<T,E,S>,public Actuatorable,public Sensorable<T>{
	public:
		/*Layer methods*/
		virtual ~LowerLayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage(T) = 0;
		virtual T prepareMessage(T, int) = 0;

		/*Actuatorable methods*/

		void addActuator(Actuator*);
		virtual void removeActuator(int);
		virtual Actuator* findActuatorById(int);

		/*Sensorable methods*/

		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(int) = 0;
		virtual LinkedList<T> readSensorsData() = 0;
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

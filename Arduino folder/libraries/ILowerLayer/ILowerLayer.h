#ifndef ILOWERLAYER
#define ILOWERLAYER

#include <Sensor.h>
#include <Actuator.h>
#include <LinkedList.h>

template <class E, class S>
class ILowerLayer {
	public:
		virtual void initLayer(int) = 0;
		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(int) = 0;
		virtual void addActuator(Actuator*) = 0;
		virtual void removeActuator(int) = 0;
		virtual LinkedList<E> readSensorsData() = 0;
		virtual void actuate(S*, bool) = 0;
		virtual void onSensorFail() = 0;
		
};

#endif
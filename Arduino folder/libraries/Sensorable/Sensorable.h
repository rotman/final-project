#ifndef SENSORABLE
#define SENSORABLE

#include <Arduino.h>
#include <Sensor.h>
#include <LinkedList.h>

template <class T>
//in green house project,'T' stands for Message.

class Sensorable {
	public:
		virtual ~Sensorable() {}
		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(int) = 0;
		virtual LinkedList<T> readSensorsData() = 0;
		virtual void onSensorFail() = 0;

	protected:
		LinkedList<Sensor*> sensorsArray;

};

#endif

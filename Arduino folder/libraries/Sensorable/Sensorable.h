#ifndef SENSORABLE
#define SENSORABLE

#include <Arduino.h>
#include <Sensor.h>
#include <LinkedList.h>

template <class S>
//in green house project,'S' stands for Message.

class Sensorable {
	public:
		virtual ~Sensorable() {}
		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(int) = 0;
		virtual LinkedList<S> readSensorsData() = 0;
		virtual void onSensorFail() = 0;

	private:
		LinkedList<Sensor*> sensorsArray;

};

#endif
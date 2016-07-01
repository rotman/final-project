#ifndef ISENSORNETWORKPLATFORM_H
#define ISENSORNETWORKPLATFORM_H

#include <Sensor.h>
#include <LinkedList.h>

template <class T, class E, class S>
class ISensorNetworkPlatform {
	public:
		virtual ~ISensorNetworkPlatform() {}
		virtual void init(T&, byte*, byte*) = 0;
		virtual void addSensor(Sensor*) = 0;
		virtual void removeSensor(Sensor*) = 0;
		virtual LinkedList<E> readSensorsData() = 0;
		virtual void sendMessage(T&, E&) = 0;
		virtual E receiveMessage(T&) = 0;
		virtual void actuate(S*, boolean) = 0;
		virtual void onSensorFail() = 0;
};

#endif
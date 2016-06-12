#ifndef SENSORABLE
#define SENSORABLE

#include <Arduino.h>
#include <Sensor.h>
#include <LinkedList.h>
#include <CommonValues.h>

template <class T>
//in green house project,'T' stands for Message.

class Sensorable {
	public:
		virtual ~Sensorable() {}
		
		void addSensor(Sensor* sensor) {
			sensorsArray.add(sensor);
		}
		
		void removeSensor(int pin) { 
			for (int i = 0; i < sensorsArray.size(); i++) {
				if (sensorsArray.get(i)->getId() == pin) {
					sensorsArray.remove(i);
					break;
				}
			}
		}
		
		LinkedList<T> readSensorsData() {
			LinkedList<T> messages = LinkedList<T>();
			for (int i = 0; i < sensorsArray.size(); i++) {
				T newMessage;
				if (sensorsArray.get(i)->getId() == CommonValues::humidityTemperatureSensorId) {
					newMessage = sensorsArray.get(i)->readSensorData(true);
				}
				else {
					newMessage = sensorsArray.get(i)->readSensorData(false);
				}
				messages.add(newMessage);
			}
			return messages;
		}
		
		virtual void onSensorFail() {}

	protected:
		LinkedList<Sensor*> sensorsArray = LinkedList<Sensor*>();


};

#endif

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
			Serial.println("Sensorable, addSensor()");
			sensorsArray.add(sensor);
		}
		
		void removeSensor(int pin) { 
			Serial.println("Sensorable, removeSensor()");
			for (int i = 0; i < sensorsArray.size(); i++) {
				if (sensorsArray.get(i)->getId() == pin) {
					sensorsArray.remove(i);
					break;
				}
			}
		}
		
		LinkedList<T> readSensorsData() {
			Serial.println("Sensorable, readSensorsData()");
			LinkedList<T> messages = LinkedList<T>();
			for (int i = 0; i < sensorsArray.size(); i++) {
				T newMessage;
				if (sensorsArray.get(i)->getId() == CommonValues::humidityTemperatureSensorId) {
					newMessage = sensorsArray.get(i)->readSensorData(true);
					messages.add(newMessage);
				}
				newMessage = sensorsArray.get(i)->readSensorData(false);
				messages.add(newMessage);
			}
			Serial.print("messages list: ");
			Serial.println(messages.size());
			return messages;
		}
		
		virtual void onSensorFail() {
			Serial.println("Sensorable, onSensorFail()");
		}

	protected:
		LinkedList<Sensor*> sensorsArray = LinkedList<Sensor*>();


};

#endif

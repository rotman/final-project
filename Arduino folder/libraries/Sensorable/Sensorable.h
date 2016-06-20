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
		
		void readSensorsData(LinkedList<T>&	 sensorsData) {
			Serial.println("Sensorable, readSensorsData()");
			for (int i = 0; i < sensorsArray.size(); i++) {
				T newMessage;
				if (sensorsArray.get(i)->getId() == CommonValues::humidityTemperatureSensorId) {
					newMessage = sensorsArray.get(i)->readSensorData(true);
					sensorsData.add(newMessage);
				}
				newMessage = sensorsArray.get(i)->readSensorData(false);
				sensorsData.add(newMessage);
			}
			Serial.print("messages list: ");
			Serial.println(sensorsData.size());
		}
		
		virtual void onSensorFail() {
			Serial.println("Sensorable, onSensorFail()");
		}
		/*LinkedList<T>& getSensorsData() {
			return this->sensorsData;
		}*/
 	protected:
		LinkedList<Sensor*> sensorsArray;
		//LinkedList<T> sensorsData = LinkedList<T>();
};

#endif

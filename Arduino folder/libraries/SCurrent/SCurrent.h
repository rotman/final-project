#ifndef S_CURRENT
#define S_CURRENT
#include <Arduino.h>
#include <Sensor.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>


class SCurrent: public Sensor {
public:
	SCurrent(int, int);
	Message readSensorData(bool isHumidity = false);
private:
	int id;
	int pin;
	int sensorValue;
};


#endif
#ifndef S_SOIL
#define S_SOIL
#include <Arduino.h>
#include <Sensor.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>


class SSoil : public Sensor {
public:
	SSoil(int);
	Message readSensorData();
private:
	int pin;
	int sensorValue;
};


#endif
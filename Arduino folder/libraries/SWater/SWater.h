#ifndef S_WATER_H
#define S_WATER_H
#include <Arduino.h>
#include <Sensor.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>


class SWater : public Sensor {
public:
	SWater(int);
	Message readSensorData();
	static  void rpm();
private:
	int pin;
	int sensorValue;
	static volatile int NbTopsFan; //measuring the rising edges of the signal
	
};


#endif
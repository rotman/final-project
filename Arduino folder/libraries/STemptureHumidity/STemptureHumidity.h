#ifndef S_TEMPERTURE_HUMIDITY_H
#define S_TEMPERTURE_HUMIDITY_H
#include <Arduino.h>
#include <Sensor.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>


class STemptureHumidity : public Sensor {
public:
	STemptureHumidity(int);
	Message readSensorData();
	//const Message prepareMessage();
	byte read_data();//aux func
private:
	int pin;
	byte dat[5];
};


#endif
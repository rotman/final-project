#ifndef SENSOR_H
#define SENSOR_H
#include <message.h>
#include <RF24.h>

//abstract class Sensor
class Sensor {
    public:
        //read function must be implemented
        //this is called a pure virtual function
        virtual Message readSensorData(bool) = 0; 
};
#endif
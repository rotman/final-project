#ifndef SENSOR_H
#define SENSOR_H
#include <message.h>
#include <RF24.h>

//abstract class Sensor
class Sensor {
    public:

        //initialize the sensor
        inline virtual void begin(){ /*nothing*/ }; 
        //read function must be implemented
        //this is called a pure virtual function
        virtual Message readSensorData() = 0; 
       // virtual const Message prepareMessage() = 0;
};
#endif
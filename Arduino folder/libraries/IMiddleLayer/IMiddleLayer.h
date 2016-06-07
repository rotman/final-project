#ifndef IMIDDLELAYER
#define IMIDDLELAYER

#include <Sensor.h>
#include <LinkedList.h>
#include <Actuator.h>


template <class S>
class IMiddleLayer {
	public:
		virtual void initLayer(int) = 0;
		virtual void addActuator(Actuator*) = 0;
		virtual void removeActuator(int) = 0;
		virtual void actuate(S*, bool) = 0;			
};

#endif
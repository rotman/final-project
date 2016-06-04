#ifndef FAN_ACTUATOR
#define FAN_ACTUTAOR

#include <Actuator.h>

class FanActuator : public Actuator {
public:
	FanActuator(int);
	void actuate(bool);
private:
	int pin;
};


#endif
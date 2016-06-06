#ifndef PUMP_ACTUATOR
#define PUMP_ACTUTAOR

#include <Actuator.h>

class PampActuator : public Actuator {
public:
	PampActuator(int, int);
	void actuate(bool);
private:
	int pin;
};


#endif
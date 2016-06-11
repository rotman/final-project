

#include <GreenHouseActuator.h>


GreenHouseActuator::GreenHouseActuator(int pin):Actuator(pin){}


void GreenHouseActuator::actuate(bool on) {
	if(on)
		pinMode(this->pin,HIGH);
	else
	pinMode(this->pin,LOW);
}


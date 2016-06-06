#include <FanActuator.h>

FanActuator::FanActuator(int id, int pin) {
	this->id = id;
	this->pin = pin;
}

void FanActuator::actuate(bool on) {
	if(on)
      digitalWrite(pin,HIGH);
	else
      digitalWrite(pin,LOW);
	
}
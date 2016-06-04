#include <FanActuator.h>

FanActuator::FanActuator(int pin) {
	this->pin = pin;
}

void FanActuator::actuate(bool on) {
	if(on)
      digitalWrite(pin,HIGH);
	else
      digitalWrite(pin,LOW);
	
}
#include <PampActuator.h>

PampActuator::PampActuator(int id, int pin) : Actuator(id){
	this->pin = pin;
}

void PampActuator::actuate(bool on) {
	if(on)
      digitalWrite(pin,HIGH);
	else
      digitalWrite(pin,LOW);
	
}
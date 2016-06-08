#include <GreenHouseActuator.h>

GreenHouseActuator::GreenHouseActuator(int pin) : Actuator(pin){
	pinMode(pin, OUTPUT);
}

void GreenHouseActuator::actuate(bool on) {
	if(on)
      digitalWrite(pin,HIGH);
	else
      digitalWrite(pin,LOW);
	
}
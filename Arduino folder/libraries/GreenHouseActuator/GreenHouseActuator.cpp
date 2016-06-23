

#include <GreenHouseActuator.h>


GreenHouseActuator::GreenHouseActuator(int pin):Actuator(pin){}


void GreenHouseActuator::actuate(bool on) {
	if(on) {
		digitalWrite(this->pin,HIGH);
		switch (pin) {
			case CommonValues::pumpPin:
				delay(CommonValues::pumpTime);
			break;
			case CommonValues::fanPin:
				delay(CommonValues::fanTime);
			break;
			case CommonValues::ventPin:
				delay(CommonValues::ventTime);			
			break;
			case CommonValues::steamPin:
				delay(CommonValues::steamTime);						
			break;
			case CommonValues::heatPin:
				delay(CommonValues::heatTime);						
			break;
			case CommonValues::lampPin:
				delay(CommonValues::lampTime);						
			break;
			default:
			break;
		}
	}
	pinMode(this->pin,LOW);

}


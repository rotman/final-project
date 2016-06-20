

#include <GreenHouseActuator.h>


GreenHouseActuator::GreenHouseActuator(int pin):Actuator(pin){}


void GreenHouseActuator::actuate(bool on) {
	if(on) {
		pinMode(this->pin,HIGH);
		switch (pin) {
			case CommonValues::pumpPin:
				delay(CommonValues::pumpTime);
			break;
			case CommonValues::fan1Pin:
				delay(CommonValues::fanTime);
			break;
			case CommonValues::fan2Pin:
				delay(CommonValues::fanTime);			
			break;
			case CommonValues::steamPin:
				delay(CommonValues::steamTime);						
			break;
			case CommonValues::heatPin:
				delay(CommonValues::heatTime);						
			break;
			default:
			break;
		}
		pinMode(this->pin,LOW);

	}
}


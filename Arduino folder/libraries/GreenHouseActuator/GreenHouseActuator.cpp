

#include <GreenHouseActuator.h>


GreenHouseActuator::GreenHouseActuator(int pin):Actuator(pin){}


Actions GreenHouseActuator::actuate(bool on) {
	Actions action;
	if(on) {
		digitalWrite(this->pin,HIGH);
		switch (pin) {
			case CommonValues::pumpPin:
				//action = //TODO
				delay(CommonValues::pumpTime);
			break;
			case CommonValues::fanPin:
				action = FAN;
				delay(CommonValues::fanTime);
			break;
			case CommonValues::ventPin:
				action = VENT;
				delay(CommonValues::ventTime);			
			break;
			case CommonValues::steamPin:
				action = STEAMER;
				delay(CommonValues::steamTime);						
			break;
			case CommonValues::heatPin:
				action = HEATER;
				delay(CommonValues::heatTime);						
			break;
			case CommonValues::lampPin:
				action = LIGHT;
				//TODO light hours
				//delay(CommonValues::lampTime);						
			break;
			default:
			break;
		}
	}
	digitalWrite(this->pin, LOW);
	Serial.print(F("action was pefformed!!!!!!!!!! :"));
	Serial.println(action);

	return action;
}


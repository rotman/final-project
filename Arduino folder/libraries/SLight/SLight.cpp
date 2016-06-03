#include <SLight.h>



SLight::SLight(int pin){
	this->pin = pin;
	pinMode(pin, INPUT);
	sensorValue = 0;
}

Message SLight	::readSensorData(bool isHumidity){
	Message message;					//create new message

	Serial.println("readSensorData called");
	sensorValue = analogRead(pin);

	Serial.print("light:");
	Serial.println(sensorValue, DEC);

  message.data= sensorValue;		//enter the data
  message.sensorType = 'L';
  Serial.print("copied from sensor to messege: check: ");
  Serial.println(message.data,DEC);	
 
  return message;
}








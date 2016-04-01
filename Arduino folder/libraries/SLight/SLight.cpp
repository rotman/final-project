#include <SLight.h>



SLight::SLight(int pin){
	this->pin = pin;
	sensorValue = 0;
}

Message SLight	::readSensorData(){
	Message message;					//create new message

	Serial.println("readSensorData called");
	sensorValue = analogRead(pin);

	Serial.print("light:");
	Serial.println(sensorValue, DEC);

  message.data[0]= sensorValue;		//enter the data
  message.sensorType = 'L';
  Serial.print("copied from sensor to messege: check: ");
  Serial.println(message.data[0],DEC);	
 
  return message;
}








#include <SSoil.h>



SSoil::SSoil(int pin){
	this->pin = pin;
	sensorValue = 0;

}

Message SSoil	::readSensorData(){
	Message message;					//create new message

	Serial.println("readSensorData called");
	sensorValue = analogRead(pin	);
	Serial.print("soil humidity:");
	Serial.println(sensorValue);

  message.data[0]= sensorValue;		//enter the data
  message.sensorType = 'S';
  Serial.print("copied from sensor to messege: check: ");
  Serial.println(message.data[0]);	
 
  return message;
}








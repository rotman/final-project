#include <SCurrent.h>

SCurrent::SCurrent(int pin){
	this->pin = pin;
	sensorValue = 0;
}

Message SCurrent::readSensorData(){
	
	//create new message
	Message message;					
	
	Serial.println("readSensorData called");
	
	// read the analog in value:
	sensorValue = analogRead(pin);

	// output in milliamps	
	int outputValue = 0;        
	
	// convert to milli amps
	outputValue = ((sensorValue * (5000/1024)) - 500)/0.133; 
	
	/* sensor outputs about 100 at rest. 
	Analog read produces a value of 0-1023, equating to 0v to 5v. 
	There's a 500mv offset to subtract. 
	The unit produces 133mv per amp of current, so
	divide by 0.133 to convert mv to ma
	*/
	
	// print the results to the serial monitor:
	Serial.print("sensor = " );                       
	Serial.print(sensorValue);      
	Serial.print("\t Current (ma) = ");      
	Serial.println(outputValue);   
	
	// wait 10 milliseconds before the next loop
	// for the analog-to-digital converter to settle
	// after the last reading:
	delay(10);

	//enter the data
	message.data[0]= outputValue;

	// set sensor type
	message.sensorType = 'C';
	
	Serial.print("copied from sensor to messege: check: ");
	Serial.println(message.data[0],DEC);	
 
  return message;
}








#include <SWater.h>


volatile int SWater::NbTopsFan = 0;

	void SWater:: rpm()     //This is the function that the interupt calls 
{
	NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
}

SWater::SWater(int pin){
	this->pin = pin;
	sensorValue = 0;
	pinMode(pin, INPUT); //initializes digital pin 2 as an input
	Serial.begin(9600); //This is the setup function where the serial port is initialised,
	attachInterrupt(digitalPinToInterrupt(pin), rpm, RISING); //and the interrupt is 
}

Message SWater::readSensorData(){
	Message message;					//create new message
	Serial.println("readSensorData called");
	NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
	sei();      //Enables interrupts
	delay(1000);   //Wait 1 second
	cli();      //Disable interrupts
	sensorValue = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 
	Serial.print(sensorValue, DEC); //Prints the number calculated above
	Serial.print(" L/hour\r\n"); //Prints "L/hour" and returns a  new line
	
	message.data[0] = sensorValue;		//enter the data
	message.sensorType = 'W';
	Serial.print("copied from sensor to messege: check: ");
	Serial.println(message.data[0], DEC);

  return message;
}










#ifndef MESSAGE_H
#define MESSAGE_H


struct Message {
	byte minimum_threshold;
	byte maximum_threshold;
	char sensorType;
	char messageType;
	short int source; 
	short int dest;
  	short int part;

  	//time?
  	int data[7];
};


#endif


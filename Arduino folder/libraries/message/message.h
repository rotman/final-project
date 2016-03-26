#ifndef MESSAGE_H
#define MESSAGE_H

struct Message {
	byte minimum_threshold;
	byte maximum_threshold;
	char sensorType;
	short int source; 
	short int dest;
	short int part;
	//int data[5];
	char data[23] ;
};


#endif


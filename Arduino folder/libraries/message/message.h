#ifndef MESSAGE_H
#define MESSAGE_H
#include <DateTime.h>
#include <Actions.h>

struct Message {
	byte minimum_threshold;
	byte maximum_threshold;
	char sensorType;
	char messageType;
	short int source; 
	short int dest;
  	short int part;
	DateTime dateTime;
  	float data;
	Actions action;
	
};


#endif


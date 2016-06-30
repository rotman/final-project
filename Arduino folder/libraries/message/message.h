#ifndef MESSAGE_H
#define MESSAGE_H
#include <DateTime.h>
#include <Actions.h>

struct Message {
	char sensorType;
	char messageType;
	uint64_t source;
	uint64_t dest;
	DateTime dateTime;
	float data;
	float additionalData;
	Actions action;
	bool flag;
};


#endif

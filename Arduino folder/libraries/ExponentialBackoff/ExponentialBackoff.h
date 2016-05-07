#ifndef EXPONENTIAL_BACKOFF_H
#define EXPONENTIAL_BACKOFF_H

#include <Arduino.h>

class ExponentialBackoff {
private:
	int maxRetries;
public:
	bool getDelayTime(int);
};

#endif
#include "ExponentialBackoff.h"


bool ExponentialBackoff:: getDelayTime(int iteration){
	return random(0, (pow(2, iteration) - 1))*51.2;
}
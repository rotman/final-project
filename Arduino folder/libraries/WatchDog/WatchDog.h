#ifndef WATCHDOG
#define WATCHDOG

#include <Arduino.h>
#include <TimerOne.h>
#include <CommonValues.h>


class WatchDog {
	
	public:
		void enable(int seconds);
		void reset();
};

#endif
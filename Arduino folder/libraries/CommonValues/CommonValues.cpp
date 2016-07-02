#include <CommonValues.h>

float CommonValues::soilHumidityThresholdMin = 100;
float CommonValues::soilHumidityThresholdMax = 1024;

float CommonValues::airHumidityThresholdMin = 50;
float CommonValues::airHumidityThresholdMax = 60;

float CommonValues::temperatureThresholdMin = 22;
float CommonValues::temperatureThresholdMax = 28;

float CommonValues::lightThresholdMin = 60; 
float CommonValues::lightThresholdMax = 100;

int CommonValues::minutesInInterval			= 3;
int CommonValues::watchDogSecondsUntilReset = 60;

const char* CommonValues::ssid 	   = "SuperBox";
const char* CommonValues::password = "0547231229";
const char* CommonValues::host     = "multlayermngmnt.com";

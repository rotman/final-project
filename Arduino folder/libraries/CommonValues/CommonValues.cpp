#include <CommonValues.h>

float CommonValues::soilHumidityThresholdMin = 15;
float CommonValues::soilHumidityThresholdMax = 15;

float CommonValues::airHumidityThresholdMin = 50;
float CommonValues::airHumidityThresholdMax = 60;

float CommonValues::temperatureThresholdMin = 24;
float CommonValues::temperatureThresholdMax = 28;

float CommonValues::lightThresholdMin = 0; //TODO its no minimum..
float CommonValues::lightThresholdMax = 500;

int CommonValues::minutesInInterval = 3;
int CommonValues::watchDogSecondsUntilReset = 60;

const char* CommonValues::ssid = "***";
const char* CommonValues::password = "**";
const char* CommonValues::host = "www.graphical-transformation.netau.net";
const char* CommonValues::key = "123456";

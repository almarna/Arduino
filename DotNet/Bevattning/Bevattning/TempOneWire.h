#ifndef _TEMPONEWIRE_h
#define _TEMPONEWIRE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Common.h"

class TempOneWire
{

	OneWire* oneWire;
	DallasTemperature* dallasSensors;

	DeviceAddress sensorAddresses[1];
public:
	DeviceStatus* Status;
	TempOneWire(int pin);
	float GetTemp();
};

#endif


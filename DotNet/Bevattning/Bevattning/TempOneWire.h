// TempOneWire.h

#ifndef _TEMPONEWIRE_h
#define _TEMPONEWIRE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef OneWire_h
	#include <OneWire.h>
#endif

#ifndef DallasTemperature_h
	#include <DallasTemperature.h>
#endif

class TempOneWire
{

	OneWire* oneWire;
	DallasTemperature* dallasSensors;

	DeviceAddress termometer1;
public:
	TempOneWire(int pin);
	float GetTemp();
};

#endif


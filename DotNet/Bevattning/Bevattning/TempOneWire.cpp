// 
// 
// 
#ifndef _TEMPONEWIRE_h
	#include "TempOneWire.h"
#endif

TempOneWire::TempOneWire(int pin)
{
	oneWire = new OneWire(pin);
	if (oneWire == NULL)
	{
		Serial.println("OneWireNull");
		return;
	}
	// Pass our oneWire reference to Dallas Temperature. 
	dallasSensors = new DallasTemperature(oneWire);
	if (dallasSensors == NULL)
	{
		Serial.println("DallasSensorsNull");
		return;
	}

	// locate devices on the bus
	Serial.print("Locating devices...");
	dallasSensors->begin();
	Serial.print("Found ");
	Serial.print(dallasSensors->getDeviceCount(), DEC);
	Serial.println(" devices.");

	// report parasite power requirements
	Serial.print("Parasite power is: ");
	Serial.println(dallasSensors->isParasitePowerMode() ? "ON" : "OFF");

	if (!dallasSensors->getAddress(termometer1, 0))
	{
		Serial.println("Unable to find address for Device 0");
	}

	dallasSensors->setResolution(termometer1, 9);

	Serial.print("Device 0 Resolution: ");
	Serial.print(dallasSensors->getResolution(termometer1), DEC);
	Serial.println();
}

float TempOneWire::GetTemp()
{
	Serial.print("Dallas temperatures...");
	dallasSensors->requestTemperatures(); // Send the command to get temperatures
	Serial.println("DONE");

	float tempC = dallasSensors->getTempC(termometer1);
	Serial.print("Temp C: ");
	Serial.print(tempC);

	return tempC;
}


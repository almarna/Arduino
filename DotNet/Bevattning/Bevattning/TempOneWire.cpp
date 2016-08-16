#include "TempOneWire.h"

TempOneWire::TempOneWire(int pin)
{

	oneWire = new OneWire(pin);
	if (oneWire == NULL)
	{
		Status = new DeviceStatus(-1, "Can not intiate OneWire");
		return;
	}

	dallasSensors = new DallasTemperature(oneWire);
	if (dallasSensors == NULL)
	{
		Status = new DeviceStatus(-2, "Can not intiate DallasTemperature");
		return;
	}

	dallasSensors->begin();
	int sensorsCount = dallasSensors->getDeviceCount();
	if (sensorsCount < 1)
	{
		Status = new DeviceStatus(-3, "No sensors found");
		return;
	}

	Serial.print("Parasite power is: ");
	Serial.println(dallasSensors->isParasitePowerMode() ? "ON" : "OFF");

	int index = 0; // todo flera sensorer
	if (!dallasSensors->getAddress(sensorAddresses[index], index))
	{
		Status = new DeviceStatus(-4, "No device at position 0");
		return;
	}

	dallasSensors->setResolution(0, 9);

	Status = new DeviceStatus(0, "OK");
	//Serial.print("Device 0 Resolution: ");
	//Serial.print(dallasSensors->getResolution(termometer1), DEC);
	//Serial.println();
}

float TempOneWire::GetTemp()
{
	if (Status->Code != 0)
	{
		return -99;
	}

	dallasSensors->requestTemperatures(); // Send the command to get temperatures

	float tempC = dallasSensors->getTempC(sensorAddresses[0]);

//	Serial.print(tempC);

	return tempC;
}


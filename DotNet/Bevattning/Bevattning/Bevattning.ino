#include "TempOneWire.h"
#include <stdarg.h>
#include <dht11.h>  //Temp+Humiditet
#include <OneWire.h> // One wire for Tempgivare
#include <DallasTemperature.h> // Tempgivare

const int PinTempHum = 2;
const int PinTempOneWire = 3;
const int AnalogueSoilHum = 0;

#define SerialSpeed 38400

struct TempHumLibResult
{
	int humidity;
	int temp;
	int status;
	char message[10];
};

void serialPrintf(char *fmt, ...);
void printJson(TempHumLibResult *tempHumLibResult, float Temp2);
void GetTempHumLibResult(int pin, TempHumLibResult *result);

TempOneWire* tempOneWire;

dht11 TempHumLib;

void setup()
{
	Serial.begin(SerialSpeed);

	tempOneWire = new TempOneWire(PinTempOneWire);

	TempHumLibResult tempHumLibResult;
	tempHumLibResult.humidity = 0;
	tempHumLibResult.temp = 0;
	tempHumLibResult.status = 0;
	strcpy(tempHumLibResult.message, "Reset");

	printJson(&tempHumLibResult, 0.);
}

void loop()
{
	TempHumLibResult tempHumLibResult;

	float oneWireTemp = tempOneWire->GetTemp();



	int soilHum = analogRead(AnalogueSoilHum);

	int recalc = (100l * (1024l - soilHum)) / 1024l;
	Serial.print(" Soilhum: ");
	Serial.println(recalc);

	GetTempHumLibResult(PinTempHum, &tempHumLibResult);

	printJson(&tempHumLibResult, oneWireTemp);

	delay(4000);
}

void GetTempHumLibResult(int pin, TempHumLibResult *result)
{
	result->humidity = 0;
	result->temp = 0;
	result->status = TempHumLib.read(PinTempHum);


	switch (result->status)
	{
	case 0:
		strcpy(result->message, "OK");
		break;
	case -1:
		strcpy(result->message, "Checksum error");
		break;
	case -2:
		strcpy(result->message, "Timeout");
		break;
	default:
		strcpy(result->message, "Unknown error");
		break;
	}

	if (result->status == 0)
	{
		result->temp = TempHumLib.temperature;
		result->humidity = TempHumLib.humidity;
	}
}

void printJson(TempHumLibResult *tempHumLibResult, float Temp2)
{
	Serial.print("{ Status: ");
	Serial.print(tempHumLibResult->status);
	Serial.print(", Temperature: ");
	Serial.print(tempHumLibResult->temp);
	Serial.print(", Humidity: ");
	Serial.print(tempHumLibResult->humidity);
	Serial.print(", Message: '");
	Serial.print(tempHumLibResult->message);
	Serial.print("' OneWireTemp: ");
	Serial.print(Temp2);
	Serial.println(" }");

	//char buffer[256]; // resulting string limited to 256 chars

	//sprintf(buffer, "{ Status: %d, Temperature: %d, Humidity: %d, Message: '%s' OneWireTemp: %2.1f }", 
	//	tempHumLibResult->status, tempHumLibResult->temp, tempHumLibResult->humidity, tempHumLibResult->message, Temp2);
	//Serial.println(buffer);
	//Serial.println(Temp2);

	//serialPrintf("{ Status: %d, Temperature: %d, Humidity: %d, Message: '%s' OneWireTemp: %2.1f }",
	//	tempHumLibResult->status, tempHumLibResult->temp, tempHumLibResult->humidity, tempHumLibResult->message, Temp2);
}

//void serialPrintf(char *fmt, ...)
//{
//
//	char buf[256]; // resulting string limited to 128 chars
//	va_list args;
//	va_start(args, fmt);
//	vsnprintf(buf, 256, fmt, args);
//	va_end(args);
//	Serial.println(buf);
//}


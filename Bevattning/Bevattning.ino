#include <stdarg.h>
#include <dht11.h>  //Temp+Humiditet

#include <OneWire.h> // One wire for Tempgivare
#include <DallasTemperature.h> // Tempgivare

const int PinTempHum = 2;
const int PinTempOneWire = 3;
const int AnalogueSoilHum = 0;

#define SerialSpeed 38400

OneWire oneWire(PinTempOneWire);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature dallasSensors(&oneWire);

DeviceAddress termometer1;

struct TempHumLibResult
{
	int humidity;
	int temp;
	int status;
	char message[10];
};

dht11 TempHumLib;

void setup()
{
    Serial.begin(SerialSpeed);
  
  
    // locate devices on the bus
    Serial.print("Locating devices...");
    dallasSensors.begin();
    Serial.print("Found ");
    Serial.print(dallasSensors.getDeviceCount(), DEC);
    Serial.println(" devices.");

    // report parasite power requirements
    Serial.print("Parasite power is: "); 
    Serial.println(dallasSensors.isParasitePowerMode() ? "ON" : "OFF");

    if (!dallasSensors.getAddress(termometer1, 0)) 
    {
        Serial.println("Unable to find address for Device 0");
    }
    
    dallasSensors.setResolution(termometer1, 9);

    Serial.print("Device 0 Resolution: ");
    Serial.print(dallasSensors.getResolution(termometer1), DEC); 
    Serial.println();
        
  	TempHumLibResult tempHumLibResult;
	tempHumLibResult.humidity = 0;
    tempHumLibResult.temp = 0;
    tempHumLibResult.status = 0;
	strcpy(tempHumLibResult.message,"Reset");

    printJson(&tempHumLibResult);
}

void loop()
{
	TempHumLibResult tempHumLibResult;

    Serial.print("Requesting temperatures...");
    dallasSensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println("DONE");
    
    float tempC = dallasSensors.getTempC(termometer1);
    Serial.print("Temp C: ");
    Serial.print(tempC);
    
    int soilHum = analogRead(AnalogueSoilHum);

    int recalc = (100l*(1024l-soilHum))/1024l;
    Serial.print(" Soilhum: ");
    Serial.println(recalc);
    
    GetTempHumLibResult(PinTempHum, &tempHumLibResult);
  
    printJson(&tempHumLibResult);

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
            strcpy(result->message,"OK"); 
            break;
        case -1:
          strcpy(result->message,"Checksum error"); 
          break;
        case -2:
          strcpy(result->message,"Timeout"); 
          break;
        default:
          strcpy(result->message,"Unknown error"); 
          break;
    }
  
    if (result->status == 0)
    {
    result->temp = TempHumLib.temperature;
    result->humidity = TempHumLib.humidity;
    }
}

void printJson(TempHumLibResult *tempHumLibResult)
{
    serialPrintf("{ Status: %d, Temperature: %d, Humidity: %d, Message: '%s' }", 
    tempHumLibResult->status, tempHumLibResult->temp, tempHumLibResult->humidity, tempHumLibResult->message);
}

void serialPrintf(char *fmt, ... )
{
    char buf[256]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(buf, 256, fmt, args);
    va_end (args);
    Serial.println(buf);
}


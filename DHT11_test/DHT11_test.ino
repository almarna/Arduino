#include <stdarg.h>
#include <dht11.h>  //Temp+Humiditet

dht11 DHT11;  //Declare objects

const int DHT11PIN = 2;  //Declare Pin Numbers

void setup()
{
  Serial.begin(38400);
  printJson(1,0,0, "Reset");
}

void loop()
{
  Serial.println("");

  int humidity = 0;
  int temp = 0;
  int chk = DHT11.read(DHT11PIN);

  char message[10];

  switch (chk)
  {
    case 0: 
      strcpy(message,"OK"); 
      break;
    case -1:
      strcpy(message,"Checksum error"); 
      break;
    case -2:
      strcpy(message,"Timeout"); 
      break;
    default:
      strcpy(message,"Unknown error"); 
      break;
  }
  
  if (chk == 0)
  {
    temp = DHT11.temperature;
    humidity = DHT11.humidity;
  }

  printJson(chk, temp, humidity, message);

  delay(4000);
}

void printJson(int chk, int temp, int humidity, char *message)
{
  serialPrintf("{ Status: %d, Temperature: %d, Humidity: %d, Message: '%s' }", 
  chk, temp, humidity, message);
}

void serialPrintf(char *fmt, ... )
{
    char buf[256]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(buf, 256, fmt, args);
    va_end (args);
    Serial.print(buf);
}


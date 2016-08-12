const int LEDRED = 13;
const int LEDGREEN = 12;
const int LEDYELLOW = 11;
const int LEDBLUE = 10;

void setup() 
{
pinMode(LEDRED,OUTPUT);
pinMode(LEDGREEN,OUTPUT);
pinMode(LEDYELLOW,OUTPUT);
pinMode(LEDBLUE,OUTPUT);
}

void loop() 
{
  for (int i=0;i<16;i++)
  {
      ShowLedNumber(i);
      delay(500);
  }
}

void ShowLedNumber(int value)
{
setLed(LEDRED,value & 1);
setLed(LEDGREEN,value & 2);
setLed(LEDYELLOW,value & 4);
setLed(LEDBLUE,value & 8);
}

void setLed(int pin, bool value)
{
  int ledValue = value ? HIGH : LOW;
  digitalWrite(pin, ledValue);
}


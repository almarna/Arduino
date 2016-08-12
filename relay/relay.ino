void setup() 
{
  pinMode(13,OUTPUT);
  setLed(13,false);
  for (int i= 2;i<10;i++)
  {
    pinMode(i,OUTPUT);
  }
}

void loop() 
{
  setLed(13,true);
  for (int i= 2;i<10;i++)
  {
    setLed(i,true);
    delay(100);
  }
  setLed(13,false);

  for (int i= 2;i<10;i++)
  {
    setLed(i,false);
    delay(100);
  }
}

void setLed(int pin, bool value)
{
  int ledValue = value ? HIGH : LOW;
  digitalWrite(pin, ledValue);
}

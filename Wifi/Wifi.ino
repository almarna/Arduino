char indata[1000];
const int LEDRED = 13;

void setup()
{
  pinMode(LEDRED,OUTPUT);
  Serial.begin(9600);
  strcpy(indata,"");
  setLed(LEDRED,false);
}


void loop()
{
  if (Serial.available() && strlen(indata) < 900) 
  {
    strcat(indata,Serial.read());
    if(strstr(indata, "ready") != NULL) 
    {
      setLed(LEDRED,true);
    }
  }
}

void setLed(int pin, bool value)
{
  int ledValue = value ? HIGH : LOW;
  digitalWrite(pin, ledValue);
}

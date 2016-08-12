const int LED = 13;
const int BUTTON = 8;
void setup() 
{
pinMode(LED,OUTPUT);
pinMode(BUTTON, INPUT);
}

void loop() 
{
  int buttonState = digitalRead(BUTTON);

  if (buttonState == HIGH)
  {
    digitalWrite(LED,HIGH);

    }
  else
  {
    digitalWrite(LED,LOW);
  }
//digitalWrite(LED,HIGH);
//delay(500);
//digitalWrite(LED,LOW);
delay(10);
}

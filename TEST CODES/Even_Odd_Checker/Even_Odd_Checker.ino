int Loop = 0;
int Timer = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
int Timer = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  Loop = (millis() - Timer)/1000;
   
if ((Loop%2) == 0)
{
  Serial.println ("Even");
}
if ((Loop%2) == 1)
{
  Serial.println ("Odd");
}
}

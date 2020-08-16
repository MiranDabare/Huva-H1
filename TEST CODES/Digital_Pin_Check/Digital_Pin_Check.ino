void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(14, INPUT);
pinMode(15, INPUT);
pinMode(16, INPUT);
pinMode(17, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(17,HIGH);
Read();
delay(1000);
Read();
digitalWrite(17,LOW);
delay(1000);


}

void Read()
{

  for (int i = 14; i <=16; i++)
  {
    Serial.print(digitalRead(i));
  }
   Serial.println("");
  
}

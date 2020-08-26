void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(14, OUTPUT);
pinMode(15, INPUT);
pinMode(16, INPUT);
pinMode(17, INPUT);

  pinMode(6, OUTPUT);
  digitalWrite(6,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(14,HIGH);
Read();
delay(100);
//Read();
//digitalWrite(17,LOW);
//delay(1000);


}

void Read()
{

  for (int i = 15; i <=17; i++)
  {
    Serial.print(digitalRead(i));
    while (digitalRead(15) == HIGH)
    {
      digitalWrite(6,LOW);
    }
    digitalWrite(6,HIGH);
  }
   Serial.println("");
  
}

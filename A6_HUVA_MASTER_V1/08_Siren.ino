void Siren_Check() //Siren Transmitter Test 
{

digitalWrite(REMOTE_GND_PIN, LOW);

  RGB_LED("BLUE");

  for (int f = 0; f <= 5; f++)
  { 
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_LED("GREEN");
  delay(500);

   
    digitalWrite(SIREN_PIN, HIGH);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_LED("YELLOW");
     delay(500);
  }

  digitalWrite(REMOTE_GND_PIN, HIGH);
}

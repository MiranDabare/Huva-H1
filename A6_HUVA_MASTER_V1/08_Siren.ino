void Siren_Check() //Siren Transmitter Test 
{

digitalWrite(REMOTE_GND_PIN, LOW);

   RGB_color(0, 0, 255); // Blue

  for (int f = 0; f <= 5; f++)
  { 
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(0, 255, 255); // Blue
  delay(500);

   
    digitalWrite(SIREN_PIN, HIGH);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(255, 255, 0); // Blue
     delay(500);
  }

  digitalWrite(REMOTE_GND_PIN, HIGH);
}

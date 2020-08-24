void Beeper()
{
  
  int Counter = 0;

      if (BeeperOn.indexOf("ON")>=0)
  {
      while (Counter < 10)
  {
      digitalWrite(BUZZER_PIN, HIGH);
     RGB_LED("YELLOW");
      delay(50);
      digitalWrite(BUZZER_PIN, LOW);
      RGB_LED("RED");
      delay(50);  

        Counter++;
  }
 RGB_LED("BLUE");
  }


      if (BeeperOn.indexOf("OFF")>=0)
  {
      while (Counter < 10)
  {
      
       RGB_LED("YELLOW");
      delay(50);
      
      RGB_LED("RED");
      delay(50);  

        Counter++;
  }
     RGB_LED("BLUE");
  }
  
}

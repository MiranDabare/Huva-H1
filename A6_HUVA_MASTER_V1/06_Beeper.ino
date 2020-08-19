void Beeper()
{
  
  int Counter = 0;

      if (BeeperOn.indexOf("ON")>=0)
  {
      while (Counter < 10)
  {
      digitalWrite(BUZZER_PIN, HIGH);
     RGB_color(0, 255, 0); // Green
      delay(50);
      digitalWrite(BUZZER_PIN, LOW);
      RGB_color(0, 0, 0); // Off
      delay(50);  

        Counter++;
  }
  RGB_color(0, 255, 0); // Green
  }


      if (BeeperOn.indexOf("OFF")>=0)
  {
      while (Counter < 10)
  {
      
       RGB_color(0, 255, 0); // Green
      delay(50);
      
      RGB_color(0, 0, 0); // Off
      delay(50);  

        Counter++;
  }
     RGB_color(0, 255, 0); // Green
  }
  
}

void Alert(){
  Serial.println("Alerting");
    
      // 15 minutes break
    int Timer = 0;

    while (Timer < 30){

        if (AlertBeeper == "ON")
        {
          for(int hz = 2400; hz < 2950; hz+=5)
          {    
            tone(BUZZER_PIN, hz, 600);
            delay(5);    
           }
 
        
  
   RGB_color(255, 0, 0); // Red
    delay(50);
   RGB_color(0, 0, 0); // Off
    delay(50);
    
      Timer++;
      incomingData.remove(0);

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        delay(50);
        break;
      }
    }


            if (AlertBeeper == "OFF")
        {
  
    RGB_color(255, 0, 0); // Red
    delay(500);
   RGB_color(0, 0, 0); // Off
    delay(500);
    
      Timer++;
      incomingData.remove(0);

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        delay(50);
        break;
      }
    }
    }

    
    RGB_color(0, 0, 0); // Off
    
 
  resetFunc();
}

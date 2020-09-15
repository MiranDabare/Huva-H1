void Alert(){
//  Serial.println("Alerting");
    
      // 15 minutes break
    int Timer = 0;

    while (Timer < AlertCount)
    {
        if (AlertBeeper == "ON")
        {
          RGB_LED("RED");          
          delay(50);
          
          for(int hz = 2400; hz < 2950; hz+=5)
          {    
            digitalWrite(SIREN_PIN, HIGH);
            digitalWrite(RF_ENABLE_PIN, HIGH);
            
            tone(BUZZER_PIN, hz, 600);
            delay(5);    
           }                  
           
           RGB_LED("BLUE");
           delay(50);              
           Timer++;
           incomingData.remove(0);

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        delay(50);
        break;
      }
        digitalWrite(SIREN_PIN, HIGH);
        digitalWrite(RF_ENABLE_PIN, HIGH);
    }
    
    if (AlertBeeper == "OFF")
    {           
      RGB_LED("RED");
      delay(500);
      RGB_LED("BLUE");
      delay(500);
    
      Timer++;
      incomingData.remove(0);

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        delay(50);
        break;
      }      
    }
    RGB_LED("BLUE");
    }
    
    RGB_LED("BLUE");
     
  resetFunc();
  
}

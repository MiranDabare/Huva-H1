bool WTF = false;

void CheckButton()
{
 delay(50);
  Serial.println("Im here");

// CONSOLE CHECK
  if (digitalRead(REMOTE_D2_PIN) == HIGH)
  {
    Beeper();
  }

  // SIREN CHECK
  if (digitalRead(REMOTE_D3_PIN) == HIGH)
  {
    Siren_Check();
  }
  

  if (digitalRead(BUTTON_PIN) == HIGH && digitalRead(REMOTE_D0_PIN) == LOW) 
  { 
    Pressed = false;
  } else if (!Pressed)
  {
    Pressed = true;
    Clock = millis();
    TriggerArmed = false ;

    Button_Timer();
    

      
      if (PressTime > 2000 && PressTime < 8000)
      {
        PressTime = 0;
        Beeper(); //Turn on the LED to let the user know alert has been set
        Serial.println("Button Pressed");
        TriggerArmed =  true;
        delay(2000); // Delay to let go of the button
        Clock2 = millis();
        Alarm_Buffer();
      }

       if (PressTime > 10000 && PressTime < 12000)
      {
       Sleep();
      }
    
}
}
     
  
   


void Alarm_Triggering()
{
             Serial.println("Triggering Sent");

              SendSMS = UserMessage1;
             
              wait = true;
//              SIM900.println("AT+CMGD=1,4\r");  
              delay(3000);
              
              wait = true;
//              send_message(SendSMS); 
              Serial.println("SMS Sent");
              delay(3000);
//              receive_message();
              
              wait = true;
//              send_message_demo2(DemoMessage2);   
           
              Serial.println("SMS Sent1");
              delay(3000);
//              receive_message();
    
              Serial.println("SMS Sent2");
              delay(3000);
//              Alert();

              TriggerArmed = false;
}

void Button_Timer()
{
  Clock = millis();
      while (digitalRead(BUTTON_PIN) == LOW || digitalRead(REMOTE_D0_PIN) == HIGH)
    {
      Serial.println(PressTime);
      PressTime = millis() - Clock ; 
      delay(50);

      if(PressTime > 2000 && PressTime < 8000)
      {
        RGB_LED("YELLOW");
        digitalWrite(BUZZER_PIN, HIGH);        
      }
      
      digitalWrite(BUZZER_PIN, LOW);

      if(PressTime > 10000 && PressTime < 12000)
      {
        RGB_LED("OFF");
      }

      if(PressTime < 2000 && TriggerArmed ==  true)
      {
         RGB_LED("RED");
         delay(200);
        
         RGB_LED("BLUE");
         delay(200);
      }

    }
}

void Alarm_Buffer()
{
  while(TriggerArmed ==  true)
  {
    Button_Timer();

    Serial.println("Waiting");
    int PressTime2 = (millis() - Clock2) ;

    RGB_LED("RED");
    delay(200);
  
    RGB_LED("BLUE");
    delay(200);
     
    Serial.println(PressTime2);

    if(PressTime > 2000 && PressTime < 3000)
    {
      Serial.println("False Alarm");
      TriggerArmed = false;
      break;
    }

    if(PressTime2 > 10000)
    {
      Serial.println("Activate Alarm");
      RGB_LED("GREEN");
      Activate_Alarm = true;
      TriggerArmed = false;
      Alarm_Triggering();
      break;
    }

    
  }
}

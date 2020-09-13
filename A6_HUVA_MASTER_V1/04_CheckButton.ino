bool WTF = false;

void CheckButton()
{

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
    

      
      if (PressTime > 50 && PressTime < 8000)
      {
        PressTime = 0;
        Beeper(); 
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
  SendSMS = "HUVA SEC12345 TRIGGER LOUD";
  wait = true;
  send_message(SendSMS);
  delay(1000);
  receive_message();
  delay(2000);
  TriggerArmed = false;
 
}

void Button_Timer()
{
  Clock = millis();
      while (digitalRead(BUTTON_PIN) == LOW || digitalRead(REMOTE_D0_PIN) == HIGH || digitalRead(REMOTE_D1_PIN) == HIGH)
    {
      Serial.println(PressTime);
      PressTime = millis() - Clock ; 
      delay(50);

      if(PressTime > 20 && PressTime < 8000)
      {
        RGB_LED("YELLOW");
        digitalWrite(BUZZER_PIN, HIGH); 
        delay(5);       
      }
      
      digitalWrite(BUZZER_PIN, LOW);
      delay(5); 

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
    int PressTime2 = (millis() - Clock2) ;

    RGB_LED("RED");
    delay(200);
  
    RGB_LED("BLUE");
    delay(200);
     
//    Serial.println(PressTime2);

    if(PressTime > 2000 && PressTime < 3000 || digitalRead(REMOTE_D1_PIN) == HIGH)
    {
//      Serial.println("False Alarm");
      TriggerArmed = false;
      break;
    }

    if(PressTime2 > 10000)
    {
//      Serial.println("Activate Alarm");
      RGB_LED("GREEN");
      Activate_Alarm = true;
      TriggerArmed = false;
      Alarm_Triggering();
//      Alert();
      break;
    }

    
  }
}

bool WTF = false;

void CheckButton()
{
// delay(50);
//  Serial.println("Im here");

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
    

      
      if (PressTime > 500 && PressTime < 8000)
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
//  String ServerNumber = "+94769295070";
//String ServerNumber2 = "+94774061725";
//
//String DemoNumber1  = "+94764035418"; //Console 1
//String DemoNumber2  = "+94774701366"; // Console 2
//
//String TestNumber  = "+94774061725";
//
//String DemoMessage1 = "SEC12345 TRIGGER LOUD";
//String DemoMessage2 = "SEC12345 TRIGGER LOUD";
//String UserMessage1 = "There is an Emergency at Mr. Kalubovila's Home!";
//String UserMessage2 = "There is an Emergency at Mr. Dabare's Home!";

              wait = true;
              send_message(UserMessage2); 
              Serial.println("SMS Sent");
              delay(3000);
              receive_message();
              
              wait = true;
              send_message_demo1(DemoMessage1);   
           
              Serial.println("SMS Sent1");
              delay(3000);
              receive_message();
    
          
              Alert();

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

      if(PressTime > 500 && PressTime < 8000)
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

//    Serial.println("Waiting");
    int PressTime2 = (millis() - Clock2) ;

    RGB_LED("RED");
    delay(200);
  
    RGB_LED("BLUE");
    delay(200);
     
//    Serial.println(PressTime2);

    if(PressTime > 2000 && PressTime < 3000)
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
      break;
    }

    
  }
}

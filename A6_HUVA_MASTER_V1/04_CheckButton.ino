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
    
    while (digitalRead(BUTTON_PIN) == LOW || digitalRead(REMOTE_D0_PIN) == HIGH)
    {
      Serial.println("While here");
      PressTime = millis() - Clock ; 
      TriggerArmed = false ;
      delay(50);
      
      if (PressTime > 2000)
      {
        Beeper(); //Turn on the LED to let the user know alert has been set
        Serial.println("Button Pressed");
        TriggerArmed =  true;
        delay(2000); // Delay to let go of the button
        Sleep();
      }
        
        while (PressTime < 20000 && TriggerArmed == true)
        {
          False_Alarm();
          Clock2 = millis();
           while (digitalRead(BUTTON_PIN) == LOW || digitalRead(REMOTE_D0_PIN) == HIGH)
           {
              int PressTime2 = millis() - Clock2 ;
              Serial.println("False Alarm");
              Serial.println(PressTime2);
              delay(100);

            if (PressTime2 > 2000)
            {
              Serial.println("Alarm Canceled");
              TriggerArmed = false ;
              WTF = true;
              PressTime = 0;
              break;                 
            }          
            }
        } 

        if (WTF == true)
        {
          WTF = false;
          break;
        }
            
 
// ===========  ALARM TRIGGERING ===============\\ 

           if (TriggerArmed == true && PressTime > 20000)
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
      
      }
     }
}  
   


void False_Alarm()
{
  // =========== FALSE ALARM ===============\\
      
        Serial.println("Waiting");

         PressTime = (millis() - Clock - 2000) ;

          RGB_LED("RED");
          delay(200);
        
          RGB_LED("BLUE");
          delay(200);
     
      
     Serial.println(PressTime);
}

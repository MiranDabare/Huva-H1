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
    float Clock = millis();
    while (digitalRead(BUTTON_PIN) == LOW || digitalRead(REMOTE_D0_PIN) == HIGH)
    {
      float PressTime = millis() - Clock ; 
      delay(50);
      if (PressTime > 2000)
      {
        Beeper(); //Turn on the LED to let the user know alert has been set
        Serial.println("Button Pressed");
        delay(2000); // Delay to let go of the button

// =========== FALSE ALARM ===============\\

         PressTime = millis() - Clock ;
            
//       SendSMS = "ALERT! DEVICE ID: " + DeviceID ;

          SendSMS = UserMessage1;
         
          wait = true;
          SIM900.println("AT+CMGD=1,4\r");  
          delay(3000);
          
          wait = true;
          send_message(SendSMS); 
          Serial.println("SMS Sent");
          delay(3000);
          receive_message();
          
          wait = true;
          send_message_demo2(DemoMessage2);   
       
          Serial.println("SMS Sent1");
          delay(3000);
          receive_message();

          Serial.println("SMS Sent2");
          delay(3000);
          Alert();
          }
     }  
   }
}

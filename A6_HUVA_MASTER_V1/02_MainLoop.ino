/////////////////////////////////   LOOP DE LOOP   /////////////////////////////////////////////

void loop()
{

  CheckButton();
  receive_message();
  Services();
//  Serial.println(BeeperOn);

  

       
} 


void Services()
{
  if(incomingData.indexOf(SecurityKey)>=0)
{

  // if received command is to turn on relay
  if(incomingData.indexOf("TRIGGER")>=0  && incomingData.indexOf("+CMT:")>=0)
  {    
    if(incomingData.indexOf("SILENT")>=0)
    {
      AlertBeeper = "OFF";
    }

     if(incomingData.indexOf("LOUD")>=0)
     {
      AlertBeeper = "ON";
      }
      
      Alert();
   
//      SendSMS = "Device Alerted! DEVICE ID: " + DeviceID ;
//      wait = true;
//    send_message(SendSMS); 
//      Serial.println("SMS Sent");
//      incomingData.remove(0);
      
    }
  else if(incomingData.indexOf("CHECK")>=0) // Format "SECXXXXX CHECK"
  {
    
    SendSMS = "IM ALIVE! DEVICE ID: ";
    wait = true;
    send_message(SendSMS);
     //Alert();
    incomingData.remove(0);  
  }

  else if(incomingData.indexOf("UPDATENUMB")>=0) // Format "SECXXXXX UPDATENUMB @+9477XXXXXXX"
  {    
    int KeyIndex = incomingData.indexOf('@');
    String NServerNumber = incomingData.substring(KeyIndex+1, KeyIndex+13);
    writeString(9, NServerNumber);  //Address 10 and String type data
    ServerNumber = NServerNumber;
    
    
    //incomingData.remove(0);

       SendSMS = "Connected to new Server! DEVICE ID: ";
       wait = true;
     send_message(SendSMS); 
     Serial.println("SMS Sent");
     incomingData.remove(0);
     //SendSMS.remove(0);
  }

    else if(incomingData.indexOf("UPDATESEC")>=0) // Format "SECXXXXX UPDATESEC @SECXXXXXX"
  {    
    int KeyIndex = incomingData.indexOf('@');
    String NSecurityKey = incomingData.substring(KeyIndex+1,KeyIndex+9);
    writeString(0, NSecurityKey);  //Address 10 and String type data

    SendSMS = "Security Key Changed To: " + NSecurityKey;
    wait = true;
     send_message(SendSMS); 
     Serial.println("SMS Sent");
     //incomingData.remove(0);
    // SendSMS.remove(0);
     
    incomingData.remove(0);  
  }

  else if(incomingData.indexOf("UPDATEBEEPER")>=0) // Format "SECXXXXX UPDATEBEEPER @1 or @0"
  { 
    int KeyIndex = incomingData.indexOf('@');
    String NAlertBeeper = incomingData.substring(KeyIndex+1,KeyIndex+3);
    writeString(22, NAlertBeeper);  //Address 10 and String type data
     
    AlertBeeper = incomingData.substring(KeyIndex+1);
   // incomingData.remove(0); 

     SendSMS = "Beeper Status: " + AlertBeeper ;
     wait = true;
     send_message(SendSMS); 
     Serial.println("SMS Sent");
     incomingData.remove(0);
     //SendSMS.remove(0);
    
  }

    else if(incomingData.indexOf("RESET")>=0) // Format "SECXXXXX CHECK"
  {
    
     resetFunc ();  

  }

    else if(incomingData.indexOf("SIGNALSTRENGTH")>=0) // Format "SECXXXXX CHECK"
  {
    
   
    // Send a sms back to confirm that the relay is turned on
    
  SIM900.println("AT+CSQ\r");  
  delay(1000);
  receive_message();
  
   if(incomingData.indexOf("+CSQ:")>=0) // Format "SECXXXXX CHECK"
  {

    int KeyIndex = incomingData.indexOf(':');
    String Signal = incomingData.substring(KeyIndex+2,KeyIndex+4);
           
     SendSMS = "SIGNAL STRENGTH: " + Signal ;
  
      
    wait = true;
    send_message(SendSMS);
    incomingData.remove(0);  
  }
  }

      else if(incomingData.indexOf("IMEI")>=0) // Format "SECXXXXX CHECK"
  {
    
   
    // Send a sms back to confirm that the relay is turned on
    
  SIM900.println("AT+CGSN\r");  
  delay(1000);
  receive_message();
  
  

    String IMEI = incomingData.substring(8);
           
     SendSMS = "IMEI: " + IMEI ;
  
      
    wait = true;
    send_message(SendSMS);
    incomingData.remove(0);  
  
  }

  

 


}




}

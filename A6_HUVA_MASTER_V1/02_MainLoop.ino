/////////////////////////////////   LOOP DE LOOP   /////////////////////////////////////////////

void loop()
{

  CheckButton();
  receive_message();
  
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
   
      SendSMS = "Device Alerted! DEVICE ID: " + DeviceID ;
      wait = true;
//    send_message(SendSMS); 
      Serial.println("SMS Sent");
      incomingData.remove(0);
      
    }
  else if(incomingData.indexOf("CHECK")>=0) // Format "SECXXXXX CHECK"
  {
    
    SendSMS = "IM ALIVE! DEVICE ID: " + DeviceID ;
    wait = true;
    send_message(SendSMS);
     //Alert();
    incomingData.remove(0);  
  }

  else if(incomingData.indexOf("UPDATENUMB")>=0) // Format "SECXXXXX UPDATENUMB @077XXXXXX"
  {    
    int KeyIndex = incomingData.indexOf('@');
    ServerNumber = incomingData.substring(KeyIndex+1);
    //incomingData.remove(0);

       SendSMS = "Connected to new Server! DEVICE ID: " + DeviceID ;
       wait = true;
     send_message(SendSMS); 
     Serial.println("SMS Sent");
     incomingData.remove(0);
     //SendSMS.remove(0);
  }

    else if(incomingData.indexOf("UPDATESEC")>=0) // Format "SECXXXXX UPDATESEC @SECXXXXXX"
  {    
    int KeyIndex = incomingData.indexOf('@');
    SecurityKey = incomingData.substring(KeyIndex+1);

    SendSMS = "Security Key Changed To: " + SecurityKey + " DEVICE ID: " + DeviceID ;
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
    BeeperOn = incomingData.substring(KeyIndex+1);
   // incomingData.remove(0); 

     SendSMS = "Beeper Status: " + BeeperOn + "DEVICE ID: " + DeviceID ;
     wait = true;
     send_message(SendSMS); 
     Serial.println("SMS Sent");
     incomingData.remove(0);
     //SendSMS.remove(0);
    
  }

    else if(incomingData.indexOf("CLEARSMS")>=0) // Format "SECXXXXX CHECK"
  {
    
    SendSMS = "ALL SMS DATABASE CLEARED: " + DeviceID ;
    // Send a sms back to confirm that the relay is turned on
    
  SIM900.println("AT+CMGD=1,4\r");  
  delay(5000);
    wait = true;
    send_message(SendSMS);
     //Alert();
     incomingData.remove(0);  
  }


//    else if(incomingData.indexOf("UPDATEID")>=0) // Format "SECXXXXX UPDATEID @HMDXXXXXX"
//  {
//    if(incomingData.indexOf(DeviceID)>=0)
//    { 
//    
//    int KeyIndex = incomingData.indexOf('%');
//    DeviceID = incomingData.substring(KeyIndex+1);
//    incomingData.remove(0);  
//    }
//  }
}
  else{
    //SIM900.println("AT+CMGD=1,4");   
  }


       
} 



//This line checks whether the host number is changed
// FORMAT -   " NUM 077406125"
// INDEX REF-   0123456789012




/////////////////////////////////   BEEPER SEQUENCE CODE   /////////////////////////////////////////////

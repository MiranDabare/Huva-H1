/////////////////////////////////   LOOP DE LOOP   /////////////////////////////////////////////

void loop()
{
  CheckButton();
  receive_message();
  Services();    
} 


void Services()
{
  if(incomingData.indexOf(SecurityKey)>=0)
{
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
    }
    
  else if(incomingData.indexOf("CHECK")>=0) // Format "SECXXXXX CHECK"
  {    
    SendSMS = "IM ALIVE!";
    wait = true;
    send_message(SendSMS);   
    incomingData.remove(0);  
  }

  else if(incomingData.indexOf("UPDATENUMB")>=0) // Format "SECXXXXX UPDATENUMB @+9477XXXXXXX"
  {    
    int KeyIndex = incomingData.indexOf('@');
    String NServerNumber = incomingData.substring(KeyIndex+1, KeyIndex+13);
    writeString(9, NServerNumber);  //Address 10 and String type data
    ServerNumber = NServerNumber;
    SendSMS = "Connected to new Server!";
    wait = true;
    send_message(SendSMS); 
    incomingData.remove(0);

  }

    else if(incomingData.indexOf("UPDATESEC")>=0) // Format "SECXXXXX UPDATESEC @SECXXXXXX"
  {    
    int KeyIndex = incomingData.indexOf('@');
    String NSecurityKey = incomingData.substring(KeyIndex+1,KeyIndex+9);
    writeString(0, NSecurityKey);  //Address 10 and String type data
    SendSMS = "Sec Key Changed: " + NSecurityKey;
    wait = true;
    send_message(SendSMS); 
   
    incomingData.remove(0);  
  }

  else if(incomingData.indexOf("UPDATEBEEPER")>=0) // Format "SECXXXXX UPDATEBEEPER @1 or @0"
  { 
    int KeyIndex = incomingData.indexOf('@');
    String NAlertBeeper = incomingData.substring(KeyIndex+1,KeyIndex+3);
    writeString(22, NAlertBeeper);  //Address 10 and String type data
    AlertBeeper = incomingData.substring(KeyIndex+1);
    SendSMS = "Beeper: " + AlertBeeper ;
    wait = true;
    send_message(SendSMS); 
    incomingData.remove(0);    
  }

    else if(incomingData.indexOf("RESET")>=0) // Format "SECXXXXX CHECK"
  {
    resetFunc ();  
  }

    else if(incomingData.indexOf("SIGNALSTRENGTH")>=0) // Format "SECXXXXX CHECK"
  { 
    SIM900.println("AT+CSQ\r");  
    delay(1000);
    receive_message();
  
   if(incomingData.indexOf("+CSQ:")>=0) // Format "SECXXXXX CHECK"
  {
    int KeyIndex = incomingData.indexOf(':');
    String Signal = incomingData.substring(KeyIndex+2,KeyIndex+4);
           
    SendSMS = "SIGNAL: " + Signal ;      
    wait = true;
    send_message(SendSMS);
    incomingData.remove(0);  
  }
  }

      else if(incomingData.indexOf("IMEI")>=0) // Format "SECXXXXX CHECK"
  {
    SIM900.println("AT+CGSN\r");  
    delay(1000);
    receive_message();
    String IMEI = incomingData.substring(8);           
    SendSMS = "IMEI: " + IMEI ;        
    wait = true;
    send_message(SendSMS);
    incomingData.remove(0);  
    }
    
       else if(incomingData.indexOf("BUFFERTIME")>=0) // Format "SECXXXXX BUFFERTIME @10000"
  {
    int KeyIndex = incomingData.indexOf('@');
    String NAlertBeeper = incomingData.substring(KeyIndex+1,KeyIndex+7);
    EEPROMWritelong(45, NAlertBeeper.toInt());
    BufferTime = EEPROMReadlong(45);
    SendSMS = "New Buffer: " + BufferTime ;
    wait = true;
    send_message(SendSMS); 
    incomingData.remove(0);   
    }
    
}
}

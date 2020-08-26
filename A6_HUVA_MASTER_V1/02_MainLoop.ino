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

    else if(incomingData.indexOf("SIGNALSTRENGTH")>=0) // Format "SECXXXXX CHECK"
  {
    
    SendSMS = "ALL SMS DATABASE CLEARED: " + DeviceID ;
    // Send a sms back to confirm that the relay is turned on
    
  SIM900.println("AT+CSQ\r");  
  delay(1000);
  String Info = incomingData;
   
    wait = true;
    send_message(Info);
    incomingData.remove(0);  
  }

    else if(incomingData.indexOf("Test")>=0) // Format "SECXXXXX Test @XXXXX"
  {
//     int KeyIndex = incomingData.indexOf('@');
//    String Tester = incomingData.substring(KeyIndex+1);

   
  SIM900.println("AT"); //Once the handshake test is successful, it will back to OK
//  updateSerial();
  SIM900.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
//  updateSerial();
  SIM900.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
//  updateSerial();
  SIM900.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
    SIM900.println("AT+CGSN"); //Check whether it has registered in the network
//  updateSerial();
    SIM900.println("AT+GSN"); //Check whether it has registered in the network
//  updateSerial();
    SIM900.println("AT+CNUM"); //Check whether it has registered in the network
//  updateSerial();
  
  receive_message();
  SendSMS = Store;
//  Serial.println(SendSMS);
    wait = true;
    send_message(SendSMS);
    incomingData.remove(0);
    resetFunc();  
  }

  


}

  else{
    //SIM900.println("AT+CMGD=1,4");   
  }


       
} 

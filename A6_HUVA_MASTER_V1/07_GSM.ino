void send_message(String SendSMS)
{
 
  while (wait == true){
    RGB_LED("RED");

    delay(100);
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);  
    SIM900.println("AT+CMGS=\"" + ServerNumber + "\""); // Replace it with your mobile number
  delay(100);
    SIM900.println(SendSMS);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
   delay(100);
  RGB_LED("BLUE");
  delay(100);
    wait =false;
  }  
}

void receive_message()
{
  if (SIM900.available() > 0)
  {
    incomingData = SIM900.readString(); // Get the data from the serial port.
//        Serial.print(incomingData); 
    delay(10); 

    }
}

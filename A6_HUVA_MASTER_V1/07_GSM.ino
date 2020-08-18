void send_message(String SendSMS)
{
 
  while (wait == true){
    SIM900.print("AT+CUSD=0\r"); 
    delay(100);
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);  
//  SIM900.println("AT+CMGS=\"+0774061725\""); // Replace it with your mobile number
    SIM900.println("AT+CMGS=\"" + ServerNumber2 + "\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(SendSMS);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);
    wait =false;
  }  
}

void send_message_demo1(String DemoMessage1)
{
  while (wait == true){
    SIM900.print("AT+CUSD=0\r"); 
    delay(100);
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);  
//  SIM900.println("AT+CMGS=\"+0774061725\""); // Replace it with your mobile number
    SIM900.println("AT+CMGS=\"" + DemoNumber1 + "\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(DemoMessage1);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);  
  SIM900.print("AT+CUSD=2\r"); 
  wait =false;
  }
}

void send_message_demo2(String DemoMessage2)
{
  while (wait == true){
    SIM900.print("AT+CUSD=0\r"); 
    delay(100);
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);  
//  SIM900.println("AT+CMGS=\"+0774061725\""); // Replace it with your mobile number
    SIM900.println("AT+CMGS=\"" + DemoNumber2 + "\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(DemoMessage2);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  SIM900.print("AT+CUSD=2\r"); 
  delay(100);  
  wait =false;
}
}

void receive_message()
{
  if (SIM900.available() > 0)
  {
    incomingData = SIM900.readString(); // Get the data from the serial port.
   
    Serial.print(incomingData); 
    delay(10); 

    }
}

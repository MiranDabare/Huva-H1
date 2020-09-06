 /////////////////////////////////   SETUP   /////////////////////////////////////////////

void setup(){

 


  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  pinMode(REMOTE_D0_PIN, INPUT);
  pinMode(REMOTE_D1_PIN, INPUT);
  pinMode(REMOTE_D2_PIN, INPUT);
  pinMode(REMOTE_D3_PIN, INPUT);
  pinMode(REMOTE_GND_PIN, OUTPUT);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GSM_PIN, OUTPUT);
  pinMode(RF_ENABLE_PIN, OUTPUT);

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GSM_PIN, LOW);
  digitalWrite(SIREN_PIN, LOW);
  digitalWrite(RF_ENABLE_PIN, HIGH);
  digitalWrite(REMOTE_GND_PIN, HIGH);

  RGB_LED("GREEN");

 delay(1000); //Let the GSM module connect

  digitalWrite(GSM_PIN, HIGH);
  delay(5000);
 
  Serial.begin(9600); // baudrate for serial monitor
  SIM900.begin(9600); // baudrate for GSM shield
  delay(1000); //Let the GSM module connect
  receive_message(); 

  
   SIM900.println("AT+IPR=9600\r"); 
   receive_message();
  delay(2000);

   SIM900.println("AT\r"); 
   receive_message();
  delay(2000);


   // set SMS mode to text mode
  SIM900.println("AT+CMGF=1\r");  
  delay(1000);
  receive_message();
  delay(1000);
  
  // set gsm module to tp show the output on serial out
  SIM900.println("AT+CNMI=2,2,0,0,0\r"); 
  delay(1000);
  receive_message();
  delay(1000);

 
  SIM900.println("AT+CMGD=1,4\r"); 
  delay(1000);
  receive_message(); 
  delay(2000);

     String NewSecKey;
  NewSecKey = read_String(0);
  SecurityKey = NewSecKey;
//  Serial.print("Read Data:");
//  Serial.println(SecurityKey);
  delay(1000);

   String NewServNumb;
  NewServNumb = read_String(9);
  ServerNumber = NewServNumb;
//  Serial.print("Read Data:");
//  Serial.println(ServerNumber);
  delay(1000);

   String NewAlertBeeper;
  NewAlertBeeper = read_String(22);
  AlertBeeper = NewAlertBeeper;
//  Serial.print("Read Data:");
//  Serial.println(AlertBeeper);
  delay(1000);


while (SignalOK == false)
{
  SIM900.println("AT+CSQ\r"); 
  delay(1000);
  receive_message();
  
   if(incomingData.indexOf("+CSQ:")>=0) // Format "SECXXXXX CHECK"
  {

    int KeyIndex = incomingData.indexOf(':');
    String Signal = incomingData.substring(KeyIndex+2,KeyIndex+4);
           
    
   Serial.println(Signal.toInt());
    incomingData.remove(0);  

    if (Signal.toInt() >= 20)
    {
//      Serial.println("Signal is gud!");
      SignalOK = true;
    }

    else
    {
//      Serial.println("Signal is bad!");
      RGB_LED("RED");
    }

        incomingData.remove(0);  
  }  

//  Serial.println(Signal);

}
  
 delay(1000);

  Serial.println("gprs initialize done!");
//    Serial.println("start to send message ...");
    RGB_LED("BLUE");
    
}
    

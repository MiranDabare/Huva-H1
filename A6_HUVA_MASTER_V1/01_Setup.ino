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

// delay(10000); //Let the GSM module connect

//  digitalWrite(GSM_PIN, HIGH);
 
  Serial.begin(9600); // baudrate for serial monitor
//  SIM900.begin(9600); // baudrate for GSM shield

//   SIM900.print("AT+CUSD=0\r"); 
//  delay(100);


   // set SMS mode to text mode
//  SIM900.print("AT+CMGF=1\r");  
//  delay(100);
  
  // set gsm module to tp show the output on serial out
//  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
//  delay(100);

 
//  SIM900.println("AT+CMGD=1,4\r");  
//  delay(5000);

  Serial.println("gprs initialize done!");
    Serial.println("start to send message ...");
    RGB_LED("BLUE");
    
}
    

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////// HUVA HOME ALERT CODE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//  DATE CREATED  : 1 JULY 2020
//  VERSION       : 3
//  PROGRAMMER    : MIRAN DABARE
///////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////   NOTES   /////////////////////////////////////////////
// * THIS CODE USES THE SIM900A MINI GSM MODULE WITH THE SIM900 GPRS LIBRARY
// * THE DEFAULT BAUDRATE OF SIM900 IS 115200
// * USE A TTL COMMUNICATOR WITH ARDUINO SERIAL MONITOR TO DROP THE BAUD TO 9600
// * SUPPORT FOR ARDUINO PRO MINI
// * REMEMBER TO PRESS RESET ON THE PRO MINI WHEN THE CODE IS JUST ABOUT TO UPLOAD
// * THE SIM900 NEEDS 500+ uF CAPACITOR PARALLE TO THE POWER TO PREVENT FROM SURGE DYING

/////////////////////////////////   HEADERS   /////////////////////////////////////////////
/*
 * COLOURS FOR REFERENCE
 * RGB_color(255, 0, 0); // Red
   RGB_color(0, 255, 0); // Green
   RGB_color(0, 0, 255); // Blue
   RGB_color(255, 255, 125); // Raspberry
   RGB_color(0, 255, 255); // Cyan
   RGB_color(255, 0, 255); // Magenta
   RGB_color(255, 255, 0); // Yellow
   RGB_color(255, 255, 255); // White
  */
#include <SoftwareSerial.h> // Library for using serial communication
SoftwareSerial SIM900(11, 10); // Pins 7, 8 are used as used as software serial pins
//

#define BUZZER_PIN  9
#define GSM_PIN     4
#define BUTTON_PIN  2

#define LED_RED_PIN 3
#define LED_GREEN_PIN 5
#define LED_BLUE_PIN  6

#define REMOTE_D3_PIN  7
#define REMOTE_GND_PIN  14
#define REMOTE_D1_PIN  16
#define REMOTE_D2_PIN  15
#define REMOTE_D0_PIN  17

#define SIREN_PIN  8
#define RF_ENABLE_PIN  12 //Pull this down before transmitting

String incomingData = "";   // for storing incoming serial data
String message = "";   // A String for storing the message
String SendSMS = "";
String DeviceBatchID = "BAT12345" ; 
String DeviceID = "HMD1";

String ServerNumber = "+94774061725";
String ServerNumber2 = "+94778755176";

String DemoNumber2  = "+94764035418";
String DemoNumber1  = "+94774701366";
String TestNumber  = "+94774061725";

String DemoMessage1 = "SEC12345 TRIGGER SILENT";
String DemoMessage2 = "SEC12345 TRIGGER LOUD";
String UserMessage1 = "There is an Emergency at Mr. Kalubovila's Home!";
String UserMessage2 = "There is an Emergency at Mr. Dabare's Home!";
String TestMessage = "This module is working fine :)";

String SecurityKey = "SEC12345";

/////////////////////////////////   VARIABLES   /////////////////////////////////////////////


bool Pressed = false;
String BeeperOn = "OFF";
String AlertBeeper = "OFF";
 bool wait = true;
 bool Pass = false;
bool GSMPass = false;
bool ConsolePass = false;


// //============ RGB LED COLOUR GOVERNING CODE ===============\\
//void RGB_color(int red_light_value, int green_light_value, int blue_light_value){
//  analogWrite(LED_RED_PIN, red_light_value);
//  analogWrite(LED_GREEN_PIN, green_light_value);
//  analogWrite(LED_BLUE_PIN, blue_light_value);
//}

 void(* resetFunc) (void) = 0;



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

// delay(10000); //Let the GSM module connect

//  digitalWrite(GSM_PIN, HIGH);
 
  Serial.begin(9600); // baudrate for serial monitor
//  SIM900.begin(9600); // baudrate for GSM shield
//
//   SIM900.print("AT+CUSD=0\r"); 
//  delay(100);
//
//
//   // set SMS mode to text mode
//  SIM900.print("AT+CMGF=1\r");  
//  delay(100);
//  
//  // set gsm module to tp show the output on serial out
//  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
//  delay(100);
//
// 
//  SIM900.println("AT+CMGD=1,4\r");  
//  delay(5000);
//
//  Serial.println("gprs initialize done!");
//    Serial.println("start to send message ...");
    RGB_color(0, 0, 255); // Blue
    
}
    

 




/////////////////////////////////   LOOP DE LOOP   /////////////////////////////////////////////

void loop()
{

//  float looptime = millis();

  CheckButton();
  

  receive_message();
  
if(incomingData.indexOf(SecurityKey)>=0)
{

  // if received command is to turn on relay
  if(incomingData.indexOf("TRIGGER")>=0  && incomingData.indexOf("+CMT:")>=0)
  {    
    if(incomingData.indexOf("SILENT")>=0){
    AlertBeeper = "OFF";
    }

     if(incomingData.indexOf("LOUD")>=0){
    AlertBeeper = "ON";
    }
     Alert();
   
      SendSMS = "Device Alerted! DEVICE ID: " + DeviceID ;
      wait = true;
//     send_message(SendSMS); 
     Serial.println("SMS Sent");
     incomingData.remove(0);

  }
  else if(incomingData.indexOf("CHECK")>=0) // Format "SECXXXXX CHECK"
  {
    
    SendSMS = "IM ALIVE! DEVICE ID: " + DeviceID ;
    // Send a sms back to confirm that the relay is turned on
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

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(LED_RED_PIN, red_light_value);
  analogWrite(LED_GREEN_PIN, green_light_value);
  analogWrite(LED_BLUE_PIN, blue_light_value);
}


/////////////////////////////////   SENDING CODE   /////////////////////////////////////////////

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

     { // the door is closed
      Pressed = false;
     } else if (!Pressed) 
     { // the door was just opened (the door is open and previously it was closed)
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
//            SendSMS = "ALERT! DEVICE ID: " + DeviceID ;

//              SendSMS = UserMessage1;
            
           
           // Send a sms back to confirm that the relay is turned on
           wait = true;

//           SIM900.println("AT+CMGD=1,4\r");  
//           delay(3000);

  wait = true;
//          send_message(SendSMS); 
          Serial.println("SMS Sent");
          delay(3000);
          receive_message();
          
          wait = true;
//        send_message_demo2(DemoMessage2);   
       
          Serial.println("SMS Sent1");
          delay(3000);
//          receive_message();

          Serial.println("SMS Sent2");
 

              delay(3000);
                Alert();
                }
          }  
        }
}

/////////////////////////////////   ALERT SEQUENCE CODE   /////////////////////////////////////////////

void Alert(){
  Serial.println("Alerting");
    
      // 15 minutes break
    int Timer = 0;

    while (Timer < 30){

        if (AlertBeeper == "ON")
        {
          for(int hz = 2400; hz < 2950; hz+=5)
          {    
            tone(BUZZER_PIN, hz, 600);
            delay(5);    
           }
 
        
  
   RGB_color(255, 0, 0); // Red
    delay(50);
   RGB_color(0, 0, 0); // Off
    delay(50);
    
      Timer++;
      incomingData.remove(0);

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        delay(50);
        break;
      }
    }


            if (AlertBeeper == "OFF")
        {
  
    RGB_color(255, 0, 0); // Red
    delay(500);
   RGB_color(0, 0, 0); // Off
    delay(500);
    
      Timer++;
      incomingData.remove(0);

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        delay(50);
        break;
      }
    }
    }

    
    RGB_color(0, 0, 0); // Off
    
 
  resetFunc();
}

/////////////////////////////////   RECEIVING CODE   /////////////////////////////////////////////


//This line checks whether the host number is changed
// FORMAT -   " NUM 077406125"
// INDEX REF-   0123456789012




/////////////////////////////////   BEEPER SEQUENCE CODE   /////////////////////////////////////////////

void Beeper()
{
  
  int Counter = 0;

      if (BeeperOn.indexOf("ON")>=0)
  {
      while (Counter < 10)
  {
      digitalWrite(BUZZER_PIN, HIGH);
     RGB_color(0, 255, 0); // Green
      delay(50);
      digitalWrite(BUZZER_PIN, LOW);
      RGB_color(0, 0, 0); // Off
      delay(50);  

        Counter++;
  }
  RGB_color(0, 255, 0); // Green
  }


      if (BeeperOn.indexOf("OFF")>=0)
  {
      while (Counter < 10)
  {
      
       RGB_color(0, 255, 0); // Green
      delay(50);
      
      RGB_color(0, 0, 0); // Off
      delay(50);  

        Counter++;
  }
     RGB_color(0, 255, 0); // Green
  }
  
}

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

void Siren_Check() //Siren Transmitter Test 
{

   RGB_color(0, 0, 255); // Blue

  for (int f = 0; f <= 5; f++)
  { 
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(0, 255, 255); // Blue
  delay(500);

   
    digitalWrite(SIREN_PIN, HIGH);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(255, 255, 0); // Blue
     delay(500);
  }
}

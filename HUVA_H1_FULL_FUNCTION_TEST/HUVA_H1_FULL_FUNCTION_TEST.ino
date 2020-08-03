///////////////////////////////////////////////////////////////////////////////////////
//////////////////////// HUVA FUNCTION TESTER ///////////////////////////////////
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


#define BUZZER_PIN  9
#define GSM_PIN     4
#define BUTTON_PIN  2

#define LED_RED_PIN 3
#define LED_GREEN_PIN 5
#define LED_BLUE_PIN  6

#define REMOTE_PIN  7
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

String DemoMessage1 = "SEC12345 TRIGGER SILENT";
String DemoMessage2 = "SEC12345 TRIGGER LOUD";
String UserMessage1 = "There is an Emergency at Mr. Kalubovila's Home!";
String UserMessage2 = "There is an Emergency at Mr. Dabare's Home!";

String SecurityKey = "SEC12345";

/////////////////////////////////   VARIABLES   /////////////////////////////////////////////


bool Pressed = false;
String BeeperOn = "OFF";
String AlertBeeper = "OFF";
 bool wait = true;

// //============ RGB LED COLOUR GOVERNING CODE ===============\\
//void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
//{
//  analogWrite(LED_RED_PIN, red_light_value);
//  analogWrite(LED_GREEN_PIN, green_light_value);
//  analogWrite(LED_BLUE_PIN, blue_light_value);
//}

 void(* resetFunc) (void) = 0;



/////////////////////////////////   SETUP   /////////////////////////////////////////////

void setup(){

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(REMOTE_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GSM_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(RF_ENABLE_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GSM_PIN, LOW);
  digitalWrite(RF_ENABLE_PIN, LOW);


 
  Serial.begin(9600); // baudrate for serial monitor

  
    
}
    

 




/////////////////////////////////   LOOP DE LOOP   /////////////////////////////////////////////

void loop()
{
 Test3();

} 



//TEST 1 - LED CHECK
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(LED_RED_PIN, red_light_value);
  analogWrite(LED_GREEN_PIN, green_light_value);
  analogWrite(LED_BLUE_PIN, blue_light_value);
}

void Test1()
{
  RGB_color(0, 0, 255); // Blue
  delay(2000);
  RGB_color(0, 255, 0); // Green
  delay(2000);
  RGB_color(255, 0, 0); // Red
  delay(2000);
    RGB_color(255, 255, 125); // Raspberry
  delay(2000);
  RGB_color(0, 255, 255); // Cyan
  delay(2000);
  RGB_color(255, 0, 255); // Magenta
  delay(2000);
  RGB_color(255, 255, 0); // Yellow
  delay(2000);
  RGB_color(255, 255, 255); // White
  delay(2000);
  RGB_color(0, 0, 0); // Off
  delay(2000);
}

void Test2() // Button Testing
{
  bool State = digitalRead(BUTTON_PIN);
  
  if(State == HIGH)
  {
 
   Serial.println("Im in High");
   RGB_color(0, 0, 255); // Blue
  
  }
  
  if(State == LOW)
  {
    Serial.println("Im in Low");
    RGB_color(255, 0, 0); // Blue
  }
  
}

void Test3()
{
  bool State = digitalRead(REMOTE_PIN);

    if(State == HIGH)
  {
 
   Serial.println("Im in High");
   RGB_color(0, 255, 255); // Blue
  
  }
  
  if(State == LOW)
  {
    Serial.println("Im in Low");
    RGB_color(255, 255, 0); // Blue
  }

  
}

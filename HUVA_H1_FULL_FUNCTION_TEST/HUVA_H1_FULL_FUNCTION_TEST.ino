///////////////////////////////////////////////////////////////////////////////////////
//////////////////////// HUVA FUNCTION TESTER ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//  DATE CREATED  : 3 AUGUST 2020
//  VERSION       : 1
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

#define REMOTE_GND_PIN  14
#define REMOTE_D0_PIN  7 // D
#define REMOTE_D1_PIN  15 // C
#define REMOTE_D2_PIN  16 // B
#define REMOTE_D3_PIN  17 // A

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
bool Pass = false;
bool GSMPass = false;
bool ConsolePass = false;

 char val;

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
  pinMode(REMOTE_D0_PIN, INPUT);
  pinMode(REMOTE_D1_PIN, INPUT);
  pinMode(REMOTE_D2_PIN, INPUT);
  pinMode(REMOTE_D3_PIN, INPUT);
  pinMode(REMOTE_GND_PIN, OUTPUT);
  
  digitalWrite(REMOTE_GND_PIN, HIGH);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GSM_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
//  pinMode(RF_ENABLE_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GSM_PIN, LOW);

  digitalWrite(SIREN_PIN, LOW);
  digitalWrite(RF_ENABLE_PIN, HIGH);


 
  Serial.begin(9600); // baudrate for serial monitor

  
    
}
    

 




/////////////////////////////////   LOOP DE LOOP   /////////////////////////////////////////////

void loop()
{



Processing_Test();
} 

void Processing_Test()
{
    if(Serial.available())
    {  //id data is available to read

     val = Serial.read();

    if (val == '1')
    {       //if r received
      Test1();      
    }
      
    if (val == '2')
    {
      for (int i = 0; i<500 ; i++)
      {
        Test2();
      }
     }

        if (val == '3')
    {
      for (int i = 0; i<500 ; i++)
      {
        Test3();
      }      
    }

        if (val == '4')
    {
      for (int i = 0; i<500 ; i++)
      {
        Test4();
        val = Serial.read();
      }      
    }

        if (val == '5')
    {
      
        Test5();
          
    }

        if (val == '6')
    {
      for (int i = 0; i<2000 ; i++)
      {
        Test6();
      }      
    }

        if (val == '7')
    {
      for (int i = 0; i<500 ; i++)
      {
        Test7();
      }      
    }
      
      
    
    }
}

void Auto_Tester ()
{
   while (ConsolePass == false){
Serial.println ("Conducting Test 1 - LED");
  Test1();

float Timer = millis();
 Serial.println ("Conducting Test 2 - BUTTON");
  while ((millis() - Timer) <10000)
  {
    Test2();
  }
  
 Timer = millis();
 Serial.println ("Conducting Test 3 - REMOTE");
    while ((millis() - Timer) <20000)
  {
    Test3();
  }

   Timer = millis();
   Serial.println ("Conducting Test 4 - BUZZER");
    while ((millis() - Timer) <20000)
  {
    Test4();
  }

   Timer = millis();
   Serial.println ("Conducting Test 5 - SMS Sending");
    while ((millis() - Timer) <60000)
  {
    Test5();
  }

   Timer = millis();
    Serial.println ("Conducting Test 6 - SMS Recieving");
    while ((millis() - Timer) <60000)
  {
    Test6();
  }

     Timer = millis();
    Serial.println ("Conducting Test 7 - Siren");
    while ((millis() - Timer) <30000)
  {
    Test7();
  }
  

ConsolePass = true;
}
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

RGB_LED("WHITE");
delay(1000);
RGB_LED("YELLOW");
delay(1000);
RGB_LED("PINK");
delay(1000);
RGB_LED("CYAN");
delay(1000);
RGB_LED("BLUE");
delay(1000);
RGB_LED("RED");
delay(1000);
RGB_LED("RED");
delay(1000);
RGB_LED("GREEN");
delay(1000);
RGB_LED("OFF");
delay(1000);
 
}

void RGB_LED(String LEDColour)
{
  if (LEDColour == "WHITE")
  {
    RGB_color(0, 0, 0); 
  }

  if (LEDColour == "YELLOW")
  {
    RGB_color(0, 0, 255); 
  }

  if (LEDColour == "PINK")
  {
    RGB_color(0, 255, 0); 
  }

  if (LEDColour == "CYAN")
  {
    RGB_color(255, 0, 0); 
  }

  if (LEDColour == "BLUE")
  {
    RGB_color(255, 255, 0);
  }

  if (LEDColour == "RED")
  {
    RGB_color(0, 255, 255); 
  }

  if (LEDColour == "GREEN")
  {
    RGB_color(255, 0, 255); 
  }

  if (LEDColour == "OFF")
  {
    RGB_color(255, 255, 255); 
  }

  
}

void Test2() // Button Testing
{
  bool State = digitalRead(BUTTON_PIN);
  
  if(State == HIGH)
  {
 
   Serial.println("Button Off");
   RGB_color(0, 0, 255); // Blue
  
  }
  
  if(State == LOW)
  {
    Serial.println("Button On");
    RGB_color(255, 0, 0); // Blue
  }
  
}

void Test3()// Remote Recieve test
{
  
  bool StateD0 = digitalRead(REMOTE_D0_PIN); // MAIN TRIGGER
  bool StateD1 = digitalRead(REMOTE_D1_PIN); // CONSOLE CHECK
  bool StateD2 = digitalRead(REMOTE_D2_PIN); // SIREN CHECK
  bool StateD3 = digitalRead(REMOTE_D3_PIN); // NC

  digitalWrite(REMOTE_GND_PIN, HIGH);

  Serial.print(digitalRead(REMOTE_D0_PIN)); Serial.print(" ");
  Serial.print(digitalRead(REMOTE_D1_PIN));Serial.print(" ");
  Serial.print(digitalRead(REMOTE_D2_PIN));Serial.print(" ");
  Serial.println(digitalRead(REMOTE_D3_PIN));
  
  RGB_color(0, 0, 0); // Blue

    if(StateD0 == HIGH)
  {
 
//   Serial.println("D0 in High");
   RGB_color(255, 0, 0); // Blue
  
  } 
   if(StateD1 == HIGH)
  {
 
//   Serial.println("D1 in High");
   RGB_color(0, 255, 0); // Blue
  
  }
   if(StateD2== HIGH)
  {
 
//   Serial.println("D2 in High");
   RGB_color(0, 0, 255); // Blue
  
  }
   if(StateD3 == HIGH)
  {
 
//   Serial.println("D3 in High");
   RGB_color(255, 255, 0); // Blue
  
  }
  
  else
  {
//    Serial.println("Im in Low");
    RGB_color(0, 255, 255); // Blue
  }

  while (digitalRead(BUTTON_PIN) == LOW)
  {
    digitalWrite(REMOTE_GND_PIN, LOW);
    Serial.println("RF OFF");
    RGB_color(125, 125, 125); // Blue
  }
  


  
}

void Test4() // Buzzer Test
{
    bool State = digitalRead(BUTTON_PIN);
     RGB_color(0, 255, 0); // Yellow
  
  if(State == HIGH)
  {
 
   Serial.println("Im in High");
   digitalWrite(BUZZER_PIN, LOW);
  RGB_color(255, 255, 0); // Yellow
  
  }
  
  if(State == LOW || val == '9')
  {
    Serial.println("Im in Low");
    digitalWrite(BUZZER_PIN, HIGH);
    RGB_color(0, 0, 255); // Blue
   
  }
}
  void Test44() // Buzzer Test
{
    
     RGB_color(0, 255, 0); // Yellow
  
  
 delay(2000);
   Serial.println("Buzzer Off");
   digitalWrite(BUZZER_PIN, LOW);
  RGB_color(255, 255, 0); // Yellow
  
 delay(2000);
    Serial.println("Buzzer On");
    digitalWrite(BUZZER_PIN, HIGH);
    RGB_color(0, 0, 255); // Blue
   
 
  
}


void Test5() // GSM SMS Sending Test
{
   if (Pass == false)
   {
    Test5_Init();
   }
}

void Test5_Init()
{
   RGB_color(255, 0, 0); // R
   
      digitalWrite(GSM_PIN, HIGH);

        delay(10000);
 

  SIM900.begin(9600); // baudrate for GSM shield

    SIM900.println("AT+IPR=9600\r"); 
  delay(2000);


   // set SMS mode to text mode
  SIM900.print("AT+CMGF=1\r");  
  delay(2000);
  
  // set gsm module to tp show the output on serial out
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  delay(2000);

 
  SIM900.println("AT+CMGD=1,4\r");  
  delay(5000);

  Serial.println("gprs initialize done!");
    Serial.println("start to send message ...");
    RGB_color(0, 0, 255); // Blue



    SIM900.print("AT+CUSD=0\r"); 
    delay(2000);
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(2000);  
    SIM900.println("AT+CMGS=\"" + TestNumber + "\""); // Replace it with your mobile number
  delay(2000);
  SIM900.println(TestMessage);   // The SMS text you want to send
  delay(2000);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(2000);
  SIM900.println();
  delay(2000);  
  SIM900.print("AT+CUSD=2\r"); 
  RGB_color(0, 255, 255); // Blue
  
  Pass =true;
  
    
}


void Test6() // GSM SMS Reciving Test (CONSOLETEST)
{
   if (Pass == false)
   {
    Test6_Init();
   }
   
   RGB_color(0, 255, 0);
}

void Test6_Init()
{
   RGB_color(255, 0, 0); // R
   
      digitalWrite(GSM_PIN, HIGH);

        delay(10000);
 

 // SIM900.begin(9600); // baudrate for GSM shield
  receive_message();

 delay(2000);

   // set SMS mode to text mode
  SIM900.print("AT+CMGF=1\r");  

  delay(2000);
  
  // set gsm module to tp show the output on serial out
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  
  delay(2000);

 
  SIM900.println("AT+CMGD=1,4\r");  
 
  delay(5000);

  Serial.println("gprs initialize done!");
    Serial.println("start to send message ...");
    RGB_color(0, 0, 255); // Blue

    while (GSMPass == false)
    {
      RGB_color(255, 255, 0);
      receive_message();
      
      if(incomingData.indexOf("CONSOLETEST")>=0)
      {
        Test1();
        GSMPass = true;
       }
    }
    
    Pass = true;
 
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


void Test7() //Siren Transmitter Test 
{
 bool State = digitalRead(BUTTON_PIN);
   RGB_color(0, 0, 255); // Blue

  if(State == LOW)
  {
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(0, 255, 255); // Blue
  }

    if(State == HIGH)
  {
    digitalWrite(SIREN_PIN, HIGH);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(255, 255, 0); // Blue
  }
}


  void Test7_1() //Siren Transmitter Test 
{
 
   RGB_color(0, 0, 255); // Blue

  
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(0, 255, 255); // Blue
delay (200);
    digitalWrite(SIREN_PIN, HIGH);
    digitalWrite(RF_ENABLE_PIN, HIGH);
    RGB_color(255, 255, 0); // Blue

    delay (200);
 
}

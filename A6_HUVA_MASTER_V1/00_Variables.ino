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
 * 
  RGB_color(0, 0, 0); // WHITE
  RGB_color(0, 0, 255); // YELLOW
  RGB_color(0, 255, 0); // PINK
  RGB_color(255, 0, 0); // CYAN
  RGB_color(255, 255, 0); // BLUE
  RGB_color(0, 255, 255); // RED
  RGB_color(255, 0, 255); // GREEN
  RGB_color(255, 255, 255); // OFF
  
  */
#include <avr/sleep.h>
#include <SoftwareSerial.h> // Library for using serial communication
SoftwareSerial SIM900(11, 10); // Pins 7, 8 are used as used as software serial pins
#include <EEPROM.h>


void writeString(char add,String data);
String read_String(char add);

#define BUZZER_PIN  9
#define GSM_PIN     4
#define BUTTON_PIN  2


#define LED_RED_PIN 3
#define LED_GREEN_PIN 5
#define LED_BLUE_PIN  6

#define REMOTE_D3_PIN  15 // A1 - D
#define REMOTE_GND_PIN  14 
#define REMOTE_D1_PIN  17 //A3 -B
#define REMOTE_D2_PIN  16 //A2 - C
#define REMOTE_D0_PIN  7 // - A

#define SIREN_PIN  8
#define RF_ENABLE_PIN  12 //Pull this down before transmitting

String incomingData = "";   // for storing incoming serial data
//String Store = "TEST RESULTS - ";
String message = "";   // A String for storing the message
String SendSMS = "";
//String DeviceBatchID = "BAT12345" ; 
//String DeviceID = "HMD1";

String ServerNumber = "+94769295070";
String ServerNumber2 = "+94774061725";

String DemoNumber1  = "+94764035418"; //Console 1
String DemoNumber2  = "+94774701366"; // Console 2

String TestNumber  = "+94774061725";

String DemoMessage1 = "SEC12345 TRIGGER LOUD";
String DemoMessage2 = "SEC12345 TRIGGER LOUD";
String UserMessage1 = "There is an Emergency at Mr. Kalubovila's Home!";
String UserMessage2 = "There is an Emergency at Mr. Dabare's Home!";

String TestMessage = "This module is working fine :)";

String SecurityKey;

/////////////////////////////////   VARIABLES   /////////////////////////////////////////////


bool Pressed = false;
String BeeperOn = "ON";
String AlertBeeper = "OFF";
 bool wait = true;
 bool Pass = false;
bool GSMPass = false;
bool ConsolePass = false;

bool TriggerArmed =  false;
bool Activate_Alarm =  false;

int PressTime = 0;
int Clock = 0;
int Clock2 = 0;

 void(* resetFunc) (void) = 0;
 

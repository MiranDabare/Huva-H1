/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#include <EEPROM.h>



int ledState;                // variable to hold the led state
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin




void setup() {


  
  // initialize serial monitor
  Serial.begin (9600);

  //check stored LED state on EEPROM using function defined at the end of the code
  checkLedState(); 
}

void loop() {
 
  EEPROM.update(0, 1);
  delay(2000);
  checkLedState();
  EEPROM.update(0, 256);
  delay(2000);
  checkLedState();

}


void checkLedState() {
   
   ledState = EEPROM.read(0);
   Serial.println(ledState);
  
   
}

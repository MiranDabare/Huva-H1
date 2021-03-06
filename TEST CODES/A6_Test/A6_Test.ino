#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(11, 10); //A6 Tx & Rx is connected to Arduino #3 & #2
//String Store = "START - ";

//AT+IPR=9600

void setup()
{

  pinMode(4,OUTPUT);
//digitalWrite(4, LOW);
//  delay(5000);
digitalWrite(4, HIGH);
delay(5000);

  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
//  Serial.begin(115200);
//  mySerial.begin(115200);

    Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(5000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
//  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
//  updateSerial();
//  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
//  updateSerial();
//  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
//    mySerial.println("AT+CGSN"); //Check whether it has registered in the network
//  updateSerial();
//    mySerial.println("AT+GSN"); //Check whether it has registered in the network
//  updateSerial();

    mySerial.println("AT+CMGF=1"); //Check whether it has registered in the network
  updateSerial();
    mySerial.println("AT+CNMI=2,2,0,0,0"); //Check whether it has registered in the network
  updateSerial();
    mySerial.println("AT+CMGD=1,4"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(200);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
    
  }
//  Serial.println(Store);
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
//    Store = Store + mySerial.readString();
  }

  

  
}

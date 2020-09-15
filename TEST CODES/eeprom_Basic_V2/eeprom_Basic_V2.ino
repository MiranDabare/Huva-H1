/*
 * Circuits4you.com
 * Reading and Writing String to EEPROM Example Code
 * Oct 2018
 */

#include <EEPROM.h>
//
void writeString(char add,String data);
String read_String(char add);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  EEPROM.begin(512);
  String data = "SEC12345";
  String data1 = "87798";
   String data2 = "OFF";

  Serial.print("Writing Data:");
  Serial.println(data);

//  writeString(0, data);  //Address 10 and String type data
//  delay(10);
//  writeString(9, data1);  //Address 10 and String type data
//  delay(10);
  writeString(22, data2);  //Address 10 and String type data
  delay(10);
//EEPROM.write(40, 0);  //Address 10 and String type data
//  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  String recivedData;
  recivedData = read_String(0);
  Serial.print("Read Data:");
  Serial.println(recivedData);
  delay(1000);

  String recivedData1;
  recivedData1 = read_String(9);
  Serial.print("Read Data:");
  Serial.println(recivedData1);
  delay(1000);

   String recivedData2;
  recivedData2 = read_String(22);
  Serial.print("Read Data:");
  Serial.println(recivedData2);
  delay(1000);

  Serial.println(EEPROM.read(40));  //Address 10 and String type data
  delay(1000);
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
//  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

#include <EEPROMex.h>

String str;
String str1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Write & Read String EEPROM . . .");
  delay(1000);
//  write_StringEEPROM(0, "SEC98765"); //write_StringEEPROM or update_StringEEPROM(Address, String)
//  delay(1000);
//  write_StringEEPROM(9, "+94774061725"); //write_StringEEPROM or update_StringEEPROM(Address, String)
//delay(1000);
//  update_StringEEPROM(0, "Uteh Str"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  str = read_StringEEPROM(9); //String = read_StringEEPROM(Address)
  Serial.println(str);
  delay(1000);

  str1 = read_StringEEPROM1(0); //String = read_StringEEPROM(Address)
  Serial.println(str1);
  delay(1000);
}

//----------------------------------------------------------------------------------------read & write string to eeprom
bool write_StringEEPROM(int Addr, String input)
{
    char charbuf[15];
    input.toCharArray(charbuf,15);
    return EEPROM.writeBlock<char>(Addr, charbuf, 15); 
}

bool update_StringEEPROM(int Addr, String input)
{
    char charbuf[15];
    input.toCharArray(charbuf,15);
    return EEPROM.updateBlock<char>(Addr, charbuf, 15); 
}

String read_StringEEPROM(int Addr)
{
  String outputEEPROM;
  char output[] = " ";

  EEPROM.readBlock<char>(Addr, output, 15); 
  //convert to string
  outputEEPROM = String (output);
  return outputEEPROM;
}

String read_StringEEPROM1(int Addr)
{
  String outputEEPROM1;
  char output1[] = " ";

  EEPROM.readBlock<char>(Addr, output1, 15); 
  //convert to string
  outputEEPROM1 = String (output1);
  return outputEEPROM1;
}
//----------------------------------------------------------------------------------------

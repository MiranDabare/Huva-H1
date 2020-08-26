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
//----------------------------------------------------------------------------------------

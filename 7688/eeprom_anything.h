#ifndef eeprom_anything_h
#define eeprom_anything_h
#include <EEPROM.h>
#include <Arduino.h>

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  int i;
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
  return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  int i;
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  return i;
}
void cleanEEPROM(){
  
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
}

  
  }

#endif /* eeprom_anything_h */


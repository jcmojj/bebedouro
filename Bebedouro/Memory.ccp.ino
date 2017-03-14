#include "Memory.h"

Memory::Memory(int size, Drink &drink, byte drinkSize){
  Serial.begin(9600);
  _drink = &drink;
  _size = size;
  _drinkSize = drinkSize;
}

void Memory::print(){
  Serial.println("\n Memory\n");
  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());
  Serial.print("Memory Total Size (EEPROM):"); Serial.println(memorySize);

  Serial.print("Serial Number Memory");  Serial.print(" from " );  Serial.print(serialNumberBegin);  Serial.print(" to "); Serial.println(serialNumberEnd);
  Serial.print("SSID Name Memory");      Serial.print(" from " );  Serial.print(ssidNameBegin);      Serial.print(" to "); Serial.println(ssidNameEnd);
  Serial.print("SSID Password Memory");  Serial.print(" from " );  Serial.print(ssidPasswordBegin);  Serial.print(" to "); Serial.println(ssidPasswordEnd);
  Serial.print("Email Memory");          Serial.print(" from " );  Serial.print(userEmailBegin);     Serial.print(" to "); Serial.println(userEmailEnd);
  Serial.print("Data Memory");           Serial.print(" from " );  Serial.print(dataMemoryBegin);        Serial.print(" to "); Serial.println(dataMemoryEnd);

  
  delay(1);
  EEPROM.begin(_size);
  uint8_t value = 0;

  Serial.print("\n");
  Serial.println("Serial Number Memory");
  Serial.print("(address=");if(serialNumberBegin<100){Serial.print(" ");} if(serialNumberBegin<10){Serial.print(" ");}Serial.print(serialNumberBegin);Serial.print(")-");
  for(byte address = serialNumberBegin; address <= serialNumberEnd; address++){
      value = EEPROM.read(address);
      if(value<100){Serial.print(" ");} if(value<10){Serial.print(" ");}
      Serial.print(value, DEC);      
      if((address+1)%25 == 0){
        Serial.print("-(address=");if(address<100){Serial.print(" ");} if(address<10){Serial.print(" ");}Serial.print(address);Serial.print(")");
        Serial.println("");
        if(address != serialNumberEnd){Serial.print("(address=");if((address+1)<100){Serial.print(" ");} if((address+1)<10){Serial.print(" ");}Serial.print(address+1);Serial.print(")-");}
        delay(1);
      }else{
        Serial.print("-");
      }
  }


  Serial.print("\n");
  Serial.println("SSID Name Memory"); 
  Serial.print("(address=");if(ssidNameBegin<100){Serial.print(" ");} if(ssidNameBegin<10){Serial.print(" ");}Serial.print(ssidNameBegin);Serial.print(")-");
  for(byte address = ssidNameBegin; address <= ssidNameEnd; address++){
      value = EEPROM.read(address);
      if(value<100){Serial.print(" ");} if(value<10){Serial.print(" ");}
      Serial.print(value, DEC);      
      if((address+1)%25 == 0){
        Serial.print("-(address=");if(address<100){Serial.print(" ");} if(address<10){Serial.print(" ");}Serial.print(address);Serial.print(")");
        Serial.println("");
        if(address != ssidNameEnd){Serial.print("(address=");if((address+1)<100){Serial.print(" ");} if((address+1)<10){Serial.print(" ");}Serial.print(address+1);Serial.print(")-");}
        delay(1);
      }else{
        Serial.print("-");
      }
  }

 Serial.print("\n");
  Serial.println("SSID Password Memory"); 
  Serial.print("(address=");if(ssidPasswordBegin<100){Serial.print(" ");} if(ssidPasswordBegin<10){Serial.print(" ");}Serial.print(ssidPasswordBegin);Serial.print(")-");
  for(byte address = ssidPasswordBegin; address <= ssidPasswordEnd; address++){
      value = EEPROM.read(address);
      if(value<100){Serial.print(" ");} if(value<10){Serial.print(" ");}
      Serial.print(value, DEC);      
      if((address+1)%25 == 0){
        Serial.print("-(address=");if(address<100){Serial.print(" ");} if(address<10){Serial.print(" ");}Serial.print(address);Serial.print(")");
        Serial.println("");
        if(address != ssidPasswordEnd){Serial.print("(address=");if((address+1)<100){Serial.print(" ");} if((address+1)<10){Serial.print(" ");}Serial.print(address+1);Serial.print(")-");}
        delay(1);
      }else{
        Serial.print("-");
      }
  }

  Serial.print("\n");
  Serial.println("Email Memory"); 
  Serial.print("(address=");if(userEmailBegin<100){Serial.print(" ");} if(userEmailBegin<10){Serial.print(" ");}Serial.print(userEmailBegin);Serial.print(")-");
  for(byte address = userEmailBegin; address <= userEmailEnd; address++){
      value = EEPROM.read(address);
      if(value<100){Serial.print(" ");} if(value<10){Serial.print(" ");}
      Serial.print(value, DEC);      
      if((address+1)%25 == 0){
        Serial.print("-(address=");if(address<100){Serial.print(" ");} if(address<10){Serial.print(" ");}Serial.print(address);Serial.print(")");
        Serial.println("");
        if(address != userEmailEnd){Serial.print("(address=");if((address+1)<100){Serial.print(" ");} if((address+1)<10){Serial.print(" ");}Serial.print(address+1);Serial.print(")-");}
        delay(1);
      }else{
        Serial.print("-");
      }
  }
  EEPROM.end();
}

void Memory::printData(){
  EEPROM.begin(_size);
  uint8_t value = 0;
  Serial.print("\n");
  Serial.println("Data Memory"); 
  Serial.print("(address=");if(dataMemoryBegin<100){Serial.print(" ");} if(dataMemoryBegin<10){Serial.print(" ");}Serial.print(dataMemoryBegin);Serial.print(")-");
  for(int address = dataMemoryBegin; address <= dataMemoryEnd; address++){
      value = EEPROM.read(address);
      if(value<100){Serial.print(" ");} if(value<10){Serial.print(" ");}
      Serial.print(value, DEC);      
      if((address+1)%25 == 0){
        Serial.print("-(address=");if(address<100){Serial.print(" ");} if(address<10){Serial.print(" ");}Serial.print(address);Serial.print(")");
        Serial.println("");
        if(address != dataMemoryEnd){Serial.print("(address=");if((address+1)<100){Serial.print(" ");} if((address+1)<10){Serial.print(" ");}Serial.print(address+1);Serial.print(")-");}
        delay(1);
      }else{
        Serial.print("-");
      }
  }
//  Serial.print("\nSerial Number Memory from "); Serial.print(SNBegin); Serial.print(" to "); Serial.println(SNEnd);
//
//  Serial.print("(address= ");Serial.print(SNBegin);Serial.print(")-");
//  for(byte address = SNBegin; address <= SNEnd; address++){
//      value = EEPROM.read(address);
//      if(value<100){
//        Serial.print(" ");
//      }
//      if(value<10){
//        Serial.print(" ");
//      }
//      Serial.print(value, DEC);      
//      if((address+1)%10 == 0){
//        Serial.print("-(address=");if(address == 9){Serial.print(" ");}Serial.print(address);Serial.print(")");
//        Serial.println("");
//        if(address != SNEnd){Serial.print("(address=");Serial.print(address+1);Serial.print(")-");}
//        delay(1);
//      }else{
//        Serial.print("-");
//      }
//  }
//
//  Serial.print("\nPosicao"); Serial.print(0);Serial.print(": ");
//  Serial.print("(address= ");Serial.print(memoryBegin);Serial.print(")-");
//  for(int address = memoryBegin; address <= memoryEnd; address++){
//      delay(1);
//      value = EEPROM.read(address);
//      if(value<100){
//        Serial.print(" ");
//      }
//      if(value<10){
//        Serial.print(" ");
//      }
//      Serial.print(value, DEC);      
//      if(((address-memoryBegin+1)%_drinkSize) == 0){
//        Serial.print("-(address=");Serial.print(address);Serial.print(")");
//        Serial.print("\nPosicao"); Serial.print((address-memoryBegin+1)/12);Serial.print(": ");
//        if(address != memoryEnd){Serial.print("(address=");Serial.print(address+1);Serial.print(")-");}
//        delay(1);
//      }else{
//        Serial.print("-");
//      }
//  }
  
  
//  for(int address = memoryBegin; address <= memoryEnd; address++){
//    Serial.print("(");Serial.print(address);Serial.print(")");
//    if(((address-memoryBegin+1))%12 == 0){
//      Serial.print("\nPosicao"); Serial.print((address-memoryBegin+1)/12);Serial.print(": ");    
//    }
//      value = EEPROM.read(address);
//      Serial.print(value, DEC); 
//    
//
//    
//  }
  EEPROM.end();
}

void Memory::saveAtMemory(Drink &drink){
  
}

bool Memory::isDrinkToSend(){
  
}




void Memory::teste(){
  _drink->println();
  int ano = _drink->getAno();
  Serial.print("Ano:"); Serial.println(ano);
}

void Memory::teste2(){
  EEPROM.begin(_size);
  for(int address = 0; address<_size; address++){
    uint8_t var = EEPROM.read(address);
    delay(1);
    Serial.print(var);
    Serial.print("Address: "); Serial.print(address); 
    //Serial.print(" - SP:"); Serial.print(var);
    //Serial.print(" - SW:"); Serial.write(EEPROM.read(address));
    //Serial.print(" - SP(int):"); Serial.print((int)EEPROM.read(address));
    //Serial.print(" - SW(int):"); Serial.write((int)EEPROM.read(address));
    //Serial.print(" - SP(char):"); Serial.print((char)EEPROM.read(address));
    //Serial.print(" - SW(char):"); Serial.write((char)EEPROM.read(address));
    Serial.println("");
  }
}



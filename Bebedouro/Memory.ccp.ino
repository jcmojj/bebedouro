#include "Memory.h"
#include "Drink.h"

Memory::Memory(int size, Drink &drink, byte drinkSize){
  Serial.begin(9600);
  _drink = &drink;
  _size = size;
  _drinkSize = drinkSize;
}

void Memory::printDrinkFromPosition(byte position){
  
//   Drink drink = Drink();
//      EEPROM.begin(memorySize);
//      uint8_t value = 0;
//      Serial.print("\n");
//      Serial.print("Position"); Serial.print(" - ");
//      int address =  dataMemoryBegin
//      for(int address = dataMemoryBegin; address <= dataMemoryEnd; address++){
//        value = EEPROM.read(address);
//        if(value<100){Serial.print(" ");} if(value<10){Serial.print(" ");}
//        Serial.print(value, DEC);      
//        if((address+1)%25 == 0){
//          Serial.print("-(address=");if(address<100){Serial.print(" ");} if(address<10){Serial.print(" ");}Serial.print(address);Serial.print(")");
//          Serial.println("");
//            if(address != dataMemoryEnd){Serial.print("(address=");if((address+1)<100){Serial.print(" ");} if((address+1)<10){Serial.print(" ");}Serial.print(address+1);Serial.print(")-");}
//        delay(1);
//        }else{
//        Serial.print("-");
//        }
//      }
//      EEPROM.end();
   
}

void Memory::getDrinkFromPosition(byte position){
  EEPROM.begin(memorySize);
  int address =  dataMemoryBegin + _drinkSize*position;
  _drink->setDia((byte)EEPROM.read(address));
  address += sizeof(byte);
  _drink->setMes((byte)EEPROM.read(address));
  address += sizeof(byte);
  int ano = ((int)(EEPROM.read(address))) << 8;
  address += sizeof(byte);
  ano += ((int)(EEPROM.read(address)));
  _drink->setAno(ano);
  address += sizeof(byte);
  _drink->setHora((byte)EEPROM.read(address));
  address += sizeof(byte);
  _drink->setMinuto((byte)EEPROM.read(address));
  address += sizeof(byte);
  _drink->setSegundo((byte)EEPROM.read(address));
  address += sizeof(byte);
  int volumeMl = ((int)(EEPROM.read(address))) << 8;
  address += sizeof(byte);
  volumeMl += ((int)(EEPROM.read(address)));
  _drink->setVolumeMl(volumeMl);
  address += sizeof(byte);
  Serial.print("TipoSinal: "); Serial.println((char)EEPROM.read(address));
  _drink->setTipoSinal((char)EEPROM.read(address));
  Serial.print("TipoSinalJust: "); Serial.println(_drink->getTipoSinal());
  address += sizeof(byte);
  int sinal = ((int)(EEPROM.read(address))) << 8;
  address += sizeof(byte);
  sinal += ((int)(EEPROM.read(address)));
  _drink->setSinal(sinal);
  EEPROM.end();
}

void Memory::setDrinkAtPosition(byte position){
  EEPROM.begin(memorySize);
  int address =  dataMemoryBegin + _drinkSize*position;
  EEPROM.write(address,_drink->getDia());
  address += sizeof(byte);
  EEPROM.write(address,_drink->getMes());
//  address += sizeof(byte);
//  EEPROM.write(address,_drink->getMes());
  address += sizeof(byte);
//  Serial.print("Ano: "); Serial.println(_drink->getAno());
//  Serial.print("(byte)Ano: "); Serial.println((byte)(_drink->getAno()));
//  Serial.print("(byte)(Ano>>8): "); Serial.println((byte)((_drink->getAno())>>8));  
  EEPROM.write(address,(byte)((_drink->getAno())>>8)); 
  address += sizeof(byte);
  EEPROM.write(address,(byte)(_drink->getAno()));
//  int ano = ((int)(EEPROM.read(address))) << 8;
//  address += sizeof(byte);
//  ano += ((int)(EEPROM.read(address)));
//  _drink->setAno(ano);
  address += sizeof(byte);
  EEPROM.write(address,_drink->getHora());
//  _drink->setHora((byte)EEPROM.read(address));
  address += sizeof(byte);
  EEPROM.write(address,_drink->getMinuto());
//  address += sizeof(byte);
//  _drink->setMinuto((byte)EEPROM.read(address));
  address += sizeof(byte);
  EEPROM.write(address,_drink->getSegundo());
//  address += sizeof(byte);
//  _drink->setSegundo((byte)EEPROM.read(address));
  address += sizeof(byte);
//  Serial.print("Ano: "); Serial.println(_drink->getAno());
//  Serial.print("(byte)Ano: "); Serial.println((byte)(_drink->getAno()));
//  Serial.print("(byte)(Ano>>8): "); Serial.println((byte)((_drink->getAno())>>8));  
  EEPROM.write(address,(byte)((_drink->getVolumeMl())>>8)); 
  address += sizeof(byte);
  EEPROM.write(address,(byte)(_drink->getVolumeMl()));
  address += sizeof(byte);
//  address += sizeof(byte);
//  int volumeMl = ((int)(EEPROM.read(address))) << 8;
//  address += sizeof(byte);
//  volumeMl += ((int)(EEPROM.read(address)));
//  _drink->setVolumeMl(volumeMl);
  //address += sizeof(byte);
  Serial.print("TipoSinalAfter: "); Serial.println((_drink->getTipoSinal()));
  EEPROM.write(address,(_drink->getTipoSinal()));
  Serial.print("TipoSinalAfterAfter: "); Serial.println((char)EEPROM.read(address));
//  _drink->setTipoSinal((char)EEPROM.read(address));
  address += sizeof(byte);
  EEPROM.write(address,(byte)((_drink->getSinal())>>8)); 
  address += sizeof(byte);
  EEPROM.write(address,(byte)(_drink->getSinal()));
//  int sinal = ((int)(EEPROM.read(address))) << 8;
//  address += sizeof(byte);
//  sinal += ((int)(EEPROM.read(address)));
//  _drink->setSinal(sinal);
  EEPROM.end();
}

void Memory::saveAtMemory(Drink &drink){
  
}

bool Memory::isDrinkToSend(){
  
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
  EEPROM.begin(memorySize);
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
  EEPROM.begin(memorySize);
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
  EEPROM.end();
}




void Memory::teste(){
  _drink->print();
  int ano = _drink->getAno();
  Serial.print("Ano:"); Serial.println(ano);
}





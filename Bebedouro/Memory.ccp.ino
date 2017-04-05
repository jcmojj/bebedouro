#include "Memory.h"
#include "Drink.h"

//Memory::Memory(int size, Drink &drink, byte drinkSize) {
////  Serial.begin(9600);
//  _drink = &drink;
//  _size = size;
//  _drinkSize = drinkSize;
//}
Memory::Memory(Drink &drink, byte drinkSize){
  Serial.begin(115200);
  _drink = &drink;
  _drinkSize = drinkSize;
}


//Memory::Memory(Drink &drink, byte drinkSize, JsonObject& jsonDrink){
////  Serial.begin(9600);
//  _drink = &drink;
//  _drinkSize = drinkSize;
//  _jsonDrink = jsonDrink;
//}

void Memory::saveDrinkAtMemory(){
  byte nextPositionToSave = getNextPositionToWriteDrink();
  byte nextPositionToDelete = getNextPositionToCleanDrink();
  if( (nextPositionToSave == nextPositionToDelete-1) || ((nextPositionToSave == 255) && (nextPositionToDelete == 1)) ){
    clearDrinkMemoryAtPosition(nextPositionToDelete);
  } 
  setDrinkAtPosition(nextPositionToSave);
}
void Memory::lastDrinkWasSentToServerWithSucess(){
  byte nextPositionToCleanDrink = getNextPositionToCleanDrink();
  Serial.print("- nextPositionToCleanDrink: "); Serial.println(nextPositionToCleanDrink);
  clearDrinkMemoryAtPosition(nextPositionToCleanDrink); 
}
byte Memory::getNextDrinkToSendToServer(){
  byte positionToSendToServer = getNextPositionToReadDrink();
  getDrinkFromPosition(positionToSendToServer);
  _drink->setPositionToSendToServer(positionToSendToServer);
  return positionToSendToServer;
}

void Memory::printDrinkFromPosition(byte position) {
  EEPROM.begin(memorySize);
  getDrinkFromPosition(position);
  _drink->print();
  EEPROM.end();
}

void Memory::getDrinkFromPosition(byte position) {
  yield();
  EEPROM.begin(memorySize);
  int address =  dataMemoryBegin + _drinkSize * (position - 1);
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
  _drink->setTipoSinal((char)EEPROM.read(address));
  address += sizeof(byte);
  int sinal = ((int)(EEPROM.read(address))) << 8;
  address += sizeof(byte);
  sinal += ((int)(EEPROM.read(address)));
  _drink->setSinal(sinal);
  yield();
  EEPROM.end();
}

void Memory::setDrinkAtPosition(byte position) {
  yield();
  EEPROM.begin(memorySize);
  int address =  dataMemoryBegin + _drinkSize * (position - 1);
  if(EEPROM.read(address) != _drink->getDia()){EEPROM.write(address, _drink->getDia());}
  address += sizeof(byte);
  if(EEPROM.read(address) != _drink->getMes()){EEPROM.write(address, _drink->getMes());}
  address += sizeof(byte);
  if(EEPROM.read(address) != (byte)((_drink->getAno()) >> 8)){EEPROM.write(address, (byte)((_drink->getAno()) >> 8));}
  address += sizeof(byte);
  if(EEPROM.read(address) != (byte)(_drink->getAno())){EEPROM.write(address, (byte)(_drink->getAno()));}
  address += sizeof(byte);
  if(EEPROM.read(address) != _drink->getHora()){EEPROM.write(address, _drink->getHora());}
  address += sizeof(byte);
  if(EEPROM.read(address) != _drink->getMinuto()){EEPROM.write(address, _drink->getMinuto());}
  address += sizeof(byte);
  if(EEPROM.read(address) != _drink->getSegundo()){EEPROM.write(address, _drink->getSegundo());}
  address += sizeof(byte);
  if(EEPROM.read(address) != (byte)((_drink->getVolumeMl()) >> 8)){EEPROM.write(address, (byte)((_drink->getVolumeMl()) >> 8));}
  address += sizeof(byte);
  if(EEPROM.read(address) != (byte)(_drink->getVolumeMl())){EEPROM.write(address, (byte)(_drink->getVolumeMl()));}
  address += sizeof(byte);
  if(EEPROM.read(address) != (_drink->getTipoSinal())){EEPROM.write(address, (_drink->getTipoSinal()));}
  address += sizeof(byte);
  if(EEPROM.read(address) != (byte)((_drink->getSinal()) >> 8)){EEPROM.write(address, (byte)((_drink->getSinal()) >> 8));}
  address += sizeof(byte);
  if(EEPROM.read(address) != (byte)(_drink->getSinal())){EEPROM.write(address, (byte)(_drink->getSinal()));}
  yield();
  EEPROM.end();
}

//correto
byte Memory::getLastUsedPositionFromBeginScan(){
  yield();
  EEPROM.begin(memorySize);
  byte readByteAnterior = 0;
  byte readByteAtual = 128;
  if( (EEPROM.read(dataMemoryBegin+2) > 127) && EEPROM.read(dataMemoryEnd+1-_drinkSize+2) < 128 ){
      //Serial.print("Last Used Position From Begin Scan Address: ");
      //Serial.println(255);
      return 255; 
  }
  for (int address = dataMemoryBegin ; address <= dataMemoryEnd; address += _drinkSize) {
    yield();
    readByteAnterior = readByteAtual;
    readByteAtual = EEPROM.read(address+2);
    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
    if( (readByteAtual > 127) && (readByteAnterior < 128) ){
      //Serial.print("Last Used Position From Begin Scan Address: ");
      //Serial.println((address - dataMemoryBegin) / 12);
      return (address - dataMemoryBegin) / 12;
    }
    yield();
  }  
  EEPROM.end();
}
byte Memory::getLastUsedPositionFromEndScan(){
  yield();
  EEPROM.begin(memorySize);
  byte readByteAnterior = 0;
  byte readByteAtual = 128;
  if( (EEPROM.read(dataMemoryBegin+2) < 128) && EEPROM.read(dataMemoryEnd+1-_drinkSize+2) > 127 ){
      //Serial.print("Last Used Position From End Scan Address: ");
      //Serial.println(1);
      return 1; 
  }

  for (int address = 1 + dataMemoryEnd - _drinkSize; address >= dataMemoryBegin; address = address - _drinkSize) {
    yield();
    readByteAnterior = readByteAtual;
    readByteAtual = EEPROM.read(address+2);
    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
    if( (readByteAtual > 127) && (readByteAnterior < 128) ){
      //Serial.print("Last Used Position From End Scan Address: ");
      //Serial.println(2+((address - dataMemoryBegin) / 12));
      return 2+((address - dataMemoryBegin) / 12);
    }
    yield();
  }  
  EEPROM.end();  
}
//// fim dos novos


byte Memory::getNextPositionToWriteDrink(){
  if(getLastUsedPositionFromBeginScan() == 255){
    return 1;
  } else{
    return getLastUsedPositionFromBeginScan()+1;
  }
}
byte Memory::getNextPositionToCleanDrink(){
  if(getLastUsedPositionFromBeginScan() == getLastUsedPositionFromEndScan()){
    return 0; // sem posicao para limpar
  }else{
    return getLastUsedPositionFromEndScan();
  }
}
byte Memory::getNextPositionToReadDrink(){
  if(getLastUsedPositionFromBeginScan() == getLastUsedPositionFromEndScan()){
    return 0; // sem posicao para limpar
  } else if(getLastUsedPositionFromEndScan() == 255){
    return 1;
  }else{
    return getLastUsedPositionFromEndScan()+1;
  }  
}

void Memory::print() {
  Serial.println("\nMemory\n");
  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());
  Serial.print("Memory Total Size (EEPROM):"); Serial.println(memorySize);
  yield();
  Serial.print("\nSerial Number Memory"); Serial.print(" from " );  Serial.print(serialNumberBegin);  Serial.print(" to "); Serial.println(serialNumberEnd);
  Serial.print("SSID Name Memory");       Serial.print(" from " );  Serial.print(ssidNameBegin);      Serial.print(" to "); Serial.println(ssidNameEnd);
  Serial.print("SSID Password Memory");   Serial.print(" from " );  Serial.print(ssidPasswordBegin);  Serial.print(" to "); Serial.println(ssidPasswordEnd);
  Serial.print("Email Memory");           Serial.print(" from " );  Serial.print(userEmailBegin);     Serial.print(" to "); Serial.println(userEmailEnd);
  Serial.print("Data Memory");            Serial.print(" from " );  Serial.print(dataMemoryBegin);        Serial.print(" to "); Serial.println(dataMemoryEnd);

  Serial.print("Water Memory Size ");     Serial.println(_drinkSize);

  yield();
  EEPROM.begin(memorySize);
  uint8_t value = 0;

  Serial.print("\n");
  Serial.println("Serial Number Memory");
  Serial.print("(address="); if (serialNumberBegin < 100) {
    Serial.print(" ");
  } if (serialNumberBegin < 10) {
    Serial.print(" ");
  } Serial.print(serialNumberBegin); Serial.print(")-");
  for (byte address = serialNumberBegin; address <= serialNumberEnd; address++) {
    yield();
    value = EEPROM.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 25 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != serialNumberEnd) {
        Serial.print("(address=");
        if ((address + 1) < 100) {
          Serial.print(" ");
        } if ((address + 1) < 10) {
          Serial.print(" ");
        } Serial.print(address + 1);
        Serial.print(")-");
      }
      yield();
    } else {
      Serial.print("-");
    }
  }


  Serial.print("\n");
  Serial.println("SSID Name Memory");
  Serial.print("(address="); if (ssidNameBegin < 100) {
    Serial.print(" ");
  } if (ssidNameBegin < 10) {
    Serial.print(" ");
  } Serial.print(ssidNameBegin); Serial.print(")-");
  for (byte address = ssidNameBegin; address <= ssidNameEnd; address++) {
    yield();
    value = EEPROM.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 25 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != ssidNameEnd) {
        Serial.print("(address=");
        if ((address + 1) < 100) {
          Serial.print(" ");
        } if ((address + 1) < 10) {
          Serial.print(" ");
        } Serial.print(address + 1);
        Serial.print(")-");
      }
      yield();
    } else {
      Serial.print("-");
    }
  }

  Serial.print("\n");
  Serial.println("SSID Password Memory");
  Serial.print("(address="); if (ssidPasswordBegin < 100) {
    Serial.print(" ");
  } if (ssidPasswordBegin < 10) {
    Serial.print(" ");
  } Serial.print(ssidPasswordBegin); Serial.print(")-");
  for (byte address = ssidPasswordBegin; address <= ssidPasswordEnd; address++) {
    yield();
    value = EEPROM.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 25 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != ssidPasswordEnd) {
        Serial.print("(address=");
        if ((address + 1) < 100) {
          Serial.print(" ");
        } if ((address + 1) < 10) {
          Serial.print(" ");
        } Serial.print(address + 1);
        Serial.print(")-");
      }
      yield();
    } else {
      Serial.print("-");
    }
  }

  Serial.print("\n");
  Serial.println("Email Memory");
  Serial.print("(address="); if (userEmailBegin < 100) {
    Serial.print(" ");
  } if (userEmailBegin < 10) {
    Serial.print(" ");
  } Serial.print(userEmailBegin); Serial.print(")-");
  for (byte address = userEmailBegin; address <= userEmailEnd; address++) {
    yield();
    value = EEPROM.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 25 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != userEmailEnd) {
        Serial.print("(address=");
        if ((address + 1) < 100) {
          Serial.print(" ");
        } if ((address + 1) < 10) {
          Serial.print(" ");
        } Serial.print(address + 1);
        Serial.print(")-");
      }
      yield();
    } else {
      Serial.print("-");
    }
  }
  EEPROM.end();
}

void Memory::printData() {
  yield();
  EEPROM.begin(memorySize);
  uint8_t value = 0;
  Serial.print("\n");
  Serial.println("Data Memory");
  Serial.print("(address= "); if (dataMemoryBegin < 100) {
    Serial.print(" ");
  } if (dataMemoryBegin < 10) {
    Serial.print(" ");
  } Serial.print(dataMemoryBegin); Serial.print(")");
  Serial.print("(Position=  1)");
  for (int address = dataMemoryBegin; address <= dataMemoryEnd; address++) {
    yield();
    value = EEPROM.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);

    if ((address + 1 - dataMemoryBegin) % _drinkSize == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != dataMemoryEnd) {
        Serial.print("(address="); if (address < 1000) {
          Serial.print(" ");
        } if (address < 100) {
          Serial.print(" ");
        } if (address < 10) {
          Serial.print(" ");
        } Serial.print(address + 1); Serial.print(")");
        Serial.print("(Position="); if ((2 + (address - dataMemoryBegin) / _drinkSize) < 100) {
          Serial.print(" ");
        } if ((2 + (address - dataMemoryBegin) / _drinkSize) < 10) {
          Serial.print(" ");
        } Serial.print(2 + (address - dataMemoryBegin) / _drinkSize); Serial.print(")");
      }
      yield();
    } else {
      Serial.print("-");
    }

  }
  EEPROM.end();
}

void Memory::clearMemory() {
  yield();
  EEPROM.begin(memorySize);
  Serial.print("Clean Memory");
  for (int address = serialNumberBegin; address <= dataMemoryEnd; address++) {
    yield();
    if (EEPROM.read(address) != 255) {
      EEPROM.write(address, 255);
    }
  }
  EEPROM.end();
}

void Memory::clearDataMemory() {
  yield();
  EEPROM.begin(memorySize);
  Serial.println("Clean Data Memory");
  for (int address = dataMemoryBegin; address <= dataMemoryEnd; address++) {
    yield();
    if (EEPROM.read(address) != 255) {
      EEPROM.write(address, 255); 
    }
  }
  byte firstByte = 0;
  EEPROM.write(dataMemoryBegin+2, firstByte);
  EEPROM.end();
}

void Memory::clearDrinkMemoryAtPosition(byte position) {
  yield();
  EEPROM.begin(memorySize);
  if(position >0 && position < 256){
//    for (int address = dataMemoryBegin + (position - 1) * _drinkSize ; address < dataMemoryBegin + (position) * _drinkSize ; address++) {
//      EEPROM.write(address, 128);
//    }    
    EEPROM.write(dataMemoryBegin + (position - 1) * _drinkSize + 2, 128);
  }
  EEPROM.end();
}

//// nao preciso me preocupar com isso
//void Memory::getSsidName(char* name){
//  yield();
//  EEPROM.begin(memorySize);
//  for(byte i = 0; i<=ssidName;i++){
//    yield();
//     name[i] = EEPROM.read(ssidNameBegin+i);
//  }
//  EEPROM.end();
//}
//void Memory::setSsidName(char* name){
//  EEPROM.begin(memorySize);
//  for(byte i = 0; i<=ssidName;i++){
//     EEPROM.write(ssidNameBegin+i,name[i]);
//  }
//  EEPROM.end();  
//}
//
//void Memory::getSsidPassword(char* password){
//  EEPROM.begin(memorySize);
//  for(byte i = 0; i<=ssidPassword;i++){
//     password[i] = EEPROM.read(ssidPasswordBegin+i);
//  }
//  EEPROM.end();
//}
//void Memory::setSsidPassword(char* password){
//  EEPROM.begin(memorySize);
//  for(byte i = 0; i<=ssidPassword;i++){
//    EEPROM.write(ssidPasswordBegin+i,password[i]);
//  }
//  EEPROM.end();
//}

void Memory::getUserEmail(char email[]){
  yield();
  EEPROM.begin(memorySize);
  int i = 0;
  do{
    yield();
     email[i] = (char)EEPROM.read(userEmailBegin+i);
     i++;
  }while((char)EEPROM.read(userEmailBegin+i) != '\0');
     email[i] = (char)EEPROM.read(userEmailBegin+i);
  EEPROM.end();  
}

byte Memory::getUserEmailSize(){
  yield();
   EEPROM.begin(memorySize);
  int size = 0;
  while((char)EEPROM.read(userEmailBegin+size) != '\0'){ 
    yield();
    size++;
  }
  return size+1;
  EEPROM.end(); 
}

void Memory::setUserEmail(const char email[]){
  yield();
  EEPROM.begin(memorySize);
//  Serial.print("Dentro setter: "); Serial.println(email);
  int i = 0;
  do{
    yield();
    EEPROM.write(userEmailBegin+i,(byte)email[i]);
    i++;
  }while(email[i] != '\0');
  EEPROM.write(userEmailBegin+i,(byte)email[i]);
  EEPROM.end();  
}





byte Memory::getDrinkAlarmPositionQuantity(){
  EEPROM.begin(memorySize);
  byte quantidade = 0;
  while(EEPROM.read(userEmailBegin+(quantidade)*2) != 255){
    quantidade++;
  }
  return quantidade;
  yield(); 
  EEPROM.end();
}
byte Memory::findDrinkAlarmPositionFrom(byte hour, byte minute){
  EEPROM.begin(memorySize);
  if(getDrinkAlarmPositionQuantity() == 0){
    return 0;
  }
  byte position = 1;
  while(( EEPROM.read(drinkAlarmPositionsBegin+(position-1)*2) != hour )&&( EEPROM.read(drinkAlarmPositionsBegin+1+(position-1)*2) != minute )){
    position++;
    yield();
    if( position == drinkAlarmPositions + 1){
      position = 0;
      break;
    }
  }
  return position;
  EEPROM.end(); 
}
bool Memory::addDrinkAlarm(byte hour, byte minute){
  EEPROM.begin(memorySize);
  if( getDrinkAlarmPositionQuantity() == 0 ){
    EEPROM.write(drinkAlarmPositionsBegin, hour);
    EEPROM.write(drinkAlarmPositionsBegin + 1, minute);
  }
   byte Posicao = getDrinkAlarmNextAlarmPosition(hour, minute) - 1;
   for(byte address = drinkAlarmPositionsBegin + getDrinkAlarmPositionQuantity()*2 ; 
            address < (drinkAlarmPositionsBegin + (Posicao-1)*2) ;
            address = address -2){
                  EEPROM.write(address, hour);
                  EEPROM.write(address + 1, minute);
                  yield();
            }
  EEPROM.write(drinkAlarmPositionsBegin+(getDrinkAlarmNextAlarmPosition(hour, minute) - 1)*2, hour);
  EEPROM.write(drinkAlarmPositionsBegin+1+(getDrinkAlarmNextAlarmPosition(hour, minute) - 1)*2, minute);  
  EEPROM.end();
}
bool Memory::clearDrinkAlam(byte hour, byte minute){
  EEPROM.begin(memorySize);
  if(findDrinkAlarmPositionFrom(hour, minute) != 0){
    EEPROM.write(drinkAlarmPositionsBegin+findDrinkAlarmPositionFrom(hour, minute)*2, 255);
    EEPROM.write(drinkAlarmPositionsBegin+1+findDrinkAlarmPositionFrom(hour, minute)*2, 255); 
  }
  return 0;
  EEPROM.end();
}
byte Memory::getDrinkAlarmHourFromPosition(byte position){
  EEPROM.begin(memorySize);
  if(getDrinkAlarmPositionQuantity() == 0){
    return 255;
  }
  yield();
  return (byte)EEPROM.read(drinkAlarmPositionsBegin+(position-1)*2);
  EEPROM.end();
}
byte Memory::getDrinkAlarmMinuteFromPosition(byte position){
  EEPROM.begin(memorySize);
  if(getDrinkAlarmPositionQuantity() == 0){
    return 255;
  }
  yield();
  return (byte)EEPROM.read(drinkAlarmPositionsBegin+1+(position-1)*2);
  EEPROM.end();
}
byte Memory::getDrinkAlarmNextAlarmPosition(byte hour, byte minute){
  EEPROM.begin(memorySize);
  if(getDrinkAlarmPositionQuantity() == 0){
    return 0;
  }
  byte posicao = 1;
  if(hour == 0 && minute == 0){
    return posicao;
  }
  float horaProcurada = hour + ((float)minute)/60;
  float horaEeprom = EEPROM.read(drinkAlarmPositionsBegin) + ((float)((byte)EEPROM.read(drinkAlarmPositionsBegin+1)))/60;
  while((posicao != getDrinkAlarmPositionQuantity())||(horaProcurada > horaEeprom)){
    horaEeprom = EEPROM.read(drinkAlarmPositionsBegin+(posicao-1)*2) + ((float)((byte)EEPROM.read(1+drinkAlarmPositionsBegin+(posicao-1)*2)))/60;
    posicao++;
    yield();
  }
  return posicao;
  EEPROM.end();
}
void Memory::clearDrinkAlarmAllPosition(){
  EEPROM.begin(memorySize);
  for(int address = drinkAlarmPositionsBegin; address< (drinkAlarmPositionsEnd + 1); address++){
    EEPROM.write(address, 255);
  }
  yield();
  EEPROM.end();  
}


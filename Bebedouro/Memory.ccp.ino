#include "Memory.h"
#include "Drink.h"

Memory::Memory(int size, Drink &drink, byte drinkSize) {
//  Serial.begin(9600);
  _drink = &drink;
  _size = size;
  _drinkSize = drinkSize;
}

void Memory::printDrinkFromPosition(byte position) {
  EEPROM.begin(memorySize);
  getDrinkFromPosition(position);
  _drink->print();
  EEPROM.end();
}

void Memory::getDrinkFromPosition(byte position) {
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
  delay(1);
  EEPROM.end();
}

void Memory::setDrinkAtPosition(byte position) {
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
  delay(1);
  EEPROM.end();
}

//correto
byte Memory::getLastUsedPositionFromBeginScan(){
  EEPROM.begin(memorySize);
  byte readByteAnterior = 0;
  byte readByteAtual = 128;
  if( (EEPROM.read(dataMemoryBegin+2) > 127) && EEPROM.read(dataMemoryEnd+1-_drinkSize+2) < 128 ){
      Serial.print("Last Used Position From Begin Scan Address: ");
      Serial.println(255);
      return 255; 
  }
  for (int address = dataMemoryBegin ; address <= dataMemoryEnd; address += _drinkSize) {
    readByteAnterior = readByteAtual;
    readByteAtual = EEPROM.read(address+2);
    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
    if( (readByteAtual > 127) && (readByteAnterior < 128) ){
      Serial.print("Last Used Position From Begin Scan Address: ");
      Serial.println((address - dataMemoryBegin) / 12);
      return (address - dataMemoryBegin) / 12;
    }
    delay(1);
  }  
  EEPROM.end();
}
byte Memory::getLastUsedPositionFromEndScan(){
  EEPROM.begin(memorySize);
  byte readByteAnterior = 0;
  byte readByteAtual = 128;
  if( (EEPROM.read(dataMemoryBegin+2) < 128) && EEPROM.read(dataMemoryEnd+1-_drinkSize+2) > 127 ){
      Serial.print("Last Used Position From End Scan Address: ");
      Serial.println(1);
      return 1; 
  }

  for (int address = 1 + dataMemoryEnd - _drinkSize; address >= dataMemoryBegin; address = address - _drinkSize) {
    readByteAnterior = readByteAtual;
    readByteAtual = EEPROM.read(address+2);
    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
    if( (readByteAtual > 127) && (readByteAnterior < 128) ){
      Serial.print("Last Used Position From End Scan Address: ");
      Serial.println(2+((address - dataMemoryBegin) / 12));
      return 2+((address - dataMemoryBegin) / 12);
    }
    delay(1);
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

  Serial.print("\nSerial Number Memory"); Serial.print(" from " );  Serial.print(serialNumberBegin);  Serial.print(" to "); Serial.println(serialNumberEnd);
  Serial.print("SSID Name Memory");       Serial.print(" from " );  Serial.print(ssidNameBegin);      Serial.print(" to "); Serial.println(ssidNameEnd);
  Serial.print("SSID Password Memory");   Serial.print(" from " );  Serial.print(ssidPasswordBegin);  Serial.print(" to "); Serial.println(ssidPasswordEnd);
  Serial.print("Email Memory");           Serial.print(" from " );  Serial.print(userEmailBegin);     Serial.print(" to "); Serial.println(userEmailEnd);
  Serial.print("Data Memory");            Serial.print(" from " );  Serial.print(dataMemoryBegin);        Serial.print(" to "); Serial.println(dataMemoryEnd);

  Serial.print("Water Memory Size ");     Serial.println(_drinkSize);

  delay(1);
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
      delay(1);
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
      delay(1);
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
      delay(1);
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
      delay(1);
    } else {
      Serial.print("-");
    }
  }
  EEPROM.end();
}

void Memory::printData() {
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
      delay(1);
    } else {
      Serial.print("-");
    }

  }
  EEPROM.end();
}

void Memory::clearMemory() {
  EEPROM.begin(memorySize);
  Serial.print("Clean Memory");
  for (int address = serialNumberBegin; address <= dataMemoryEnd; address++) {
    if (EEPROM.read(address) != 255) {
      EEPROM.write(address, 255); delay(1);
    }
  }
  EEPROM.end();
}

void Memory::clearDataMemory() {
  EEPROM.begin(memorySize);
  Serial.println("Clean Data Memory");
  for (int address = dataMemoryBegin; address <= dataMemoryEnd; address++) {
    if (EEPROM.read(address) != 255) {
      EEPROM.write(address, 255); delay(1);
    }
  }
//  byte firstByte = 0;
//  EEPROM.write(dataMemoryBegin, firstByte);
  EEPROM.end();
}

void Memory::clearDrinkMemoryAtPosition(byte position) {
  EEPROM.begin(memorySize);
  if(position >0 && position < 256){
//    for (int address = dataMemoryBegin + (position - 1) * _drinkSize ; address < dataMemoryBegin + (position) * _drinkSize ; address++) {
//      EEPROM.write(address, 128);
//    }    
    EEPROM.write(dataMemoryBegin + (position - 1) * _drinkSize + 2, 128);
  }
  EEPROM.end();
}


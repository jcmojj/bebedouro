#include "Memory.h"


Memory::Memory(Drink &drink, byte drinkSize, RtcDS3231<TwoWire> &rtc) {
//  Wire.begin(AT24C32_ADDRESS);
//  Serial.begin(115200);
//  delay(3000);
  _drink = &drink;
  _drinkSize = drinkSize;
  _rtc = &rtc;
  if (dataMemoryEnd > 4095) {
    Serial.println("ESTOUROU MEMORIA");
  }
}

void Memory::memoryTest() {
  Serial.println("GRAVANDO");
  byte valor = 0;
  for (int address = 0; address < 4096; address++) {
    Serial.print("Address: "); Serial.print(address);
    Serial.print(" - Valor Salvo: "); Serial.print(valor);
    eeprom_write_char(address, valor);
    Serial.print(" - Valor Recuperado: "); Serial.println((byte)eeprom_read_char(address));
    valor++;
  }
    Serial.println("RECUPERANDO");
    for (int address = 0; address < 4096; address++) {
      Serial.print("Address: "); Serial.print(address);
      Serial.print(" - Valor Salvo: "); Serial.print(valor);
      Serial.print(" - Valor Recuperado: "); Serial.println((byte)eeprom_read_char(address));
      valor++;
    }
      memory.printData();
      memory.clearDataMemory();
      memory.printData();
      memory.print();
      memory.clearMemory();
      memory.print();
}
byte Memory::eeprom_read_byte(const unsigned int address) {
  byte rdata = 0;
  uint8_t  highAddressByte  = (uint8_t) (address >> 8);
  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8));
  Wire.beginTransmission(AT24C32_ADDRESS);
  Wire.write(highAddressByte);
  Wire.write(lowAddressByte);
  Wire.endTransmission(false);
  Wire.requestFrom(AT24C32_ADDRESS, (uint8_t)1);
  delay(30);
  if (Wire.available()) {
    rdata = (byte)Wire.read();
  }
  delay(30);
  return rdata;
}

char Memory::eeprom_read_char(const unsigned int address) {
  char rdata = 0xFF;//'\0';
  uint8_t  highAddressByte  = (uint8_t) (address >> 8);
  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8));
  Wire.beginTransmission(AT24C32_ADDRESS);
  Wire.write(highAddressByte);
  Wire.write(lowAddressByte);
  Wire.endTransmission(false);
  Wire.requestFrom(AT24C32_ADDRESS, (uint8_t)1);
  delay(3);
  if (Wire.available()) {
    delay(3);
    rdata = (char)Wire.read();
  }
  delay(3);
  return rdata;
}

void Memory::eeprom_write_byte(const unsigned int address, const byte data) {
  uint8_t  highAddressByte  = (uint8_t) (address >> 8);
  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8));
  Wire.beginTransmission(AT24C32_ADDRESS);
  Wire.write(highAddressByte);
  Wire.write(lowAddressByte);
  Wire.write(data);
  delay(3);
  Wire.endTransmission();
  delay(3);
}

void Memory::eeprom_write_char(const unsigned int address, const char data) {
  uint8_t  highAddressByte  = (uint8_t) (address >> 8);
  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8));
  Wire.beginTransmission(AT24C32_ADDRESS);
  Wire.write(highAddressByte);
  Wire.write(lowAddressByte);
  Wire.write(data);
  delay(30);
  Wire.endTransmission();
  delay(30);
}
///-------------------
char* Memory::readBytes(unsigned int end, char * dest, int limit) { //size -> se nao sabe colocar limit
  //
  //  uint8_t filledBytes = 0;
  //  while( (dest[filledBytes] != '\0')&&(filledBytes<limit)&&(filledBytes<size) ){
  //    Serial.print(filledBytes);Serial.print("-");
  //    filledBytes++;
  //  }
  int address = end;
  int i = 0;
  uint8_t  highAddressByte;
  uint8_t  lowAddressByte;
  int interation = 0;
  //  char var;

  highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
  Wire.beginTransmission(AT24C32_ADDRESS);
  Wire.write(highAddressByte);
  Wire.write(lowAddressByte);
  Wire.endTransmission(false);
  Wire.requestFrom(AT24C32_ADDRESS, (uint8_t)32);

  while (i < limit) {


    Serial.print("i:"); Serial.print(i);
    Serial.print(" limit:"); Serial.print(limit);
    Serial.print(" address: "); Serial.print(address);
    delay(3);
    if ( Wire.available() ) {
//      delay(50);
      //      byte zoado = (byte)Wire.read();
      //      Serial.print("byte:(");Serial.print(zoado);Serial.print(")");
      //      dest[i] = (char)zoado;
      dest[i] = (char)Wire.read();
      dest[i + 1] = '\0';
      Serial.print(" value:("); Serial.print(dest[i]); Serial.print(") ");
      delay(3);
    } else {
      Serial.print("MERDA!");
    }
    if ((i + 1) % 32 == 0) {
      //finish
      delay(5);
      Wire.endTransmission();
      delay(5);
      printEmail();
      interation++;
      address = address + 32;
      //start
      highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
      lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
      Wire.beginTransmission(AT24C32_ADDRESS);
      Wire.write(highAddressByte);
      Wire.write(lowAddressByte);
      Wire.endTransmission(false);
      Wire.requestFrom(AT24C32_ADDRESS, (uint8_t)32);
      delay(5);
    }

    i++;
    Serial.println("");
  }

  delay(50);
  //  Wire.endTransmission();
  delay(50);
  return dest;
}


//char* Memory::readBytes(const unsigned int address, char * dest,int limit){
//  uint8_t count  = 64;
//  Serial.print("-->BEGIN-READ<--");
//  uint8_t  highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
//  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
//  Wire.beginTransmission(AT24C32_ADDRESS);   // Initialize the Tx buffer
//  Wire.write(highAddressByte); // MSB
//  Wire.write(lowAddressByte); // LSB
//  Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
//  uint8_t i = 0;
//  Wire.requestFrom(AT24C32_ADDRESS, (uint8_t)count);  // Read bytes from slave register address
//
//  Serial.print("\nRead:");
//  while (Wire.available() && i < 32 ) {
//    delay(5);
//    dest[i] = (char)Wire.read();
//    delay(5);
//    dest[i+1] = '\0';
//    Serial.print(dest[i]);
////    Serial.print("i(");Serial.print(i); Serial.print("): "); Serial.print(dest[i]); Serial.print(" - ");
//    i++;
//  }
//
//  Serial.print("\nEND: ");
//  if(count > 32 && count < (limit+1) ){
//   readBytes(address+32, (dest+32),limit);
//  }
//  Serial.print("-->END-READ<--");
//  return dest;
//}
//--------------------------------
//  memory.writeBytes(48, &teste[0],40);
//bool Memory::writeBytes(const unsigned int address, char * dest, byte size, byte limit){
//  Serial.print("\n\n-->BEGIN-WRITE<--\n - Count:");
//  Serial.print("Address:");Serial.print(address); Serial.print(" - limit:");Serial.println(limit);
//  uint8_t count = 0;
//  while( (dest[count] != '\0') && (count<limit) &&(count<size) ){
//     Serial.print(count);Serial.print("-");
//    count++;
//  }
//
//  Serial.println("");
//  uint8_t  highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
//  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
//  Wire.beginTransmission(AT24C32_ADDRESS);   // Initialize the Tx buffer
//  Wire.write(highAddressByte); // MSB
//  Wire.write(lowAddressByte); // LSB
//
//  Serial.print("\nWire.write:    ");
//  for(byte i = 0;((i<count)&&(i<15));i++){
//    Serial.print(dest[i]);
//    Wire.write(dest[i]);
//  }
//  delay(5);
//  Wire.endTransmission();       // Send the Tx buffer, but send a restart to keep connection alive
//  delay(10);
//  char tont[200];
////  Serial.print("ResultadoInt:   ");Serial.print(readBytes(0, 100, &tont[0],limit));
////  Serial.print("\nbytesint: "); Serial.println(readBytes(48,60,&teste[0]));
//  if(count>15 ){
//   writeBytes(address+15, (dest+15),(size-15), (limit-15) );
//  }
//  Serial.print("\n--> END-WRITE<--\n");
//}

bool Memory::writeBytes( unsigned int address, char * dest, int limit) { //size -> se nao sabe colocar limit //// limit = size 64

  uint8_t filledBytes = 0;
  while ( (dest[filledBytes] != '\0') && (filledBytes < limit) ) {
    Serial.print(filledBytes); Serial.print("-");
    filledBytes++;
  }
  Serial.println("");
  
  int i = 0;
  uint8_t  highAddressByte;
  uint8_t  lowAddressByte;
  int interation = 0;

  highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
  Wire.beginTransmission(AT24C32_ADDRESS);
  Wire.write(highAddressByte);
  Wire.write(lowAddressByte);

  while (i < limit) {
    delay(3);
    Serial.print("i: ");Serial.print(i);
    Serial.print(" -address-:");Serial.print(address);
    Serial.print(" -dest[i]:");Serial.print(dest[i]);
    Serial.print(" -filledBytes:");Serial.println(filledBytes);
    
    if (i < filledBytes) {
//      Serial.print("<");
//      Serial.print(dest[i]);
      Wire.write((byte)dest[i]);
    } else {
//      Serial.print(">");
//      Serial.print('0');
      Wire.write('\0');
    }
    if ((i + 1) % 15 == 0) {
      //finish
      delay(5);
      Wire.endTransmission();
      delay(5);
      printEmail();
      interation++;
      address = address + 15;
      //start
      highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
      lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
      Wire.beginTransmission(AT24C32_ADDRESS);
      Wire.write(highAddressByte);
      Wire.write(lowAddressByte);
    }

    i++;
  }
  delay(5);
  Wire.endTransmission();
  delay(5);



  //
  //  Serial.print("\n\n-->BEGIN-WRITE<--\n - Count:");
  //  Serial.print("Address:");Serial.print(address); Serial.print(" - limit:");Serial.println(limit);
  //
  //  uint8_t filledBytes = 0;
  //  while( (dest[filledBytes] != '\0')&&(filledBytes<limit)&&(filledBytes<size) ){
  //     Serial.print(filledBytes);Serial.print("-");
  //    filledBytes++;
  //  }
  //  if(size>j){
  //    filledBytes = size;
  //  }
  //
  //  uint8_t  highAddressByte  = (uint8_t) (address >> 8);  // byte with the four MSBits of the address
  //  uint8_t  lowAddressByte   = (uint8_t) (address - ((uint16_t) highAddressByte << 8)); // byte with the eight LSbits of the address
  //  Wire.beginTransmission(AT24C32_ADDRESS);
  //  Wire.write(highAddressByte);
  //  Wire.write(lowAddressByte);
  //
  //
  //  Serial.print("\nWire.write:    ");
  //  for(byte i = 0;((i<limit)&&(i<15));i++){
  //    if(i<filledBytes{
  //      Serial.print("<");
  //      Serial.print(dest[i]);
  //      Wire.write(dest[i]);
  //    }else{
  //      Serial.print(">");
  //      Serial.print('0');
  //      Wire.write('\0');
  //    }
  //  }
  //  delay(5);
  //  Wire.endTransmission();
  //  delay(10);
  ////  char tont[200];
  ////  Serial.print("ResultadoInt:   ");Serial.print(readBytes(0, 100, &tont[0],limit));
  ////  Serial.print("\nbytesint: "); Serial.println(readBytes(48,60,&teste[0]));
  //
  //  if(count>15 ){
  //   writeBytes((address+15), (dest+15), (size-15), (limit-15) );
  //  }
  //  Serial.print("\n--> END-WRITE<--\n");
}



//
//void Memory::saveDrinkAtMemory() {
//  byte nextPositionToSave = getNextPositionToWriteDrink();
//  byte nextPositionToDelete = getNextPositionToCleanDrink();
//  if ( (nextPositionToSave == nextPositionToDelete - 1) || ((nextPositionToSave == 255) && (nextPositionToDelete == 1)) ) {
//    clearDrinkMemoryAtPosition(nextPositionToDelete);
//  }
//  setDrinkAtPosition(nextPositionToSave);
//}
//void Memory::lastDrinkWasSentToServerWithSucess() {
//  byte nextPositionToCleanDrink = getNextPositionToCleanDrink();
//  Serial.print("- nextPositionToCleanDrink: "); Serial.println(nextPositionToCleanDrink);
//  clearDrinkMemoryAtPosition(nextPositionToCleanDrink);
//}
//byte Memory::getNextDrinkToSendToServer() {
//  byte positionToSendToServer = getNextPositionToReadDrink();
//  getDrinkFromPosition(positionToSendToServer);
//  _drink->setPositionToSendToServer(positionToSendToServer);
//  return positionToSendToServer;
//}
//
//void Memory::printDrinkFromPosition(byte position) {
//  EEPROM.begin(memorySize);
//  getDrinkFromPosition(position);
//  _drink->print();
//  EEPROM.end();
//}
//
//void Memory::getDrinkFromPosition(byte position) {
//  yield();
//  EEPROM.begin(memorySize);
//  int address =  dataMemoryBegin + _drinkSize * (position - 1);
//  _drink->setDia((byte)EEPROM.read(address));
//  address += sizeof(byte);
//  _drink->setMes((byte)EEPROM.read(address));
//  address += sizeof(byte);
//  int ano = ((int)(EEPROM.read(address))) << 8;
//  address += sizeof(byte);
//  ano += ((int)(EEPROM.read(address)));
//  _drink->setAno(ano);
//  address += sizeof(byte);
//  _drink->setHora((byte)EEPROM.read(address));
//  address += sizeof(byte);
//  _drink->setMinuto((byte)EEPROM.read(address));
//  address += sizeof(byte);
//  _drink->setSegundo((byte)EEPROM.read(address));
//  address += sizeof(byte);
//  int volumeMl = ((int)(EEPROM.read(address))) << 8;
//  address += sizeof(byte);
//  volumeMl += ((int)(EEPROM.read(address)));
//  _drink->setVolumeMl(volumeMl);
//  address += sizeof(byte);
//  _drink->setTipoSinal((char)EEPROM.read(address));
//  address += sizeof(byte);
//  int sinal = ((int)(EEPROM.read(address))) << 8;
//  address += sizeof(byte);
//  sinal += ((int)(EEPROM.read(address)));
//  _drink->setSinal(sinal);
//  yield();
//  EEPROM.end();
//}
//
//void Memory::setDrinkAtPosition(byte position) {
//  yield();
//  EEPROM.begin(memorySize);
//  int address =  dataMemoryBegin + _drinkSize * (position - 1);
//  if (EEPROM.read(address) != _drink->getDia()) {
//    EEPROM.write(address, _drink->getDia());
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != _drink->getMes()) {
//    EEPROM.write(address, _drink->getMes());
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (byte)((_drink->getAno()) >> 8)) {
//    EEPROM.write(address, (byte)((_drink->getAno()) >> 8));
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (byte)(_drink->getAno())) {
//    EEPROM.write(address, (byte)(_drink->getAno()));
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != _drink->getHora()) {
//    EEPROM.write(address, _drink->getHora());
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != _drink->getMinuto()) {
//    EEPROM.write(address, _drink->getMinuto());
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != _drink->getSegundo()) {
//    EEPROM.write(address, _drink->getSegundo());
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (byte)((_drink->getVolumeMl()) >> 8)) {
//    EEPROM.write(address, (byte)((_drink->getVolumeMl()) >> 8));
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (byte)(_drink->getVolumeMl())) {
//    EEPROM.write(address, (byte)(_drink->getVolumeMl()));
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (_drink->getTipoSinal())) {
//    EEPROM.write(address, (_drink->getTipoSinal()));
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (byte)((_drink->getSinal()) >> 8)) {
//    EEPROM.write(address, (byte)((_drink->getSinal()) >> 8));
//  }
//  address += sizeof(byte);
//  if (EEPROM.read(address) != (byte)(_drink->getSinal())) {
//    EEPROM.write(address, (byte)(_drink->getSinal()));
//  }
//  yield();
//  EEPROM.end();
//}
//
////correto
//byte Memory::getLastUsedPositionFromBeginScan() {
//  yield();
//  EEPROM.begin(memorySize);
//  byte readByteAnterior = 0;
//  byte readByteAtual = 128;
//  if ( (EEPROM.read(dataMemoryBegin + 2) > 127) && EEPROM.read(dataMemoryEnd + 1 - _drinkSize + 2) < 128 ) {
//    //Serial.print("Last Used Position From Begin Scan Address: ");
//    //Serial.println(255);
//    return 255;
//  }
//  for (int address = dataMemoryBegin ; address <= dataMemoryEnd; address += _drinkSize) {
//    yield();
//    readByteAnterior = readByteAtual;
//    readByteAtual = EEPROM.read(address + 2);
//    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
//    if ( (readByteAtual > 127) && (readByteAnterior < 128) ) {
//      //Serial.print("Last Used Position From Begin Scan Address: ");
//      //Serial.println((address - dataMemoryBegin) / 12);
//      return (address - dataMemoryBegin) / 12;
//    }
//    yield();
//  }
//  EEPROM.end();
//}
//byte Memory::getLastUsedPositionFromEndScan() {
//  yield();
//  EEPROM.begin(memorySize);
//  byte readByteAnterior = 0;
//  byte readByteAtual = 128;
//  if ( (EEPROM.read(dataMemoryBegin + 2) < 128) && EEPROM.read(dataMemoryEnd + 1 - _drinkSize + 2) > 127 ) {
//    //Serial.print("Last Used Position From End Scan Address: ");
//    //Serial.println(1);
//    return 1;
//  }
//
//  for (int address = 1 + dataMemoryEnd - _drinkSize; address >= dataMemoryBegin; address = address - _drinkSize) {
//    yield();
//    readByteAnterior = readByteAtual;
//    readByteAtual = EEPROM.read(address + 2);
//    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
//    if ( (readByteAtual > 127) && (readByteAnterior < 128) ) {
//      //Serial.print("Last Used Position From End Scan Address: ");
//      //Serial.println(2+((address - dataMemoryBegin) / 12));
//      return 2 + ((address - dataMemoryBegin) / 12);
//    }
//    yield();
//  }
//  EEPROM.end();
//}
////// fim dos novos
//
//
//byte Memory::getNextPositionToWriteDrink() {
//  if (getLastUsedPositionFromBeginScan() == 255) {
//    return 1;
//  } else {
//    return getLastUsedPositionFromBeginScan() + 1;
//  }
//}
//byte Memory::getNextPositionToCleanDrink() {
//  if (getLastUsedPositionFromBeginScan() == getLastUsedPositionFromEndScan()) {
//    return 0; // sem posicao para limpar
//  } else {
//    return getLastUsedPositionFromEndScan();
//  }
//}
//byte Memory::getNextPositionToReadDrink() {
//  if (getLastUsedPositionFromBeginScan() == getLastUsedPositionFromEndScan()) {
//    return 0; // sem posicao para limpar
//  } else if (getLastUsedPositionFromEndScan() == 255) {
//    return 1;
//  } else {
//    return getLastUsedPositionFromEndScan() + 1;
//  }
//}
//
//void Memory::preenchendoDrinksParaTeste() {
//  clearDataMemory();
//  for (byte mes = 1; mes < 11 ; mes++) {
//    for (byte dia = 1; dia < 30 ; dia ++) {
//      drink.setValue(dia, mes, 1984, 9, 50, 30, 57, 'c', 111, 0, 0);
//      saveDrinkAtMemory();
//    }
//  }
//  Serial.println("Memoria Limpa");
//}
void Memory::printEmail(){
  yield();
  char value = 0;
  Serial.print("\n");
  Serial.println("Email Memory");
  Serial.print("(address="); if (userEmailBegin < 100) {
    Serial.print(" ");
  } if (userEmailBegin < 10) {
    Serial.print(" ");
  } Serial.print(userEmailBegin); Serial.print(")-");
  for (int address = userEmailBegin; address <= userEmailEnd; address++) {
    yield();
    value = eeprom_read_char(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 32 == 0) {
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
}

void Memory::print() {
  Serial.println("\nMemory\n");
  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());
  Serial.print("Memory Total Size (EEPROM):"); Serial.println(memorySize);
  yield();

  Serial.print("\n");
  Serial.print("Email Memory");       Serial.print(" from " );  Serial.print(userEmailBegin);             Serial.print(" to "); Serial.println(userEmailEnd);
  Serial.print("Serial Number Memory"); Serial.print(" from " );  Serial.print(serialNumberBegin);          Serial.print(" to "); Serial.println(serialNumberEnd);
  Serial.print("Drink Alarm Memory");   Serial.print(" from " );  Serial.print(drinkAlarmPositionsBegin);   Serial.print(" to "); Serial.println(drinkAlarmPositionsEnd);
  Serial.print("Meal Alarm Memory");    Serial.print(" from " );  Serial.print(mealAlarmPositionsBegin);    Serial.print(" to "); Serial.println(mealAlarmPositionsEnd);
  Serial.print("Cleaning Alarm Memory"); Serial.print(" from " );  Serial.print(cleaningAlarmPositionsBegin); Serial.print(" to "); Serial.println(cleaningAlarmPositionsEnd);
  Serial.print("Data Memory");          Serial.print(" from " );  Serial.print(dataMemoryBegin);            Serial.print(" to "); Serial.println(dataMemoryEnd);
  Serial.print("Water Memory Size ");   Serial.println(_drinkSize);
  int memUsada = userEmailSpace + serialNumberSpace + drinkAlarmPositions * drinkAlarmPositionsSize + mealAlarmPositions * mealAlarmPositionsSize + cleaningAlarmPositions * cleaningAlarmPositionsSize + dataMemorySize;
  Serial.print("\nMemoria Total Usada: ");  Serial.print(memUsada); Serial.print(" - "); Serial.print(((double)memUsada) / 4096, 1); Serial.println("%");
  Serial.print("Memoria Total Livre: ");  Serial.print("4096 - memUsada");

  yield();
  char value = 0;


  printEmail();

  Serial.print("\n");
  Serial.println("Serial Number Memory");
  Serial.print("(address="); if (serialNumberBegin < 100) {
    Serial.print(" ");
  } if (serialNumberBegin < 10) {
    Serial.print(" ");
  } Serial.print(serialNumberBegin); Serial.print(")-");
  for (int address = serialNumberBegin; address <= serialNumberEnd; address++) {
    yield();
    value = eeprom_read_char(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 32 == 0) {
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
  //----
  Serial.print("\n");
  Serial.println("Drink Alarm Memory");
  Serial.print("(address="); if (drinkAlarmPositionsBegin < 100) {
    Serial.print(" ");
  } if (drinkAlarmPositionsBegin < 10) {
    Serial.print(" ");
  } Serial.print(drinkAlarmPositionsBegin); Serial.print(")-");
  for (int address = drinkAlarmPositionsBegin; address <= drinkAlarmPositionsEnd; address++) {
    yield();
    value = eeprom_read_char(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 32 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != drinkAlarmPositionsEnd) {
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
  //----

  //----
  Serial.print("\n");
  Serial.println("Meal Alarm Memory");
  Serial.print("(address="); if (mealAlarmPositionsBegin < 100) {
    Serial.print(" ");
  } if (mealAlarmPositionsBegin < 10) {
    Serial.print(" ");
  } Serial.print(mealAlarmPositionsBegin); Serial.print(")-");
  for (int address = mealAlarmPositionsBegin; address <= mealAlarmPositionsEnd; address++) {
    yield();
    value = eeprom_read_char(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 32 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != mealAlarmPositionsEnd) {
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
  Serial.println("Cleaning Alarm Memory");
  Serial.print("(address="); if (cleaningAlarmPositionsBegin < 100) {
    Serial.print(" ");
  } if (cleaningAlarmPositionsBegin < 10) {
    Serial.print(" ");
  } Serial.print(userEmailBegin); Serial.print(")-");
  for (int address = cleaningAlarmPositionsBegin; address <= cleaningAlarmPositionsEnd; address++) {
    yield();
    value = eeprom_read_char(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 32 == 0) {
      Serial.print("-(address="); if (address < 100) {
        Serial.print(" ");
      } if (address < 10) {
        Serial.print(" ");
      } Serial.print(address); Serial.print(")");
      Serial.println("");
      if (address != cleaningAlarmPositionsEnd) {
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


}

void Memory::printData() {
  uint8_t value = 0;
  Serial.println("\nData Memory");
  Serial.print("(address= "); if (dataMemoryBegin < 100) {
    Serial.print(" ");
  } if (dataMemoryBegin < 10) {
    Serial.print(" ");
  }
  Serial.print(dataMemoryBegin);
  Serial.print(")(Position=  1)");
  for (int address = dataMemoryBegin; address <= dataMemoryEnd; address++) {
    yield();
    value = eeprom_read_char(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);

    if ((address + 1 - dataMemoryBegin) % _drinkSize == 0) {
      Serial.print("-(address=");
      if (address < 100) {
        Serial.print(" ");
      }
      if (address < 10) {
        Serial.print(" ");
      }
      Serial.print(address);
      Serial.println(")");
      if (address != dataMemoryEnd) {
        Serial.print("(address="); if (address < 1000) {
          Serial.print(" ");
        }
        if (address < 100) {
          Serial.print(" ");
        }
        if (address < 10) {
          Serial.print(" ");
        }
        Serial.print(address + 1);
        Serial.print(")(Position=");
        if ((2 + (address - dataMemoryBegin) / _drinkSize) < 100) {
          Serial.print(" ");
        } if ((2 + (address - dataMemoryBegin) / _drinkSize) < 10) {
          Serial.print(" ");
        }
        Serial.print(2 + (address - dataMemoryBegin) / _drinkSize);
        Serial.print(")");
      }
      yield();
    } else {
      Serial.print("-");
    }
  }
}

void Memory::cleanInfo() {
  Serial.print("Clean Info");
  for (int address = infoByteBegin; address <= infoByteEnd; address++) {
    yield();
    if (eeprom_read_char(address) != 255) {
      eeprom_write_char(address, '\0');
    }
  }
  Serial.println("\nInfo has been clean!");
}

void Memory::clearMemory() {
  Serial.print("Clean Memory");
//  for (int address = userEmailBegin; address <= dataMemoryEnd; address++) {
//    yield();
//    if (eeprom_read_char(address) != 255) {
//      eeprom_write_char(address, 255);
//    }
//  }
cleanInfo();
clearDataMemory();
}

void Memory::clearDataMemory() {
  Serial.println("Clean Data Memory");
  for (int address = dataMemoryBegin; address <= dataMemoryEnd; address++) {
    yield();
    if (eeprom_read_char(address) != 255) {
      eeprom_write_char(address, 255);
    }
  }
  byte firstByte = 0;
  eeprom_write_char(dataMemoryBegin + 2, firstByte);
}

//void Memory::clearDrinkMemoryAtPosition(byte position) {
//  yield();
//  EEPROM.begin(memorySize);
//  if (position > 0 && position < 256) {
//    //    for (int address = dataMemoryBegin + (position - 1) * _drinkSize ; address < dataMemoryBegin + (position) * _drinkSize ; address++) {
//    //      EEPROM.write(address, 128);
//    //    }
//    EEPROM.write(dataMemoryBegin + (position - 1) * _drinkSize + 2, 128);
//  }
//  EEPROM.end();
//}
//
//
//void Memory::getUserEmail(char email[]) {
//  int i = 0;
//
//
//
//
//  do {
//    yield();
//    email[i] = (char)EEPROM.read(userEmailBegin + i);
//    i++;
//  } while ((char)EEPROM.read(userEmailBegin + i) != '\0');
//  email[i] = (char)EEPROM.read(userEmailBegin + i);
//}
////
//byte Memory::getUserEmailSize() {
//  yield();
//  EEPROM.begin(memorySize);
//  int size = 0;
//  while ((char)EEPROM.read(userEmailBegin + size) != '\0') {
//    yield();
//    size++;
//  }
//  return size + 1;
//  EEPROM.end();
//}
//
//void Memory::setUserEmail(const char email[]) {
//  yield();
//  EEPROM.begin(memorySize);
//  //  Serial.print("Dentro setter: "); Serial.println(email);
//  int i = 0;
//  do {
//    yield();
//    EEPROM.write(userEmailBegin + i, (byte)email[i]);
//    i++;
//  } while (email[i] != '\0');
//  EEPROM.write(userEmailBegin + i, (byte)email[i]);
//  EEPROM.end();
//}
//
//
///* --------------------------------- Alarm --------------------------------- */
//
//
//byte Memory::getDrinkAlarmPositionQuantity() {
////  EEPROM.begin(memorySize);
//  uint16_t quantidade = 0;
//  Serial.print(" getQty:");
////    Serial.print("(ERadd3n: ");     Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
////    Serial.print("(ER: ");          Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
////    Serial.print("(ERadd3n: ");     Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
////    Serial.print("(ERn: ");         Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.println(")");
//
////Serial.print("(ERt: ");         Serial.print(EEPROM.read(drinkAlarmPositionsBegin));Serial.println(")");
////    Serial.print("\naddress: "); Serial.println(drinkAlarmPositionsBegin + (quantidade) * 2);
////    Serial.print("(ER0: ");         Serial.print(EEPROM.read(0));Serial.println(")");
////    Serial.print("(ERt: ");         Serial.print(EEPROM.read(drinkAlarmPositionsBegin));Serial.println(")");
////    Serial.print("(ERn: ");         Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.println(")");
//  while (readByte(drinkAlarmPositionsBegin + (quantidade) * 2) != 255) {
//    Serial.print("\n - (drinkAlarmPositionsBegin + (quantidade) * 2): "); Serial.print((drinkAlarmPositionsBegin + (quantidade) * 2));
//    Serial.print(" - 1Eepromread: ");Serial.print(readByte(drinkAlarmPositionsBegin + (quantidade) * 2));
//    Serial.print("- quant: "); Serial.print(quantidade);
//    quantidade++;
//  }
////  EEPROM.end();
////  return 0;
//  return quantidade;
//  yield();
////  EEPROM.end();
//}
//byte Memory::findDrinkAlarmPositionFrom(byte hour, byte minute) {
//  EEPROM.begin(memorySize);
//  if (getDrinkAlarmPositionQuantity() == 0) {
//    return 0;
//  }
//  byte position = 1;
//  while (( EEPROM.read(drinkAlarmPositionsBegin + (position - 1) * 2) != hour ) && ( EEPROM.read(drinkAlarmPositionsBegin + 1 + (position - 1) * 2) != minute )) {
//    position++;
//    yield();
//    if ( position == drinkAlarmPositions + 1) {
//      position = 0;
//      break;
//    }
//  }
//  return position;
//  EEPROM.end();
//}
//bool Memory::addDrinkAlarm(byte hour, byte minute) {
////  EEPROM.begin(memorySize);
//  Serial.print("add");
//  float horarioAdd =hour + ((float)minute)/60;
//  byte quantidade = getDrinkAlarmPositionQuantity();
//  float maiorHorario;
//  if(quantidade == 0){
//    maiorHorario = 0;
//  }else{
//    maiorHorario =readByte( drinkAlarmPositionsBegin+2*(quantidade-1) ) + ((float)( readByte( 1+drinkAlarmPositionsBegin+2*(quantidade-1) ) ))/60;
//  }
//
//
//  Serial.print(" - horarioAdd: "); Serial.print(horarioAdd); Serial.print(" - maiorHorario: "); Serial.print(maiorHorario); Serial.print(" - quantidade: "); Serial.println(quantidade);
//  if ( quantidade == 25 ){
////    EEPROM.end();
//    return false;
//  }else if ( quantidade == 0 ) {
//    Serial.println("In(0)");
//    writeByte(drinkAlarmPositionsBegin, hour);//EEPROM.commit();
//    Serial.print("(ERadd0h: ");Serial.print(readByte(drinkAlarmPositionsBegin));Serial.print(")");
//    writeByte(drinkAlarmPositionsBegin + 1, minute);//EEPROM.commit();
//     Serial.print("(ERadd0m: ");Serial.print(readByte(drinkAlarmPositionsBegin+1));Serial.print(")");
//  }else if( horarioAdd > maiorHorario ){
//    Serial.print("In(maior)");
//    writeByte(drinkAlarmPositionsBegin+2*(getDrinkAlarmPositionQuantity()), hour);//EEPROM.commit();
//    writeByte(1+drinkAlarmPositionsBegin+2*(getDrinkAlarmPositionQuantity()),minute);//EEPROM.commit();
//  } else {
//    byte Posicao = getDrinkAlarmNextAlarmPosition(hour, minute) - 1;
//    for (byte address = drinkAlarmPositionsBegin + getDrinkAlarmPositionQuantity() * 2 ;
//         address < (drinkAlarmPositionsBegin + (Posicao - 1) * 2) ;
//         address = address - 2) {
//          Serial.println("\nDENTRO FOR DO ADD");
//      writeByte(address, hour);//EEPROM.commit();
//      writeByte(address + 1, minute);//EEPROM.commit();
//      yield();
//    }
//    writeByte(drinkAlarmPositionsBegin + (getDrinkAlarmNextAlarmPosition(hour, minute) - 1) * 2, hour);EEPROM.commit();
//    writeByte(drinkAlarmPositionsBegin + 1 + (getDrinkAlarmNextAlarmPosition(hour, minute) - 1) * 2, minute);EEPROM.commit();
//  }
////  Serial.print("(ERadd2: ");Serial.print(readByte(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
////  EEPROM.end();
//  return true;
//
//}
//bool Memory::clearDrinkAlam(byte hour, byte minute) {
//  EEPROM.begin(memorySize);
//  if (findDrinkAlarmPositionFrom(hour, minute) != 0) {
//    EEPROM.write(drinkAlarmPositionsBegin + findDrinkAlarmPositionFrom(hour, minute) * 2, 255);
//    EEPROM.write(drinkAlarmPositionsBegin + 1 + findDrinkAlarmPositionFrom(hour, minute) * 2, 255);
//  }
//  return 0;
//  EEPROM.end();
//}
//byte Memory::getDrinkAlarmHourFromPosition(byte position) {
//  EEPROM.begin(memorySize);
////  if (getDrinkAlarmPositionQuantity() == 0) {
////    return 255;
////  }
//  yield();
//  return (byte)EEPROM.read(drinkAlarmPositionsBegin + (position - 1) * 2);
//  EEPROM.end();
//}
//byte Memory::getDrinkAlarmMinuteFromPosition(byte position) {
//  EEPROM.begin(memorySize);
////  if (getDrinkAlarmPositionQuantity() == 0) {
////    return 255;
////  }
//  yield();
//  return (byte)EEPROM.read(drinkAlarmPositionsBegin + 1 + (position - 1) * 2);
//  EEPROM.end();
//}
//byte Memory::getDrinkAlarmNextAlarmPosition(byte hour, byte minute) {
//  EEPROM.begin(memorySize);
//  if (getDrinkAlarmPositionQuantity() == 0) {
//    return 0;
//  }
//  byte posicao = 1;
//  if (hour == 0 && minute == 0) {
//    return posicao;
//  }
//  float horaProcurada = hour + ((float)minute) / 60;
//  float horaEeprom = EEPROM.read(drinkAlarmPositionsBegin) + ((float)((byte)EEPROM.read(drinkAlarmPositionsBegin + 1))) / 60;
//  while ((posicao != getDrinkAlarmPositionQuantity()) || (horaProcurada > horaEeprom)) {
//    horaEeprom = EEPROM.read(drinkAlarmPositionsBegin + (posicao - 1) * 2) + ((float)((byte)EEPROM.read(1 + drinkAlarmPositionsBegin + (posicao - 1) * 2))) / 60;
//    posicao++;
//    yield();
//  }
//  return posicao;
//  EEPROM.end();
//}
//void Memory::clearDrinkAlarmAllPosition() {
//  EEPROM.begin(memorySize);
//  for (int address = drinkAlarmPositionsBegin; address < (drinkAlarmPositionsEnd + 1); address++) {
//    EEPROM.write(address, 255);
//  }
//  yield();
//  EEPROM.end();
//}
//void Memory::DrinkAlarmTest() {
//  EEPROM.begin(memorySize);
//  Serial.println("Dentro drink");
//  clearDrinkAlarmAllPosition();
//  memory.print();
////  Serial.println("Dentro drink");
////  Serial.print("Qty0: (");Serial.print(getDrinkAlarmPositionQuantity());Serial.println(")");
////  EEPROM.write(drinkAlarmPositionsBegin,1);EEPROM.commit();Serial.print("drinkAlarmPositionsBegin:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin));
////  EEPROM.write(drinkAlarmPositionsBegin+1,1);EEPROM.commit();Serial.print("drinkAlarmPositionsBegin+1:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin+1));
////  Serial.print("Qty1: (");Serial.print(getDrinkAlarmPositionQuantity());Serial.println(")");
//////  EEPROM.write(drinkAlarmPositionsBegin+2,1);Serial.print("drinkAlarmPositionsBegin+2:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin+2));
//////  EEPROM.write(drinkAlarmPositionsBegin+3,1);Serial.print("drinkAlarmPositionsBegin+3:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin+3));
////  Serial.print("Qty2: (");Serial.print(getDrinkAlarmPositionQuantity());Serial.println(")");
//  int i = 1;
//  while (i < 26) {
//    int hour = i - 1;
//    int minute = i * 2;
//    Serial.print("\ni: ");                              Serial.print(i);
//    Serial.print(" - hour: ");                        Serial.print(hour);
//    Serial.print(" - minute: ");                      Serial.print(minute);
//    Serial.print(" - addSucess: ");                   Serial.print(addDrinkAlarm(hour, minute));//Serial.print("(ERadd3: ");Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
////    Serial.print(" - quantPostion: ");                Serial.print(getDrinkAlarmPositionQuantity());
////    Serial.print(" - DrinkAlarmNextAlarmPosition: "); Serial.print(getDrinkAlarmNextAlarmPosition(hour,minute));
//    Serial.print(" - eeprom.hour: ");                 Serial.print(getDrinkAlarmHourFromPosition(i));//Serial.print("(ERadd4: ");Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
//    Serial.print(" - eeprom.minute: ");               Serial.print(getDrinkAlarmMinuteFromPosition(i)+1);//Serial.print("(ERadd5: ");Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
////    Serial.print(" - quantPostion: ");                Serial.print(getDrinkAlarmPositionQuantity());
////    Serial.print(" - findDrink(h2/,m/2): ");          Serial.print(findDrinkAlarmPositionFrom(hour/2,minute/2));
////    Serial.print(" - DrinkAlarmNextAlarmPosition(h2/,m/2): "); Serial.println(getDrinkAlarmNextAlarmPosition(hour/2,minute/2));
//    i++;
//  }
//  memory.print();
//  EEPROM.end();
//}
//
//uint8_t Memory::readByte(uint16_t address){
//  uint8_t value;
//  EEPROM.begin(memorySize);
//  value = EEPROM.read(address); Serial.print("(readValue:"); Serial.print(value);Serial.print(")");
////  EEPROM.commit();
//  EEPROM.end();
//  return value;
//}
//void Memory::writeByte(uint16_t address, uint8_t value){
//  EEPROM.begin(memorySize);
//  EEPROM.write(address, value);
////  EEPROM.commit();
//  EEPROM.end();
//}


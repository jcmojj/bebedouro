#include "Memory.h"
#include "Drink.h"

Memory::Memory(Drink &drink, byte drinkSize) {
  Serial.begin(115200);
//  rtc.Begin();
  _drink = &drink;
  _drinkSize = drinkSize;

}
//void Memory::memoryTest() {
//  //    memTest();// longo estraga o eeprom
//  //    print();
//  //  emailTest();
//  //  print();
//  //  cleanInfoMemory();
////    printInfo();
////    print();
////    cleanDataMemory();
//    preenchendoDrinksParaTeste();
//    printData();
//
//  Serial.print("Drink TESTE TESTE TESTE TESTE TESTE TESTE TESTE ");
//  drinkAlarmTest();
//    Serial.print("Meal TESTE TESTE TESTE TESTE TESTE TESTE TESTE ");
//  mealAlarmTest();
//    Serial.print("Cleaning TESTE TESTE TESTE TESTE TESTE TESTE TESTE ");
//  cleaningAlarmTest();
////  Serial.print("NOVO TESTE NOVO TESTE NOVO TESTE V NOVO TESTE NOVO TESTE");
////  AlarmTest(drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//  
////  mem.write(drinkAlarmPositionsBegin,8);
////  mem.write(drinkAlarmPositionsBegin+1,30);
////  mem.write(drinkAlarmPositionsBegin+2,9);
////  mem.write(drinkAlarmPositionsBegin+3,15);
////  printDrinkAlarm();
////  Serial.print("Quantity: "); Serial.println(getDrinkAlarmPositionQuantity());
////  Serial.print("find 8:30: "); Serial.println(findDrinkAlarmPositionFrom(8,30));
////  Serial.print("find 9:15: "); Serial.println(findDrinkAlarmPositionFrom(9,15));
////  Serial.print("find 10h: "); Serial.println(findDrinkAlarmPositionFrom(10,00));
////  printDrinkAlarm();
////  Serial.print("Next alarm: "); Serial.println(getDrinkAlarmNextAlarmPosition(10,30));
////  if(addDrinkAlarm(10,30)){
////    Serial.println(" adicionado com sucesso");
////  }
//////  cleanDrinkAlarmAllPosition();
////  printDrinkAlarm();
////  Serial.print("\nNext alarm: "); Serial.println(getDrinkAlarmNextAlarmPosition(12,30));
////  if(addDrinkAlarm(12,30)){
////    Serial.println(" adicionado com sucesso");
////  }
////  printDrinkAlarm();
////  Serial.print("\nNext alarm: "); Serial.println(getDrinkAlarmNextAlarmPosition(8,00));
////  if(addDrinkAlarm(8,0)){
////    Serial.println(" adicionado com sucesso");
////  }
////  printDrinkAlarm();
////  Serial.print("\nNext alarm: "); Serial.println(getDrinkAlarmNextAlarmPosition(12,0));
////  if(addDrinkAlarm(12,0)){
////    Serial.println(" adicionado com sucesso");
////  }
////  printDrinkAlarm();
//  //  getDrinkAlarmPositionQuantity();
//  //  print();
//  //  memTest();// longo
//  //  print();
//}
//void Memory::memTest() {
//  Serial.println("\n REALIZANDO TESTE DO EEPROM DO RTC3231");
//  // read and write byte
//  Serial.println("Write 42 to address 12");
//  mem.write(12, 42);
//  Serial.println("Read byte from address 12 ...");
//  byte b = mem.read(12);
//  byte b1;
//  Serial.print("... read: ");
//  Serial.println(b, DEC);
//  Serial.println();
//  for (int address = 0; address != 255; address++) {
//    yield();
//    Serial.print("Write ");
//    Serial.print((byte)((byte)address + (byte)100));
//    Serial.print(" to address ");
//    Serial.print(address);
//    mem.write(address + 100, (byte)address);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(address);
//    Serial.print("...   ");
//    b1 = mem.read(address);
//    Serial.print("... read: ");
//    Serial.print(b, DEC);
//    yield();
//    if (b1 == b1) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//
//  // read and write byte
//  Serial.println("\nWrite 'a' to address 12");
//  mem.write(12, (byte)'a');
//  Serial.println("Read char from address 12 ...");
//  char c = (char)mem.read(12);
//  char c1;
//  Serial.print("... read: ");
//  Serial.println(c);
//  Serial.println();
//  for (int address = 32; address != 126; address++) {
//    yield();
//    c = (char)address;
//    Serial.print("Write ");
//    Serial.print(c);
//    Serial.print(" to address ");
//    Serial.print(address);
//    mem.write(address, (byte)c);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(address);
//    Serial.print("...   ");
//    c1 = (char)mem.read(address);
//    Serial.print("... read: ");
//    Serial.print(c1);
//    yield();
//    if (c == c1) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//
//  // read and write integer
//  Serial.println();
//  Serial.println("Write 65000 to address 15");
//  mem.writeInt(15, 65000);
//  Serial.println("Read integer from address 15 ...");
//  unsigned int i = mem.readInt(15);
//  unsigned int i1;
//  Serial.print("... read: ");
//  Serial.println(i, DEC);
//  Serial.println();
//  for (unsigned int value = 16; value != 65536; value = value * 2) {
//    yield();
//    i = value;
//    Serial.print("Write ");
//    Serial.print(i);
//    Serial.print(" to address ");
//    Serial.print(value / 16 - 1);
//    mem.writeInt(value / 16 - 1, value);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(value / 16 - 1);
//    Serial.print("...   ");
//    i1 = mem.readInt(value / 16 - 1);
//    Serial.print("... read: ");
//    Serial.print(i1);
//    yield();
//    if (i == i1) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//
//  // read and write long
//  Serial.println();
//  Serial.println("Write 1111111111 to address 31");
//  mem.writeLong(31, 1111111111);
//  Serial.println("Read long from address 31 ...");
//  unsigned long l2 = mem.readLong(31);
//  unsigned long l21;
//  Serial.print("... read: ");
//  Serial.println(l2, DEC);
//  Serial.println();
//  Serial.println();
//  for (unsigned int value = 16; value != 65536; value = value * 2) {
//    yield();
//    l2 = value * value;
//    Serial.print("Write ");
//    Serial.print(l2, DEC);
//    Serial.print(" to address ");
//    Serial.print(value / 16 - 1);
//    mem.writeLong(value / 16 - 1, l2);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(value / 16 - 1);
//    Serial.print("...   ");
//    l21 = mem.readLong(value / 16 - 1);
//    Serial.print("... read: ");
//    Serial.print(l21, DEC);
//    yield();
//    if (l2 == l21) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//  for (unsigned int value = 16; value != 65536; value = value * 2) {
//    yield();
//    l2 = value * value;
//    Serial.print("Write ");
//    Serial.print(l2, DEC);
//    Serial.print(" to address ");
//    Serial.print(value / 16 + 4);
//    mem.writeLong(value / 16 + 4, l2);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(value / 16 + 4);
//    Serial.print("...   ");
//    l21 = mem.readLong(value / 16 + 4);
//    Serial.print("... read: ");
//    Serial.print(l21, DEC);
//    yield();
//    if (l2 == l21) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//
//  // read and write float
//  Serial.println();
//  Serial.println("Write 3.1415926535897932384626433832 to address 40");
//  mem.writeFloat(40, 3.1415926535897932384626433832);
//  Serial.println("Read float from address 40 ...");
//  float f = mem.readFloat(40);
//  float f1;
//  Serial.print("... read: ");
//  Serial.println(f, DEC);
//  Serial.println();
//  for (unsigned int value = 16; value != 65536; value = value * 2) {
//    yield();
//    float ifvalue = (float) value;
//    float i1value = 128.0 / ifvalue;
//    f = 3.141592  + i1value;
//    Serial.print("Write ");
//    Serial.print(f, DEC);
//    Serial.print(" to address ");
//    Serial.print(value / 16 - 1);
//    mem.writeFloat(value / 16 - 1, f);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(value / 16 - 1);
//    Serial.print("...   ");
//    f1 = mem.readFloat(value / 16 - 1);
//    Serial.print("... read: ");
//    Serial.print(f1, DEC);
//    yield();
//    if (f == f1) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//
//  // read and write double
//  Serial.println();
//  Serial.println("Write 3.1415926535897932384626433832 to address 40");
//  mem.writeDouble(40, 3.1415926535897932384626433832);
//  Serial.println("Read double from address 40 ...");
//  double d = mem.readDouble(40);
//  double d1;
//  Serial.print("... read: ");
//  Serial.println(d, DEC);
//  Serial.println();
//  for (unsigned int value = 16; value != 65536; value = value * 2) {
//    yield();
//    double idvalue = (double) value;
//    double iddvalue = 128.0 / idvalue;
//    d = 3.1415926535897932384626433832  + iddvalue;
//    Serial.print("Write ");
//    Serial.print(d, DEC);
//    Serial.print(" to address ");
//    Serial.print(value / 16 - 1);
//    mem.writeDouble(value / 16 - 1, d);
//    Serial.print(" ---> Read byte from address ");
//    Serial.print(value / 16 - 1);
//    Serial.print("...   ");
//    d1 = mem.readDouble(value / 16 - 1);
//    Serial.print("... read: ");
//    Serial.print(d1, DEC);
//    yield();
//    if (d == d1) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//  char arrayPronto[190];
//  // read and write char
//  Serial.println();
//  Serial.print("Write chars: '");
//  char msg[] = "This is a message";
//  Serial.print(msg);
//  Serial.println("' to address 200");
//  mem.writeChars(200, msg, sizeof(msg));
//  Serial.println("Read chars from address 200 ...");
//  char msg2[30];
//  mem.readChars(200, msg2, sizeof(msg2));
//  Serial.print("... read: '");
//  Serial.print(msg2);
//  Serial.println("'");
//  Serial.println();
//  char letra1[2]; letra1[1] = '\0';
//  char letra2[2]; letra2[1] = '\0';
//  for (int address = 32; address != 126; address++) {
//    yield();
//    arrayPronto[2 * (address - 32)] = (char)address;
//    arrayPronto[2 * (address - 32) + 1] = (char)address;
//    letra1[0] = (char)address;
//    Serial.print("Write ");
//    Serial.print(letra1);
//    Serial.print(" to address ");
//    Serial.print(address);
//    mem.writeChars(address, letra1, sizeof(letra1));
//    Serial.print(" ---> Read letras from address ");
//    Serial.print(address);
//    Serial.print("...   ");
//    mem.readChars(address, letra2, sizeof(letra2));
//    Serial.print("... read: ");
//    Serial.print(letra2);
//    yield();
//    if (letra1[0] == letra2[0]) {
//      Serial.println(" --> OK");
//    } else {
//      Serial.println(" --> ERRO");
//    }
//  }
//
//  Serial.println();
//  arrayPronto[sizeof(arrayPronto) - 1] = '\0';
//  arrayPronto[sizeof(arrayPronto) - 2] = 'f';
//  Serial.print("ArrayPronto:");
//  Serial.print("size: ");
//  Serial.println(sizeof(arrayPronto));
//  Serial.print("Array: ");
//  Serial.println(arrayPronto);
//  Serial.print("arrayPronto[ "); Serial.print(sizeof(arrayPronto) - 1); Serial.print("]: ");
//  Serial.println(arrayPronto[sizeof(arrayPronto) - 1]);
//  int  maiorOld = 0;
//  char arrayProntoBig[10 * sizeof(arrayPronto)];
//  for (int i = 0; i < sizeof(arrayPronto); i++) {
//    for (int j = 0; j < 10; j++) {
//      arrayProntoBig[i * 10 + j] = arrayPronto[i];
//      maiorOld++;
//    }
//  }
//  Serial.println(arrayProntoBig);
//  int maiorNew = 0;
//  yield();
//  while ( (arrayProntoBig[maiorNew] != '\0') ) {
//    maiorNew++;
//  }
//  Serial.print("MaiorOld posicao ocupada de arrayProntoBig é ");
//  Serial.println(maiorOld);
//  Serial.print("MaiorNew posicao ocupada de arrayProntoBig é ");
//  Serial.println(maiorNew);
//  for (int i = maiorNew - 10; i < maiorOld; i++) {
//    yield();
//    Serial.print("arrayProntoBig[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(arrayProntoBig[i]);
//    arrayProntoBig[i] = i - maiorNew;
//    Serial.print("----->(byte)arrayProntoBig[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print((byte)arrayProntoBig[i]);
//    Serial.println();
//  }
//  arrayProntoBig[maiorOld - 1] = '\0';
//  Serial.print("(byte)arrayProntoBig[");
//  Serial.print(maiorOld - 1);
//  Serial.print("]=");
//  Serial.print((byte)arrayProntoBig[i]);
//  Serial.print("<--");
//
//  //----------------------- 30 bytes
//  byte pos30Read[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9};
//  Serial.println();
//  Serial.print("30pos\nsize:");
//  Serial.println(sizeof(pos30Read));
//
//  // read bytes with multiple steps
//  Serial.println("Read 30 single bytes starting at address 1000");
//  Serial.print("\nWrite 30pos(");
//  for (int i = 0; i < sizeof(pos30Read); i++) {
//    Serial.print(pos30Read[i]);
//  }
//  Serial.println(")to address 1000");
//  mem.write(1000, (byte*)pos30Read, sizeof(pos30Read));
//  Serial.println("Read byte from address 1000 ...");
//  byte pos30byte;
//  for ( int i = 0; i < sizeof(pos30Read); i++) {
//    yield();
//    byte pos30byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos30byte);
//    if (pos30Read[i] == pos30byte) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//
//  // read bytes with multiple steps
//  Serial.print("\nWrite 30pos(");
//  for (int i = 0; i < sizeof(pos30Read); i++) {
//    Serial.print(pos30Read[i]);
//  }
//  Serial.println(")to address 1000");
//  Serial.println("\nRead 30 bytes with one operation at address 1000");
//  byte pos30Write[sizeof(pos30Read)];
//  Serial.println("Read byte from address 1000 ...");
//  memset(&pos30Write[0], 32, sizeof(pos30Write));
//  mem.read(1000, pos30Write, sizeof(pos30Write));
//
//  for ( int i = 0; i < sizeof(pos30Write); i++) {
//    yield();
//    byte pos30byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos30Write[i]);
//    if (pos30Read[i] == pos30Write[i]) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//  //------------------------------- 32 bytes
//
//
//  byte pos32Read[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 0, 0};
//  Serial.println();
//  Serial.print("32pos\nsize:");
//  Serial.println(sizeof(pos32Read));
//
//  // read bytes with multiple steps
//  Serial.println("Read 32 single bytes starting at address 1000");
//  Serial.print("\nWrite 32pos(");
//  for (int i = 0; i < sizeof(pos32Read); i++) {
//    Serial.print(pos32Read[i]);
//  }
//  Serial.println(")to address 1000");
//  mem.write(1000, (byte*)pos32Read, sizeof(pos32Read));
//  Serial.println("Read byte from address 1000 ...");
//  byte pos32byte;
//  for ( int i = 0; i < sizeof(pos32Read); i++) {
//    yield();
//    byte pos32byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos32byte);
//    if (pos32Read[i] == pos32byte) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//
//  // read bytes with multiple steps
//  Serial.print("\nWrite 32pos(");
//  for (int i = 0; i < sizeof(pos32Read); i++) {
//    Serial.print(pos32Read[i]);
//  }
//  Serial.println(")to address 1000");
//  Serial.println("\nRead 32 bytes with one operation at address 1000");
//  byte pos32Write[sizeof(pos32Read)];
//  Serial.println("Read byte from address 1000 ...");
//  memset(&pos32Write[0], 32, sizeof(pos32Write));
//  mem.read(1000, pos32Write, sizeof(pos32Write));
//
//  for ( int i = 0; i < sizeof(pos32Write); i++) {
//    yield();
//    byte pos32byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos32Write[i]);
//    if (pos32Read[i] == pos32Write[i]) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//  //------------------------------- 33 bytes
//
//  byte pos33Read[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 0, 0, 0};
//  Serial.println();
//  Serial.print("33pos\nsize:");
//  Serial.println(sizeof(pos33Read));
//
//  // read bytes with multiple steps
//  Serial.println("Read 33 single bytes starting at address 1000");
//  Serial.print("\nWrite 33pos(");
//  for (int i = 0; i < sizeof(pos33Read); i++) {
//    Serial.print(pos33Read[i]);
//  }
//  Serial.println(")to address 1000");
//  mem.write(1000, (byte*)pos33Read, sizeof(pos33Read));
//  Serial.println("Read byte from address 1000 ...");
//  byte pos33byte;
//  for ( int i = 0; i < sizeof(pos33Read); i++) {
//    yield();
//    byte pos33byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos33byte);
//    if (pos33Read[i] == pos33byte) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//
//  // read bytes with multiple steps
//  Serial.print("\nWrite 33pos(");
//  for (int i = 0; i < sizeof(pos33Read); i++) {
//    Serial.print(pos33Read[i]);
//  }
//  Serial.println(")to address 1000");
//  Serial.println("\nRead 33 bytes with one operation at address 1000");
//  byte pos33Write[sizeof(pos33Read)];
//  Serial.println("Read byte from address 1000 ...");
//  memset(&pos33Write[0], 33, sizeof(pos33Write));
//  mem.read(1000, pos33Write, sizeof(pos33Write));
//
//  for ( int i = 0; i < sizeof(pos33Write); i++) {
//    yield();
//    byte pos33byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos33Write[i]);
//    if (pos33Read[i] == pos33Write[i]) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//  //----------------------- 80 bytes
//
//  byte pos80Read[] = {  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
//                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
//                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
//                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
//                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
//                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
//                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
//                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
//                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
//                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7
//                     };
//  Serial.println();
//  Serial.print("80pos\nsize:");
//  Serial.println(sizeof(pos80Read));
//
//  // read bytes with multiple steps
//  Serial.println("Read 80 single bytes starting at address 1000");
//  Serial.print("\nWrite 80pos(");
//  for (int i = 0; i < sizeof(pos80Read); i++) {
//    Serial.print(pos80Read[i]);
//  }
//  Serial.println(")to address 1000");
//  mem.write(1000, (byte*)pos80Read, sizeof(pos80Read));
//  Serial.println("Read byte from address 1000 ...");
//  byte pos80byte;
//  for ( int i = 0; i < sizeof(pos80Read); i++) {
//    yield();
//    byte pos80byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos80byte);
//    if (pos80Read[i] == pos80byte) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//
//  // read bytes with multiple steps
//  Serial.print("\nWrite 80pos(");
//  for (int i = 0; i < sizeof(pos80Read); i++) {
//    Serial.print(pos80Read[i]);
//  }
//  Serial.println(")to address 1000");
//  Serial.println("\nRead 80 bytes with one operation at address 1000");
//  byte pos80Write[sizeof(pos80Read)];
//  Serial.println("Read byte from address 1000 ...");
//  memset(&pos80Write[0], 80, sizeof(pos80Write));
//  mem.read(1000, pos80Write, sizeof(pos80Write));
//
//  for ( int i = 0; i < sizeof(pos80Write); i++) {
//    yield();
//    byte pos80byte = mem.read(1000 + i);
//    Serial.print("i[");
//    Serial.print(i);
//    Serial.print("]=");
//    Serial.print(pos80Write[i]);
//    if (pos80Read[i] == pos80Write[i]) {
//      Serial.print(" --> OK   ///   ");
//    } else {
//      Serial.print(" --> ERRO ///   ");
//    }
//    if ((i + 1) % 3 == 0) {
//      Serial.println();
//    }
//  }
//  Serial.println();
//
//  // email!!!! 16 bytes
//  Serial.println();
//  Serial.println("16 bytes");
//  for (int endereco = 0; endereco < 64; endereco++) {
//    yield();
//    char email[64] = "jcmojj@gmail.com";
//    char emailLido[64];
//    Serial.print(" Get address");
//    Serial.print(endereco);
//    Serial.print(" and write email: ");
//    Serial.print(email);
//    mem.write(endereco, (byte*)email, sizeof(email));
//
//    memset(&emailLido[0], 32, sizeof(emailLido));
//    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
//    Serial.print(" --> From address ");
//    Serial.print(endereco);
//    Serial.print(" read email: ");
//    Serial.print(emailLido);
//
//    Serial.print("  posicao do zero é ");
//    int pos = 0;
//    while ( emailLido[pos] != '\0') {
//      pos++;
//    }
//    Serial.println(pos);
//  }
//
//  // email!!!! 32 bytes
//  Serial.println();
//  for (int endereco = 0; endereco < 64; endereco++) {
//    yield();
//    char email[64] = "jcmojj@gmail.comjcmojj@gmail.com";
//    char emailLido[64];
//    Serial.print(" Get address");
//    Serial.print(endereco);
//    Serial.print(" and write email: ");
//    Serial.print(email);
//    mem.write(endereco, (byte*)email, sizeof(email));
//
//    memset(&emailLido[0], 32, sizeof(emailLido));
//    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
//    Serial.print(" --> From address ");
//    Serial.print(endereco);
//    Serial.print(" read email: ");
//    Serial.println(emailLido);
//  }
//
//  // email!!!! 48 bytes
//  Serial.println();
//  for (int endereco = 0; endereco < 64; endereco++) {
//    yield();
//    char email[64] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.com";
//    char emailLido[64];
//    Serial.print(" Get address");
//    Serial.print(endereco);
//    Serial.print(" and write email: ");
//    Serial.print(email);
//    mem.write(endereco, (byte*)email, sizeof(email));
//
//    memset(&emailLido[0], 32, sizeof(emailLido));
//    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
//    Serial.print(" --> From address ");
//    Serial.print(endereco);
//    Serial.print(" read email: ");
//    Serial.println(emailLido);
//  }
//
//  // email!!!! 64 bytes
//  Serial.println();
//  for (int endereco = 0; endereco < 64; endereco++) {
//    yield();
//    char email[64] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.co";
//    char emailLido[64];
//    Serial.print(" Get address");
//    Serial.print(endereco);
//    Serial.print(" and write email: ");
//    Serial.print(email);
//    mem.write(endereco, (byte*)email, sizeof(email));
//
//    memset(&emailLido[0], 32, sizeof(emailLido));
//    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
//    Serial.print(" --> From address ");
//    Serial.print(endereco);
//    Serial.print(" read email: ");
//    Serial.println(emailLido);
//  }
//
//  // email!!!! 65 bytes
//  Serial.println();
//  for (int endereco = 0; endereco < 65; endereco++) {
//    yield();
//    char email[65] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.com";
//    char emailLido[65];
//    Serial.print(" Get address");
//    Serial.print(endereco);
//    Serial.print(" and write email: ");
//    Serial.print(email);
//    mem.write(endereco, (byte*)email, sizeof(email));
//
//    memset(&emailLido[0], 32, sizeof(emailLido));
//    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
//    Serial.print(" --> From address ");
//    Serial.print(endereco);
//    Serial.print(" read email: ");
//    Serial.println(emailLido);
//  }
//
//  // email!!!! 16 bytes - 1000 posicoes
//  Serial.println();
//  for (int endereco = 0; endereco < 1000; endereco++) {
//    yield();
//    char email[64] = "jcmojj@gmail.com";
//    char emailLido[64];
//    Serial.print(" Get address");
//    Serial.print(endereco);
//    Serial.print(" and write email: ");
//    Serial.print(email);
//    mem.write(endereco, (byte*)email, sizeof(email));
//
//    memset(&emailLido[0], 32, sizeof(emailLido));
//    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
//    Serial.print(" --> From address ");
//    Serial.print(endereco);
//    Serial.print(" read email: ");
//    Serial.println(emailLido);
//  }
//}// FIM ---------------------------------------------------------------->>> memTest
//void Memory::emailTest() {
//  char emailTeste[] = "jcmojj@gmail.com";
//  memory.setUserEmail(emailTeste);
//  char emailBuffer[userEmailSpace + 1];
//  memory.getUserEmail(emailBuffer);
//  Serial.println("Testando Gravacao de Email");
//  Serial.print("emailTeste: "); Serial.println(emailTeste);
//  Serial.print("emailBuffer: "); Serial.println(emailBuffer);
//
//  Serial.println("");
//  char emailTeste2[] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.com";
//  memory.setUserEmail(emailTeste2);
//  Serial.print("emailTeste: "); Serial.println(emailTeste);
//  Serial.print("emailBuffer: "); Serial.println(emailBuffer);
//
//  Serial.println("");
//  memory.getUserEmail(emailBuffer);
//  Serial.print("emailTeste: "); Serial.println(emailTeste);
//  Serial.print("emailBuffer: "); Serial.println(emailBuffer);
//}
//void Memory::snTest() {
//  char sn[] = "ABCDEFfchgkvjhlbjd324&ˆ$#!@&*()/ sfd\fsdf\fdsf/";
//  memory.setSN(sn);
//  char snBuffer[serialNumberSpace + 1];
//  memory.getSN(sn);
//  Serial.println("Testando Gravacao de Serial Number");
//  Serial.print("sn: "); Serial.println(sn);
//  Serial.print("snBuffer: "); Serial.println(snBuffer);
//
//  Serial.println("");
//  char sn2[] = "snmojj@gmail.comsnmojj@gmail.comsnmojj@gmail.comsnmojj@gmail.com";
//  memory.setSN(sn2);
//  Serial.print("sn: "); Serial.println(sn);
//  Serial.print("snBuffer: "); Serial.println(snBuffer);
//
//  Serial.println("");
//  memory.getSN(sn2);
//  Serial.print("sn: "); Serial.println(sn);
//  Serial.print("snBuffer: "); Serial.println(snBuffer);
//}
//void Memory::preenchendoDrinksParaTeste() {
//  cleanDataMemory();
//  for (byte mes = 1; mes < 11 ; mes++) {
//    for (byte dia = 1; dia < 30 ; dia ++) {
//      yield();
//      drink.setValue(dia, mes, 1984, 9, 50, 30, 57, 'c', 111, 0, 0);
//      saveDrinkAtMemory();
//    }
//  }
//  Serial.println("Memoria Preenchida para Teste");
//}
//
//
//void Memory::saveDrinkAtMemory() {
//  yield();
//  byte nextPositionToSave = getNextPositionToWriteDrink();
//  byte nextPositionToDelete = getNextPositionToCleanDrink();
//  if ( (nextPositionToSave == nextPositionToDelete - 1) || ((nextPositionToSave == 255) && (nextPositionToDelete == 1)) ) {
//    cleanDrinkMemoryAtPosition(nextPositionToDelete);
//  }
//  setDrinkAtPosition(nextPositionToSave);
//  yield();
//}
//void Memory::lastDrinkWasSentToServerWithSucess() {
//  byte nextPositionToCleanDrink = getNextPositionToCleanDrink();
//  Serial.print("- nextPositionToCleanDrink: "); Serial.println(nextPositionToCleanDrink);
//  cleanDrinkMemoryAtPosition(nextPositionToCleanDrink);
//}
//byte Memory::getNextDrinkToSendToServer() {
//  byte positionToSendToServer = getNextPositionToReadDrink();
//  getDrinkFromPosition(positionToSendToServer);
//  _drink->setPositionToSendToServer(positionToSendToServer);
//  return positionToSendToServer;
//}
//
//void Memory::printDrinkFromPosition(byte position) {
//  getDrinkFromPosition(position);
//  _drink->print();
//}
//void Memory::getDrinkFromPosition(byte position) {
//  yield();
//  byte drinkArray[_drinkSize];
//  memset(&drinkArray[0], 48, _drinkSize);
//  int address =  dataMemoryBegin + _drinkSize * (position - 1);
//  mem.read(address, (byte*)drinkArray, _drinkSize);
//  address = 0;
//  _drink->setDia(drinkArray[address++]);
//  _drink->setMes(drinkArray[address++]);
//  int ano = ((int)(drinkArray[address++])) << 8;
//  ano += ((int)(drinkArray[address++]));
//  _drink->setAno(ano);
//  _drink->setHora(drinkArray[address++]);
//  _drink->setMinuto(drinkArray[address++]);
//  _drink->setSegundo(drinkArray[address++]);
//  int volumeMl = ((int)(drinkArray[address++])) << 8;
//  volumeMl += ((int)(drinkArray[address++]));
//  _drink->setVolumeMl(volumeMl);
//  _drink->setTipoSinal((char)drinkArray[address++]);
//  int sinal = ((int)(drinkArray[address++])) << 8;
//  sinal += ((int)(drinkArray[address++]));
//  _drink->setSinal(sinal);
//}
//void Memory::setDrinkAtPosition(byte position) {
//  yield();
//  byte drinkArray[_drinkSize];
//  memset(&drinkArray[0], 48, _drinkSize);
//  int address = 0;
//  drinkArray[address++] = _drink->getDia();
//  drinkArray[address++] = _drink->getMes();
//  drinkArray[address++] = (byte)((_drink->getAno()) >> 8);
//  drinkArray[address++] = (byte)(_drink->getAno());
//  drinkArray[address++] = _drink->getHora();
//  drinkArray[address++] = _drink->getMinuto();
//  drinkArray[address++] = _drink->getSegundo();
//  drinkArray[address++] = (byte)((_drink->getVolumeMl()) >> 8);
//  drinkArray[address++] = (byte)(_drink->getVolumeMl());
//  drinkArray[address++] = (byte)_drink->getTipoSinal();
//  drinkArray[address++] = (byte)((_drink->getSinal()) >> 8);
//  drinkArray[address++] = (byte)(_drink->getSinal());
//  address =  dataMemoryBegin + _drinkSize * (position - 1);
//  mem.write(address, (byte*)drinkArray, _drinkSize);
//}
//
//byte Memory::getLastUsedPositionFromBeginScan() {
//  byte readByteAnterior = 0;
//  byte readByteAtual = 128;
//  if ( (mem.read(dataMemoryBegin + 2) > 127) && mem.read(dataMemoryEnd + 1 - _drinkSize + 2) < 128 ) {
//    //Serial.print("Last Used Position From Begin Scan Address: ");
//    //Serial.println(255);
//    return 255;
//  }
//  for (int address = dataMemoryBegin ; address <= dataMemoryEnd; address += _drinkSize) {
//    yield();
//    readByteAnterior = readByteAtual;
//    readByteAtual = mem.read(address + 2);
//    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
//    if ( (readByteAtual > 127) && (readByteAnterior < 128) ) {
//      //Serial.print("Last Used Position From Begin Scan Address: ");
//      //Serial.println((address - dataMemoryBegin) / 12);
//      return (address - dataMemoryBegin) / 12;
//    }
//    yield();
//  }
//}
//byte Memory::getLastUsedPositionFromEndScan() {
//  byte readByteAnterior = 0;
//  byte readByteAtual = 128;
//  if ( (mem.read(dataMemoryBegin + 2) < 128) && mem.read(dataMemoryEnd + 1 - _drinkSize + 2) > 127 ) {
//    //Serial.print("Last Used Position From End Scan Address: ");
//    //Serial.println(1);
//    return 1;
//  }
//
//  for (int address = 1 + dataMemoryEnd - _drinkSize; address >= dataMemoryBegin; address = address - _drinkSize) {
//    yield();
//    readByteAnterior = readByteAtual;
//    readByteAtual = mem.read(address + 2);
//    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
//    if ( (readByteAtual > 127) && (readByteAnterior < 128) ) {
//      //Serial.print("Last Used Position From End Scan Address: ");
//      //Serial.println(2+((address - dataMemoryBegin) / 12));
//      return 2 + ((address - dataMemoryBegin) / 12);
//    }
//    yield();
//  }
//}
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
//void Memory::print() {
//  printInfo();
//  printData();
//}
//void Memory::printInfo() {
//  Serial.println("\nMemory\n");
//  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
//  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
//  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());
//  Serial.print("Memory Total Size (EEPROM):4096 bytes"); //Serial.println(memorySize);
//  yield();
//  Serial.print("\n");
//  Serial.print("Email Memory");       Serial.print(" from " );  Serial.print(userEmailBegin);             Serial.print(" to "); Serial.println(userEmailEnd);
//  Serial.print("Serial Number Memory"); Serial.print(" from " );  Serial.print(serialNumberBegin);          Serial.print(" to "); Serial.println(serialNumberEnd);
//  Serial.print("Drink Alarm Memory");   Serial.print(" from " );  Serial.print(drinkAlarmPositionsBegin);   Serial.print(" to "); Serial.println(drinkAlarmPositionsEnd);
//  Serial.print("Meal Alarm Memory");    Serial.print(" from " );  Serial.print(mealAlarmPositionsBegin);    Serial.print(" to "); Serial.println(mealAlarmPositionsEnd);
//  Serial.print("Cleaning Alarm Memory"); Serial.print(" from " );  Serial.print(cleaningAlarmPositionsBegin); Serial.print(" to "); Serial.println(cleaningAlarmPositionsEnd);
//  Serial.print("Data Memory");          Serial.print(" from " );  Serial.print(dataMemoryBegin);            Serial.print(" to "); Serial.println(dataMemoryEnd);
//  Serial.print("Water Memory Size ");   Serial.println(_drinkSize);
//  int memUsada = userEmailSpace + serialNumberSpace + drinkAlarmPositions * drinkAlarmPositionsSize + mealAlarmPositions * mealAlarmPositionsSize + cleaningAlarmPositions * cleaningAlarmPositionsSize + dataMemorySize;
//  Serial.print("\nMemoria Total Usada: ");  Serial.print(memUsada); Serial.print(" - "); Serial.print((((double)memUsada) / 4096.0) * 100, 2); Serial.println("%");
//  Serial.print("Memoria Total Livre: ");  Serial.print(4096 - memUsada);
//  yield();
//  printEmail();
//  printSerialNumber();
//  printDrinkAlarm();
//  printMealAlarm();
//  printCleaningAlarm();
//}
//void Memory::printData() {
//  yield();
//  uint8_t value = 0;
//  Serial.print("\n");
//  Serial.println("Data Memory");
//  Serial.print("(address= "); if (dataMemoryBegin < 100) {
//    Serial.print(" ");
//  } if (dataMemoryBegin < 10) {
//    Serial.print(" ");
//  } Serial.print(dataMemoryBegin); Serial.print(")");
//  Serial.print("(Position=  1)");
//  for (int address = dataMemoryBegin; address <= dataMemoryEnd; address++) {
//    yield();
//    value = mem.read(address);
//    if (value < 100) {
//      Serial.print(" ");
//    } if (value < 10) {
//      Serial.print(" ");
//    }
//    Serial.print(value, DEC);
//
//    if ((address + 1 - dataMemoryBegin) % _drinkSize == 0) {
//      Serial.print("-(address="); if (address < 100) {
//        Serial.print(" ");
//      } if (address < 10) {
//        Serial.print(" ");
//      } Serial.print(address); Serial.print(")");
//      Serial.println("");
//      if (address != dataMemoryEnd) {
//        Serial.print("(address="); if (address < 1000) {
//          Serial.print(" ");
//        } if (address < 100) {
//          Serial.print(" ");
//        } if (address < 10) {
//          Serial.print(" ");
//        } Serial.print(address + 1); Serial.print(")");
//        Serial.print("(Position="); if ((2 + (address - dataMemoryBegin) / _drinkSize) < 100) {
//          Serial.print(" ");
//        } if ((2 + (address - dataMemoryBegin) / _drinkSize) < 10) {
//          Serial.print(" ");
//        } Serial.print(2 + (address - dataMemoryBegin) / _drinkSize); Serial.print(")");
//      }
//      yield();
//    } else {
//      Serial.print("-");
//    }
//  }
//}
//void Memory::printEmail() {
//  uint8_t value = 0;
//  Serial.print("\n");
//  Serial.println("Email Memory");
//  Serial.print("(address="); if (userEmailBegin < 100) {
//    Serial.print(" ");
//  } if (userEmailBegin < 10) {
//    Serial.print(" ");
//  } Serial.print(userEmailBegin); Serial.print(")-");
//  for (int address = userEmailBegin; address <= userEmailEnd; address++) {
//    yield();
//    value = mem.read(address);
//    if (value < 100) {
//      Serial.print(" ");
//    } if (value < 10) {
//      Serial.print(" ");
//    }
//    Serial.print(value, DEC);
//    if ((address + 1) % 16 == 0) {
//      Serial.print("-(address="); if (address < 100) {
//        Serial.print(" ");
//      } if (address < 10) {
//        Serial.print(" ");
//      } Serial.print(address); Serial.print(")");
//      Serial.println("");
//      if (address != userEmailEnd) {
//        Serial.print("(address=");
//        if ((address + 1) < 100) {
//          Serial.print(" ");
//        } if ((address + 1) < 10) {
//          Serial.print(" ");
//        } Serial.print(address + 1);
//        Serial.print(")-");
//      }
//      yield();
//    } else {
//      Serial.print("-");
//    }
//  }
//}
//void Memory::printSerialNumber() {
//  uint8_t value = 0;
//  Serial.print("\n");
//  Serial.println("Serial Number Memory");
//  Serial.print("(address="); if (serialNumberBegin < 100) {
//    Serial.print(" ");
//  } if (serialNumberBegin < 10) {
//    Serial.print(" ");
//  } Serial.print(serialNumberBegin); Serial.print(")-");
//  for (int address = serialNumberBegin; address <= serialNumberEnd; address++) {
//    yield();
//    value = mem.read(address);
//    if (value < 100) {
//      Serial.print(" ");
//    } if (value < 10) {
//      Serial.print(" ");
//    }
//    Serial.print(value, DEC);
//    if ((address + 1) % 16 == 0) {
//      Serial.print("-(address="); if (address < 100) {
//        Serial.print(" ");
//      } if (address < 10) {
//        Serial.print(" ");
//      } Serial.print(address); Serial.print(")");
//      Serial.println("");
//      if (address != serialNumberEnd) {
//        Serial.print("(address=");
//        if ((address + 1) < 100) {
//          Serial.print(" ");
//        } if ((address + 1) < 10) {
//          Serial.print(" ");
//        } Serial.print(address + 1);
//        Serial.print(")-");
//      }
//      yield();
//    } else {
//      Serial.print("-");
//    }
//  }
//}
//void Memory::printAlarm(int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {
//  uint8_t value = 0;
//  Serial.print("\n");
//  Serial.println(" Alarm Memory");
//  Serial.print("(address="); if (AlarmPositionsBegin < 100) {
//    Serial.print(" ");
//  } if (AlarmPositionsBegin < 10) {
//    Serial.print(" ");
//  } Serial.print(AlarmPositionsBegin); Serial.print(")-");
//  byte AlarmPositionsEnd = (AlarmPositionsBegin+AlarmPositions*AlarmPositionsSize-1);
//  for (int address = AlarmPositionsBegin; address <= AlarmPositionsEnd; address++) {
//    yield();
//    value = mem.read(address);
//    if (value < 100) {
//      Serial.print(" ");
//    } if (value < 10) {
//      Serial.print(" ");
//    }
//    Serial.print(value, DEC);
//    if ((address + 1) % 16 == 0) {
//      Serial.print("-(address="); if (address < 100) {
//        Serial.print(" ");
//      } if (address < 10) {
//        Serial.print(" ");
//      } Serial.print(address); Serial.print(")");
//      Serial.println("");
//      if (address != AlarmPositionsEnd) {
//        Serial.print("(address=");
//        if ((address + 1) < 100) {
//          Serial.print(" ");
//        } if ((address + 1) < 10) {
//          Serial.print(" ");
//        } Serial.print(address + 1);
//        Serial.print(")-");
//      }
//      yield();
//    } else {
//      Serial.print("-");
//    }
//  }
//}
//void Memory::printDrinkAlarm() {
//  printAlarm(drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//void Memory::printMealAlarm() {
//  printAlarm(mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);  
//}
//void Memory::printCleaningAlarm() {
//  printAlarm(cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//
//void Memory::cleanMemory() {
//  yield();
//  cleanInfoMemory();
//  cleanDataMemory();
//}
//void Memory::cleanInfoMemory() {
//  Serial.print("Clean Info Memory");
//  byte cleanArray[30];
//  byte size = sizeof(cleanArray);
//  memset(&cleanArray[0], 0, size);
//  Serial.print("cleanArray: ");
//  for (int i = 0; i < sizeof(cleanArray); i++) {
//    Serial.print(cleanArray[i]); Serial.print("-");
//  }
//
//  byte cleanArray2[30];
//  byte size2 = sizeof(cleanArray2);
//  memset(&cleanArray2[0], 255, size2);
//  Serial.print("cleanArray2: ");
//  for (int i = 0; i < sizeof(cleanArray2); i++) {
//    Serial.print(cleanArray2[i]); Serial.print("-");
//  }
//
//  for (int address = infoByteBegin; address <= infoByteEnd; ) {
//    yield();
//    if ( address < (serialNumberEnd - size) ) {
//      mem.write(address, (byte*)cleanArray, size);
//      address = address + size;
//    } else if (address < serialNumberEnd) {
//      mem.write(address, 0);
//      address++;
//    } else if ( address < (infoByteEnd - size2) ) {
//      mem.write(address, (byte*)cleanArray2, size2);
//      address = address + size2;
//    } else {
//      mem.write(address, 255);
//      address++;
//    }
//    Serial.print("cleanInfoMemory-Address: "); Serial.println(address);
//  }
//  Serial.println("\nInfo has been clean!");
//
//}
//void Memory::cleanDataMemory() {
//  yield();
//  for (int address = dataMemoryBegin; address <= dataMemoryEnd; ) {
//    yield();
//    byte cleanArray[30];
//    byte size = sizeof(cleanArray);
//    memset(&cleanArray[0], 255, size);
//    if ( address < (infoByteEnd - size) ) {
//      mem.write(address, (byte*)cleanArray, size);
//      address = address + size;
//    } else {
//      mem.write(address, 255);
//      address++;
//    }
//  }
//  byte firstByte = 0;
//  //Importante
//  mem.write(dataMemoryBegin + 2, firstByte);
//  Serial.println("\nDrink data has been clean!");
//}
//void Memory::cleanDrinkMemoryAtPosition(byte position) {
//  yield();
//  if (position > 0 && position < 256) {
//    byte drinkArray[_drinkSize];
//    memset(&drinkArray[0], 128, _drinkSize);
//    int address =  dataMemoryBegin + _drinkSize * (position - 1);
//    mem.write(address, (byte*)drinkArray, _drinkSize);
//  }
//}
//
//void Memory::getUserEmail(char email[]) {
//  yield();
//  //  byte size = userEmailSpace+1;
//  //  char email[size];
//  memset(&email[0], 0, userEmailSpace + 1);
//  mem.readChars(userEmailBegin, email, userEmailSpace);
//}
//void Memory::setUserEmail(const char email[]) {
//  yield();
//  char emailCorreto[userEmailSpace + 1];
//  memset(&emailCorreto[0], 0, sizeof(emailCorreto));//limpando
//  Serial.print("sizeof(emailCorreto): "); Serial.println(sizeof(emailCorreto));
//  Serial.print("sizeof(email): "); Serial.println(sizeof(email));
//  strncpy(emailCorreto, email, sizeof(emailCorreto));
//  mem.writeChars(userEmailBegin, emailCorreto, userEmailSpace);
//}
//void Memory::getSN(char sn[]) {
//  yield();
//  //  byte size = userEmailSpace+1;
//  //  char email[size];
//  memset(&sn[0], 0, serialNumberSpace + 1);
//  mem.readChars(serialNumberBegin, sn, serialNumberSpace);
//}
//void Memory::setSN(const char sn[]) {
//  yield();
//  char snCorreto[serialNumberSpace + 1];
//  memset(&snCorreto[0], 0, sizeof(snCorreto));//limpando
//  Serial.print("sizeof(emailCorreto): "); Serial.println(sizeof(snCorreto));
//  Serial.print("sizeof(sn): "); Serial.println(sizeof(sn));
//  strncpy(snCorreto, sn, sizeof(snCorreto));
//  mem.writeChars(serialNumberBegin, snCorreto, serialNumberSpace);
//}
//
//byte Memory::getAlarmHourFromPosition            (byte position, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) { // mudar para private
//  return mem.read(AlarmPositionsBegin + (position - 1) * AlarmPositionsSize);
//}
//byte Memory::getAlarmMinuteFromPosition          (byte position, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) { // mudar para private
//  return mem.read(1+AlarmPositionsBegin + (position - 1) * AlarmPositionsSize);
//}
//byte Memory::getAlarmPositionQuantity                           (int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) { // a primeira posicao é 1 - 0 significa vazio
//  byte size = AlarmPositions * AlarmPositionsSize + 1;
//  byte Alarms[size];
//  memset(&Alarms[0], 0, size);
//  mem.read(AlarmPositionsBegin, Alarms, size);
//  byte positionQuantity = 0;
//  byte i = 0;
//  while ( (Alarms[i] != 255) && (i < size - 1) ) {
//    yield();
//    if ( (Alarms[i] != 255) && (Alarms[i + 1] != 255) ) {
//      positionQuantity++;
//    }
//    i++;
//    i++;
//  }
//  return positionQuantity;
//}
//byte Memory::findAlarmPositionFrom      (byte hour, byte minute, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {  // a primeira posicao é 1, 0 significa que nao encontrou (ou é vazio)
//  byte size = AlarmPositions * AlarmPositionsSize + 1;
//  byte Alarms[size];
//  memset(&Alarms[0], 0, size);
//  mem.read(AlarmPositionsBegin, Alarms, size);
//  byte i = 0;
//  byte position = 0;
//  while ( (i < size - 1) ) {
//    yield();
//    if ( (Alarms[i] == hour) && (Alarms[i + 1] == minute) ) {
//      position = (i + 2) / 2;
//    }
//    i++;
//    i++;
//  }
//  return position;
//}
//void Memory::cleanAlarmAllPosition                              (int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {
//  byte size = AlarmPositions * AlarmPositionsSize;
//  Serial.print("cleanAlarmAllPosition");
//  byte cleanArray[size];
//  memset(&cleanArray[0], 255, size);
//  mem.write(AlarmPositionsBegin, (byte*)cleanArray, size);
//}
//byte Memory::getAlarmNextAlarmPosition  (byte hour, byte minute, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {
//  byte AlarmPositionQuantity = getAlarmPositionQuantity(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  if (AlarmPositionQuantity == 0) {
//    return 0;
//  }
//  if (AlarmPositionQuantity == AlarmPositions) {
//    return 0;
//  }
//  byte posicao = 1;
//  if (hour == 0 && minute == 0) {
//    return posicao;
//  }
//  byte size = AlarmPositions * AlarmPositionsSize;
//  byte Alarms[size];
//  memset(&Alarms[0], 0, size);
//  mem.read(AlarmPositionsBegin, Alarms, size);
//  float horaProcurada = (float)hour + ((float)minute) / 60.0;
//  float horaEeprom = (float)Alarms[(posicao - 1) * 2] + ( (float)( Alarms[1 + (posicao - 1) * 2] ) ) / 60.0;
//  while ( (horaProcurada > horaEeprom) ) {
//    if( (posicao) == AlarmPositionQuantity ){
//      return 0;
//    }
//    posicao++;
//    horaEeprom = (float)Alarms[(posicao - 1) * 2] + ( (float)( Alarms[1 + (posicao - 1) * 2] ) ) / 60.0;
//  }
//  Serial.print(" -posicao return:"); Serial.println(posicao);
//  return posicao; 
//}
//byte Memory::getAlarmExactAlarmPosition (byte hour, byte minute, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {
//  byte AlarmPositionQuantity = getAlarmPositionQuantity(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  if (AlarmPositionQuantity == 0) {
//    return 0;
//  }
//  byte size = AlarmPositions * AlarmPositionsSize;
//  char Alarms[size];
//  memset(&Alarms[0], 0, size);
//  mem.readChars(AlarmPositionsBegin, Alarms, size);
//  byte posicao = 1;
//  float horaProcurada = (float)hour + ((float)minute) / 60.0;
//  float horaEeprom = (float)Alarms[(posicao - 1) * 2] + ( (float)( Alarms[1 + (posicao - 1) * 2] ) ) / 60.0;
//  while ( horaProcurada != horaEeprom ) {
//    if( (posicao-1) == (AlarmPositionQuantity + 1) ){
//      return 0;
//    }
//    posicao++;
//    horaEeprom = (float)Alarms[(posicao - 1) * 2] + ( (float)( Alarms[1 + (posicao - 1) * 2] ) ) / 60.0;
//  }
//  Serial.print("\n -posicao igual encontrada:"); Serial.print(posicao);
//  Serial.print(" -hora: "); Serial.print(hour);
//  Serial.print(" -minuto: "); Serial.println(minute);
//  return posicao; 
//}
//bool Memory::cleanAlarm                 (byte hour, byte minute, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {
//  byte AlarmExactAlarmPosition = getAlarmExactAlarmPosition(hour, minute, AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  if( AlarmExactAlarmPosition == 0 ){
//    return false;
//  }
//  if (AlarmExactAlarmPosition == AlarmPositions) {
//    int hourminute = (((int)255)<<8) + (int)255;
//    mem.writeInt(AlarmPositionsBegin+(AlarmPositions-1)*AlarmPositionsSize, hourminute);
//    return true;
//  }
//
//  byte size = AlarmPositions * AlarmPositionsSize;
//  byte Alarms[size];
//  memset(&Alarms[0], 0, size);
//  mem.read(AlarmPositionsBegin, Alarms, size);
//  byte AlarmPositionQuantity = getAlarmPositionQuantity(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  byte positionHour = (AlarmExactAlarmPosition-1)*AlarmPositionsSize;
//  byte positionMinute = (AlarmExactAlarmPosition-1)*AlarmPositionsSize+1;
//  while( positionHour != (AlarmPositionQuantity-1)*AlarmPositionsSize){
//    Alarms[positionHour]   = Alarms[positionHour+2];
//    Alarms[positionMinute] = Alarms[positionMinute+2];
//    positionHour++;
//    positionHour++;
//    positionMinute++;
//    positionMinute++;
//  }
//  Alarms[positionHour]   = 255;
//  Alarms[positionMinute] = 255;
//  mem.write(AlarmPositionsBegin, Alarms, size);
//  return true; 
//}
//bool Memory::addAlarm                   (byte hour, byte minute, int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {// falta verificar se ja existe
//  if( (hour>23) || (minute>59) ){
//    return false;
//  }
//  if( getAlarmExactAlarmPosition(hour, minute, AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize) != 0 ){
//    return false;
//  }
//  byte AlarmPositionQuantity = getAlarmPositionQuantity(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  if (AlarmPositionQuantity == AlarmPositions) {
//    return false;
//  }
//  if (AlarmPositionQuantity == 0) {
//    int hourminute = (((int)minute)<<8) + (int)hour;
//    mem.writeInt(AlarmPositionsBegin, hourminute);
//    return true;
//  }
//  byte size = AlarmPositions * AlarmPositionsSize;
//  byte Alarms[size];
//  memset(&Alarms[0], 0, size);
//  mem.read(AlarmPositionsBegin, Alarms, size);
//  byte AlarmNextAlarmPosition = getAlarmNextAlarmPosition(hour,minute, AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  byte positionHour = AlarmPositionQuantity*AlarmPositionsSize;
//  byte positionMinute = AlarmPositionQuantity*AlarmPositionsSize + 1;
//  while( positionHour != (AlarmNextAlarmPosition-1)*2){
//    Alarms[positionHour]   = Alarms[positionHour-2];
//    Alarms[positionMinute] = Alarms[positionMinute-2];
//    positionHour--;
//    positionHour--;
//    positionMinute--;
//    positionMinute--;
//  }
//  Alarms[positionHour] = hour;
//  Alarms[positionMinute] = minute;
//  mem.write(AlarmPositionsBegin, Alarms, size);
//  return true; 
//}
//void Memory::AlarmTest                                          (int AlarmPositionsBegin, byte AlarmPositions, byte AlarmPositionsSize) {
// printInfo();
// cleanAlarmAllPosition(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  int sinal = 1;
//  int sinal2 = 1;
//  byte minuto = 30;
//  byte hora = 0;
//  if(addAlarm(10,30,AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize)){
//    Serial.println(" adicionado com sucesso");
//  }
//  if(addAlarm(10,30,AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize)){
//    Serial.println(" adicionado com sucesso");
//  }else{
//    Serial.println(" nao adicionado com sucesso");    
//  }
//  
//  for(byte i =0;i<64;i++){
//    if(i%2 == 0){ sinal=1;}else{sinal=-1;}
//    if(i%3==0){sinal2 =-1;}
//    if(i%5==0){sinal2 = 1;}
//    if(i%24 == 0){ minuto = 30;}
//    if(i%4 == 0 ){ hora++;}
//    hora = hora + sinal2;
//    minuto = minuto+i*sinal;
//    addAlarm(hora,minuto,AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//    printAlarm(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
////    Serial.print("\nComparacao: printDrinkAlarm() esta abaixo");
////    printDrinkAlarm();
//  }
//  cleanAlarm(mem.read(AlarmPositionsBegin+62),mem.read(AlarmPositionsBegin+63),AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  printAlarm(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  cleanAlarm(10,10,AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  printAlarm(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  for(int i = 0;i<9;i++){
//    cleanAlarm(mem.read(AlarmPositionsBegin+18),mem.read(AlarmPositionsBegin+19),AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//    printAlarm(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  }
//  for(int i = 0;i<10;i++){
//    cleanAlarm(mem.read(AlarmPositionsBegin+6),mem.read(AlarmPositionsBegin+7),AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//    printAlarm(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  }  
//  for(int i = 0;i<12;i++){
//    cleanAlarm(mem.read(AlarmPositionsBegin),mem.read(AlarmPositionsBegin+1),AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//    printAlarm(AlarmPositionsBegin, AlarmPositions, AlarmPositionsSize);
//  }  
//  printInfo();
//}
//
//byte Memory::getDrinkAlarmHourFromPosition  (byte position){
//  return getAlarmHourFromPosition(position, drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//byte Memory::getDrinkAlarmMinuteFromPosition(byte position){
//  return getAlarmMinuteFromPosition(position, drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize); 
//}
//byte Memory::getDrinkAlarmPositionQuantity  (){
//  return getAlarmPositionQuantity(drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//byte Memory::findDrinkAlarmPositionFrom     (byte hour, byte minute){
//  return findAlarmPositionFrom(hour, minute,drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//void Memory::cleanDrinkAlarmAllPosition     (){
//  cleanAlarmAllPosition(drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//byte Memory::getDrinkAlarmNextAlarmPosition (byte hour, byte minute){
//  return getAlarmNextAlarmPosition(hour, minute,drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//byte Memory::getDrinkAlarmExactAlarmPosition(byte hour, byte minute){
//  return getAlarmExactAlarmPosition(hour, minute,drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//bool Memory::cleanDrinkAlarm                (byte hour, byte minute){
//  return cleanAlarm(hour, minute,drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//bool Memory::addDrinkAlarm                  (byte hour, byte minute){
//  return addAlarm(hour, minute,drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}
//void Memory::drinkAlarmTest                 (){
//  AlarmTest(drinkAlarmPositionsBegin, drinkAlarmPositions, drinkAlarmPositionsSize);
//}      
//
//byte Memory::getMealAlarmHourFromPosition  (byte position){
//  return getAlarmHourFromPosition(position, mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//byte Memory::getMealAlarmMinuteFromPosition(byte position){
//  return getAlarmMinuteFromPosition(position, mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize); 
//}
//byte Memory::getMealAlarmPositionQuantity  (){
//  return getAlarmPositionQuantity(mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//byte Memory::findMealAlarmPositionFrom     (byte hour, byte minute){
//  return findAlarmPositionFrom(hour, minute,mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//void Memory::cleanMealAlarmAllPosition     (){
//  cleanAlarmAllPosition(mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//byte Memory::getMealAlarmNextAlarmPosition (byte hour, byte minute){
//  return getAlarmNextAlarmPosition(hour, minute,mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//byte Memory::getMealAlarmExactAlarmPosition(byte hour, byte minute){
//  return getAlarmExactAlarmPosition(hour, minute,mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//bool Memory::cleanMealAlarm                (byte hour, byte minute){
//  return cleanAlarm(hour, minute,mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//bool Memory::addMealAlarm                  (byte hour, byte minute){
//  return addAlarm(hour, minute,mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}
//void Memory::mealAlarmTest                 (){
//  AlarmTest(mealAlarmPositionsBegin, mealAlarmPositions, mealAlarmPositionsSize);
//}      
//
//byte Memory::getCleaningAlarmHourFromPosition  (byte position){
//  return getAlarmHourFromPosition(position, cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//byte Memory::getCleaningAlarmMinuteFromPosition(byte position){
//  return getAlarmMinuteFromPosition(position, cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize); 
//}
//byte Memory::getCleaningAlarmPositionQuantity  (){
//  return getAlarmPositionQuantity(cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//byte Memory::findCleaningAlarmPositionFrom     (byte hour, byte minute){
//  return findAlarmPositionFrom(hour, minute,cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//void Memory::cleanCleaningAlarmAllPosition     (){
//  cleanAlarmAllPosition(cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//byte Memory::getCleaningAlarmNextAlarmPosition (byte hour, byte minute){
//  return getAlarmNextAlarmPosition(hour, minute,cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//byte Memory::getCleaningAlarmExactAlarmPosition(byte hour, byte minute){
//  return getAlarmExactAlarmPosition(hour, minute,cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//bool Memory::cleanCleaningAlarm                (byte hour, byte minute){
//  return cleanAlarm(hour, minute,cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//bool Memory::addCleaningAlarm                  (byte hour, byte minute){
//  return addAlarm(hour, minute,cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}
//void Memory::cleaningAlarmTest                 (){
//  AlarmTest(cleaningAlarmPositionsBegin, cleaningAlarmPositions, cleaningAlarmPositionsSize);
//}      
///* ------------------------------------------- RTC ------------------------------------------- */
//void      Memory::rtcBegin() {
//  Serial.print("RTC compiled: ");
//  Serial.print(__DATE__);
//  Serial.print(" ");
//  Serial.println(__TIME__);
//  //--------RTC SETUP ------------
//
//  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
//  //    printTime(const compiled);
//  Serial.println();
//
//  if (!rtc.IsDateTimeValid())
//  {
//    // Common Cuases:
//    //    1) first time you ran and the device wasn't running yet
//    //    2) the battery on the device is low or even missing
//
//    Serial.println("RTC lost confidence in the DateTime!");
//
//    // following line sets the RTC to the date & time this sketch was compiled
//    // it will also reset the valid flag internally unless the Rtc device is
//    // having an issue
//
//    rtc.SetDateTime(compiled);
//  }
//
//  if (!rtc.GetIsRunning())
//  {
//    Serial.println("RTC was not actively running, starting now");
//    rtc.SetIsRunning(true);
//  }
//  yield();
//  RtcDateTime now = rtc.GetDateTime();
//  if (now < compiled)
//  {
//    Serial.println("RTC is older than compile time!  (Updating DateTime)");
//    rtc.SetDateTime(compiled);
//  }
//  else if (now > compiled)
//  {
//    Serial.println("RTC is newer than compile time. (this is expected)");
//  }
//  else if (now == compiled)
//  {
//    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
//  }
//
//  // never assume the Rtc was last configured by you, so
//  // just clear them to your needed state
//  rtc.Enable32kHzPin(false);
//  //    rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
//  rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmBoth);
//  printTemperature();
//  updateClock();
//  //  atualizarAlarmes();
//}
//void      Memory::updateClock() {
//  now = rtc.GetDateTime();
//  //  printTime(const now);
//}
//void      Memory::setClockDateTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, uint8_t hour, uint8_t minute, uint8_t second) {
//  rtc.SetIsRunning(false);
//  rtc.SetDateTime(RtcDateTime(year, month, dayOfMonth, hour, minute, second));
//  rtc.SetIsRunning(true);
//  if (isDateTimeValid()) {
//    Serial.println("Hora Atualizada com Sucesso");
//  }
//  printNowDateTime();
//}
//void      Memory::printDateTime(const RtcDateTime& dt) {
//  char datestring[20];
//  snprintf_P(datestring,
//             countof(datestring),
//             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
//             dt.Month(),
//             dt.Day(),
//             dt.Year(),
//             dt.Hour(),
//             dt.Minute(),
//             dt.Second() );
//  Serial.print(datestring);
//}
//void      Memory::printNowDateTime() {
//  RtcDateTime dt = rtc.GetDateTime();
//  printDateTime(dt);
//
//}
//float     Memory::getTemperature() {
//  RtcTemperature temp = rtc.GetTemperature();
//  Serial.print("Temperature: ");
//  Serial.print(temp.AsFloat());
//  Serial.println("C");
//  return temp.AsFloat();
//}
//byte      Memory::getTemperatureFromFloatToByte(float tempFloat) {
//  //  float tempFloat = rtc.GetTemperature().AsFloat();
//  float decimal = tempFloat - (int)tempFloat;
//  byte temp;
//  if (tempFloat >= 0) {
//    temp = (byte)tempFloat + 64 * 1; //se for positivo
//  } else {
//    temp = (byte)tempFloat + 64 * 0; //se for negativo
//  }
//  if ((decimal > 0.25) && (decimal < 0.75)) {
//    temp = temp + 128 * 1; // se for 0.5
//  } else {
//    temp = temp + 128 * 0; // se for 0.0
//  }
//  return temp;
//}
//float     Memory::getTemperatureFromByteToFloat(byte temp) {
//  //  float tempFloat = rtc.GetTemperature().AsFloat();
//  float floatTemp = 0;
//  bool isPositive = 0;
//  bool isHalfDecimal = 0;
//  if ( temp > 127) {
//    isHalfDecimal = 1;
//    temp = temp - 128;
//  }
//  if ( temp > 63) {
//    isPositive = 1;
//    temp = temp - 64;
//  }
//  return ((float)temp + 0.5 * ((float)isHalfDecimal)) * (2 * ((float)isPositive) - 1);
//}
//void      Memory::printTemperature() {
//  Serial.print("Temperature: ");
//  Serial.print( (rtc.GetTemperature()).AsFloat());
//  Serial.println("C");
//}
//bool      Memory::isDateTimeValid() {
//
//  Serial.println("RTC lost confidence in the DateTime!");
//  return rtc.IsDateTimeValid();
//}
//uint16_t  Memory::getYear() {
//  return now.Year();
//}
//uint8_t   Memory::getMonth() {
//  return now.Month();
//}
//uint8_t   Memory::getDay() {
//  return now.Day();
//}
//uint8_t   Memory::getHour() {
//  return now.Hour();
//}
//uint8_t   Memory::getMinute() {
//  return now.Minute();
//}
//uint8_t   Memory::getSecond() {
//  return now.Second();
//}

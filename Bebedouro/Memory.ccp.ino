#include "Memory.h"
#include "Drink.h"

//Memory::Memory(int size, Drink &drink, byte drinkSize) {
////  Serial.begin(9600);
//  _drink = &drink;
//  _size = size;
//  _drinkSize = drinkSize;
//}
Memory::Memory(Drink &drink, byte drinkSize) {
  Serial.begin(115200);
  _drink = &drink;
  _drinkSize = drinkSize;
}
void Memory::memoryTest() {
  //  memTest();// longo
  //  print();
  //  emailTest();
  //  print();
//    cleanMemory();
  print();
  preenchendoDrinksParaTeste();
  print();
  //  getDrinkAlarmPositionQuantity();
  //  print();
  //  memTest();// longo
  //  print();
}
void Memory::memTest() {
  Serial.println("\n REALIZANDO TESTE DO EEPROM DO RTC3231");
  // read and write byte
  Serial.println("Write 42 to address 12");
  mem.write(12, 42);
  Serial.println("Read byte from address 12 ...");
  byte b = mem.read(12);
  byte b1;
  Serial.print("... read: ");
  Serial.println(b, DEC);
  Serial.println();
  for (int address = 0; address != 255; address++) {
    yield();
    Serial.print("Write ");
    Serial.print((byte)((byte)address + (byte)100));
    Serial.print(" to address ");
    Serial.print(address);
    mem.write(address + 100, (byte)address);
    Serial.print(" ---> Read byte from address ");
    Serial.print(address);
    Serial.print("...   ");
    b1 = mem.read(address);
    Serial.print("... read: ");
    Serial.print(b, DEC);
    yield();
    if (b1 == b1) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }

  // read and write byte
  Serial.println("\nWrite 'a' to address 12");
  mem.write(12, (byte)'a');
  Serial.println("Read char from address 12 ...");
  char c = (char)mem.read(12);
  char c1;
  Serial.print("... read: ");
  Serial.println(c);
  Serial.println();
  for (int address = 32; address != 126; address++) {
    yield();
    c = (char)address;
    Serial.print("Write ");
    Serial.print(c);
    Serial.print(" to address ");
    Serial.print(address);
    mem.write(address, (byte)c);
    Serial.print(" ---> Read byte from address ");
    Serial.print(address);
    Serial.print("...   ");
    c1 = (char)mem.read(address);
    Serial.print("... read: ");
    Serial.print(c1);
    yield();
    if (c == c1) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }

  // read and write integer
  Serial.println();
  Serial.println("Write 65000 to address 15");
  mem.writeInt(15, 65000);
  Serial.println("Read integer from address 15 ...");
  unsigned int i = mem.readInt(15);
  unsigned int i1;
  Serial.print("... read: ");
  Serial.println(i, DEC);
  Serial.println();
  for (unsigned int value = 16; value != 65536; value = value * 2) {
    yield();
    i = value;
    Serial.print("Write ");
    Serial.print(i);
    Serial.print(" to address ");
    Serial.print(value / 16 - 1);
    mem.writeInt(value / 16 - 1, value);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value / 16 - 1);
    Serial.print("...   ");
    i1 = mem.readInt(value / 16 - 1);
    Serial.print("... read: ");
    Serial.print(i1);
    yield();
    if (i == i1) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }

  // read and write long
  Serial.println();
  Serial.println("Write 1111111111 to address 31");
  mem.writeLong(31, 1111111111);
  Serial.println("Read long from address 31 ...");
  unsigned long l2 = mem.readLong(31);
  unsigned long l21;
  Serial.print("... read: ");
  Serial.println(l2, DEC);
  Serial.println();
  Serial.println();
  for (unsigned int value = 16; value != 65536; value = value * 2) {
    yield();
    l2 = value * value;
    Serial.print("Write ");
    Serial.print(l2, DEC);
    Serial.print(" to address ");
    Serial.print(value / 16 - 1);
    mem.writeLong(value / 16 - 1, l2);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value / 16 - 1);
    Serial.print("...   ");
    l21 = mem.readLong(value / 16 - 1);
    Serial.print("... read: ");
    Serial.print(l21, DEC);
    yield();
    if (l2 == l21) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }
  for (unsigned int value = 16; value != 65536; value = value * 2) {
    yield();
    l2 = value * value;
    Serial.print("Write ");
    Serial.print(l2, DEC);
    Serial.print(" to address ");
    Serial.print(value / 16 + 4);
    mem.writeLong(value / 16 + 4, l2);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value / 16 + 4);
    Serial.print("...   ");
    l21 = mem.readLong(value / 16 + 4);
    Serial.print("... read: ");
    Serial.print(l21, DEC);
    yield();
    if (l2 == l21) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }

  // read and write float
  Serial.println();
  Serial.println("Write 3.1415926535897932384626433832 to address 40");
  mem.writeFloat(40, 3.1415926535897932384626433832);
  Serial.println("Read float from address 40 ...");
  float f = mem.readFloat(40);
  float f1;
  Serial.print("... read: ");
  Serial.println(f, DEC);
  Serial.println();
  for (unsigned int value = 16; value != 65536; value = value * 2) {
    yield();
    float ifvalue = (float) value;
    float i1value = 128.0 / ifvalue;
    f = 3.141592  + i1value;
    Serial.print("Write ");
    Serial.print(f, DEC);
    Serial.print(" to address ");
    Serial.print(value / 16 - 1);
    mem.writeFloat(value / 16 - 1, f);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value / 16 - 1);
    Serial.print("...   ");
    f1 = mem.readFloat(value / 16 - 1);
    Serial.print("... read: ");
    Serial.print(f1, DEC);
    yield();
    if (f == f1) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }

  // read and write double
  Serial.println();
  Serial.println("Write 3.1415926535897932384626433832 to address 40");
  mem.writeDouble(40, 3.1415926535897932384626433832);
  Serial.println("Read double from address 40 ...");
  double d = mem.readDouble(40);
  double d1;
  Serial.print("... read: ");
  Serial.println(d, DEC);
  Serial.println();
  for (unsigned int value = 16; value != 65536; value = value * 2) {
    yield();
    double idvalue = (double) value;
    double iddvalue = 128.0 / idvalue;
    d = 3.1415926535897932384626433832  + iddvalue;
    Serial.print("Write ");
    Serial.print(d, DEC);
    Serial.print(" to address ");
    Serial.print(value / 16 - 1);
    mem.writeDouble(value / 16 - 1, d);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value / 16 - 1);
    Serial.print("...   ");
    d1 = mem.readDouble(value / 16 - 1);
    Serial.print("... read: ");
    Serial.print(d1, DEC);
    yield();
    if (d == d1) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }
  char arrayPronto[190];
  // read and write char
  Serial.println();
  Serial.print("Write chars: '");
  char msg[] = "This is a message";
  Serial.print(msg);
  Serial.println("' to address 200");
  mem.writeChars(200, msg, sizeof(msg));
  Serial.println("Read chars from address 200 ...");
  char msg2[30];
  mem.readChars(200, msg2, sizeof(msg2));
  Serial.print("... read: '");
  Serial.print(msg2);
  Serial.println("'");
  Serial.println();
  char letra1[2]; letra1[1] = '\0';
  char letra2[2]; letra2[1] = '\0';
  for (int address = 32; address != 126; address++) {
    yield();
    arrayPronto[2 * (address - 32)] = (char)address;
    arrayPronto[2 * (address - 32) + 1] = (char)address;
    letra1[0] = (char)address;
    Serial.print("Write ");
    Serial.print(letra1);
    Serial.print(" to address ");
    Serial.print(address);
    mem.writeChars(address, letra1, sizeof(letra1));
    Serial.print(" ---> Read letras from address ");
    Serial.print(address);
    Serial.print("...   ");
    mem.readChars(address, letra2, sizeof(letra2));
    Serial.print("... read: ");
    Serial.print(letra2);
    yield();
    if (letra1[0] == letra2[0]) {
      Serial.println(" --> OK");
    } else {
      Serial.println(" --> ERRO");
    }
  }

  Serial.println();
  arrayPronto[sizeof(arrayPronto) - 1] = '\0';
  arrayPronto[sizeof(arrayPronto) - 2] = 'f';
  Serial.print("ArrayPronto:");
  Serial.print("size: ");
  Serial.println(sizeof(arrayPronto));
  Serial.print("Array: ");
  Serial.println(arrayPronto);
  Serial.print("arrayPronto[ "); Serial.print(sizeof(arrayPronto) - 1); Serial.print("]: ");
  Serial.println(arrayPronto[sizeof(arrayPronto) - 1]);
  int  maiorOld = 0;
  char arrayProntoBig[10 * sizeof(arrayPronto)];
  for (int i = 0; i < sizeof(arrayPronto); i++) {
    for (int j = 0; j < 10; j++) {
      arrayProntoBig[i * 10 + j] = arrayPronto[i];
      maiorOld++;
    }
  }
  Serial.println(arrayProntoBig);
  int maiorNew = 0;
  yield();
  while ( (arrayProntoBig[maiorNew] != '\0') ) {
    maiorNew++;
  }
  Serial.print("MaiorOld posicao ocupada de arrayProntoBig é ");
  Serial.println(maiorOld);
  Serial.print("MaiorNew posicao ocupada de arrayProntoBig é ");
  Serial.println(maiorNew);
  for (int i = maiorNew - 10; i < maiorOld; i++) {
    yield();
    Serial.print("arrayProntoBig[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(arrayProntoBig[i]);
    arrayProntoBig[i] = i - maiorNew;
    Serial.print("----->(byte)arrayProntoBig[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print((byte)arrayProntoBig[i]);
    Serial.println();
  }
  arrayProntoBig[maiorOld - 1] = '\0';
  Serial.print("(byte)arrayProntoBig[");
  Serial.print(maiorOld - 1);
  Serial.print("]=");
  Serial.print((byte)arrayProntoBig[i]);
  Serial.print("<--");

  //----------------------- 30 bytes
  byte pos30Read[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9};
  Serial.println();
  Serial.print("30pos\nsize:");
  Serial.println(sizeof(pos30Read));

  // read bytes with multiple steps
  Serial.println("Read 30 single bytes starting at address 1000");
  Serial.print("\nWrite 30pos(");
  for (int i = 0; i < sizeof(pos30Read); i++) {
    Serial.print(pos30Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos30Read, sizeof(pos30Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos30byte;
  for ( int i = 0; i < sizeof(pos30Read); i++) {
    yield();
    byte pos30byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos30byte);
    if (pos30Read[i] == pos30byte) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();

  // read bytes with multiple steps
  Serial.print("\nWrite 30pos(");
  for (int i = 0; i < sizeof(pos30Read); i++) {
    Serial.print(pos30Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 30 bytes with one operation at address 1000");
  byte pos30Write[sizeof(pos30Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos30Write[0], 32, sizeof(pos30Write));
  mem.read(1000, pos30Write, sizeof(pos30Write));

  for ( int i = 0; i < sizeof(pos30Write); i++) {
    yield();
    byte pos30byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos30Write[i]);
    if (pos30Read[i] == pos30Write[i]) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();
  //------------------------------- 32 bytes


  byte pos32Read[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 0, 0};
  Serial.println();
  Serial.print("32pos\nsize:");
  Serial.println(sizeof(pos32Read));

  // read bytes with multiple steps
  Serial.println("Read 32 single bytes starting at address 1000");
  Serial.print("\nWrite 32pos(");
  for (int i = 0; i < sizeof(pos32Read); i++) {
    Serial.print(pos32Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos32Read, sizeof(pos32Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos32byte;
  for ( int i = 0; i < sizeof(pos32Read); i++) {
    yield();
    byte pos32byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos32byte);
    if (pos32Read[i] == pos32byte) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();

  // read bytes with multiple steps
  Serial.print("\nWrite 32pos(");
  for (int i = 0; i < sizeof(pos32Read); i++) {
    Serial.print(pos32Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 32 bytes with one operation at address 1000");
  byte pos32Write[sizeof(pos32Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos32Write[0], 32, sizeof(pos32Write));
  mem.read(1000, pos32Write, sizeof(pos32Write));

  for ( int i = 0; i < sizeof(pos32Write); i++) {
    yield();
    byte pos32byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos32Write[i]);
    if (pos32Read[i] == pos32Write[i]) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();
  //------------------------------- 33 bytes

  byte pos33Read[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 0, 0, 0};
  Serial.println();
  Serial.print("33pos\nsize:");
  Serial.println(sizeof(pos33Read));

  // read bytes with multiple steps
  Serial.println("Read 33 single bytes starting at address 1000");
  Serial.print("\nWrite 33pos(");
  for (int i = 0; i < sizeof(pos33Read); i++) {
    Serial.print(pos33Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos33Read, sizeof(pos33Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos33byte;
  for ( int i = 0; i < sizeof(pos33Read); i++) {
    yield();
    byte pos33byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos33byte);
    if (pos33Read[i] == pos33byte) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();

  // read bytes with multiple steps
  Serial.print("\nWrite 33pos(");
  for (int i = 0; i < sizeof(pos33Read); i++) {
    Serial.print(pos33Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 33 bytes with one operation at address 1000");
  byte pos33Write[sizeof(pos33Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos33Write[0], 33, sizeof(pos33Write));
  mem.read(1000, pos33Write, sizeof(pos33Write));

  for ( int i = 0; i < sizeof(pos33Write); i++) {
    yield();
    byte pos33byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos33Write[i]);
    if (pos33Read[i] == pos33Write[i]) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();
  //----------------------- 80 bytes

  byte pos80Read[] = {  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
                        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3,
                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
                        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7
                     };
  Serial.println();
  Serial.print("80pos\nsize:");
  Serial.println(sizeof(pos80Read));

  // read bytes with multiple steps
  Serial.println("Read 80 single bytes starting at address 1000");
  Serial.print("\nWrite 80pos(");
  for (int i = 0; i < sizeof(pos80Read); i++) {
    Serial.print(pos80Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos80Read, sizeof(pos80Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos80byte;
  for ( int i = 0; i < sizeof(pos80Read); i++) {
    yield();
    byte pos80byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos80byte);
    if (pos80Read[i] == pos80byte) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();

  // read bytes with multiple steps
  Serial.print("\nWrite 80pos(");
  for (int i = 0; i < sizeof(pos80Read); i++) {
    Serial.print(pos80Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 80 bytes with one operation at address 1000");
  byte pos80Write[sizeof(pos80Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos80Write[0], 80, sizeof(pos80Write));
  mem.read(1000, pos80Write, sizeof(pos80Write));

  for ( int i = 0; i < sizeof(pos80Write); i++) {
    yield();
    byte pos80byte = mem.read(1000 + i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos80Write[i]);
    if (pos80Read[i] == pos80Write[i]) {
      Serial.print(" --> OK   ///   ");
    } else {
      Serial.print(" --> ERRO ///   ");
    }
    if ((i + 1) % 3 == 0) {
      Serial.println();
    }
  }
  Serial.println();

  // email!!!! 16 bytes
  Serial.println();
  Serial.println("16 bytes");
  for (int endereco = 0; endereco < 64; endereco++) {
    yield();
    char email[64] = "jcmojj@gmail.com";
    char emailLido[64];
    Serial.print(" Get address");
    Serial.print(endereco);
    Serial.print(" and write email: ");
    Serial.print(email);
    mem.write(endereco, (byte*)email, sizeof(email));

    memset(&emailLido[0], 32, sizeof(emailLido));
    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
    Serial.print(" --> From address ");
    Serial.print(endereco);
    Serial.print(" read email: ");
    Serial.print(emailLido);

    Serial.print("  posicao do zero é ");
    int pos = 0;
    while ( emailLido[pos] != '\0') {
      pos++;
    }
    Serial.println(pos);
  }

  // email!!!! 32 bytes
  Serial.println();
  for (int endereco = 0; endereco < 64; endereco++) {
    yield();
    char email[64] = "jcmojj@gmail.comjcmojj@gmail.com";
    char emailLido[64];
    Serial.print(" Get address");
    Serial.print(endereco);
    Serial.print(" and write email: ");
    Serial.print(email);
    mem.write(endereco, (byte*)email, sizeof(email));

    memset(&emailLido[0], 32, sizeof(emailLido));
    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
    Serial.print(" --> From address ");
    Serial.print(endereco);
    Serial.print(" read email: ");
    Serial.println(emailLido);
  }

  // email!!!! 48 bytes
  Serial.println();
  for (int endereco = 0; endereco < 64; endereco++) {
    yield();
    char email[64] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.com";
    char emailLido[64];
    Serial.print(" Get address");
    Serial.print(endereco);
    Serial.print(" and write email: ");
    Serial.print(email);
    mem.write(endereco, (byte*)email, sizeof(email));

    memset(&emailLido[0], 32, sizeof(emailLido));
    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
    Serial.print(" --> From address ");
    Serial.print(endereco);
    Serial.print(" read email: ");
    Serial.println(emailLido);
  }

  // email!!!! 64 bytes
  Serial.println();
  for (int endereco = 0; endereco < 64; endereco++) {
    yield();
    char email[64] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.co";
    char emailLido[64];
    Serial.print(" Get address");
    Serial.print(endereco);
    Serial.print(" and write email: ");
    Serial.print(email);
    mem.write(endereco, (byte*)email, sizeof(email));

    memset(&emailLido[0], 32, sizeof(emailLido));
    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
    Serial.print(" --> From address ");
    Serial.print(endereco);
    Serial.print(" read email: ");
    Serial.println(emailLido);
  }

  // email!!!! 65 bytes
  Serial.println();
  for (int endereco = 0; endereco < 65; endereco++) {
    yield();
    char email[65] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.com";
    char emailLido[65];
    Serial.print(" Get address");
    Serial.print(endereco);
    Serial.print(" and write email: ");
    Serial.print(email);
    mem.write(endereco, (byte*)email, sizeof(email));

    memset(&emailLido[0], 32, sizeof(emailLido));
    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
    Serial.print(" --> From address ");
    Serial.print(endereco);
    Serial.print(" read email: ");
    Serial.println(emailLido);
  }

  // email!!!! 16 bytes - 1000 posicoes
  Serial.println();
  for (int endereco = 0; endereco < 1000; endereco++) {
    yield();
    char email[64] = "jcmojj@gmail.com";
    char emailLido[64];
    Serial.print(" Get address");
    Serial.print(endereco);
    Serial.print(" and write email: ");
    Serial.print(email);
    mem.write(endereco, (byte*)email, sizeof(email));

    memset(&emailLido[0], 32, sizeof(emailLido));
    mem.read(endereco, (byte*)emailLido, sizeof(emailLido));
    Serial.print(" --> From address ");
    Serial.print(endereco);
    Serial.print(" read email: ");
    Serial.println(emailLido);


  }
  emailTest();
}// FIM ---------------------------------------------------------------->>> memTest


void  Memory::emailTest() {
  char emailTeste[] = "jcmojj@gmail.com";
  memory.setUserEmail(emailTeste);
  char emailBuffer[userEmailSpace + 1];
  memory.getUserEmail(emailBuffer);
  Serial.println("Testando Gravacao de Email");
  Serial.print("emailTeste: "); Serial.println(emailTeste);
  Serial.print("emailBuffer: "); Serial.println(emailBuffer);

  Serial.println("");
  char emailTeste2[] = "jcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.comjcmojj@gmail.com";
  memory.setUserEmail(emailTeste2);
  Serial.print("emailTeste: "); Serial.println(emailTeste);
  Serial.print("emailBuffer: "); Serial.println(emailBuffer);

  Serial.println("");
  memory.getUserEmail(emailBuffer);
  Serial.print("emailTeste: "); Serial.println(emailTeste);
  Serial.print("emailBuffer: "); Serial.println(emailBuffer);
}// FIM ---------------------------------------------------------------->>> emailTest

void Memory::saveDrinkAtMemory() {
  byte nextPositionToSave = getNextPositionToWriteDrink();
  byte nextPositionToDelete = getNextPositionToCleanDrink();
  if ( (nextPositionToSave == nextPositionToDelete - 1) || ((nextPositionToSave == 255) && (nextPositionToDelete == 1)) ) {
    cleanDrinkMemoryAtPosition(nextPositionToDelete);
  }
  setDrinkAtPosition(nextPositionToSave);
}
void Memory::lastDrinkWasSentToServerWithSucess() {
  byte nextPositionToCleanDrink = getNextPositionToCleanDrink();
  Serial.print("- nextPositionToCleanDrink: "); Serial.println(nextPositionToCleanDrink);
  cleanDrinkMemoryAtPosition(nextPositionToCleanDrink);
}
byte Memory::getNextDrinkToSendToServer() {
  byte positionToSendToServer = getNextPositionToReadDrink();
  getDrinkFromPosition(positionToSendToServer);
  _drink->setPositionToSendToServer(positionToSendToServer);
  return positionToSendToServer;
}

void Memory::printDrinkFromPosition(byte position) {
  getDrinkFromPosition(position);
  _drink->print();
}
void Memory::getDrinkFromPosition(byte position) {
  yield();
  byte drinkArray[_drinkSize];
  memset(&drinkArray[0], 48, _drinkSize);
  int address =  dataMemoryBegin + _drinkSize * (position - 1);
  mem.read(address, (byte*)drinkArray, _drinkSize);
  address=0;
  _drink->setDia(drinkArray[address++]);
  _drink->setMes(drinkArray[address++]);
  int ano = ((int)(drinkArray[address++])) << 8;
  ano += ((int)(drinkArray[address++]));
  _drink->setAno(ano);
  _drink->setHora(drinkArray[address++]);
  _drink->setMinuto(drinkArray[address++]);
  _drink->setSegundo(drinkArray[address++]);
  int volumeMl = ((int)(drinkArray[address++])) << 8;
  volumeMl += ((int)(drinkArray[address++]));
  _drink->setVolumeMl(volumeMl);
  _drink->setTipoSinal((char)drinkArray[address++]);
  int sinal = ((int)(drinkArray[address++])) << 8;
  sinal += ((int)(drinkArray[address++]));
  _drink->setSinal(sinal);
}
void Memory::setDrinkAtPosition(byte position) {
  yield();
  byte drinkArray[_drinkSize];
  memset(&drinkArray[0], 48, _drinkSize);
  int address = 0;
  drinkArray[address++] = _drink->getDia();
  drinkArray[address++] = _drink->getMes();
  drinkArray[address++] = (byte)((_drink->getAno()) >> 8);
  drinkArray[address++] = (byte)(_drink->getAno());
  drinkArray[address++] = _drink->getHora();
  drinkArray[address++] = _drink->getMinuto();
  drinkArray[address++] = _drink->getSegundo();
  drinkArray[address++] = (byte)((_drink->getVolumeMl()) >> 8);
  drinkArray[address++] = (byte)(_drink->getVolumeMl());
  drinkArray[address++] = (byte)_drink->getTipoSinal();
  drinkArray[address++] = (byte)((_drink->getSinal()) >> 8);
  drinkArray[address++] = (byte)(_drink->getSinal());
  address =  dataMemoryBegin + _drinkSize * (position - 1);
  mem.write(address, (byte*)drinkArray, _drinkSize);
}

//correto
byte Memory::getLastUsedPositionFromBeginScan() {
  byte readByteAnterior = 0;
  byte readByteAtual = 128;
  if ( (mem.read(dataMemoryBegin + 2) > 127) && mem.read(dataMemoryEnd + 1 - _drinkSize + 2) < 128 ) {
    //Serial.print("Last Used Position From Begin Scan Address: ");
    //Serial.println(255);
    return 255;
  }
  for (int address = dataMemoryBegin ; address <= dataMemoryEnd; address += _drinkSize) {
    yield();
    readByteAnterior = readByteAtual;
    readByteAtual = mem.read(address + 2);
    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
    if ( (readByteAtual > 127) && (readByteAnterior < 128) ) {
      //Serial.print("Last Used Position From Begin Scan Address: ");
      //Serial.println((address - dataMemoryBegin) / 12);
      return (address - dataMemoryBegin) / 12;
    }
    yield();
  }
}
byte Memory::getLastUsedPositionFromEndScan() {
  byte readByteAnterior = 0;
  byte readByteAtual = 128;
  if ( (mem.read(dataMemoryBegin + 2) < 128) && mem.read(dataMemoryEnd + 1 - _drinkSize + 2) > 127 ) {
    //Serial.print("Last Used Position From End Scan Address: ");
    //Serial.println(1);
    return 1;
  }

  for (int address = 1 + dataMemoryEnd - _drinkSize; address >= dataMemoryBegin; address = address - _drinkSize) {
    yield();
    readByteAnterior = readByteAtual;
    readByteAtual = mem.read(address + 2);
    //if (/*readByte < 128 || (readByte + 1) < 128 ||*/ (readByte + 2) < 128 /*|| (readByte + 4) < 128 || (readByte + 5) < 128*/) {
    if ( (readByteAtual > 127) && (readByteAnterior < 128) ) {
      //Serial.print("Last Used Position From End Scan Address: ");
      //Serial.println(2+((address - dataMemoryBegin) / 12));
      return 2 + ((address - dataMemoryBegin) / 12);
    }
    yield();
  }
}
//// fim dos novos


byte Memory::getNextPositionToWriteDrink() {
  if (getLastUsedPositionFromBeginScan() == 255) {
    return 1;
  } else {
    return getLastUsedPositionFromBeginScan() + 1;
  }
}
byte Memory::getNextPositionToCleanDrink() {
  if (getLastUsedPositionFromBeginScan() == getLastUsedPositionFromEndScan()) {
    return 0; // sem posicao para limpar
  } else {
    return getLastUsedPositionFromEndScan();
  }
}
byte Memory::getNextPositionToReadDrink() {
  if (getLastUsedPositionFromBeginScan() == getLastUsedPositionFromEndScan()) {
    return 0; // sem posicao para limpar
  } else if (getLastUsedPositionFromEndScan() == 255) {
    return 1;
  } else {
    return getLastUsedPositionFromEndScan() + 1;
  }
}

void Memory::preenchendoDrinksParaTeste() {
  cleanDataMemory();
  for (byte mes = 1; mes < 11 ; mes++) {
    for (byte dia = 1; dia < 30 ; dia ++) {
      yield();
      drink.setValue(dia, mes, 1984, 9, 50, 30, 57, 'c', 111, 0, 0);
      saveDrinkAtMemory();
    }
  }
  Serial.println("Memoria Preenchida para Teste");
}
void Memory::print() {
  printInfo();
  printData();
}
void Memory::printInfo() {
  Serial.println("\nMemory\n");
  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());
  Serial.print("Memory Total Size (EEPROM):4096 bytes"); //Serial.println(memorySize);
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
  Serial.print("\nMemoria Total Usada: ");  Serial.print(memUsada); Serial.print(" - "); Serial.print((((double)memUsada) / 4096.0) * 100, 2); Serial.println("%");
  Serial.print("Memoria Total Livre: ");  Serial.print(4096 - memUsada);
  yield();
  printEmail();
  printDrinkAlarm();
  printMealAlarm();
  printCleaningAlarm();
}
void Memory::printEmail() {
  uint8_t value = 0;
  Serial.print("\n");
  Serial.println("Email Memory");
  Serial.print("(address="); if (userEmailBegin < 100) {
    Serial.print(" ");
  } if (userEmailBegin < 10) {
    Serial.print(" ");
  } Serial.print(userEmailBegin); Serial.print(")-");
  for (int address = userEmailBegin; address <= userEmailEnd; address++) {
    yield();
    value = mem.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 16 == 0) {
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
void Memory::printDrinkAlarm() {
  uint8_t value = 0;
  Serial.print("\n");
  Serial.println("Drink Alarm Memory");
  Serial.print("(address="); if (drinkAlarmPositionsBegin < 100) {
    Serial.print(" ");
  } if (drinkAlarmPositionsBegin < 10) {
    Serial.print(" ");
  } Serial.print(drinkAlarmPositionsBegin); Serial.print(")-");
  for (int address = drinkAlarmPositionsBegin; address <= drinkAlarmPositionsEnd; address++) {
    yield();
    value = mem.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 16 == 0) {
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
}
void Memory::printMealAlarm() {
  uint8_t value = 0;
  Serial.print("\n");
  Serial.println("Meal Alarm Memory");
  Serial.print("(address="); if (mealAlarmPositionsBegin < 100) {
    Serial.print(" ");
  } if (mealAlarmPositionsBegin < 10) {
    Serial.print(" ");
  } Serial.print(mealAlarmPositionsBegin); Serial.print(")-");
  for (int address = mealAlarmPositionsBegin; address <= mealAlarmPositionsEnd; address++) {
    yield();
    value = mem.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 16 == 0) {
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
}
void Memory::printCleaningAlarm() {
  uint8_t value = 0;
  Serial.print("\n");
  Serial.println("Cleaning Alarm Memory");
  Serial.print("(address="); if (mealAlarmPositionsBegin < 100) {
    Serial.print(" ");
  } if (mealAlarmPositionsBegin < 10) {
    Serial.print(" ");
  } Serial.print(cleaningAlarmPositionsBegin); Serial.print(")-");
  for (int address = cleaningAlarmPositionsBegin; address <= cleaningAlarmPositionsEnd; address++) {
    yield();
    value = mem.read(address);
    if (value < 100) {
      Serial.print(" ");
    } if (value < 10) {
      Serial.print(" ");
    }
    Serial.print(value, DEC);
    if ((address + 1) % 16 == 0) {
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
    value = mem.read(address);
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

void Memory::cleanMemory() {
  yield();
  cleanInfoMemory();
  cleanDataMemory();
}
void Memory::cleanInfoMemory() {
  Serial.print("Clean Info Memory");
  byte cleanArray[30];
  byte size = sizeof(cleanArray);
  memset(&cleanArray[0], 0, size);
//  Serial.print("cleanArray: ");
//  for (int i = 0; i < sizeof(cleanArray); i++) {
//    Serial.print(cleanArray[i]); Serial.print("-");
//  }

  byte cleanArray2[30];
  byte size2 = sizeof(cleanArray2);
  memset(&cleanArray2[0], 255, size2);
//  Serial.print("cleanArray2: ");
//  for (int i = 0; i < sizeof(cleanArray2); i++) {
//    Serial.print(cleanArray2[i]); Serial.print("-");
//  }

  for (int address = infoByteBegin; address <= infoByteEnd; ) {
    yield();
    if ( address < (userEmailEnd - size) ) {
      mem.write(address, (byte*)cleanArray, size);
      address = address + size;
    } else if (address < userEmailEnd) {
      mem.write(address, 0);
      address++;
    } else if ( address < (infoByteEnd - size2) ) {
      mem.write(address, (byte*)cleanArray2, size2);
      address = address + size;
    } else {
      mem.write(address, 255);
      address++;
    }
    Serial.print("Address: "); Serial.println(address);
  }
  Serial.println("\nInfo has been clean!");
}
void Memory::cleanDataMemory() {
  yield();
  for (int address = dataMemoryBegin; address <= dataMemoryEnd; ) {
    yield();
    byte cleanArray[30];
    byte size = sizeof(cleanArray);
    memset(&cleanArray[0], 255, size);
    if ( address < (infoByteEnd - size) ) {
      mem.write(address, (byte*)cleanArray, size);
      address = address + size;
    } else {
      mem.write(address, 255);
      address++;
    }
  }
  byte firstByte = 0;
  mem.write(dataMemoryBegin + 2, firstByte);
  Serial.println("\nDrink data has been clean!");
}
void Memory::cleanDrinkMemoryAtPosition(byte position) {
  yield();
  if (position > 0 && position < 256) {
    byte drinkArray[_drinkSize];
    memset(&drinkArray[0], 128, _drinkSize);
    int address =  dataMemoryBegin + _drinkSize * (position - 1);
    mem.write(address, (byte*)drinkArray, _drinkSize);
  }
}

void Memory::getUserEmail(char email[]) {
  yield();
  //  byte size = userEmailSpace+1;
  //  char email[size];
  memset(&email[0], 0, userEmailSpace + 1);
  mem.readChars(userEmailBegin, email, userEmailSpace);
}
void Memory::setUserEmail(const char email[]) {
  yield();
  char emailCorreto[userEmailSpace + 1];
  memset(&emailCorreto[0], 0, sizeof(emailCorreto));//limpando
  Serial.print("sizeof(emailCorreto): "); Serial.println(sizeof(emailCorreto));
  Serial.print("sizeof(email): "); Serial.println(sizeof(email));
  strncpy(emailCorreto, email, sizeof(emailCorreto));
  mem.writeChars(userEmailBegin, emailCorreto, userEmailSpace);
}


/* --------------------------------- Alarm --------------------------------- */


//byte Memory::getDrinkAlarmPositionQuantity() {
//  //  EEPROM.begin(memorySize);
//  uint16_t quantidade = 0;
//  Serial.print(" getQty:");
//  while ((mem.read(drinkAlarmPositionsBegin + (quantidade) * 2) != 255) && (quantidade < drinkAlarmPositions)) {
//    //    Serial.print("\n - (drinkAlarmPositionsBegin + (quantidade) * 2): "); Serial.print((drinkAlarmPositionsBegin + (quantidade) * 2));
//    //    Serial.print(" - 1Eepromread: "); Serial.print(readByte(drinkAlarmPositionsBegin + (quantidade) * 2));
//    Serial.print(" - quant:"); Serial.print(quantidade);
//    quantidade++;
//  }
//  //  EEPROM.end();
//  return 0;
//
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
//  //  EEPROM.begin(memorySize);
//  Serial.print("add");
//  float horarioAdd = hour + ((float)minute) / 60;
//  byte quantidade = getDrinkAlarmPositionQuantity();
//  float maiorHorario;
//  if (quantidade == 0) {
//    maiorHorario = 0;
//  } else {
//    maiorHorario = readByte( drinkAlarmPositionsBegin + 2 * (quantidade - 1) ) + ((float)( readByte( 1 + drinkAlarmPositionsBegin + 2 * (quantidade - 1) ) )) / 60;
//  }
//
//
//  Serial.print(" - horarioAdd: "); Serial.print(horarioAdd); Serial.print(" - maiorHorario: "); Serial.print(maiorHorario); Serial.print(" - quantidade: "); Serial.println(quantidade);
//  if ( quantidade == 25 ) {
//    //    EEPROM.end();
//    return false;
//  } else if ( quantidade == 0 ) {
//    Serial.println("In(0)");
//    writeByte(drinkAlarmPositionsBegin, hour);//EEPROM.commit();
//    Serial.print("(ERadd0h: "); Serial.print(readByte(drinkAlarmPositionsBegin)); Serial.print(")");
//    writeByte(drinkAlarmPositionsBegin + 1, minute);//EEPROM.commit();
//    Serial.print("(ERadd0m: "); Serial.print(readByte(drinkAlarmPositionsBegin + 1)); Serial.print(")");
//  } else if ( horarioAdd > maiorHorario ) {
//    Serial.print("In(maior)");
//    writeByte(drinkAlarmPositionsBegin + 2 * (getDrinkAlarmPositionQuantity()), hour); //EEPROM.commit();
//    writeByte(1 + drinkAlarmPositionsBegin + 2 * (getDrinkAlarmPositionQuantity()), minute); //EEPROM.commit();
//  } else {
//    byte Posicao = getDrinkAlarmNextAlarmPosition(hour, minute) - 1;
//    for (byte address = drinkAlarmPositionsBegin + getDrinkAlarmPositionQuantity() * 2 ;
//         address < (drinkAlarmPositionsBegin + (Posicao - 1) * 2) ;
//         address = address - 2) {
//      Serial.println("\nDENTRO FOR DO ADD");
//      writeByte(address, hour);//EEPROM.commit();
//      writeByte(address + 1, minute);//EEPROM.commit();
//      yield();
//    }
//    writeByte(drinkAlarmPositionsBegin + (getDrinkAlarmNextAlarmPosition(hour, minute) - 1) * 2, hour); EEPROM.commit();
//    writeByte(drinkAlarmPositionsBegin + 1 + (getDrinkAlarmNextAlarmPosition(hour, minute) - 1) * 2, minute); EEPROM.commit();
//  }
//  //  Serial.print("(ERadd2: ");Serial.print(readByte(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
//  //  EEPROM.end();
//  return true;
//
//}
//bool Memory::cleanDrinkAlam(byte hour, byte minute) {
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
//  //  if (getDrinkAlarmPositionQuantity() == 0) {
//  //    return 255;
//  //  }
//  yield();
//  return (byte)EEPROM.read(drinkAlarmPositionsBegin + (position - 1) * 2);
//  EEPROM.end();
//}
//byte Memory::getDrinkAlarmMinuteFromPosition(byte position) {
//  EEPROM.begin(memorySize);
//  //  if (getDrinkAlarmPositionQuantity() == 0) {
//  //    return 255;
//  //  }
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
//void Memory::cleanDrinkAlarmAllPosition() {
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
//  cleanDrinkAlarmAllPosition();
//  memory.print();
//  //  Serial.println("Dentro drink");
//  //  Serial.print("Qty0: (");Serial.print(getDrinkAlarmPositionQuantity());Serial.println(")");
//  //  EEPROM.write(drinkAlarmPositionsBegin,1);EEPROM.commit();Serial.print("drinkAlarmPositionsBegin:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin));
//  //  EEPROM.write(drinkAlarmPositionsBegin+1,1);EEPROM.commit();Serial.print("drinkAlarmPositionsBegin+1:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin+1));
//  //  Serial.print("Qty1: (");Serial.print(getDrinkAlarmPositionQuantity());Serial.println(")");
//  ////  EEPROM.write(drinkAlarmPositionsBegin+2,1);Serial.print("drinkAlarmPositionsBegin+2:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin+2));
//  ////  EEPROM.write(drinkAlarmPositionsBegin+3,1);Serial.print("drinkAlarmPositionsBegin+3:");Serial.println(EEPROM.read(drinkAlarmPositionsBegin+3));
//  //  Serial.print("Qty2: (");Serial.print(getDrinkAlarmPositionQuantity());Serial.println(")");
//  int i = 1;
//  while (i < 26) {
//    int hour = i - 1;
//    int minute = i * 2;
//    Serial.print("\ni: ");                              Serial.print(i);
//    Serial.print(" - hour: ");                        Serial.print(hour);
//    Serial.print(" - minute: ");                      Serial.print(minute);
//    Serial.print(" - addSucess: ");                   Serial.print(addDrinkAlarm(hour, minute));//Serial.print("(ERadd3: ");Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
//    //    Serial.print(" - quantPostion: ");                Serial.print(getDrinkAlarmPositionQuantity());
//    //    Serial.print(" - DrinkAlarmNextAlarmPosition: "); Serial.print(getDrinkAlarmNextAlarmPosition(hour,minute));
//    Serial.print(" - eeprom.hour: ");                 Serial.print(getDrinkAlarmHourFromPosition(i));//Serial.print("(ERadd4: ");Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
//    Serial.print(" - eeprom.minute: ");               Serial.print(getDrinkAlarmMinuteFromPosition(i) + 1); //Serial.print("(ERadd5: ");Serial.print(EEPROM.read(drinkAlarmPositionsBegin + (0) * 2));Serial.print(")");
//    //    Serial.print(" - quantPostion: ");                Serial.print(getDrinkAlarmPositionQuantity());
//    //    Serial.print(" - findDrink(h2/,m/2): ");          Serial.print(findDrinkAlarmPositionFrom(hour/2,minute/2));
//    //    Serial.print(" - DrinkAlarmNextAlarmPosition(h2/,m/2): "); Serial.println(getDrinkAlarmNextAlarmPosition(hour/2,minute/2));
//    i++;
//  }
//  memory.print();
//  EEPROM.end();
//}

//uint8_t Memory::readByte(uint16_t address) {
//  uint8_t value;
//  EEPROM.begin(memorySize);
//  value = EEPROM.read(address); Serial.print("(readValue:"); Serial.print(value); Serial.print(")");
//  //  EEPROM.commit();
//  EEPROM.end();
//  return value;
//}
//void Memory::writeByte(uint16_t address, uint8_t value) {
//  EEPROM.begin(memorySize);
//  EEPROM.write(address, value);
//  //  EEPROM.commit();
//  EEPROM.end();
//}


#include <Wire.h>
#include <At24c32.h>

At24c32 mem;

void setup() {
  Serial.begin(115200);
  //  delay(3000);

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
    if(b1 == b1){
      Serial.println(" --> OK");
    }else{
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
    if(c == c1){
      Serial.println(" --> OK");
    }else{
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
    i = value;
    Serial.print("Write ");
    Serial.print(i);
    Serial.print(" to address ");
    Serial.print(value/16-1);
    mem.writeInt(value/16-1, value);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value/16-1);
    Serial.print("...   ");
    i1 = mem.readInt(value/16-1);
    Serial.print("... read: ");
    Serial.print(i1);
    yield();
    if(i == i1){
      Serial.println(" --> OK");
    }else{
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
    l2 = value * value;
    Serial.print("Write ");
    Serial.print(l2,DEC);
    Serial.print(" to address ");
    Serial.print(value/16-1);
    mem.writeLong(value/16-1, l2);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value/16-1);
    Serial.print("...   ");
    l21 = mem.readLong(value/16-1);
    Serial.print("... read: ");
    Serial.print(l21, DEC);
    yield();
    if(l2 == l21){
      Serial.println(" --> OK");
    }else{
      Serial.println(" --> ERRO");
    }
  }
  for (unsigned int value = 16; value != 65536; value = value * 2) {
    l2 = value * value;
    Serial.print("Write ");
    Serial.print(l2,DEC);
    Serial.print(" to address ");
    Serial.print(value/16+4);
    mem.writeLong(value/16+4, l2);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value/16+4);
    Serial.print("...   ");
    l21 = mem.readLong(value/16+4);
    Serial.print("... read: ");
    Serial.print(l21, DEC);
    yield();
    if(l2 == l21){
      Serial.println(" --> OK");
    }else{
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
    float ifvalue = (float) value;
    float i1value = 128.0/ifvalue;
    f = 3.141592  + i1value;
    Serial.print("Write ");
    Serial.print(f,DEC);
    Serial.print(" to address ");
    Serial.print(value/16-1);
    mem.writeFloat(value/16-1,f);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value/16-1);
    Serial.print("...   ");
    f1 = mem.readFloat(value/16-1);
    Serial.print("... read: ");
    Serial.print(f1, DEC);
    yield();
    if(f == f1){
      Serial.println(" --> OK");
    }else{
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
    double idvalue = (double) value;
    double iddvalue = 128.0/idvalue;
    d = 3.1415926535897932384626433832  + iddvalue;
    Serial.print("Write ");
    Serial.print(d,DEC);
    Serial.print(" to address ");
    Serial.print(value/16-1);
    mem.writeDouble(value/16-1,d);
    Serial.print(" ---> Read byte from address ");
    Serial.print(value/16-1);
    Serial.print("...   ");
    d1 = mem.readDouble(value/16-1);
    Serial.print("... read: ");
    Serial.print(d1, DEC);
    yield();
    if(d == d1){
      Serial.println(" --> OK");
    }else{
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
    arrayPronto[2*(address-32)] = (char)address;
    arrayPronto[2*(address-32)+1] = (char)address;
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
    if(letra1[0] == letra2[0]){
      Serial.println(" --> OK");
    }else{
      Serial.println(" --> ERRO");
    }
  }
  
  Serial.println();
  arrayPronto[sizeof(arrayPronto)-1] = '\0';
    arrayPronto[sizeof(arrayPronto)-2] = 'f';
  Serial.print("ArrayPronto:");
  Serial.print("size: ");
  Serial.println(sizeof(arrayPronto));
  Serial.print("Array: ");
  Serial.println(arrayPronto);
  Serial.print("arrayPronto[ ");Serial.print(sizeof(arrayPronto)-1);Serial.print("]: ");
  Serial.println(arrayPronto[sizeof(arrayPronto)-1]);
  int  maiorOld = 0;
  char arrayProntoBig[10 * sizeof(arrayPronto)];
  for(int i = 0; i< sizeof(arrayPronto); i++){
    for(int j = 0; j<10;j++){
      arrayProntoBig[i*10+j] =arrayPronto[i];
      maiorOld++;
    }
  }
  Serial.println(arrayProntoBig);
  int maiorNew = 0;
  while( (arrayProntoBig[maiorNew] != '\0') ){
    maiorNew++;
  }
  Serial.print("MaiorOld posicao ocupada de arrayProntoBig é ");
  Serial.println(maiorOld);
  Serial.print("MaiorNew posicao ocupada de arrayProntoBig é ");
  Serial.println(maiorNew);
  for(int i = maiorNew - 10; i<maiorOld; i++){
    Serial.print("arrayProntoBig[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(arrayProntoBig[i]);
    arrayProntoBig[i] = i-maiorNew;
    Serial.print("----->(byte)arrayProntoBig[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print((byte)arrayProntoBig[i]);
    Serial.println();
  }
  arrayProntoBig[maiorOld-1] = '\0';
    Serial.print("(byte)arrayProntoBig[");
    Serial.print(maiorOld-1);
    Serial.print("]=");
    Serial.print((byte)arrayProntoBig[i]);
    Serial.print("<--");

  //----------------------- 30 bytes
  byte pos30Read[] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9};
  Serial.println();
  Serial.print("30pos\nsize:");
  Serial.println(sizeof(pos30Read));
  
  // read bytes with multiple steps
    Serial.println("Read 30 single bytes starting at address 1000");
  Serial.print("\nWrite 30pos(");
  for(int i =0;i<sizeof(pos30Read);i++){
    Serial.print(pos30Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos30Read, sizeof(pos30Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos30byte;
  for( int i=0; i<sizeof(pos30Read);i++){
    byte pos30byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos30byte);
    if(pos30Read[i] == pos30byte){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  
  // read bytes with multiple steps
  Serial.print("\nWrite 30pos(");
  for(int i =0;i<sizeof(pos30Read);i++){
    Serial.print(pos30Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 30 bytes with one operation at address 1000");
  byte pos30Write[sizeof(pos30Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos30Write[0],32,sizeof(pos30Write));
  mem.read(1000, pos30Write, sizeof(pos30Write));
  
  for( int i=0; i<sizeof(pos30Write);i++){
    byte pos30byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos30Write[i]);
    if(pos30Read[i] == pos30Write[i]){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  //------------------------------- 32 bytes

     
  byte pos32Read[] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9,0,0};
  Serial.println();
  Serial.print("32pos\nsize:");
  Serial.println(sizeof(pos32Read));
  
  // read bytes with multiple steps
    Serial.println("Read 32 single bytes starting at address 1000");
  Serial.print("\nWrite 32pos(");
  for(int i =0;i<sizeof(pos32Read);i++){
    Serial.print(pos32Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos32Read, sizeof(pos32Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos32byte;
  for( int i=0; i<sizeof(pos32Read);i++){
    byte pos32byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos32byte);
    if(pos32Read[i] == pos32byte){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  
  // read bytes with multiple steps
  Serial.print("\nWrite 32pos(");
  for(int i =0;i<sizeof(pos32Read);i++){
    Serial.print(pos32Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 32 bytes with one operation at address 1000");
  byte pos32Write[sizeof(pos32Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos32Write[0],32,sizeof(pos32Write));
  mem.read(1000, pos32Write, sizeof(pos32Write));
  
  for( int i=0; i<sizeof(pos32Write);i++){
    byte pos32byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos32Write[i]);
    if(pos32Read[i] == pos32Write[i]){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  //------------------------------- 33 bytes

  byte pos33Read[] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9,0,0,0};
  Serial.println();
  Serial.print("33pos\nsize:");
  Serial.println(sizeof(pos33Read));
  
  // read bytes with multiple steps
    Serial.println("Read 33 single bytes starting at address 1000");
  Serial.print("\nWrite 33pos(");
  for(int i =0;i<sizeof(pos33Read);i++){
    Serial.print(pos33Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos33Read, sizeof(pos33Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos33byte;
  for( int i=0; i<sizeof(pos33Read);i++){
    byte pos33byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos33byte);
    if(pos33Read[i] == pos33byte){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  
  // read bytes with multiple steps
  Serial.print("\nWrite 33pos(");
  for(int i =0;i<sizeof(pos33Read);i++){
    Serial.print(pos33Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 33 bytes with one operation at address 1000");
  byte pos33Write[sizeof(pos33Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos33Write[0],33,sizeof(pos33Write));
  mem.read(1000, pos33Write, sizeof(pos33Write));
  
  for( int i=0; i<sizeof(pos33Write);i++){
    byte pos33byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos33Write[i]);
    if(pos33Read[i] == pos33Write[i]){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  //----------------------- 80 bytes

  byte pos80Read[] = {  0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,
                        0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,
                        0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,
                        0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,
                        0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,
                        4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,
                        4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,
                        4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,
                        4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,
                        4,4,4,4,5,5,5,5,6,6,6,6,7,7,7};
  Serial.println();
  Serial.print("80pos\nsize:");
  Serial.println(sizeof(pos80Read));
  
  // read bytes with multiple steps
    Serial.println("Read 80 single bytes starting at address 1000");
  Serial.print("\nWrite 80pos(");
  for(int i =0;i<sizeof(pos80Read);i++){
    Serial.print(pos80Read[i]);
  }
  Serial.println(")to address 1000");
  mem.write(1000, (byte*)pos80Read, sizeof(pos80Read));
  Serial.println("Read byte from address 1000 ...");
  byte pos80byte;
  for( int i=0; i<sizeof(pos80Read);i++){
    byte pos80byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos80byte);
    if(pos80Read[i] == pos80byte){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();
  
  // read bytes with multiple steps
  Serial.print("\nWrite 80pos(");
  for(int i =0;i<sizeof(pos80Read);i++){
    Serial.print(pos80Read[i]);
  }
  Serial.println(")to address 1000");
  Serial.println("\nRead 80 bytes with one operation at address 1000");
  byte pos80Write[sizeof(pos80Read)];
  Serial.println("Read byte from address 1000 ...");
  memset(&pos80Write[0],80,sizeof(pos80Write));
  mem.read(1000, pos80Write, sizeof(pos80Write));
  
  for( int i=0; i<sizeof(pos80Write);i++){
    byte pos80byte = mem.read(1000+i);
    Serial.print("i[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(pos80Write[i]);
    if(pos80Read[i] == pos80Write[i]){
      Serial.print(" --> OK   ///   ");
    }else{
      Serial.print(" --> ERRO ///   ");
    }    
    if((i+1)%3 == 0){
      Serial.println();
    }
  }
  Serial.println();

  // email!!!! 16 bytes
  Serial.println();
  Serial.println("16 bytes");
  for(int endereco = 0; endereco<64;endereco++){
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
    while( emailLido[pos] != '\0'){
      pos++;
    }
    Serial.println(pos);   
  }

  // email!!!! 32 bytes
  Serial.println();
  for(int endereco = 0; endereco<64;endereco++){
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
  for(int endereco = 0; endereco<64;endereco++){
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
  for(int endereco = 0; endereco<64;endereco++){
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
  for(int endereco = 0; endereco<65;endereco++){
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
  for(int endereco = 0; endereco<1000;endereco++){
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
  
}


void loop() {

}

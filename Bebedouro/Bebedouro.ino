#include "Drink.h"
#include "Memory.h"

Drink drink = Drink();
Memory memory = Memory(4095,drink,drink.getSize());

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Testes");


//  Drink drink = Drink();
//  drink.setValue(11,12,1984,11,50,30,57,'c',111);
//  Serial.print("Dia: "+ drink.getDia());
//  // put your setup code here, to run once:
  memory.print();
  memory.printData();
  //memory.teste2();
}

void loop() {
  
  
 // drink.setValue(11,12,1984,11,50,30,57,'c',111);
 // drink.println();
 // memory.teste();
  
  delay(1000);

}

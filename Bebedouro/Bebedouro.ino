#include "Drink.h"
#include "Memory.h"

Drink drink = Drink();
Memory memory = Memory(4095,drink,drink.getSize());

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Testes");



  drink.setValue(11,12,1984,11,50,30,57,'c',111);
  drink.print();
  memory.getDrinkFromPosition(1);
  drink.print();
  drink.setValue(11,12,1984,11,50,30,57,'c',111);
  Serial.println("SET");
  memory.setDrinkAtPosition(1);
  drink.print();
  Serial.println("GET");
  memory.getDrinkFromPosition(1);
  drink.print();
//  Serial.print("Dia: "+ drink.getDia());
//  // put your setup code here, to run once:
//  memory.print();
//  memory.printData();
  memory.printDrinkFromPosition(1);
  memory.getDrinkFromPosition(1);
  //memory.teste2();
}

void loop() {
  
  
 // drink.setValue(11,12,1984,11,50,30,57,'c',111);
 // drink.println();
 // memory.teste();
  
  delay(1000);

}

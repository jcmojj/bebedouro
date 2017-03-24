#include "Drink.h"
#include "Memory.h"

Drink drink = Drink();
Memory memory = Memory(4095, drink, drink.getSize());

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Testes");

  memory.clearDataMemory();

  //  drink.setValue(11,12,1984,11,50,30,57,'c',111);
  //  drink.print();
  //  memory.getDrinkFromPosition(1);
  //  drink.print();
//  drink.setValue(20, 2, 17, 11, 50, 30, 57, 'c', 111);
//  memory.setDrinkAtPosition(1);
//  memory.setDrinkAtPosition(5);
//  memory.setDrinkAtPosition(10);
  //  drink.print();
  //  memory.getDrinkFromPosition(1);
  //  drink.print();
  ////  Serial.print("Dia: "+ drink.getDia());
  ////  // put your setup code here, to run once:
  ////  memory.print();
  ////  memory.printData();
  //  memory.printDrinkFromPosition(1);
  //  memory.getDrinkFromPosition(1);
  //memory.teste2();
  //   memory.clearDataMemory();
//  memory.print();
//  byte begin = memory.getFilledAddressFromBeginScan();
//  byte end = memory.getFilledAddressFromEndScan();
  drink.setValue(1, 0, 0, 0, 0, 0, 0, 0, 0);
  memory.clearDrinkMemoryAtPosition(1);
  memory.setDrinkAtPosition(100);
  byte begin = memory.getFilledAddressFromBeginScan();
  byte end = memory.getFilledAddressFromEndScan();
  memory.printData();
}

void loop() {


  // drink.setValue(11,12,1984,11,50,30,57,'c',111);
  // drink.println();
  // memory.teste();

  delay(1000);

}

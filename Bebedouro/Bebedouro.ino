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
//  memory.print();
  memory.clearDataMemory();

    drink.setValue(11,12,1984,11,50,30,57,'c',111);
//    for(int i = 6 ; i<256 ;i++){
//        memory.setDrinkAtPosition(i);
//    }
//    
////    memory.getDrinkFromPosition(1);
//
//
    memory.setDrinkAtPosition(1);
     memory.printData();
     memory.clearDrinkMemoryAtPosition(1);
          memory.printData();

//    memory.setDrinkAtPosition(2);
//    memory.setDrinkAtPosition(3);
//    memory.setDrinkAtPosition(4);
//
////    memory.setDrinkAtPosition(252);
////    memory.setDrinkAtPosition(253);
////    memory.setDrinkAtPosition(254);
////    memory.setDrinkAtPosition(255);

//Serial.print("Write: ");Serial.println(memory.getNextPositionToWriteDrink());
//Serial.print("Clean: ");Serial.println(memory.getNextPositionToCleanDrink());
//Serial.print("Read: ");Serial.println(memory.getNextPositionToReadDrink());


//    Serial.print("BeginScanRes: ");
//    Serial.println(memory.getLastUsedPositionFromBeginScan());
//    Serial.print("EndScanRes: ");
//    Serial.println(memory.getLastUsedPositionFromEndScan());
    
//    drink.print();
//  drink.setValue(20, 2, 17, 11, 50, 30, 57, 'c', 111);
//  memory.setDrinkAtPosition(2);
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

//  drink.setValue(1, 0, 0, 0, 0, 0, 0, 0, 0);
//  memory.clearDrinkMemoryAtPosition(1);
//  memory.setDrinkAtPosition(100);
//  byte begin = memory.getFilledAddressFromBeginScan();
//  byte end = memory.getFilledAddressFromEndScan();
  memory.printData();
}

void loop() {


  // drink.setValue(11,12,1984,11,50,30,57,'c',111);
  // drink.println();
  // memory.teste();

  delay(1000);

}

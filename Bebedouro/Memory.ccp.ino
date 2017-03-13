#include "Memory.h"

Memory::Memory(int size, Drink &drink){
  _drink = &drink;
}

void Memory::teste(){
  _drink->println();
  int ano = _drink->getAno();
  Serial.print("Ano:"); Serial.println(ano);
}


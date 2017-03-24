#include "Drink.h"
#include "Memory.h"

Drink drink = Drink();
Memory memory = Memory(4095, drink, drink.getSize());

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }


}

void loop() {




  delay(1000);

}

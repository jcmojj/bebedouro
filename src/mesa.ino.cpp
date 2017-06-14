#include <Arduino.h>
#include "Mesa.h"

// Mesa teste;
Mesa thing(6);

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  // in tec =0;

}

void loop() {
 Serial.print("Object's Number: ");
 Serial.print(thing.Number());
 Serial.println();
 delay(1000);
}

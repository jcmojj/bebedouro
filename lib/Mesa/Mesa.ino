#include <Arduino.h>
#include "Table.h"

long baud = 9600;
Table  mesa = Table(baud,200, 20,0.0175);

void setup() {
  Serial.begin(baud);
  Serial.print("Iniciando");

}

void loop() {
  mesa.updatePinData();
  mesa.serialRead();
  
}

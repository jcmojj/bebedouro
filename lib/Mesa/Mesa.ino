#include <Arduino.h>
#include "Table.h"

long baud = 9600;
Table  mesa = Table(baud);

void setup() {
  Serial.begin(baud);
  Serial.print("Iniciando");

}

void loop() {
  mesa.updatePinData();
  mesa.serialRead();
}

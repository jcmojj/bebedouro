#include "Service.h"

Service::Service(Memory &memory, Drink &drink) {
//  Rtc.Begin();
  _memory = &memory;
  _drink = &drink;
  

}
//void Service::begin(){ //no setup
//  Serial.print("Service Begin");
//  memory.rtcBegin(); //-------> adicionar
//  _clockInterval = 500;
//  _clockMillis = millis();
//  pinMode(outputA0, OUTPUT);
//  digitalWrite(outputA0, LOW);
//  pinMode(outputA1, OUTPUT);
//  digitalWrite(outputA1, LOW);
//  pinMode(outputA2, OUTPUT);
//  digitalWrite(outputA2, LOW);
//  pinMode(analogPin, INPUT);
//  _ainputReadInterval = 15;
//  _ainputReadMillis = millis();
//  _ainputPrintMillis = millis();
//  _inputPinCounter = 0; // pino lido
//  _selectInputPin = 255; //pino a ser lido ou 255 para ler todos
//  Serial.print("Service End");
//}
//void Service::loop() {
//  if((_clockMillis-millis()) > _clockInterval){
//    memory.updateClock();
//    _clockMillis=millis();
//  }
//
//  if((_ainputReadMillis-millis()) > _ainputReadInterval){
//    if(_selectInputPin<8){
//      updateInputPinValue(_selectInputPin);
//    }else{
//      updateInputPinValue(255);
//    }
//    _ainputReadMillis = millis();
//  }
//  if((_ainputPrintMillis-millis()) > 500*_ainputReadInterval){
//    for(int i =0; i<8;i++){
//      yield();
//      Serial.print(" - Pino[");
//      Serial.print(i);
//      Serial.print("]: ");
//      Serial.print(_analogInput[i]);
//      Serial.print("V");
//    }
//    Serial.println("");
//    _ainputPrintMillis=millis();
//  }
//
  
//}


/*CD4051 - http://labdegaragem.com/profiles/blogs/tutorial-sobre-4051-multiplexador-demultiplexador-e-como-utiliz
 * PINOS - 1 debaixo com bola a esquerda- conta sentido anti-horario
 * 1-Y4 - 100
 * 2-Y6 - 110
 * 3-Z - PORTA ANALOGICA ARDUINO - A0
 * 4-Y7 - 111
 * 5-Y5 - 101
 * 6-E - terra - para funcionar
 * 7-VEE - terra -ensão negativa para geração de ruído 
 * 8-VSS - terra
 * 9-A2 100
 * 10-A1 010
 * 11-A0 001
 * 12-Y3 - 011
 * 13-Y0 - 000
 * 14-Y1 - 001
 * 15-Y2 - 010
 * 16-VDD-3-15V
 */

 
//void Service::updateInputPinValue(byte pin){
//  _analogInput[_inputPinCounter] = analogRead(analogPin);///+_analogInput[_inputPinCounter])/2;
//  if(pin < 8){
//    _inputPinCounter = pin;
//  }else if(_inputPinCounter > 6){
//    _inputPinCounter = 0;
//  }else{
//    _inputPinCounter++;
//  }   
//      Serial.print("inputPinCounter:"); Serial.print(_inputPinCounter);
//      Serial.print(" =("); Serial.print(bitRead(_inputPinCounter,0));
//      Serial.print(","); Serial.print(bitRead(_inputPinCounter,1));
//      Serial.print(","); Serial.print(bitRead(_inputPinCounter,2));Serial.print(")");
//      digitalWrite(outputA0, bitRead(_inputPinCounter,0));
//      digitalWrite(outputA1, bitRead(_inputPinCounter,1));
//      digitalWrite(outputA2, bitRead(_inputPinCounter,2));
//
// 
//}



#include "Service.h"

Service::Service(Memory &memory, Drink &drink) {
//  Rtc.Begin();
  _memory = &memory;
  _drink = &drink;
  

}
void Service::begin(){ //no setup
  memory.rtcBegin();
  _clockInterval = 500;
  _clockMillis = 0;
  analogInputBegin();

  
}
void Service::loop() {
  yield();
  if((_clockMillis-millis()) > _clockInterval){
    memory.updateClock();
  }
  
  yield();
  if((_ainputReadMillis-millis()) > _ainputReadInterval){
    if(_fixInputPin<8){
      updateInputPinValue(_fixInputPin);
    }else{
      updateInputPinValue(255);
    }
  }
  
}


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
void Service::analogInputBegin(){
  pinMode(outputA0, OUTPUT);
  digitalWrite(outputA0, LOW);
  pinMode(outputA1, OUTPUT);
  digitalWrite(outputA1, LOW);
  pinMode(outputA2, OUTPUT);
  digitalWrite(outputA2, LOW);
  _ainputReadInterval = 150;
  _ainputReadMillis = 0;
  _inputPinCounter = 0;
  _fixInputPin = 255;
  for(byte i=0;i<8;i++){
    _analogInput[i]=0;
  }
}
 
void Service::updateInputPinValue(byte pin){
  if(pin < 8){
    _inputPinCounter = pin;
  }else if(_inputPinCounter == 8){
    _inputPinCounter = 0;
  }else{
    _inputPinCounter++;
  }
  switch(_inputPinCounter){
    case 0:
      digitalWrite(outputA0, LOW);
      digitalWrite(outputA1, LOW);
      digitalWrite(outputA2, LOW);
    break;
    case 1:
      digitalWrite(outputA0, HIGH);
      digitalWrite(outputA1, LOW);
      digitalWrite(outputA2, LOW);
    break;
    case 2:
      digitalWrite(outputA0, LOW);
      digitalWrite(outputA1, HIGH);
      digitalWrite(outputA2, LOW);
    break;
    case 3:
      digitalWrite(outputA0, HIGH);
      digitalWrite(outputA1, HIGH);
      digitalWrite(outputA2, LOW);
    break;
    case 4:
      digitalWrite(outputA0, LOW);
      digitalWrite(outputA1, LOW);
      digitalWrite(outputA2, HIGH);
    break;
    case 5:
      digitalWrite(outputA0, HIGH);
      digitalWrite(outputA1, LOW);
      digitalWrite(outputA2, HIGH);
    break;
    case 6:
      digitalWrite(outputA0, LOW);
      digitalWrite(outputA1, HIGH);
      digitalWrite(outputA2, HIGH);
    break;
    case 7:
      digitalWrite(outputA0, HIGH);
      digitalWrite(outputA1, HIGH);
      digitalWrite(outputA2, HIGH);
    break; 
  }
  _analogInput[_inputPinCounter] = analogRead(analogPin);
}



#include "Table.h"

//Table::Table(Stepper &stepper, Ultrasonic &ultrasonic){
//  _stepper = &stepper;
//  _ultrasonic = &ultrasonic;
//}

Table::Table(long baudrate):stepper(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4),motor(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4),ultrasonic(hcsr04Trigger, hcsr04Echo){
  Serial.begin(baudrate);
  pinMode(switchUpPin, INPUT_PULLUP);
  pinMode(switchDownPin, INPUT_PULLUP);  
  subindo = false;
  descendo = false;
  movendo = false;
  stepMin = 10;
  stepCounter = 0;
  stepTotal = 5370;//mudar DEPOIS
  float pps = 1100; // 1100pps-3.2kgf.cm -- 1200pps-2.2kgf.cm -- pulses per second
  float degree_per_step = 1.8;
  float steps_per_turn = 360/degree_per_step;
  maxSpeedRPM = (pps/steps_per_turn)*60;
  stepper.setSpeed(maxSpeedRPM);
  t0 = 0;
  t1 = 0;
}





void Table::serialRead(){
  while(Serial.available()){
    serialString = Serial.readString();
  }
  if( (!serialString.compareTo("subir"))||(subindo) ){
    subir(); 
//    Serial.print("[a: "); Serial.print(serialString.compareTo("subir"));
//    Serial.print("b: "); Serial.print(!serialString.compareTo("subir"));
//    Serial.print("c: "); Serial.print(subindo); Serial.print("]");
  }
  if( (!serialString.compareTo("descer"))||(descendo) ){
    descer();
  }
  if(!serialString.substring(0,4).compareTo("mover")){
    mover();
  }
  // sobe e para no switch - velocidade alta
  // desce e para no switch - velocidade alta
  // calibrar - vai ate embaixo, encontra o switch inferior e sobe ate o de cima - velocidade baixa
  // medir(tipo,intervalo) - sobe rapido ate o switch, e desce lento fazendo medicoes do modelo com o intervalo, depois sobe lento fazendo as mesmas medidas, depois desce rapido
  // numero - se for numero anda os estepes levando em consideracao o sinal
  serialString = "";
  
}

void Table::subir(){
  if(!subindo){Serial.print("Subindo");}
  subindo = true;
  if(!switchUpIsOn){
    if(stepCounter > (stepTotal-stepsPerRevolution) ){
      stepper.setSpeed(motorSpeedRPM/10);
    }
    stepper.step(stepMin);
    stepCounter += stepMin;
//    delay(stepMin);
  }else{
    subindo = false;
    Serial.print("Fim de Curso Superior - ");
  }
  printStepData();
}
void Table::descer(){
  if(!descendo){Serial.print("descendo");}
  descendo = true;
  if(!switchDownIsOn){
    if(stepCounter < (stepsPerRevolution) ){
      stepper.setSpeed(motorSpeedRPM/10);
    }
    stepper.step(-stepMin);
    stepCounter += -stepMin;
//    delay(stepMin);
  }else{
    descendo = false;
    Serial.print("Fim de Curso Inferior - ");
  }
  printStepData();
}
void Table::mover(){
  movendo = true;
}
void Table::calibrar(){
  
}
void Table::medir(){
  
}
void Table::printStepData(){
  printStepCounter();
  printMotorSpeedRPM();
  printSwitchStatus();
  printTimeSec();
  Serial.println("");
}
void Table::printTimeSec(){
  Serial.print(" -Tempo: "); Serial.print(millis()/1000); 
  Serial.print(","); Serial.print(millis()%1000); Serial.print("seg"); 
}
void Table::printSwitchStatus(){
  Serial.print(" -UP: "); Serial.print(switchUpIsOn);
  Serial.print(" -DOWN: "); Serial.print(switchDownIsOn);
}
void Table::printMotorSpeedRPM(){
  Serial.print(" -Speed: "); Serial.print(motorSpeedRPM); Serial.print("RPM");
}
void Table::printStepCounter(){
  Serial.print(" -Counting: "); Serial.print(stepCounter); Serial.print("steps");
}
void Table::updatePinData(){
  switchUpIsOn = !digitalRead(switchUpPin);
  switchDownIsOn = !digitalRead(switchDownPin);
  motorSpeedRPM = map(analogRead(speedPin), 0, 1023, 0, maxSpeedRPM);
  if (motorSpeedRPM > 0) {
     stepper.setSpeed(motorSpeedRPM);
  }
}
float Table::getDistanciaUltrasomMm(){
  long microsec = ultrasonic.timing();
  return ultrasonic.convert(microsec, Ultrasonic::CM);
}
float Table::getDistanciaUltrasomPol(){
  long microsec = ultrasonic.timing();
  return ultrasonic.convert(microsec, Ultrasonic::IN);
}




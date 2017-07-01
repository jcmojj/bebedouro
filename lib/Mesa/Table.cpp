#include "Table.h"

//Table::Table(Stepper &stepper, Ultrasonic &ultrasonic){
//  _stepper = &stepper;
//  _ultrasonic = &ultrasonic;
//}

Table::Table(long baudrate, int stepsPerRevolution, int encoderPulsePerRev, float encoderMmPerPulse):
        stepper(_stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4),
        motor(stepperIN1, stepperIN2, stepperIN3, _stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4),
         ultrasonic(hcsr04Trigger, hcsr04Echo),
         sharpir(),
         encoder(encoderdt, encoderclk){
  Serial.begin(baudrate);
  _stepsPerRevolution = stepsPerRevolution;
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
  movendoCounter = 0;
  encoderZero = 0;
  _encoderPulsePerRev = encoderPulsePerRev;
  _encoderMmPerPulse = encoderMmPerPulse;
  _mmPerRev =  _encoderPulsePerRev * _encoderMmPerPulse;
}





void Table::serialRead(){
  while(Serial.available()){
    serialString = Serial.readString();
//    Serial.println(serialString);
//    Serial.println(serialString[0]);
//    Serial.println(serialString[4]);
//    Serial.println(serialString.substring(0,4));
//    Serial.println(serialString.substring(0,4).compareTo("mover"));
//    Serial.println(!serialString.substring(0,4).compareTo("mover"));
//    Serial.println(serialString.substring(0,5));
//    Serial.println(serialString.substring(0,5).compareTo("mover"));
//    Serial.println(!serialString.substring(0,5).compareTo("mover"));
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
  if(!serialString.substring(0,5).compareTo("mover")||(movendoCounter!=0)){
    if(!serialString.compareTo("")){
      if(movendoCounter>0){movendoCounter--;}
      if(movendoCounter<0){movendoCounter++;}
    }else{
      movendoCounter = serialString.substring(serialString.indexOf("(")+1,serialString.indexOf(")")).toInt();
      Serial.println("movendo");
    }
    mover();
//    Serial.print("\nsubstring: ");
//    Serial.print(serialString.substring(serialString.indexOf("(")+1,serialString.indexOf(")")));
//        Serial.print("\nsubstringtoInt: ");
//    Serial.print(serialString.substring(serialString.indexOf("(")+1,serialString.indexOf(")")).toInt());
//    serialString.substring(serialString.indexOf("("),serialString.indexOf(")"));
    
  }
    if( (!serialString.compareTo("medir"))||(medindo) ){
    medir();
  }
  // sobe e para no switch - velocidade alta
  // desce e para no switch - velocidade alta
  // calibrar - vai ate embaixo, encontra o switch inferior e sobe ate o de cima - velocidade baixa
  // medir(tipo,intervalo) - sobe rapido ate o switch, e desce lento fazendo medicoes do modelo com o intervalo, depois sobe lento fazendo as mesmas medidas, depois desce rapido
  // numero - se for numero anda os estepes levando em consideracao o sinal
  serialString = "";
  
}

void Table::subir(){
  if(!subindo){Serial.println("Subindo");}
  subindo = true;
  if(!switchUpIsOn){
    if(stepCounter > (stepTotal-_stepsPerRevolution) ){
      stepper.setSpeed(motorSpeedRPM/10);
    }
    stepper.step(stepMin);
    stepCounter += stepMin;
    printStepData();
//    delay(stepMin);
  }else{
    subindo = false;
    printStepData();
    Serial.print("\nFim de Curso Superior - ");
  }
}
void Table::descer(){
  if(!descendo){Serial.println("Descendo");}
  descendo = true;
  if(!switchDownIsOn){
    if(stepCounter < (_stepsPerRevolution) ){
      stepper.setSpeed(motorSpeedRPM/10);
    }
    stepper.step(-stepMin);
    stepCounter += -stepMin;
    printStepData();
//    delay(stepMin);
  }else{
    descendo = false;
    printStepData();
    Serial.print("\nFim de Curso Inferior - ");
  }
}
void Table::mover(){
  if(movendoCounter!=0){
    if( (stepCounter < (_stepsPerRevolution) )||(stepCounter > (stepTotal-_stepsPerRevolution)) ){
      stepper.setSpeed(motorSpeedRPM/10);
    }
    if(movendoCounter>0){
      stepper.step(stepMin);
      stepCounter += stepMin;
    }
    if(movendoCounter<0){
      stepper.step(-stepMin);
      stepCounter += -stepMin;
    }
    printStepData();

//    delay(stepMin);
  }else{
    printStepData();
//    movendoCounter = 0;
    Serial.print("\nFim de Movimento - ");
  }
  if(switchDownIsOn||switchUpIsOn){
    printStepData();
    movendoCounter = 0;
    Serial.print("\nFim de Movimento - ");
    Serial.print("\nFim de Curso");
  }
}
void Table::calibrar(){
  stepper.setSpeed(motorSpeedRPM/10);
  while(!switchDownIsOn){
    stepper.step(-1);
  }
  int stepTotalInternoUp = 0;
  int stepTotalInternoDown = 1000;
  do{
  stepTotalInternoUp = 0;
  while(!switchUpIsOn){
    stepper.step(+1);
    stepTotalInternoUp++;
  }
  stepTotalInternoDown = 0;
  while(!switchDownIsOn){
    stepper.step(-1);
    stepTotalInternoDown++;
  }
  Serial.print("\nUp:");
  Serial.print(stepTotalInternoUp);
  Serial.print(" - Down: ");
  Serial.print(stepTotalInternoDown);
  }while(stepTotalInternoUp!=stepTotalInternoDown);
  Serial.println("-Ok");
  stepTotal = stepTotalInternoDown;
}
void Table::medir(){
  stepper.step(stepTotal); // deve estar embaixo
  long steps = 0;
  long stepsToGo = stepTotal;
  while(stepTotal!=0){

    
    printMeasureData();
  }
  
}

void Table::printMeasureData(){
  // imprimir encoder
  // imprimir sharp
  Serial.print ("");
  Serial.print (" -US: ");Serial.print (getDistanciaUltrasomMm());
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
  encoder.tick();
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
long Table::getEncoderPosition(){
  return encoder.getPosition()-encoderZero;
}
void Table::setEncoderZero(){
  encoderZero = encoder.getPosition();
  encoder.setPosition(encoderZero);
}
double Table::getEncoderPositionMm(){
  return getEncoderPosition();
}




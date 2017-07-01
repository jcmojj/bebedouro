#include "Motor.h"


Motor::Motor(int dirpin, int steppin, int enablepin, int stepsPerRevolution, uint8_t stepperIN1, uint8_t stepperIN2, uint8_t stepperIN3, uint8_t stepperIN4)
      :stepper(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4){
    _dirpin = dirpin;
    _steppin = steppin;
    _enablepin = enablepin;
    _stepsPerRevolution = stepsPerRevolution;
    _direction = 1;
}


void Motor::setSpeed(int maxSpeedRPM){
  stepper.setSpeed(maxSpeedRPM);
}

void Motor::step(int speedRPM){ 
  
  stepper.step(_direction);
  stepper.setSpeed(speedRPM);
  
  int stepMsDelay = _stepsPerRevolution*speedRPM/60000;
  digitalWrite(_steppin, LOW); // This LOW to HIGH change is what creates the 
  delayMicroseconds(stepMsDelay/2);
  digitalWrite(_steppin, HIGH);
  delayMicroseconds(stepMsDelay/2);
}

void Motor::setDirection(int direction){ //direction 1 ou -1
  if(direction == 1){
    digitalWrite(_steppin, HIGH); //descer =1
  }else{
    digitalWrite(_steppin, LOW); //subir  =-1
  }
  _direction = direction;
}
int Motor::getDirection(){
  return _direction;
}


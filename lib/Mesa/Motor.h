#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Stepper.h>

class Motor{

  public:
//  Motor();
    Motor(int dirpin, int steppin, int enablepin, int stepsPerRevolution, uint8_t stepperIN1, uint8_t stepperIN2, uint8_t stepperIN3, uint8_t stepperIN4);
    void setSpeed(int speedRPM);
    void step(int speed);
    void setDirection(int direction); //descer =1 - //subir  =-1
    int getDirection();
  private:
    Stepper stepper;
    byte _dirpin;
    byte _steppin;
    byte _enablepin;
    int _stepsPerRevolution;
    int _direction;//direction 1 ou -1
    
};
#endif

#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Stepper.h>

class Motor{

  public:
//  Motor();
    Motor(int stepsPerRevolution, uint8_t stepperIN1, uint8_t stepperIN2, uint8_t stepperIN3, uint8_t stepperIN4);
  private:
    Stepper stepper;

};
#endif

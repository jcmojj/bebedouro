#include "Motor.h"


Motor::Motor(int stepsPerRevolution, uint8_t stepperIN1, uint8_t stepperIN2, uint8_t stepperIN3, uint8_t stepperIN4)
      :stepper(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4){
  
}

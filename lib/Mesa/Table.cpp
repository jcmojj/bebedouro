#include "Table.h"

//Table::Table(Stepper &stepper, Ultrasonic &ultrasonic){
//  _stepper = &stepper;
//  _ultrasonic = &ultrasonic;
//}

Table::Table():stepper(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4),ultrasonic(hcsr04Trigger, hcsr04Echo){
 // stepper = &stepper;
//  _ultrasonic = &ultrasonic;
//  stepper.setSpeed(10);
}

void Table::printMotorSpeedRPM(){
  Serial.print(" - Speed: "); Serial.print(motorSpeed); Serial.print("RPM");
}
int Table::getMotorSpeedRPM(){
  return motorSpeed;
}
void Table::setSpeed(){
  int speedPinRead = analogRead(A2); // tem que alimentar com 1.1v ou fazer um divisor
  motorSpeed = map(speedPinRead, 0, 1023, 0, getMaxSpeed());
    // set the motor speed:
  if (motorSpeed > 0) {
    // myStepper.setSpeed(motorSpeed);
  }
}
float Table::getMaxSpeed(){
  float pps = 1100; // 1100pps-3.2kgf.cm -- 1200pps-2.2kgf.cm -- pulses per second
  float degree_per_step = 1.8;
  float steps_per_turn = 360/degree_per_step;
  float rpmMax = (pps/steps_per_turn)*60;
  return rpmMax;
}
bool Table::switchUpIsOn(){
  return !digitalRead(switchUpPin);
}
bool Table::switchDownIsOn(){
  return !digitalRead(switchDownPin);
}

float Table::getDistanciaUltrasomMm(){
  long microsec = ultrasonic.timing();
  return ultrasonic.convert(microsec, Ultrasonic::CM);
}

float Table::getDistanciaUltrasomPol(){
  long microsec = ultrasonic.timing();
  return ultrasonic.convert(microsec, Ultrasonic::IN);
}



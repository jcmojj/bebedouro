#ifndef Table_h
#define Table_h
#include "Arduino.h"
#include <Stepper.h>
#include <Ultrasonic.h>

const uint8_t RX                 = 0;
const uint8_t TX                 = 1;
const uint8_t hcsr04Trigger      = 2;
const uint8_t hcsr04Echo         = 3;
const uint8_t operationIsMovePin = 4; // on-off
const uint8_t oneTurnPin         = 6; //botao
const uint8_t oneStepPin         = 7; // botao
const uint8_t stepperIN1         = 8;
const uint8_t stepperIN2         = 9;
const uint8_t stepperIN3         = 10;
const uint8_t stepperIN4         = 11;
const uint8_t switchUpPin        = 12;
const uint8_t switchDownPin      = 13;
const byte sharpIRaPin           = 14; //A0
const byte sharpIRbPi            = 15; //A1
const uint8_t speedPi            = 16; //A2
const uint8_t livre3             = 17; //A3
const uint8_t livre4             = 18; //A4
const uint8_t livre5             = 19; //A5
const uint8_t livre6             = 20; //A6
const uint8_t livre7             = 21; //A7


//Stepper stepper = Stepper(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4);
//Ultrasonic ultrasonic = Ultrasonic(hcsr04Trigger, hcsr04Echo);
//Table mesa = Table(stepper,ultrasonic);

//Stepper
const int stepsPerRevolution = 200; // = 360/1.8





class Table{

  public:
//    Table(Stepper &stepper, Ultrasonic &ultrasonic);
    Table();
    int getMotorSpeedRPM();
    void printMotorSpeedRPM();

    float getDistanciaUltrasomPol();
    float getDistanciaUltrasomMm();

  private:
    bool switchUpIsOn();
    bool switchDownIsOn();
    float getMaxSpeed();
    void setSpeed();
    int motorSpeed;
//    Stepper *_stepper;
//    Ultrasonic *_ultrasonic;
    Stepper stepper;
    Ultrasonic ultrasonic;
    
};
#endif

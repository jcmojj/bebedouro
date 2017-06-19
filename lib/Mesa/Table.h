#ifndef Table_h
#define Table_h
#include "Arduino.h"
#include <Stepper.h>
#include <Ultrasonic.h>
#include "Sharpir.h"
#include "Motor.h"

const uint8_t RX                 = 0;
const uint8_t TX                 = 1;
const uint8_t hcsr04Trigger      = 2;
const uint8_t hcsr04Echo         = 3;
//const uint8_t operationIsMovePin = 4; // on-off
//const uint8_t oneTurnPin         = 6; //botao
//const uint8_t oneStepPin         = 7; // botao
const uint8_t stepperIN1         = 8;
const uint8_t stepperIN2         = 9;
const uint8_t stepperIN3         = 10;
const uint8_t stepperIN4         = 11;
const uint8_t switchUpPin        = 12;
const uint8_t switchDownPin      = 13;
const byte sharpIRaPin           = 14; //A0
const byte sharpIRbPin           = 15; //A1
const uint8_t speedPin           = 16; //A2
const uint8_t livre3             = 17; //A3
const uint8_t livre4             = 18; //A4
const uint8_t livre5             = 19; //A5
const uint8_t livre6             = 20; //A6
const uint8_t livre7             = 21; //A7


//Stepper
const int stepsPerRevolution = 200; // = 360/1.8

//String serialString;



class Table{

  public:
    Table(long baudrate);
    
    
    void updatePinData();
    void serialRead();

    void printStepData();
    
    int getMotorSpeedRPM();
    float getDistanciaUltrasomPol();
    float getDistanciaUltrasomMm();

  private:
    
    bool switchUpIsOn;
    bool switchDownIsOn;
    int motorSpeedRPM;

    Stepper stepper;
    int maxSpeedRPM;

    void subir();
    void descer();
    void mover();
    void calibrar();
    void medir();
    String serialString;

    bool subindo;
    bool descendo;
    bool movendo;

    int stepMin;
    long stepTotal;
    long stepCounter;

    // printStepData
    void printMotorSpeedRPM();
    void printStepCounter();
    void printSwitchStatus();
    void printTimeSec();

    long t0;
    long t1;
    
    
    
    Ultrasonic ultrasonic;
    Motor motor;
    Sharpir sharpir;
    
};
#endif



#include <Stepper.h>
#include <Ultrasonic.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
const int halfRevolution = stepsPerRevolution/2;
const int quarterRevolution = stepsPerRevolution/4;
const byte RX                 = 0;
const byte TX                 = 1;
const byte hcsr04Trigger      = 2;
const byte hcsr04Echo         = 3;
//const byte directionPin       = 3; // botao
const byte operationIsMovePin = 4; // on-off
const byte oneTurnPin         = 6; //botao
const byte oneStepPin         = 7; // botao
const byte stepperIN1         = 8;
const byte stepperIN2         = 9;
const byte stepperIN3         = 10;
const byte stepperIN4         = 11;
const byte switchUpPin        = 12;
const byte switchDownPin      = 13;
const byte sharpIRa           = A0;
const byte sharpIRb           = A1;
const byte speed              = A2;
const byte livre3             = A3;
const byte livre4             = A4;
const byte livre5             = A5;
const byte livre6             = A6;
const byte livre7             = A7;




long directionTime            = 0;
long oneTurnPinTime           = 0;
long oneStepPinTime           = 0;

int oneTurnCount              = 0;

boolean estaSubindo           = 1;
boolean switchUp              = 0;
boolean switchDown            = 0;
boolean operationIsWait       = 1;

boolean directionChangeBySwitch = 0; // set true while direction didnt change yet


int speedPinRead              = 560;
int motorSpeed                = 60;



// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, stepperIN1, stepperIN2, stepperIN3, stepperIN4);

long stepCount = 0;  // number of steps the motor has taken

void setup() {

  Serial.begin(9600);
  //analogReference(INTERNAL); // aref pin fica sem nada - 1.1V
  Serial.println("setup");
  // stepper functions -- o !->not  serve para inverter a logica do INPUT_PULLUP
  pinMode(LED_BUILTIN,        OUTPUT);
//  pinMode(directionPin,       INPUT_PULLUP);
  pinMode(operationIsMovePin, INPUT_PULLUP);
  pinMode(oneTurnPin,         INPUT_PULLUP);
  pinMode(oneStepPin,         INPUT_PULLUP);
}



void loop() {
//  Serial.println("loop");
  // stepper functions
  setLed(); // activate led
  setSpeed();      // Velocidade - ligar potenciometro - pino analogico A2
  setDirection();  // Sentido - ligar botaoA/B - pino digital 4
  setOperation();  // Modo - 1 volta / constante - pino digital 5 
  setOneTurn();    // Ativa 1 volta - botao click - pino digital 6
  setOneStep();    // Ativa 1 step - botao click - pino digital 7
  Serial.println("");
}

void setOneTurn(){
  if( (1-!digitalRead(operationIsMovePin))&&(!digitalRead(oneTurnPin))&&( (millis()-oneTurnPinTime) > 1000)  ){
    oneTurnCount += (1+2*((byte)estaSubindo-1))*stepsPerRevolution;
    oneTurnPinTime = millis();
    Serial.println("setOneTurn a");
//    Serial.print(":(1+2*((byte)estaSubindo-1))"); Serial.print((1+2*((byte)estaSubindo-1)));
//    Serial.print(":(1+2*(estaSubindo-1))"); Serial.print((1+2*(estaSubindo-1)));
//    Serial.print(":(1+2*(estaSubindo-1))*2"); Serial.print((1+2*(estaSubindo-1))*2);
//    Serial.print(":(1+2*((byte)estaSubindo-1))*2"); Serial.print((1+2*(estaSubindo-1))*2);
Serial.print("(1-!digitalRead(operationIsMovePin)): "); Serial.println((1-!digitalRead(operationIsMovePin)));
Serial.print("(!digitalRead(oneTurnPin)): "); Serial.println((!digitalRead(oneTurnPin)));
Serial.print("( (millis()-oneTurnPinTime) > 1000): "); Serial.println(( (millis()-oneTurnPinTime) > 1000));
Serial.print("millis(): "); Serial.println(millis());
Serial.print("oneTurnPinTime: "); Serial.println(oneTurnPinTime);
Serial.print("((millis()-oneTurnPinTime)): "); Serial.println(((millis()-oneTurnPinTime)));
 
  
  }
  if(oneTurnCount > 0){
    myStepper.step((1+2*((byte)estaSubindo-1)));
    oneTurnCount  +=(1+2*((byte)estaSubindo-1));
    stepCount     += (1+2*((byte)estaSubindo-1));
    Serial.println("setOneTurn b");
  }
}

void setOneStep(){
  if( ((millis()-oneStepPinTime) > 1000)&&(!digitalRead(oneStepPin)) ){
    myStepper.step( (1)*(1-!digitalRead(operationIsMovePin))*(1+2*((byte)estaSubindo-1))*(!digitalRead(oneStepPin)) );
    stepCount = stepCount + (1)*(1-!digitalRead(operationIsMovePin))*(1+2*((byte)estaSubindo-1))*(!digitalRead(oneStepPin));
    Serial.println("setOneStep");
  }
}

void setOperation(){
      // step 1/100 of a revolution:
    myStepper.step( (stepsPerRevolution/100)*(!digitalRead(operationIsMovePin))*(1+2*((byte)estaSubindo-1)) ); // anda 1%
    stepCount = stepCount + (stepsPerRevolution/100)*(!digitalRead(operationIsMovePin))*(1+2*((byte)estaSubindo-1));
    if((!digitalRead(operationIsMovePin))){ 
      Serial.println("setOperation c");
    }
}

void setDirection(){
  if( ( (!digitalRead(switchUpPin))||(!digitalRead(switchDownPin)) )&&(!directionChangeBySwitch) ){ // ativa mudanca de direcao e comeca a ignorarar switch ativado
    directionChangeBySwitch = true;
    estaSubindo = !estaSubindo;
  }
  if( ( (digitalRead(switchUpPin))&&(digitalRead(switchDownPin)) )&&(directionChangeBySwitch) ){ // se switch desativado e mudanca ja comecou, confirma mudanca
    directionChangeBySwitch = false;
    Serial.println("setDirection b");
  }
//  if( ( ( millis() - directionTime ) > 500 )&&(!digitalRead(directionPin)) ){ // mudanca de direcao porque apertou o botao
//    estaSubindo = !estaSubindo;
//    directionTime = millis();
//  }
  Serial.print("setDirection: "); Serial.print(estaSubindo?"Cima":"Baixo");
}

void setSpeed(){
  speedPinRead = analogRead(A2); // tem que alimentar com 1.1v ou fazer um divisor
  float pps = 1100; // 1100pps-3.2kgf.cm -- 1200pps-2.2kgf.cm -- pulses per second
  float degree_per_step = 1.8;
  float steps_per_turn = 360/degree_per_step;
  float rpm = (pps/steps_per_turn)*60;
  motorSpeed = map(speedPinRead, 0, 1023, 0, rpm);
    // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    Serial.print(" - Speed: "); Serial.print(motorSpeed);
  }  
}

void setLed(){
    if(stepCount%180<90){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}

int getSteps(){
  return stepCount;
}

float getAlturaMesaMM(){
  const float alturaMinima = 35.5;
  const float passo = 2400/800;
  return alturaMinima + stepCount/passo;
}


// fim de curso - verde comum... no- nc


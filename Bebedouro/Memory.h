#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include "Drink.h"
#include <Wire.h>
#include <At24c32.h>
#include <RtcDS3231.h>
// DS3231 SDA --> SDA D4
// DS3231 SCL --> SCL D5
// DS3231 VCC --> 3.3v or 5v
// DS3231 GND --> GND
RtcDS3231<TwoWire> rtc(Wire);
RtcDateTime now;
#define countof(a) (sizeof(a) / sizeof(a[0]))

#define drinkAlarmPositionsSize     2
#define mealAlarmPositionsSize      2
#define cleaningAlarmPositionsSize  2

#define userEmailSpace          2 * 32
#define serialNumberSpace       1 * 32
#define drinkAlarmPositions         32
#define mealAlarmPositions          32 
#define cleaningAlarmPositions      32


#define infoByteBegin               0
#define userEmailBegin              infoByteBegin
#define userEmailEnd                (userEmailBegin+userEmailSpace-1)
#define serialNumberBegin           (userEmailEnd+1)
#define serialNumberEnd             (serialNumberBegin+serialNumberSpace-1)
#define drinkAlarmPositionsBegin    (serialNumberEnd+1)
#define drinkAlarmPositionsEnd      (drinkAlarmPositionsBegin+drinkAlarmPositions*drinkAlarmPositionsSize-1)
#define mealAlarmPositionsBegin     (drinkAlarmPositionsEnd+1)
#define mealAlarmPositionsEnd       (mealAlarmPositionsBegin+mealAlarmPositions*mealAlarmPositionsSize-1)
#define cleaningAlarmPositionsBegin (mealAlarmPositionsEnd+1)
#define cleaningAlarmPositionsEnd   (cleaningAlarmPositionsBegin+cleaningAlarmPositions*cleaningAlarmPositionsSize-1)
#define infoByteEnd                 cleaningAlarmPositionsEnd

#define freeSpace dataMemoryBegin -  cleaningAlarmPositionsEnd+1

#define dataMemoryBegin 1024
#define dataMemorySize (_drinkSize*255)
#define dataMemoryEnd (dataMemoryBegin+dataMemorySize-1) // 4083 byte --> pode ir ate 4095
#define memorySize dataMemoryEnd



// Ultima posicao enviada sempre tera o numero 128+64+32 na posicao do dia
// Posicao a ser enviada sempre tera dia menor que 32
// Apos ser enviada o numero do dia sempre tera que ser acrescido de 128+64+32
// Inicializacao devera salvar o numero 128+64+32 na posicao de todos os dias

class Memory{
  public:
    Memory(Drink &drink, byte drinkSize);
    void memTest();
    void memoryTest();
    
    
    void saveDrinkAtMemory();//no-yes // fazer lembrando de apagar memoria caso esteja cheia
    void lastDrinkWasSentToServerWithSucess(); //no-yes//fazer
    byte getNextDrinkToSendToServer(); //no-yes//fazer
   
    void cleanMemory();
    void cleanInfoMemory();
    void cleanDataMemory(); 
    void cleanDrinkMemoryAtPosition(byte position); //no-yes
    
    void print(); 
    void printInfo(); 
    void printData();
    void printEmail();
    void printDrinkAlarm();
    void printMealAlarm();
    void printCleaningAlarm();
     
    void preenchendoDrinksParaTeste(); //no
    void printDrinkFromPosition(byte position); //no-yes
    void getDrinkFromPosition(byte position); //no-yes
    void setDrinkAtPosition(byte position); //no-yes

    byte getLastUsedPositionFromBeginScan(); //no-yes
    byte getLastUsedPositionFromEndScan(); //no-yes

    byte getNextPositionToWriteDrink(); //no-yes
    byte getNextPositionToCleanDrink(); //no-yes
    byte getNextPositionToReadDrink(); //no-yes

    void getUserEmail(char *  );
    void setUserEmail(const char *email);
    void emailTest();



//    byte getDrinkAlarmPositionQuantity(); //0=sem posicao - 1<=posicao<=25 //no
//    bool addDrinkAlarm(byte hour, byte minute); //no
//    byte findDrinkAlarmPositionFrom(byte hour, byte minute); //no
//    bool cleanDrinkAlam(byte hour, byte minute); //no
//    byte getDrinkAlarmHourFromPosition(byte position); //no
//    byte getDrinkAlarmMinuteFromPosition(byte position); //no
//    byte getDrinkAlarmNextAlarmPosition(byte hour, byte minute); //0=sem posicao - 1<=posicao<=25 //no
//    void cleanDrinkAlarmAllPosition(); //no
//    void DrinkAlarmTest(); //no

    
//    void rtcLoop();
//    void getClockTime();
//    void setClockTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, uint8_t hour, uint8_t minute, uint8_t second);
//    void printDateTime(const RtcDateTime& dt);
//    void printNowDateTime();    
//    bool isDateTimeValid();
//    float getTemperature();
//    void printTemperature();
//    void atualizarAlarmes();
    
  private:
    int getNextPositionAvailable();
    Drink *_drink;
    int _size;
    byte _drinkSize;
    RtcDateTime now;
//    uint8_t readByte(uint16_t address);
//    void writeByte(uint16_t address, uint8_t value);
    At24c32 mem;
//    JsonObject& _jsonDrink;
    void rtcBegin();

  
};


#endif

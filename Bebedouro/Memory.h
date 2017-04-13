#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include "Drink.h"
#include <pgmspace.h>
#include <Wire.h>
#include <At24c32.h>
#include <RtcDS3231.h>
#include <pgmspace.h>
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

class Memory {
  public:
    Memory(Drink &drink, byte drinkSize);
    void memTest();
    void memoryTest();
    void preenchendoDrinksParaTeste();

    void saveDrinkAtMemory(); // fazer lembrando de apagar memoria caso esteja cheia
    void lastDrinkWasSentToServerWithSucess(); //fazer
    byte getNextDrinkToSendToServer(); //fazer

    void cleanMemory();
    void cleanInfoMemory();
    void cleanDataMemory();
    void cleanDrinkMemoryAtPosition(byte position);

    void print();
    void printInfo();
    void printData();
    void printEmail();
    void printSerialNumber();
    void printDrinkAlarm();
    void printMealAlarm();
    void printCleaningAlarm();

    void printDrinkFromPosition(byte position);
    void getDrinkFromPosition(byte position);
    void setDrinkAtPosition(byte position);

    byte getLastUsedPositionFromBeginScan();
    byte getLastUsedPositionFromEndScan();

    byte getNextPositionToWriteDrink();
    byte getNextPositionToCleanDrink();
    byte getNextPositionToReadDrink();

    void getUserEmail(char *email  );
    void setUserEmail(const char *email);
    void emailTest();
    
    void getSN(char *sn  );
    void setSN(const char *sn);
    void snTest();


        byte getDrinkAlarmPositionQuantity(); //0=sem posicao - 1<=posicao<=25 //no
        bool addDrinkAlarm(byte hour, byte minute); //no
        byte findDrinkAlarmPositionFrom(byte hour, byte minute); //no
    //    bool cleanDrinkAlam(byte hour, byte minute); //no
        byte getDrinkAlarmHourFromPosition(byte position); //no
        byte getDrinkAlarmMinuteFromPosition(byte position); //no
        byte getDrinkAlarmNextAlarmPosition(byte hour, byte minute); //0=sem posicao - 1<=posicao<=25 //no
        void cleanDrinkAlarmAllPosition(); //no
    //    void DrinkAlarmTest(); //no


    //    void rtcLoop();
    void  updateClock();
    void  setClockDateTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, uint8_t hour, uint8_t minute, uint8_t second);
    void  printDateTime(const RtcDateTime& dt);
    void  printNowDateTime();
    bool  isDateTimeValid();
    float getTemperature();
    byte  getTemperatureFromFloatToByte(float temp);
    float getTemperatureFromByteToFloat(byte temp);
    void  printTemperature();
    void  rtcBegin();
    uint16_t getYear();
    uint8_t  getMonth();
    uint8_t  getDay();
    uint8_t  getHour();
    uint8_t  getMinute();
    uint8_t  getSecond();



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



};


#endif

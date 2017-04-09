#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include "Drink.h"
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>

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

const uint8_t AT24C32_ADDRESS = 0x57;

// Ultima posicao enviada sempre tera o numero 128+64+32 na posicao do dia
// Posicao a ser enviada sempre tera dia menor que 32
// Apos ser enviada o numero do dia sempre tera que ser acrescido de 128+64+32
// Inicializacao devera salvar o numero 128+64+32 na posicao de todos os dias

class Memory{
  public:
  
    Memory(Drink &drink, byte drinkSize, RtcDS3231<TwoWire> &rtc);
    char eeprom_read_char(const unsigned int address);
    byte eeprom_read_byte(const unsigned int address);
    void eeprom_write_char(const unsigned int address, const char data);
    void eeprom_write_byte(const unsigned int address, const byte data);


//    void saveDrinkAtMemory(); // fazer lembrando de apagar memoria caso esteja cheia
//    void lastDrinkWasSentToServerWithSucess(); //fazer
//    byte getNextDrinkToSendToServer(); //fazer
//    //lembrar de usar o ano ou o tipo de dado para alternar confirmacao de posicao --> trabalhoso --> por ultimo
//  
    void memoryTest();
    void cleanInfo();   
    void clearMemory();
    void clearDataMemory();
//    void clearDrinkMemoryAtPosition(byte position);
//
//    void preenchendoDrinksParaTeste();
    void print();
    void printData();
//    void printDrinkFromPosition(byte position);
//    void getDrinkFromPosition(byte position);
//    void setDrinkAtPosition(byte position);
//
//    byte getLastUsedPositionFromBeginScan();
//    byte getLastUsedPositionFromEndScan();
//
//    byte getNextPositionToWriteDrink();
//    byte getNextPositionToCleanDrink();
//    byte getNextPositionToReadDrink();
//
    char* readBytes(const unsigned int address, uint8_t count, char * dest,int limit); //void getUserEmail(char email[]);
    bool writeBytes(unsigned int address, char * dest, int size, int limit);
//    void setUserEmail(const char email[]);
//    byte getUserEmailSize();  
//
//    void getSsidName(char* name);
//    void setSsidName(char* name);
//
//    void getSsidPassword(char* password);
//    void setSsidPassword(char* password);
//
//    byte getDrinkAlarmPositionQuantity(); //0=sem posicao - 1<=posicao<=25
//    bool addDrinkAlarm(byte hour, byte minute);
//    byte findDrinkAlarmPositionFrom(byte hour, byte minute);
//    bool clearDrinkAlam(byte hour, byte minute);
//    byte getDrinkAlarmHourFromPosition(byte position);
//    byte getDrinkAlarmMinuteFromPosition(byte position);
//    byte getDrinkAlarmNextAlarmPosition(byte hour, byte minute); //0=sem posicao - 1<=posicao<=25
//    void clearDrinkAlarmAllPosition();
//    void DrinkAlarmTest();
//    
//    
    
  private:
//    int getNextPositionAvailable();
    Drink *_drink;
//    int _size;
    byte _drinkSize;
    RtcDS3231<TwoWire> *_rtc;
//    uint8_t readByte(uint16_t address);
//    void writeByte(uint16_t address, uint8_t value);
////    JsonObject& _jsonDrink;
//
//  
};


#endif

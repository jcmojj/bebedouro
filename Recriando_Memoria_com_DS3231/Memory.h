#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include "Drink.h"
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
//#include <EEPROM.h>

#define drinkAlarmPositions 25
#define mealAlarmPositions 25
#define serialNumber 50
#define ssidName 50
#define ssidPassword 50
#define userName 50
#define userEmail 50
#define dataMemorySize (_drinkSize*255)

#define drinkAlarmPositionsBegin 0
#define drinkAlarmPositionsEnd (drinkAlarmPositionsBegin+drinkAlarmPositions*2-1)
#define mealAlarmPositionsBegin (drinkAlarmPositionsEnd+1)
#define mealAlarmPositionsEnd (mealAlarmPositionsBegin+mealAlarmPositions*2-1)
#define serialNumberBegin (mealAlarmPositionsEnd+1)
#define serialNumberEnd (serialNumberBegin+serialNumber-1)
#define ssidNameBegin (serialNumberEnd+1)
#define ssidNameEnd (ssidNameBegin+ssidName-1)
#define ssidPasswordBegin (ssidNameEnd+1)
#define ssidPasswordEnd (ssidPasswordBegin+ssidPassword-1)
#define userEmailBegin (ssidPasswordEnd+1)
#define userEmailEnd (userEmailBegin+userEmail-1)
#define dataMemoryBegin (userEmailEnd+1)
#define dataMemoryEnd (dataMemoryBegin+dataMemorySize-1) //4194304
#define memorySize dataMemoryEnd
//#define drinkSize 12 //bytes

// Ultima posicao enviada sempre tera o numero 128+64+32 na posicao do dia
// Posicao a ser enviada sempre tera dia menor que 32
// Apos ser enviada o numero do dia sempre tera que ser acrescido de 128+64+32
// Inicializacao devera salvar o numero 128+64+32 na posicao de todos os dias

class Memory{
  public:
  
    Memory(Drink &drink, byte drinkSize, RtcDS3231<TwoWire> &rtc);
//    Memory(Drink &drink, byte drinkSize);

//    void testaRtc(RtcDS3231<TwoWire> &rtc){
//      RtcDS3231<TwoWire> *rd = &rtc;
//      
////      printDateTime(now);
////      while(true){
////        RtcDateTime now = rd->GetDateTime();
////        Serial.print("Segundo: "); Serial.print(now.Second());
////      }
//    }
//    #define countof(a) (sizeof(a) / sizeof(a[0]))
//    void printDateTime(const RtcDateTime& dt){
//  char datestring[20];
//
//  snprintf_P(datestring, 
//      countof(datestring),
//      PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
//      dt.Month(),
//      dt.Day(),
//      dt.Year(),
//      dt.Hour(),
//      dt.Minute(),
//      dt.Second() );
//    Serial.print(datestring);
//}
//    void saveDrinkAtMemory(); // fazer lembrando de apagar memoria caso esteja cheia
//    void lastDrinkWasSentToServerWithSucess(); //fazer
//    byte getNextDrinkToSendToServer(); //fazer
//    //lembrar de usar o ano ou o tipo de dado para alternar confirmacao de posicao --> trabalhoso --> por ultimo
//    
//    void clearMemory();
//    void clearDataMemory();
//    void clearDrinkMemoryAtPosition(byte position);
//
//    void preenchendoDrinksParaTeste();
//    void print();
//    void printData();
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
//    void getUserEmail(char email[]);
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

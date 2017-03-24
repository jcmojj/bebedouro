#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include "Drink.h"
#include <EEPROM.h>

#define serialNumber 50
#define ssidName 50
#define ssidPassword 50
#define userName 50
#define userEmail 50
#define dataMemorySize (_drinkSize*255)

#define serialNumberBegin 0
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
    Memory(int size, Drink &drink, byte drinkSize);
    void clearMemory();
    void clearDataMemory();
    void clearDrinkMemoryAtPosition(byte position);

    void print();
    void printData();
    void printDrinkFromPosition(byte position);
    void getDrinkFromPosition(byte position);
    void setDrinkAtPosition(byte position);

    byte getLastUsedPositionFromBeginScan();
    byte getLastUsedPositionFromEndScan();

    byte getNextPositionToWriteDrink();
    byte getNextPositionToCleanDrink();
    byte getNextPositionToReadDrink();
    

  private:
    int getNextPositionAvailable();
    Drink *_drink;
    int _size;
    byte _drinkSize;

  
};


#endif

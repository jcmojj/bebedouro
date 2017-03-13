#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include "Drink.h"



class Memory{
  public:
    Memory(int size, Drink &drink);
    void teste();
//    boolean checkWaterToSend();
//    void setMililitroAgua(byte dia, byte mes, byte ano2Dig, byte hora, byte minuto, byte mililitroAgua, byte sinalPet); // 7 bytes
//    byte getDia(byte posicao);
//    byte getMes(byte posicao);
//    byte getAno2Dig(byte posicao);
//    byte getHora(byte posicao);
//    byte getMinuto(byte posicao);
//    byte getMililitroAgua(byte posicao);
//    byte getSinalPet(byte posicao);
//    byte getDia(byte posicao);
    
//    void setSerialNumber(char*[10] );
//    *char getSerialNumber();


  private:
//    void apagarPosicao(byte posicao);
    int getPositionAvailable();
    Drink *_drink;
  
};


#endif

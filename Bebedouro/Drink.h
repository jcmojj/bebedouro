#ifndef Drink_h
#define Drink_h

#include "Arduino.h"

class Drink{
  public:
    Drink();
    void setEmpty();
    boolean isEmpty();
    void setValue(byte dia, byte mes, int ano, byte hora, byte minuto, byte segundo, int volumeMl,  char tipoSinal, int sinal); // 8 bytes
    byte getDia();
    byte getMes();
    int getAno();
    byte getHora();
    byte getMinuto();
    byte getSegundo();
    int getVolumeMl();
    char getTipoSinal();
    int getSinal();
    void println();

  private:
    byte _dia;
    byte _mes;
    int _ano;
    byte _hora;
    byte _minuto;
    byte _segundo;
    int _volumeMl;
    char _tipoSinal;
    int _sinal;    
  
};

#endif

#ifndef Drink_h
#define Drink_h

#include "Arduino.h"

class Drink{
  public:
    Drink();
    void setEmpty();
    boolean isEmpty();
    int getSize(); // return the value of bytes of one drink object
    void setValue(byte dia, byte mes, int ano, byte hora, byte minuto, byte segundo, int volumeMl, char tipoSinal, int sinal, byte positionToSendToServer, byte positionReceivedByServer); // 12 bytes
    byte getDia();
    byte getMes();
    int getAno();
    byte getHora();
    byte getMinuto();
    byte getSegundo();
    int getVolumeMl();
    char getTipoSinal();
    int getSinal();
    byte getPositionToSendToServer();
    byte getPositionReceivedByServer();
    
    void setDia(byte dia);
    void setMes(byte mes);
    void setAno(int ano);
    void setHora(byte hora);
    void setMinuto(byte minuto);
    void setSegundo(byte segundo);
    void setVolumeMl(int volumeMl);
    void setTipoSinal(char tipoSinal);
    void setSinal(int sinal);
    void setPositionToSendToServer(byte position);
    void setPositionReceivedByServer(byte position);
    
    void print();

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
    byte _position;    
    byte _positionReceivedByServer;
    byte _positionToSendToServer;
};

#endif

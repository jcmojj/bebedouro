#include "Drink.h"

Drink::Drink(){
  Serial.begin(9600);
  _dia = 0;
  _mes = 0;
  _ano = 0;
  _hora = 0;
  _minuto = 0;
  _segundo = 0;
  _volumeMl = 0;
  _tipoSinal = 0;
  _sinal = 0; 
}


void Drink::setEmpty(){
  _dia = 0;
  _mes = 0;
  _ano = 0;
  _hora = 0;
  _minuto = 0;
  _segundo = 0;
  _volumeMl = 0;
  _tipoSinal = 0;
  _sinal = 0;
}

boolean Drink::isEmpty(){
  if (_dia == 0 && _mes == 0){
    return true;
  }else{
    return false;
  }  
}
void Drink::setValue(byte dia, byte mes, int ano, byte hora, byte minuto, byte segundo, int volumeMl, char tipoSinal, int sinal){
  _dia = dia;
  _mes = mes;
  _ano = ano;
  _hora = hora;
  _minuto = minuto;
  _segundo = segundo;
  _volumeMl = volumeMl;
  _tipoSinal = tipoSinal;
  _sinal = sinal; 
}

byte Drink::getDia(){
  return _dia;
}

byte Drink::getMes(){
  return _mes;
}

int Drink::getAno(){
  return _ano;
}

byte Drink::getHora(){
  return _hora;
}

byte Drink::getMinuto(){
  return _minuto;
}

byte Drink::getSegundo(){
  return _segundo;
}

int Drink::getVolumeMl(){
  return _volumeMl;
}

char Drink::getTipoSinal(){
  return _tipoSinal;
}

int Drink::getSinal(){
  return _sinal;
}

void Drink::setDia(byte dia){
  _dia = dia;
}

void Drink::setMes(byte mes){
  _mes = mes;
}

void Drink::setAno(int ano){
  _ano = ano;
}

void Drink::setHora(byte hora){
  _hora = hora;
}

void Drink::setMinuto(byte minuto){
  _minuto = minuto;
}

void Drink::setSegundo(byte segundo){
  _segundo = segundo;
}

void Drink::setVolumeMl(int volumeMl){
  _volumeMl = volumeMl;
}

void Drink::setTipoSinal(char tipoSinal){
  _tipoSinal = tipoSinal;
}

void Drink::setSinal(int sinal){
  _sinal = sinal;
}

int Drink::getSize(){
  //return _size;
  return 12;
}

void Drink::print(){
  Serial.print(getDia());
  Serial.print("/");Serial.print(getMes());
  Serial.print("/");Serial.print(getAno());
  Serial.print(" - ");Serial.print(getHora());
  Serial.print(":");Serial.print(getMinuto());
  Serial.print(":");Serial.print(getSegundo());
  Serial.print(" - Vol:");Serial.print(getVolumeMl());
  Serial.print("ml - ");Serial.print(getTipoSinal());
  Serial.print(": ");Serial.print(getSinal());
  Serial.println("");  
}


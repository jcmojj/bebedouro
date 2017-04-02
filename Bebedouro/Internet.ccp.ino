#include "Internet.h"



Internet::Internet(WebSocketsClient &webSocket,Memory &memory,Drink &drink){
  Serial.begin(115200);
  _webSocket = &webSocket;
  _memory = &memory;
  _drink = &drink;
  

}

void Internet::connect(){
  _isConnected = true;
}
void Internet::disconnect(){
  _isConnected = false;
}
void Internet::getText(){
  
}
void Internet::getBin(){
  
}

void Internet::sendDrink(byte position){
  _memory->getDrinkFromPosition(position);
  long hash = 12345;
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = "drink";
  
  char emailTeste[] = "jcmojj@gmail.com";
  _memory->setUserEmail(emailTeste);
  Serial.print("Size: "); Serial.println(_memory->getUserEmailSize());
  char emailBuffer[_memory->getUserEmailSize()+1];
  _memory->getUserEmail(emailBuffer);
  Serial.print("emailBuffer: "); Serial.print(emailBuffer);
  root["email"] = String(emailBuffer);
  JsonObject& data = root.createNestedObject("data");
     data["dia"] = _drink->getDia();
     data["mes"] = _drink->getMes();
     data["ano"] = _drink->getAno();;
   JsonObject& horario = root.createNestedObject("horario");
     horario["hora"] = _drink->getHora();
     horario["minuto"] = _drink->getMinuto();
     horario["segundo"] = _drink->getSegundo();
   root["volumeMl"] = _drink->getVolumeMl();
   JsonObject& sinal = root.createNestedObject("sinal");
   String c = String(_drink->getTipoSinal());
      sinal["tipoSinal"] = String(_drink->getTipoSinal());
      sinal["valor"] = _drink->getSinal();
//   root.prettyPrintTo(Serial);
    String output;
    root.printTo(output);
    webSocket.sendTXT(output);
   
   
}

void Internet::check(){
  byte position =  _memory->getNextPositionToReadDrink();
  if (position){
    Serial.print("Sending drink from position:"); Serial.println(position);
    sendDrink(position);
  }
}


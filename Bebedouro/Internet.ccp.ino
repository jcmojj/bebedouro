#include "Internet.h"



Internet::Internet(Service &service, Memory &memory, Drink &drink){
  Serial.begin(115200);
  _memory = &memory;
  _drink = &drink;
  _service = &service;
  _isConnected = false;
  _sendCounter = 0;

}

void Internet::loop(){
  internet.checkDrinkToSend(); // compara o valor e so envia se o valor no position received for zero // nao envia nada
  yield();
  internet.confirmDrinkWasSuccessfullySent(); // anula o valor do position received // confirma o valor 40  e zera o 
}

void Internet::connect(){
  _isConnected = true;
}
void Internet::disconnect(){
  _isConnected = false;
}
bool Internet::isConnected(){
  return _isConnected;
}
bool Internet::checkSendCounter(){
  if(_sendCounter < sendCounterLimit){
    return true;
  }
  return false;
}
byte Internet::getSendCounter(){
  return _sendCounter;
}
byte Internet::addSendCounter(){
  _sendCounter++;
}
byte Internet::clearSendCounter(){
  _sendCounter = 0;
}
void Internet::getText(){
  
}
void Internet::getBin(){
  
}
void Internet::parseJson(uint8_t * json){
  internet.clearSendCounter();
  Serial.println("parseJson");
  StaticJsonBuffer<400> jsonBufferRoot; //400
   JsonObject& root = jsonBufferRoot.parseObject(json);
   if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
   }
//   if( !((byte)root["hash"]) ){
//     StaticJsonBuffer<50> jsonBufferRootIf;
//     JsonObject& rootif = jsonBufferRootIf.createObject();
//     _hashForReceivedMessage = root["hash"];
//     rootif["hashfromserver"] = _hashForReceivedMessage;
//     String output;
//     root.printTo(output);
//     yield();
//     webSocket.sendTXT(output);
//   }
   if( ((byte)root["position"]) ){
//    Serial.println("dentro parse - position");
    _drink->setPositionReceivedByServer(root["position"]);
    drinkToSendTime = millis()+checkDrinkToSendInterval;
    byte teste = (byte)root["position"]; Serial.print("dentro do parse - position: "); Serial.println(teste);
   }
   if(root["Connected"]){
    internet.connect();
   }
   
//   teste = root["position"]; Serial.print("root[position]"); Serial.println(teste);
  
}
void Internet::sendDrink(){
  yield();
  StaticJsonBuffer<400> jsonBuffer; //400
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = "drink";
  
  char emailBuffer[userEmailSpace+1];
  emailBuffer[userEmailSpace] = '\0';
  _memory->getUserEmail(emailBuffer);
  
  root["email"] = String(emailBuffer);
  root["position"] = _drink->getPositionToSendToServer();
  JsonObject& date = root.createNestedObject("date");
     date["dia"] = _drink->getDia();
     date["mes"] = _drink->getMes();
     date["ano"] = _drink->getAno();;
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
    Serial.print("Tentando enviar: "); Serial.println(output);
    
    yield();
    internet.addSendCounter();
    webSocket.sendTXT(output);
   Serial.print("SendDrink Position: ");Serial.println(_drink->getPositionToSendToServer()); 
//   //SIMULANDO APAGAR DEPOIS ----- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   Serial.print("Simulando: _drink->getPositionToSendToServer(): "); Serial.print(_drink->getPositionToSendToServer());
//  // --->>>> mandar um json simulando a resposta do servidor _drink->setPositionReceivedByServer(_drink->getPositionToSendToServer());
//   StaticJsonBuffer<50> jsonBuffersim;
//   JsonObject& rootsim = jsonBuffersim.createObject();
//   rootsim["drinkpositionreceived"] = _memory->getPositionToSendToServer();
//    String output;
//    rootsim.printTo(output);
//    yield();
//    webSocket.sendTXT(output);
//   //SIMULANDO APAGAR DEPOIS -----
}

void Internet::checkDrinkToSend(){
  yield();
//  drinkToSendTime = millis();
//  byte position =  _memory->getNextPositionToReadDrink();
//Serial.print("(millis()-drinkToSendTime): "); Serial.print((millis()-drinkToSendTime));
//Serial.print(" -((millis()-drinkToSendTime)>checkDrinkToSendInterval): "); Serial.println(((millis()-drinkToSendTime)>checkDrinkToSendInterval));
  if (internet.isConnected()&&(_memory->getNextDrinkToSendToServer())&&
      ((millis()-drinkToSendTime)>checkDrinkToSendInterval)&&
      !(_drink->getPositionReceivedByServer())&&
      checkSendCounter()
      ){
//    Serial.print("Sending drink from position:"); Serial.println(position);
    Serial.print("Entrou no checkDrinkToSend - Enviando Position: "); Serial.println(_drink->getPositionToSendToServer());
    sendDrink();
    drinkToSendTime = millis();
  }
}

void Internet::confirmDrinkWasSuccessfullySent(){
  //SIMULANDO APAGAR DEPOIS ----- fazer o local para recebero json e confirmar o recebimento pelo servidor
  if(((_drink->getPositionToSendToServer()) == _drink->getPositionReceivedByServer())&&
  //  ((_drink->getPositionToSendToServer()) != 0)&&
    (_drink->getPositionReceivedByServer() != 0)){
        Serial.print("confirmDrinkWasSuccessfullySent - ");
        Serial.print("Received Drink Position: ");Serial.print(_drink->getPositionReceivedByServer()); 
  //   _drink->setPositionToSendToServer(0);
     
//     Serial.print(" - PositionToSendToServer(): "); Serial.print(_drink->getPositionToSendToServer()); 
//     Serial.print("- PositionReceivedByServer(): "); Serial.println(_drink->getPositionReceivedByServer());
    _memory->lastDrinkWasSentToServerWithSucess(); 
//    _memory->printData();   
  }
  _drink->setPositionReceivedByServer(0);// tenho que zerar de qq forma para poder liberar enviar outro nesse meio tempo.. senao nao envia

//  tento enviar outro ---> acho que ele faz isso sozinho
  
}

void Internet::jsonTest(){
  StaticJsonBuffer<400> jsonBuffer; //400
  JsonObject& root = jsonBuffer.createObject();
  root["email"] = "jcmojj@gmail.com";
  String output;
  root.printTo(output);
  Serial.print("Tentando enviar: "); Serial.println(output);
  
  Serial.println("parseJson");
  StaticJsonBuffer<400> jsonBufferRoot2; //400
  JsonObject& root2 = jsonBufferRoot2.parseObject(output);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
   }

   Serial.print("\nTestando Json - Write");
   String teste = root["email"];
   Serial.print("Write: "); Serial.println(teste);
   int tamanho = sizeof(teste);
   Serial.print("Tamanho: "); Serial.println(tamanho);
   int posmax =0;
   while((teste[posmax] != '\0')){//&&(posmax<tamanho)){
    posmax++;
   }
   Serial.print("Posmax: "); Serial.println(posmax);

   Serial.print("\nTestando Json - Read");
   String teste2 = root2["email"];
   Serial.print("Read: "); Serial.println(teste2); 
   int tamanho2 =  sizeof(teste2);
   Serial.print("Tamanho: "); Serial.println(tamanho2);
   int posmax2 =0;
   while((teste2[posmax2] != '\0')&&(posmax2<tamanho2)){
    posmax2++;
   }
   Serial.print("Posmax: "); Serial.println(posmax2);   
}


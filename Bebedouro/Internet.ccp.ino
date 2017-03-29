#include "Internet.h"



Internet::Internet(WebSocketsClient &webSocket,Memory &memory,Drink &drink){
  Serial.begin(115200);
//  _webSocket = &webSocket;
//  _memory = &memory;
//  _drink = &drink;
  

}
//
//void Internet::connect(){
//  Serial.print("Internet conectada");
////  _isConnected = true;
//}
//void Internet::disconnect(){
////  _isConnected = false;
////}
//void Internet::getText(){
//  
//}
//void Internet::getBin(){
//  
//}
//
//void Internet::sendDrink(byte drink){
//  
//}

//void Internet::check(){
//  byte drinkToSend = 0;// _memory->getNextDrinkToSendToServer();
//  if (drinkToSend > 0){
//    Serial.print("Sending drink from position:"); Serial.println(drinkToSend);
//    sendDrink(drinkToSend);
//  }
//}


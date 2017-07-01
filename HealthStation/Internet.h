#ifndef Internet_h
#define Internet_h

#define checkDrinkToSendInterval 2000 //16382 // 16,3s
unsigned long drinkToSendTime = 0;
#define sendCounterLimit  50

#include "Arduino.h"

#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

#include <WiFiMulti.h> // #include <ESP8266WiFiMulti.h>   // WebSocket 
#include <WebSocketsClient.h>   // WebSocket 
#include <Hash.h>               // WebSocket 
#include <WiFi.h>         //https://github.com/esp8266/Arduino //#include <ESP8266WiFi.h>        // WiFiManager WebSocket 
#include <ArduinoJson.h>        // Json


class Internet{
  public:
    Internet(Service &service, Memory &memory,Drink &drink);
//    void connect();
//    void disconnect();
//    bool isConnected();
//    void getText();
//    void getBin();
//    void parseJson(uint8_t * payload);
//    void sendDrink();
//    void checkDrinkToSend();
//    void confirmDrinkWasSuccessfullySent();
//    byte getSendCounter();
//    byte addSendCounter();
//    byte clearSendCounter();
//    bool checkSendCounter();
//    void loop();
//    void jsonTest();

  private:
//    WebSocketsClient *_webSocket;
    Memory *_memory;
    Drink *_drink;
    Service *_service;
//    bool _isConnected;
//    unsigned long _hashForSentMessage;
//    unsigned long _hashForReceivedMessage;
//    byte _sendCounter;
  
};

#endif

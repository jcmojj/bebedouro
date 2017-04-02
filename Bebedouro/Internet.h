#ifndef Internet_h
#define Internet_h

#include "Arduino.h"
#include <ESP8266WiFiMulti.h>   // WebSocket 
#include <WebSocketsClient.h>   // WebSocket 
#include <Hash.h>               // WebSocket 
#include <ESP8266WiFi.h>        // WiFiManager WebSocket 
#include <ArduinoJson.h>        // Json


class Internet{
  public:
    Internet(WebSocketsClient &webSocket,Memory &memory,Drink &drink);
    void connect();
    void disconnect();
    void getText();
    void getBin();
    void sendDrink(byte drink);
    void check();

  private:
    WebSocketsClient *_webSocket;
    Memory *_memory;
    Drink *_drink;
    bool _isConnected;
  
};

#endif

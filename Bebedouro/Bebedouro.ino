#include "Drink.h"
#include "Memory.h"
#include "Internet.h"

// arduino OTA para fazer atualizacao pelo ar
// DEFINIR STA ou Access Point -- conexao pelo celular

#include <ESP8266WiFi.h>        // WiFiManager WebSocket 
#include <DNSServer.h>          // WiFiManager
#include <ESP8266WebServer.h>   // WiFiManager
#include <WiFiManager.h>        // WiFiManager
#include <Ticker.h>             // WiFiManager

#include <ESP8266WiFiMulti.h>   // WebSocket 
#include <WebSocketsClient.h>   // WebSocket 
#include <Hash.h>               // WebSocket 

Ticker ticker;                  // WiFiManager

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;



Drink drink = Drink();
//Memory memory = Memory(4095, drink, drink.getSize());
Memory memory = Memory(drink, drink.getSize());
//  Memory memory = Memory(drink, drink.getSize(),jsonDrink);
Internet internet = Internet(webSocket,memory,drink);

//int i = 0;


  /* ------------------------------------------------------------------- */
  /* -----------------------        SETUP        ----------------------- */
  /* ------------------------------------------------------------------- */
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

//  drink.setValue(20, 2, 17, 11, 50, 30, 57, 'c', 111);
//  memory.saveDrinkAtMemory();
  memory.printData();
  /* ----------------------- SETUP - WiFiManager ----------------------- */
  pinMode(BUILTIN_LED, OUTPUT);
  ticker.attach(0.6, tick);
  WiFiManager wifiManager;
//  wifiManager.resetSettings(); //reset saved settings
  // wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0)); // pode ser que o certo seja antes do if, mas acho que tanto faz
  // wifiManager.setSTAStaticIPConfig(IPAddress(192,168,0,99), IPAddress(192,168,0,1), IPAddress(255,255,255,0));//wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn); / ip gateway subnet mask
  // wifiManager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>"); // add html head info
  // WiFiManagerParameter custom_text("<p>This is just a text paragraph</p>"); // add text info
  // wifiManager.addParameter(&custom_text); // add text info
  // WiFiManagerParameter custom_mqtt_server("server", "mqtt server", "iot.eclipse", 40, " readonly"); // didn't get it
   wifiManager.setMinimumSignalQuality(20); // filter networks with less than 10
  // wifiManager.setDebugOutput(false); // turn it false when put to production  
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setTimeout(360);
  if(!wifiManager.autoConnect("MyKidPet","truncitec")) {// acess point name and password
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    delay(3000);
    ESP.reset();
    delay(5000);
  }
//  /ESP8266WIFISTA.h
  Serial.print("local ip: "); Serial.println(WiFi.localIP());
  Serial.print("subnetMask: "); Serial.println(WiFi.subnetMask());
  Serial.print("gatewayIP: "); Serial.println(WiFi.gatewayIP());  
  Serial.print("dnsIP: "); Serial.println(WiFi.dnsIP());  
  Serial.print("macAddress: "); Serial.println(WiFi.macAddress());
  Serial.print("hostname: "); Serial.println(WiFi.hostname());

  Serial.print("WIFI SSID: ");Serial.println(WiFi.SSID());
  Serial.print("WIFI BSSI MAC: ");Serial.println(WiFi.BSSIDstr());
  Serial.print("WIFI Password: ");Serial.println(WiFi.psk());
  Serial.print("WIFI RSSI sinal: ");Serial.println(WiFi.RSSI());
  
  wifiManager.autoConnect("MyKidPet"); // WiFiManager
  Serial.println("connected...yeey :)"); 
  ticker.detach();
  digitalWrite(BUILTIN_LED, LOW); //keep LED on
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  /* ----------------------- SETUP - WiFiManager ----------------------- */
  
//  memory.clearDataMemory();
//  for(byte mes = 1; mes<11 ; mes++){
//    for(byte dia = 1; dia<30 ; dia ++){
//      drink.setValue(dia,mes,1984,9,50,30,57,'c',111);
//      memory.saveDrinkAtMemory();
//    }
//  }

  Serial.println("Fim do WiFi Manager");
//     webSocket.begin("ws://localhost:8080/EchoChamber/echo", 80);
     webSocket.begin("echo.websocket.org", 80, "/echo","arduino");
     webSocket.onEvent(webSocketEvent);

     Serial.print("Fim WebSocket");
   char emailTeste[] = "jcmojj@gmail.com";
//  memory.setUserEmail(emailTeste);

  memory.print();
//  memory.printData();
//ticker.attach(10, internetcheck);
}
  /* ------------------------------------------------------------------- */
  /* -----------------------     END - SETUP     ----------------------- */
  /* ------------------------------------------------------------------- */




  /* ------------------------------------------------------------------- */
  /* -----------------------         LOOP        ----------------------- */
  /* ------------------------------------------------------------------- */
void loop() {

  webSocket.loop();
//  internet.check();



  
//  Serial.print("i= ");Serial.print(i); Serial.print("->");
//  if (i==5){
//    Serial.print("5-");
//    webSocket.sendTXT("Send: 5");
//  }

//i++;
  delay(10);

}
  /* ------------------------------------------------------------------- */
  /* -----------------------      END - LOOP     ----------------------- */
  /* ------------------------------------------------------------------- */




  /* ------------------------------------------------------------------- */
  /* -----------------------     WiFi Manager    ----------------------- */
  /* ------------------------------------------------------------------- */
// WiFiManager
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  ticker.attach(0.2, tick);
}

void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

  /* ------------------------------------------------------------------- */
  /* -----------------------  END - WiFi Manager ----------------------- */
  /* ------------------------------------------------------------------- */




  #define Serial Serial
//void internetcheck(){internet.check();}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {


    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            internet.disconnect();
            break;
        case WStype_CONNECTED:
            {
                Serial.printf("[WSc] Connected to url: %s\n",  payload);
                internet.connect();
        
          // send message to server when Connected
        webSocket.sendTXT("Connected");
//        i=1;
            }
            break;
        case WStype_TEXT:
            Serial.printf("[WSc] get text: %s\n", payload);
            internet.getText();
      // send message to server
      // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary lenght: %u\n", lenght);
            hexdump(payload, lenght);
            internet.getBin();
            // send data to server
            // webSocket.sendBIN(payload, lenght);
            break;
    }

}

#include "Drink.h"
#include "Memory.h"
#include "Service.h"
#include "Internet.h"

// WifiManager(begin)
#include <WiFi.h>         //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#define TRIGGER_PIN 0
// WifiManager(end)

#include "time.h"
time_t this_second = 0;
time_t last_second = 0;

Drink drink = Drink();
Memory memory = Memory(drink, drink.getSize());
Service service = Service(memory,drink);
Internet internet = Internet(service, memory,drink);

void setup() {
    Serial.begin(115200);
    while (!Serial) {
      ;
    }
    // WifiManager(begin)
    Serial.println("\n Starting");
    pinMode(TRIGGER_PIN, INPUT);
    wifiManagerConnect();
    // WifiManager(end)

delay(1000);
 configTime(0, 0, "br.pool.ntp.org","time.nist.gov", "time.windows.com");
     while (!time(nullptr)) {
        Serial.print(".");
        delay(1000);
    }
        time_t now = time(nullptr);
    Serial.println(ctime(&now));
    printLocalTime();
    delay(3000);
    printLocalTime();
}

void printLocalTime()
{
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}



void loop() {

//teste
    time(&this_second); // atualiza a hora e me devolve os segundos atuais
     if (this_second != last_second)
     {
         last_second = this_second;
         if ((this_second % 5) == 0)
         {
             Serial.print(ctime(&this_second));
         }
         struct tm * ptm = {0};
         ptm = gmtime ( &this_second );
         Serial.print("\nSeg: ");Serial.print(ptm->tm_sec);
         Serial.print(" - Min:");Serial.print(ptm->tm_min);
         Serial.print(" - Hora: ");Serial.print(ptm->tm_hour);
         Serial.print(" - DiaMes: ");Serial.print(ptm->tm_mday);
         Serial.print(" - Mes: ");Serial.print(ptm->tm_mon);
         Serial.print(" - Ano: ");Serial.print(ptm->tm_year);
         Serial.print(" - DiaSemana: ");Serial.print(ptm->tm_wday);
         Serial.print(" - DiaAno: ");Serial.print(ptm->tm_yday);
         

     }
     struct tm timeinfo;
     if(getLocalTime(&timeinfo)){
        Serial.println("Correct");

    }else{
      Serial.println("Failed to obtain time - Retry");
      configTime(3600, 3600, "br.pool.ntp.org","time.nist.gov", "time.windows.com");

    }
     delay(500);
//teste
  
  
    
  // WifiManager(begin)
  // is configuration portal requested?
//  if ( digitalRead(TRIGGER_PIN) == LOW ) {
//    wifiManagerConnectOnDemand();
//  }
// WifiManager(end)
}

// WifiManager(begin)
void wifiManagerConnect(){ // quando perde a conexão entra nesse modo
    WiFiManager wifiManager;
    //wifiManager.resetSettings(); //reset saved settings
    
//    wifiManager.setMinimumSignalQuality(20); // filter networks with less than 20
//    wifiManager.setTimeout(20); // qdo acaba luz espera esse tempo p entrar no modo de config
    wifiManager.setBreakAfterConfig(true);
//    wifiManager.setAPCallback(configModeCallback);
//    wifiManager.setDebugOutput(true);
//    wifiManager.setRemoveDuplicateAPs(true);


    if (!wifiManager.autoConnect("MyKidPet","12345678")) {// nao tem sentido ter senha uma rede que vai ficar aberta pouco tempo
      Serial.println("failed to connect and hit timeout");
      delay(3000);
  Serial.print("local ip: "); Serial.println(WiFi.localIP());
  Serial.print("subnetMask: "); Serial.println(WiFi.subnetMask());
  Serial.print("gatewayIP: "); Serial.println(WiFi.gatewayIP());  
  Serial.print("dnsIP: "); Serial.println(WiFi.dnsIP());  
  Serial.print("macAddress: "); Serial.println(WiFi.macAddress());
//  Serial.print("hostname: "); Serial.println(WiFi.hostname());

  Serial.print("WIFI SSID: ");Serial.println(WiFi.SSID());
  Serial.print("WIFI BSSI MAC: ");Serial.println(WiFi.BSSIDstr());
  Serial.print("WIFI Password: ");Serial.println(WiFi.psk());
  Serial.print("WIFI RSSI sinal: ");Serial.println(WiFi.RSSI());
  Serial.println("");
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }
    Serial.println("connected...yeey :)");
    Serial.print("\nlocal ip: ");  Serial.println(WiFi.localIP());
}

//void wifiManagerConnectOnDemand(){ // quando botao for apertado
//    WiFiManager wifiManager;
//    //wifiManager.resetSettings(); //reset saved settings
//    wifiManager.setMinimumSignalQuality(20); // filter networks with less than 20
//    wifiManager.setTimeout(120);
//    wifiManager.setBreakAfterConfig(true);
// 
//    if (!wifiManager.startConfigPortal("MyKidPet","truncitec")) {
//      Serial.println("failed to connect and hit timeout");
//      delay(3000);
//      //reset and try again, or maybe put it to deep sleep
//      ESP.restart();
//      delay(5000);
//    }
//    Serial.println("connected...yeey :)");
//    Serial.print("\nlocal ip: ");  Serial.println(WiFi.localIP());
//}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode(callBack):");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
//  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.print("local ip: "); Serial.println(WiFi.localIP());
  Serial.print("subnetMask: "); Serial.println(WiFi.subnetMask());
  Serial.print("gatewayIP: "); Serial.println(WiFi.gatewayIP());  
  Serial.print("dnsIP: "); Serial.println(WiFi.dnsIP());  
  Serial.print("macAddress: "); Serial.println(WiFi.macAddress());
//  Serial.print("hostname: "); Serial.println(WiFi.hostname());

  Serial.print("WIFI SSID: ");Serial.println(WiFi.SSID());
  Serial.print("WIFI BSSI MAC: ");Serial.println(WiFi.BSSIDstr());
  Serial.print("WIFI Password: ");Serial.println(WiFi.psk());
  Serial.print("WIFI RSSI sinal: ");Serial.println(WiFi.RSSI());
  Serial.println("");
}
// WifiManager(end)

//#include "Drink.h"
//#include "Memory.h"
//#include "Service.h"
//#include "Internet.h"
//
//
//// arduino OTA para fazer atualizacao pelo ar
//// DEFINIR STA ou Access Point -- conexao pelo celular
//
//#include <ESP8266WiFi.h>        // WiFiManager WebSocket 
//#include <DNSServer.h>          // WiFiManager
//#include <ESP8266WebServer.h>   // WiFiManager
//#include <WiFiManager.h>        // WiFiManager
//#include <Ticker.h>             // WiFiManager
//
//#include <ESP8266WiFiMulti.h>   // WebSocket 
//#include <WebSocketsClient.h>   // WebSocket 
//#include <Hash.h>               // WebSocket 
//
////#define DEBUG_ESP_PORT Serial;
//
//Ticker ticker;                  // WiFiManager
//
//ESP8266WiFiMulti WiFiMulti;
//WebSocketsClient webSocket;
//
//
//
//Drink drink = Drink();
////Memory memory = Memory(4095, drink, drink.getSize());
//Memory memory = Memory(drink, drink.getSize());
////  Memory memory = Memory(drink, drink.getSize(),jsonDrink);
//Service service = Service(memory,drink);
//Internet internet = Internet(service, memory,drink);
//
//
////int i = 0;
//
//
//  /* ------------------------------------------------------------------- */
//  /* -----------------------        SETUP        ----------------------- */
//  /* ------------------------------------------------------------------- */
//void setup() {
//  Serial.begin(115200);
//  while (!Serial) {
//    ;
//  }
////
////  drink.setValue(20, 2, 17, 11, 50, 30, 57, 'c', 111,100,120);
////  memory.saveDrinkAtMemory();
////  memory.printData();
//  /* ----------------------- SETUP - WiFiManager ----------------------- */
//  pinMode(BUILTIN_LED, OUTPUT);
//  service.begin();
//  ticker.attach(0.6, tick);
//  WiFiManager wifiManager;
////  wifiManager.resetSettings(); //reset saved settings
//  // wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0)); // pode ser que o certo seja antes do if, mas acho que tanto faz
//  // wifiManager.setSTAStaticIPConfig(IPAddress(192,168,0,99), IPAddress(192,168,0,1), IPAddress(255,255,255,0));//wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn); / ip gateway subnet mask
//  // wifiManager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>"); // add html head info
//  // WiFiManagerParameter custom_text("<p>This is just a text paragraph</p>"); // add text info
//  // wifiManager.addParameter(&custom_text); // add text info
//  // WiFiManagerParameter custom_mqtt_server("server", "mqtt server", "iot.eclipse", 40, " readonly"); // didn't get it
//   wifiManager.setMinimumSignalQuality(20); // filter networks with less than 10
//  // wifiManager.setDebugOutput(false); // turn it false when put to production  
//  wifiManager.setAPCallback(configModeCallback);
//  wifiManager.setTimeout(360);
//  if(!wifiManager.autoConnect("MyKidPet","truncitec")) {// acess point name and password
//    Serial.println("failed to connect and hit timeout");
//    //reset and try again, or maybe put it to deep sleep
//    delay(3000);
//    ESP.reset();
//    delay(5000);
//  }
////  /ESP8266WIFISTA.h
//  Serial.print("local ip: "); Serial.println(WiFi.localIP());
//  Serial.print("subnetMask: "); Serial.println(WiFi.subnetMask());
//  Serial.print("gatewayIP: "); Serial.println(WiFi.gatewayIP());  
//  Serial.print("dnsIP: "); Serial.println(WiFi.dnsIP());  
//  Serial.print("macAddress: "); Serial.println(WiFi.macAddress());
//  Serial.print("hostname: "); Serial.println(WiFi.hostname());
//
//  Serial.print("WIFI SSID: ");Serial.println(WiFi.SSID());
//  Serial.print("WIFI BSSI MAC: ");Serial.println(WiFi.BSSIDstr());
//  Serial.print("WIFI Password: ");Serial.println(WiFi.psk());
//  Serial.print("WIFI RSSI sinal: ");Serial.println(WiFi.RSSI());
//  
//  wifiManager.autoConnect("MyKidPet"); // WiFiManager
//  Serial.println("connected...yeey :)"); 
//  ticker.detach();
//  digitalWrite(BUILTIN_LED, LOW); //keep LED on
//  Serial.println("local ip");
//  Serial.println(WiFi.localIP());
//  /* ----------------------- SETUP - WiFiManager ----------------------- */
//   Serial.println("Fim do WiFi Manager"); 
////// teste da memoria recebendo alarmes
////  memory.DrinkAlarmTest();
////  zerando e preenchendo a memoria
//  
//  //memory.memoryTest();//<-----------------------------------
//
//
////     webSocket.begin("ws://localhost:8080/EchoChamber/echo", 80);
////     webSocket.begin("echo.websocket.org", 80, "/echo","arduino");
////     webSocket.begin("echo.websocket.org", 80, "/echo","arduino");
//       webSocket.begin("websocket-echo.herokuapp.com", 80, "/","arduino"); //melhor<-----
////webSocket.beginSocketIO("socketio-echo.herokuapp.com", 81, "/","arduino");
////webSocket.beginSocketIO("socketio-echo.herokuapp.com", 80, "/socket.io/?EIO=3");
////webSocket.beginSocketIO("socketio-echo.herokuapp.com", 80, "/socket.io/?EIO=3&transport=websocket"); // melhor 2
//
////webSocket.beginSocketIO("socketio-echo.herokuapp.com", 80);
////webSocket.beginSocketIO("https://socketio-chat-example.now.sh/", 80);
////webSocket.beginSocketIO("socketio-chat-example.now.sh/", 80);
//
////webSocket.beginSocketIO("socketio-echo.herokuapp.com", 80, "/","arduino");
//
////webSocket.beginSocketIO("http://socketio-echo.herokuapp.com", 80);
////webSocket.beginSocketIO("https://socketio-echo.herokuapp.com", 80); ---->>>>  teste: webSocket.beginSSL("webrouter.server", 443, "/path"); https://github.com/esp8266/Arduino/issues/1442
////webSocket.beginSocketIO("ws://socketio-echo.herokuapp.com", 80); ---->>>>> errado: webSocket.beginSSL("wss://echo.websocket.org") or just webSocket.beginSSL("echo.websocket.org")
////webSocket.beginSocketIO("wss://socketio-echo.herokuapp.com", 80); ----->>>> certo: webSocket.beginSSL("echo.websocket.org", 443);
//
////     webSocket.beginSSL("http://echo.herokuapp.com/", 80, "/","arduino");
// //webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
//
//     webSocket.onEvent(webSocketEvent);
//
//     Serial.print("Fim WebSocket");
////   char emailTeste[] = "jcmojj@gmail.com";
////  memory.setUserEmail(emailTeste);
//
////  memory.print();
////  memory.clearDataMemory();
////  memory.printData();
//
////ticker.attach(10, internetcheck);
//
//// Testes Setup
////memory.memTest();
////internet.jsonTest();
////memory.memoryTest();//apaga e testa
//
////  service.begin();//<------------------
//}
//  /* ------------------------------------------------------------------- */
//  /* -----------------------     END - SETUP     ----------------------- */
//  /* ------------------------------------------------------------------- */
//
//
//
//
//  /* ------------------------------------------------------------------- */
//  /* -----------------------         LOOP        ----------------------- */
//  /* ------------------------------------------------------------------- */
//void loop() {
//  
//  webSocket.loop(); // coloca um valor no position receive // verifica que recebeu o valor position = 40
//  internet.loop();
////  service.loop();
//
//
//  
////  Serial.print("i= ");Serial.print(i); Serial.print("->");
////  if (i==5){
////    Serial.print("5-");
////    webSocket.sendTXT("Send: 5");
////  }
//
////i++;
////  delay(10);
//
//}
//  /* ------------------------------------------------------------------- */
//  /* -----------------------      END - LOOP     ----------------------- */
//  /* ------------------------------------------------------------------- */
//
//
//
//
//  /* ------------------------------------------------------------------- */
//  /* -----------------------     WiFi Manager    ----------------------- */
//  /* ------------------------------------------------------------------- */
//// WiFiManager
//void configModeCallback (WiFiManager *myWiFiManager) {
//  Serial.println("Entered config mode");
//  Serial.println(WiFi.softAPIP());
//  //if you used auto generated SSID, print it
//  Serial.println(myWiFiManager->getConfigPortalSSID());
//  ticker.attach(0.2, tick);
//}
//
//void tick()
//{
//  //toggle state
//  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
//  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
//}
//
//  /* ------------------------------------------------------------------- */
//  /* -----------------------  END - WiFi Manager ----------------------- */
//  /* ------------------------------------------------------------------- */
//
//
//
//
//  #define Serial Serial
////void internetcheck(){internet.check();}
//
//void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
//
//
//    switch(type) {
//        case WStype_DISCONNECTED:
//            Serial.printf("[WSc] Disconnected!\n");
//            internet.disconnect();
//            break;
//        case WStype_CONNECTED:
//            {
//                Serial.printf("[WSc] Connected to url: %s\n",  payload);
//                
//        
//          // send message to server when Connected
//        webSocket.sendTXT("{\"Connected\":1}");
////        i=1;
//            }
//            break;
//        case WStype_TEXT:
//            Serial.printf("[WSc] get text: %s\n", payload);
//            internet.parseJson(payload);
//            internet.getText();
//            //logica parar parsear info do server -- se voltar drinkpositionreceived x// ai ativo o posicaoRecebida
//      // send message to server
////       webSocket.sendTXT("NERI VIADINHO!");
//            break;
//        case WStype_BIN:
//            Serial.printf("[WSc] get binary lenght: %u\n", lenght);
//            hexdump(payload, lenght);
//            internet.getBin();
//            // send data to server
//            // webSocket.sendBIN(payload, lenght);
//            break;
//    }
//
//}

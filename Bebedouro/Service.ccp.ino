#include "Service.h"

Service::Service(Memory &memory, Drink &drink) {
//  Rtc.Begin();
  _memory = &memory;
  _drink = &drink;


}
void Service::begin(){
  memory.rtcBegin();
  _clockInterval = 0;
  _clockMillis = 0;
}
void Service::loop() {
  if((_clockMillis-millis()) > _clockInterval){
    memory.updateClock();
  }
  
}
/* ------------------------------------------- RTC ------------------------------------------- */

/* ------------------------------------------- RTC ------------------------------------------- */




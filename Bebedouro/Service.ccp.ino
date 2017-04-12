#include "Service.h"

Service::Service(Memory &memory, Drink &drink) {
//  Rtc.Begin();
  _memory = &memory;
  _drink = &drink;


}
void Service::begin(){
  memory.rtcBegin();
}
void Service::loop() {
//  getClockTime();
}
/* ------------------------------------------- RTC ------------------------------------------- */

/* ------------------------------------------- RTC ------------------------------------------- */




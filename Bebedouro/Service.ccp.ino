#include "Service.h"

Service::Service(Memory &memory, Drink &drink) {
  Rtc.Begin();
  _memory = &memory;
  _drink = &drink;


  /* ------------------------------------------- RTC ------------------------------------------- */
  Serial.print("RTC compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);
  //--------RTC SETUP ------------

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  //    printTime(const compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
    // Common Cuases:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");

    // following line sets the RTC to the date & time this sketch was compiled
    // it will also reset the valid flag internally unless the Rtc device is
    // having an issue

    Rtc.SetDateTime(compiled);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.Enable32kHzPin(false);
  //    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmBoth);
  
  atualizarAlarmes();

  /* ------------------------------------------- RTC ------------------------------------------- */


}

void Service::loop() {
  getClockTime();
}
/* ------------------------------------------- RTC ------------------------------------------- */
void Service::atualizarAlarmes(){

//   // Alarm 1 set to trigger every day when 
//  // the hours, minutes, and seconds match
//  RtcDateTime alarmTime = now + 88; // into the future
//  
//  DS3231AlarmOne alarm1( // momento de lavar pote
//    alarmTime.Day(),
//    alarmTime.Hour(),
//    alarmTime.Minute(),
//    alarmTime.Second(),
//    DS3231AlarmOneControl_HoursMinutesSecondsMatch);
//  Rtc.SetAlarmOne(alarm1);
//
//  // Alarm 2 set to trigger at the top of the minute
//  DS3231AlarmTwo alarm2(  // momento de encher agua ou colocar comida
//    0,
//    0,
//    0,
//    DS3231AlarmTwoControl_OncePerMinute);
//  Rtc.SetAlarmTwo(alarm2);
//
//  // throw away any old alarm state before we ran
//  Rtc.LatchAlarmsTriggeredFlags();
  
}
void Service::getClockTime() {
  RtcDateTime now = Rtc.GetDateTime();
  //  printTime(const now);
}
void Service::setClockTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, uint8_t hour, uint8_t minute, uint8_t second) {
  Rtc.SetIsRunning(false);
  Rtc.SetDateTime(RtcDateTime(year, month, dayOfMonth, hour, minute, second));
  Rtc.SetIsRunning(true);
  if (isDateTimeValid()) {
    Serial.println("Hora Atualizada com Sucesso");
  }
  printNowDateTime();
}
void Service::printDateTime(const RtcDateTime& dt) {
  char datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}
void Service::printNowDateTime() {
  RtcDateTime dt = Rtc.GetDateTime();
  char datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}
float Service::getTemperature() {
  RtcTemperature temp = Rtc.GetTemperature();
  Serial.print(temp.AsFloat());
  Serial.println("C");
  return temp.AsFloat();
}
void Service::printTemperature() {
  Serial.print( (Rtc.GetTemperature()).AsFloat());
  Serial.println("C");
}
bool Service::isDateTimeValid() {
  Serial.println("RTC lost confidence in the DateTime!");
  return Rtc.IsDateTimeValid();
}
/* ------------------------------------------- RTC ------------------------------------------- */




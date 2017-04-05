#ifndef Service_h
#define Service_h

#include "Arduino.h"



#include <pgmspace.h>
// CONNECTIONS:

//3.3V
//ADC0
//D0/GPIO16 - USER/WAKE - ONLY READ/WRITE - NO PWM/I2C/OW
//D1/GPIO5 - DS3231 SCL
//D2/GPIO4 - DS3231 SDA
//D3/GPIO0 - FLASH
//D4/GPIO2 - TXD1(UART)
//D5/GPIO14 - HSCLK(hSPI)
//D6/GPIO12 - HMISO(hSPI)
//D7/GPIO13 - HMOSI(hSPI) / RXD2(UART)
//D8/GPIO15 - HCS(hSPI) / TXD2(UART)
//D9/GPIO3 - RXD0(UART)
//D10/GPIO1 - TXD0(UART)
//GND - GND
//3.3V - 3V3
//
//A0/ADC0 - TOUT
//SD3/GPIO10 - SDD3
//SD2/GPIO9 - SDD2
//SD1/MOSI(SPI) - SDD1
//CMD/CS(SPI) - SDCMD
//SD0/MISO(SPI)  -SDD0
//CLK/SCLK(SPI) - SDCLK
//VIN - VIN 5V(POWER)




// DS3231 SDA --> SDA D4
// DS3231 SCL --> SCL D5
// DS3231 VCC --> 3.3v or 5v
// DS3231 GND --> GND
#include <RtcDS3231.h>
#include <Wire.h> // must be included here so that Arduino library object file references work
RtcDS3231<TwoWire> Rtc(Wire);
RtcDateTime now;
#define countof(a) (sizeof(a) / sizeof(a[0]))

//#include <SoftwareWire.h>  // must be included here so that Arduino library object file references work
//SoftwareWire myWire(SDA, SCL);
//RtcDS3231<SoftwareWire> Rtc(myWire);



class Service{
  public:
    Service(Memory &memory,Drink &drink);
    void loop();
    void getClockTime();
    void setClockTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, uint8_t hour, uint8_t minute, uint8_t second);
    void printDateTime(const RtcDateTime& dt);
    void printNowDateTime();    
    bool isDateTimeValid();
    float getTemperature();
    void printTemperature();
    void atualizarAlarmes();
    
    
  private:
    Memory *_memory;
    Drink *_drink;
};

#endif

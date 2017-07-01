#ifndef Service_h
#define Service_h

#include "Arduino.h"
//#include <RtcDateTime.h>

#define analogPin A0
#define outputA0  D6
#define outputA1  D7
#define outputA2  D8


//#include <pgmspace.h>
/* CONNECTIONS:

//3.3V
//ADC0
//D0/GPIO16 - USER/WAKE - ONLY READ/WRITE - NO PWM/I2C/OW
//D1/GPIO5 - DS3231 SCL --> SCL D5
//D2/GPIO4 - DS3231 SDA --> SDA D4
//D3/GPIO0 - FLASH
//D4/GPIO2 - TXD1(UART)
//D5/GPIO14 - HSCLK(hSPI)
//D6/GPIO12 - HMISO(hSPI)               - outputA0 CD4051
//D7/GPIO13 - HMOSI(hSPI) / RXD2(UART)  - outputA1 CD4051
//D8/GPIO15 - HCS(hSPI) / TXD2(UART)    - outputA2 CD4051
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


DS3231 SDA --> SDA D4
DS3231 SCL --> SCL D5
DS3231 VCC --> 3.3v or 5v
DS3231 GND --> GND
*/



/*CD4051 - http://labdegaragem.com/profiles/blogs/tutorial-sobre-4051-multiplexador-demultiplexador-e-como-utiliz
 * PINOS - 1 debaixo com bola a esquerda- conta sentido anti-horario
 * 1-Y4 - 100
 * 2-Y6 - 110
 * 3-Z - PORTA ANALOGICA ARDUINO - A0
 * 4-Y7 - 111
 * 5-Y5 - 101
 * 6-E - terra - para funcionar
 * 7-VEE - terra -ensão negativa para geração de ruído 
 * 8-VSS - terra
 * 9-A2 100
 * 10-A1 010
 * 11-A0 001
 * 12-Y3 - 011
 * 13-Y0 - 000
 * 14-Y1 - 001
 * 15-Y2 - 010
 * 16-VDD-3-15V
 */

class Service{
  public:
    Service(Memory &memory,Drink &drink);
//    void loop();
//    void begin();

    
    
  private:
    Memory *_memory;
    Drink *_drink;
//    int _clockInterval;
//    long _clockMillis;
//    int _ainputReadInterval;
//    long _ainputPrintMillis;
//    long _ainputReadMillis;
//    int _analogInput[8];
////    bool _boot;
//
//   
//    void updateInputPinValue(byte pin);
//    byte _inputPinCounter;
//    byte _selectInputPin;
//    
//    void inputBegin();
};

#endif

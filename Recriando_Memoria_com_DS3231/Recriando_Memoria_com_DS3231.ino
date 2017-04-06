#include "Drink.h"
#include "Memory.h"

// CONNECTIONS:
// DS3231 SDA --> SDA - d2
// DS3231 SCL --> SCL - d1
// DS3231 VCC --> 3.3v or 5v
// DS3231 GND --> GND


#include <pgmspace.h>


//D1/GPIO5 - DS3231 SCL
//D2/GPIO4 - DS3231 SDA
// for software wire use below
//#include <SoftwareWire.h>  // must be included here so that Arduino library object file references work
//#include <RtcDS3231.h>
//
//SoftwareWire myWire(4, 5);//SoftwareWire myWire(SDA, SCL); //nano é assim sda = 4 e scl = 5
//RtcDS3231<SoftwareWire> Rtc(myWire);
// for software wire use above */

/* for normal hardware wire use below */
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
RtcDS3231<TwoWire> rtc(Wire);
/* for normal hardware wire use above */

Drink drink = Drink();
Memory memory = Memory(drink, drink.getSize(), rtc);
//Memory memory = Memory(drink, drink.getSize(), rtc);


void setup () 
{ //memory.testaRtc(rtc);
    Serial.begin(115200);
//    Serial.begin(9600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    //--------RTC SETUP ------------
    rtc.Begin();
    // if you are using ESP-01 then uncomment the line below to reset the pins to
    // the available pins for SDA, SCL
    // Wire.begin(0, 2); // due to limited pins, use pin 0 and 2 for SDA, SCL

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!rtc.IsDateTimeValid()) 
    {   rtc.SetIsRunning(false);
        Serial.println("\nRTC lost confidence in the DateTime!");
        rtc.SetDateTime(compiled);
        Serial.println("\nCompiled");
        printDateTime(compiled);
        Serial.println("\nGetDateTime");
        printDateTime(rtc.GetDateTime());
    }

    if (!rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        rtc.SetIsRunning(true);
    }

    RtcDateTime now = rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        rtc.SetDateTime(compiled);
    }

    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    rtc.Enable32kHzPin(false);
    rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone); 

    Serial.println("GRAVANDO");
    byte valor = 0;
    for(int address = 0; address<4096; address++){
      Serial.print("Address: "); Serial.print(address);
      Serial.print(" - Valor Salvo: "); Serial.print(valor);
      memory.eeprom_write(address, valor);
      Serial.print(" - Valor Recuperado: ");Serial.println((byte)memory.eeprom_read(address));
      valor++;
    }
    Serial.println("RECUPERANDO");
    for(int address = 0; address<4096; address++){
      Serial.print("Address: "); Serial.print(address);
      Serial.print(" - Valor Salvo: "); Serial.print(valor);
      Serial.print(" - Valor Recuperado: ");Serial.println((byte)memory.eeprom_read(address));
      valor++;
    } 
    
}

void loop () 
{
    RtcDateTime now = rtc.GetDateTime();
    delay(15000);
    printDateTime(now);
    Serial.println();

//    for(;;)
//    {
//        rtc.SetIsRunning(false);
//        Serial.println(">>> Rtc ready for storage <<<");
//
//        delay(10000); // ten seconds
//    }
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
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

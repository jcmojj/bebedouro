#include "Drink.h"
#include "Memory.h"

// CONNECTIONS:
// DS3231 SDA --> SDA - d2dsd
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

    memory.eeprom_write_char(0,5);

    Serial.print("ep1026: "); Serial.print(memory.eeprom_read_char(1026));
//    memory.memoryTest();
//      char teste[200];
////    Serial.print("\nbytes: "); Serial.write(memory.readBytes(70,10));
////    Serial.print("\nbytes: "); Serial.println(memory.readBytes(48,64,&teste[0]));
//for(byte i =1;i<130;i++){
//  Serial.print("\nPosicoes="); Serial.print(i+48-1);
//  Serial.print("\nbytes: "); Serial.println(memory.readBytes(48,i,&teste[0],200));
//}
// memory.memoryTest();
 
// String teste = "123456789112345678921234567893123456789qwertyuiopasdfghjklzxcvbnm1234567890qwertyuiop0987654321lkjhgfdsa12345zxcvb67890nm,.123456789112345678921234567893123456789qwertyuiopasdfghjklzxcvbnm1234567890qwertyuiop0987654321lkjhgfdsa12345zxcvb67890nm,.";
//  char buffer[250];
//  char teste[250];
//  Serial.print("\nbytes1: "); Serial.println(memory.readBytes(48,100,&teste[0],101));

//  teste[0] = 'j';
//  teste[1] = 'o';
//  teste[2] = 's';
//  teste[3] = 'e';
//  teste[4] = 'j';
//  teste[5] = 'o';
//  teste[6] = 's';
//  teste[7] = 'e';
//  teste[8] = '\0';


//memory.cleanInfo();
char email[userEmailSpace] = "jcmojj@gmail.com";
Serial.print("Size: ");Serial.println(sizeof(email));
memory.writeBytes(0,&email[0],sizeof(email),userEmailSpace);

char buffer[userEmailSpace];
Serial.print("\nreadBytes: ");  Serial.print(memory.readBytes(0,sizeof(email),&email[0],userEmailSpace));
Serial.print("\nreadByte: ");   
for(int i = 0; i<userEmailSpace;i++){
  Serial.print(memory.eeprom_read_byte(i));
}
Serial.print("\nreadChar: ");   
for(int i = 0; i<userEmailSpace;i++){
  Serial.print(memory.eeprom_read_char(i));
}



//char teste[] = "123456789112345678921234567893123456789qwertyuiopasdfghjklzxcvbnm1234567890qwertyuiop0987654321lkjhgfdsa12345zxcvb67890nm,.123456789112345678921234567893123456789qwertyuiopasdfghjklzxcvbnm1234567890qwertyuiop0987654321lkjhgfdsa12345zxcvb67890nm,.";
//  memory.writeBytes(0, &teste[0],55,64);
//  Serial.print("\nPrint: "); Serial.println(memory.readBytes(0,64,&buffer[0],64));
//  memory.print();
////  memory.writeBytes(48, 2, &teste[0]);
//  
//  Serial.print("\nPosicoes="); Serial.print(2);
//  Serial.print("\nbytes2: "); Serial.println(memory.readBytes(0,100,&teste[0]));
//    Serial.print("\nPosicoes="); Serial.print(2);
//  Serial.print("\nbytes3: "); Serial.println(memory.readBytes(0,100,&teste[0]));
//    char email[] = "jcmojj@gmail.com";
    
    
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


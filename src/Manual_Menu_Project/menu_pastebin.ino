#include <Bounce2.h>
#include <LiquidCrystal.h> // on importe la bibliothèque pour LCD
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#include "InputManager.h"
#include "defineUsedAction.h"
#include "FileFunction.h"


//-----------Menu vars-----------
InputManager BP_mnger(15,16,17,A0);
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

char btn_push;
byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 13;


//----------------GPS Vars --------------
unsigned int GPSSearchPeriod=2000;//2000 milisecondes
long unsigned int oldMillisVallue;//2000 milisecondes
bool isStarted=false; // to start the gps if it is true
TinyGPSPlus gps;// The TinyGPS++ object
SoftwareSerial ss(3, 2);//The serial connection to the GPS deviceRXPin=3;TXPin=2


//------------SD write & Read--------------
bool fileIsChanged=true;
String FileName="IF232017/Tour3.txt";
//-----------Functions-------
#include "GPSFunction.h"
#include "menuFunction.h"


void setup()
{
    lcd.begin(8,2);  //Initialize a 2x16 type LCD
    Serial.begin(9600);  //Initialize a 2x16 type LCD
    ss.begin(4800);  //Initialize a 2x16 type LCD
    SD.begin(10);
    MainMenuDisplay();
    delay(1000);
}
void loop()
{
//  read the button signification
    btn_push = ReadKeypad();
    // deal with menu
    MainMenuBtn();
    // action is set
    dealWithUsedEvents();

    while (ss.available() > 0){

    if (gps.encode(ss.read()))
      if (gps.location.isUpdated() || gps.date.isUpdated() || gps.time.isUpdated() || gps.altitude.isUpdated()
        || gps.satellites.isUpdated() || gps.hdop.isUpdated()){
          if (isStarted && (GPSSearchPeriod<=millis()-oldMillisVallue)) {
            if (fileIsChanged) {
                overWriteLine2File(FileName,makeGPSSentence( ));
                fileIsChanged=false;
            }
            else{
              WriteLine2File(FileName,makeGPSSentence( ));
            }
          oldMillisVallue=millis();

        }
         }
}

}

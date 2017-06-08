#include <MenuBackend.h>
#include <LiquidCrystal.h>
#include <Bounce2.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

// instance variables
//File myFile;
/*void readFunction(String fileName) ;
void overWriteLine2File( String fileName, String line);
void WriteLine2File( String fileName, String line);*/
//------------ GPS vars----------------
TinyGPSPlus gps;// The TinyGPS++ object
SoftwareSerial ss(3, 2);//The serial connection to the GPS deviceRXPin=3;TXPin=2
//-----local-------
#include "InputManager.h"
#include "defineUsedAction.h"
#include "menuFunction.h"
#include "GPSFunction.h"

void dealWithUsedEvents(byte menuUsed );
//----------- parametters vars------------
byte read;
long unsigned int GPSSearchPeriod=2000;//2000 milisecondes
long unsigned int oldMillisVallue;//2000 milisecondes

bool isStarted=false; // to start the gps if it is true
void setup()
{
  Serial.begin(9600);
  ss.begin(4800);
  lcd.begin(8, 2);
  menuSetup();
}


void loop()
{
  read=BP_mnger.pressedButton();
  navigateMenus(read);
  dealWithUsedEvents(menuUsedCode);
  menuUsedCode=0;

    while (ss.available() > 0){
    if (gps.encode(ss.read()))
      if (gps.location.isUpdated() || gps.date.isUpdated() || gps.time.isUpdated() || gps.altitude.isUpdated()
        || gps.satellites.isUpdated() || gps.hdop.isUpdated()){
          if (isStarted && (GPSSearchPeriod<=millis()-oldMillisVallue)) {
          makeGPSSentence( );
          oldMillisVallue=millis();// if i comment this line it works

        }
         }
}


}
void dealWithUsedEvents(byte menuUsed ){
      if(menuUsed!=0){
          // deal with what has been used

        switch (menuUsed) {
          case UBattery:
            DisplayTextfloat("Bat:",BP_mnger.gettension(),1,0);
            break;

          case UonOff:
            DisplayText("Started","Filename");
            isStarted=!isStarted;
            Serial.print("isStarted: ");
            Serial.println(isStarted);
            break;

          case UCourt:
            DisplayText("UCourt","Filename");
            GPSSearchPeriod=2000;
            break;

          case UMoyen:
            DisplayText("UMoyen","Filename");
            GPSSearchPeriod=15000;
            break;

          case UTour3:
            DisplayText("UTour3","Filename");
            break;

          case UCompagne:
            DisplayText("UCompagne","Filename");
            break;

          case UBatiment:
            DisplayText("UBatiment","Filename");
           break;

          case UCoord:
            DisplayValues(gps.location.lat(),gps.location.lng(),7 );
            break;

          case UTime:

          DisplayTextint("D:","T:",gps.date.value(),gps.time.value());

            break;

          case UStatus:
          DisplayTextint("Sat:","HDOP",gps.satellites.value(),gps.hdop.value());
            break;

        /*  case UAltitude:
          DisplayTextfloat("A:",gps.altitude.meters(),6,0);
            break;

          case USDInfo:
            DisplayText("SDInfo","Filename");
            break;

          case USendTour3:
            DisplayText("SndFile1","Filename");
            break;
          case USendCompagne:
            DisplayText("SndFile2","Filename");
            break;
          case USendBatiment:
            DisplayText("USendBatiment","Filename");
            break;*/

          }



        }

}

/*
void WriteLine2File( String fileName, String line) {
 File myFile = SD.open("Compagne.txt", FILE_WRITE);

  if (myFile) {
     myFile.println(line);
       myFile.close();


   } else {
     Serial.println("error opening test.txt");
   }
 }

void overWriteLine2File( String fileName, String line) {
  File myFile = SD.open("Compagne.txt", O_WRITE | O_CREAT | O_TRUNC);

  if (myFile) {
     myFile.println(line);
       myFile.close();


   } else {
     Serial.println("error opening test.txt");
   }
 }
void readFunction(String fileName) {
  //  myFile = SD.open("IF232017/tour3.txt
 File myFile = SD.open(fileName);

    if (myFile) {
      Serial.print(fileName);
      Serial.println(": ");

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
}
*/

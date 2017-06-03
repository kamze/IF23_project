/**
 * This is the structure of the modelled menu
 *
 * Batterie ok ? if used return 1 " L1: Batterie; L2 e %"
 * Iteneraire
 *   Start  ok? L1: newfile; L2: deltaT=15sec"
 *   Stop  ok?  stop the GPS
 *   Options file
 *      NewFile: ok?
 *      OverWr: ok?
 *   Option points
 *      1sec: ok?
 *      30sec ok?
 *      1min ok?
 * GPSData
 *   Coord ok? "L1: latitude;L2 longitude"
 *   Time ok? "L1:date  ; L2:time"
 *   Status ok? "L1: sat nomber;L2 Hdop"
 *   SpdAlti ok? "L1:speed  ; L2:Altitude"
 * Filemnger ok? "L1: Taille available ; L2: nombre fichier"
 *      lister chose effaser...
 *
 *CE QUI MANQUE: retour depuis n'importe quelle item vers son pere
 *              prevoir define etat used
 *               ajouter des option pour les delai & et fichiers
 *
 */
#include <MenuBackend.h>
#include <LiquidCrystal.h>
#include <Bounce2.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "InputManager.h"
#include "defineUsedAction.h"
#include "menuFunction.h"
#include "GPSFunction.h"


//------------ GPS vars----------------

TinyGPSPlus gps;// The TinyGPS++ object

SoftwareSerial ss(3, 2);//The serial connection to the GPS deviceRXPin=3;TXPin=2
String GPSSentence;

//----------- parametters vars------------
byte read;
unsigned int GPSSearchPeriod=2000;//2000 milisecondes
bool isStarted=false; // to start the gps if it is true
bool isNewFile=true;
void setup()
{
  Serial.begin(9600);
  ss.begin(4800);

  lcd.begin(8, 2);
  menuSetup();
  Serial.println("Starting navigation:\r\nOK: s   Down: s   Left: q   Right: d   z: esp");
}


void loop()
{

  read=BP_mnger.pressedButton();
  navigateMenus(read);
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      if (gps.location.isUpdated() || gps.date.isUpdated() || gps.time.isUpdated() || gps.altitude.isUpdated()
        || gps.satellites.isUpdated() || gps.hdop.isUpdated()   )
      {

        //GPSSentence=makeGPSSentence( gps);

        if(getmenuUsed()!=0){
          Serial.print("menuUsedCode: ");
          Serial.println(getmenuUsed());
          // deal with what has been used

            switch (getmenuUsed()) {
          case UBattery:
            DisplayTextfloat("Bat:",BP_mnger.gettension(),1,0);
            break;

          case UStart:
            DisplayText("Started","Filename");
            isStarted=true;
            break;

          case UStop:
            DisplayText("Stop","Filename");
            isStarted=true;
            break;

          case UNewFile:
            DisplayText("UNewFile","Filename");
            isNewFile=true;
            break;

          case UOverWr:
            DisplayText("UOverWr","Filename");
            isNewFile=false;
            break;

          case UCourt:
            DisplayText("UCourt","Filename");
            GPSSearchPeriod=2000;
            break;

          case UMoyen:
            DisplayText("UMoyen","Filename");
            GPSSearchPeriod=15000;
            break;

          case ULong:
            DisplayText("ULong","Filename");
            GPSSearchPeriod=60000;
            break;

          case UCoord:
            DisplayValues(gps.location.lat(),gps.location.lng(),7 );
            break;

          case UTime:

          DisplayTextint("D","T",gps.date.value(),gps.time.value());

            break;

          case UStatus:
          DisplayTextint("Sat:","HDOP",gps.satellites.value(),gps.hdop.value());
            break;

          case UAltitude:
          DisplayTextfloat("A:",gps.altitude.meters(),6,0);
            break;

          case UFilemnger:
            DisplayText("UFilemnger","Filename");
            break;
          }

          setmenuUsed(0);

        }
      }
}

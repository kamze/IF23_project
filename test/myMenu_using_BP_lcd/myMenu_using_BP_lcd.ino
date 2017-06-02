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
#include <Arduino.h>
#include <MenuBackend.h>
#include <LiquidCrystal.h>
#include <Bounce2.h>
#include "InputManager.h"
#include "defineUsedAction.h"

void handleInvalidMove(MenuMoveEvent menu);
void menuChangeEvent(MenuChangeEvent changed);
void menuUseEvent(MenuUseEvent used);
void navigateMenus( byte read);
//this controls the menu backend and the event generation
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
byte menuUsedCode=0;
InputManager BP_mnger(15,16,17,A0);
byte read;
bool isStarted=false;
bool isNewFile=true;
unsigned int GPSSearchPeriod=2000;//2000 milisecondes

MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent);
//beneath is the list of menu items needed to build the menu
MenuItem Battery     = MenuItem(menu, "Battery ", 1);//----usable
MenuItem Iteneraire  = MenuItem(menu, "Itener  ", 1);
MenuItem Start       = MenuItem(menu, "Start   ", 2);//----usable
MenuItem Stop        = MenuItem(menu, "Stop    ", 2);//----usable
MenuItem FileOpn     = MenuItem(menu, "FileOpn ", 2);
MenuItem NewFile     = MenuItem(menu, "NewFile ", 3);//----usable
MenuItem OverWr      = MenuItem(menu, "OverWr  ", 3);//----usable
MenuItem PtOpn       = MenuItem(menu, "PtOpn   ", 2);
MenuItem Seconde_1   = MenuItem(menu, "Court   ", 3);//----usable
MenuItem Secondes_15 = MenuItem(menu, "Moyen   ", 3);//----usable
MenuItem Minute_1    = MenuItem(menu, "Long    ", 3);//----usable
MenuItem GPSData     = MenuItem(menu, "GPSData ", 1);
MenuItem Coord       = MenuItem(menu, "Coord   ", 2);//----usable
MenuItem Time        = MenuItem(menu, "Time    ", 2);//----usable
MenuItem Status      = MenuItem(menu, "Status  ", 2);//----usable
MenuItem SpdAlti     = MenuItem(menu, "SpdAlti ", 2);//----usable
MenuItem Filemnger   = MenuItem(menu, "Filemngr", 1);//----usable

// Display somthing on line 1 and 2 of the lcd screen
void DisplayText(String line1,String line2){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
// Display somthing on line 1 and 2 of the lcd screen
void DisplayValues(String line1,float value, byte precision=3){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(value,precision);
}

void menuSetup()
{
  Serial.println("Setting up menu...");
  //add the file menu to the menu root
  menu.getRoot().add(Battery);
  Battery.addRight(Iteneraire).addRight(GPSData ).addRight(Filemnger);
  Iteneraire.add(Start ).addRight(Stop).addRight(FileOpn).addRight(PtOpn);
  GPSData.add(Coord).addRight(Time).addRight(Status).addRight(SpdAlti);
  FileOpn.add(NewFile).addRight(OverWr);
  PtOpn.add(Seconde_1).addRight(Secondes_15).addRight(Minute_1);
}


//  This is where you define a behaviour for a menu item

void DisplayUsedEvent(byte usedEventNumber ){
 switch (usedEventNumber) {
  case UBattery:
    DisplayValues("Battery",BP_mnger.gettension(),1);
  break;

  case UStart:
    DisplayText("Started","Filename");
    isStarted=true;
  break;

  case UStop:
    DisplayText("UStop","Filename");
    isStarted=false;
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
    DisplayText("UCoord","Filename");
  break;

  case UTime:
    DisplayText("UTime","Filename");
  break;

  case UStatus:
    DisplayText("UStatus","Filename");
  break;

  case USpdAlti:
    DisplayText("USpdAlti","Filename");
  break;

  case UFilemnger:
    DisplayText("UFilemnger","Filename");
  break;

}

}

void menuUseEvent(MenuUseEvent used)
{
  /*lcd.setCursor(0, 0);
  lcd.print(used.item.getName());
  lcd.setCursor(0, 1);
  lcd.print("Used    ");*/

  // ------battery------------

  if(used.item.isEqual(Battery)){
    //Serial.println(used.item.getName());
    menuUsedCode=UBattery;
  }
  // ------Iteneraire------------
  else if (used.item.isEqual(Start)) {
  //  Serial.println(used.item.getName());
    menuUsedCode=UStart ;
  }
  else if (used.item.isEqual(Stop)) {
  //  Serial.println(used.item.getName());
    menuUsedCode=UStop ;
  }
  else if(used.item.isEqual(NewFile)){
    //Serial.println(used.item.getName());
    menuUsedCode=UNewFile;
  }
  else if (used.item.isEqual(OverWr)) {
    //Serial.println(used.item.getName());
    menuUsedCode=UOverWr;
  }
  else if (used.item.isEqual(Seconde_1)) {
  //  Serial.println(used.item.getName());
    menuUsedCode=UCourt;
  }
  else if(used.item.isEqual(Secondes_15)){
    //Serial.println(used.item.getName());
    menuUsedCode=UMoyen;
  }
  else if (used.item.isEqual(Minute_1)) {
    Serial.println(used.item.getName());
    menuUsedCode=ULong;
  }
  // ------GPSdata------------
  else if(used.item.isEqual(Coord)){
    //Serial.println(used.item.getName());
    menuUsedCode=UCoord;
  }
  else if (used.item.isEqual(Time)) {
    //Serial.println(used.item.getName());
    menuUsedCode=UTime;
  }
  else if (used.item.isEqual(Status)) {
    //Serial.println(used.item.getName());
    menuUsedCode=UStatus;
  }
  else if (used.item.isEqual(SpdAlti)) {
    //Serial.println(used.item.getName());
    menuUsedCode=USpdAlti;
  }
  // ------File manger------------
  else if (used.item.isEqual(Filemnger)) {
    //Serial.println(used.item.getName());
    menuUsedCode=UFilemnger;
  }

}

/*Here we get a notification whenever the user changes the menu
 That is, when the menu is navigated*/
void menuChangeEvent(MenuChangeEvent changed)
{
  //Serial.print("Menu change ");
  //Serial.print(changed.from.getName());
  //Serial.print(" ");
  //Serial.println(changed.to.getName());
  //------by lcd----------------
  lcd.setCursor(0, 0);
  lcd.print(changed.from.getName());
  lcd.setCursor(0, 1);
  lcd.print(changed.to.getName());
}


void navigateMenus( byte read) {
  MenuItem currentMenu=menu.getCurrent();

  switch (read){

  case 1:

    if(!(currentMenu.hasAfterChildren())){  //if the current menu has a child and has been pressed enter then menu navigate to item below
      menu.use();
    }
    else{  //otherwise, if menu has no child and has been pressed enter the current menu is used
      menu.moveDown();
    }
    break;

  case 2:
    menu.moveLeft();

    break;
  case 3:
    menu.moveRight();

    break;
  case 4:
    //menu.toRoot();  //back to main
    menu.moveUp();

    break;
  }
}


void setup()
{
  Serial.begin(9600);
  lcd.begin(8, 2);
  menuSetup();
  Serial.println("Starting navigation:\r\nOK: s   Down: s   Left: q   Right: d   z: esp");
}


void loop()
{
  read=BP_mnger.pressedButton();
  navigateMenus(read);

  if(menuUsedCode!=0){
    Serial.print("menuUsedCode: ");
    Serial.println(menuUsedCode);
    DisplayUsedEvent(menuUsedCode);
    menuUsedCode=0;

  }
}

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
MenuItem altitude     = MenuItem(menu, "altitude ", 2);//----usable
MenuItem Filemnger   = MenuItem(menu, "Filemngr", 1);//----usable

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
InputManager BP_mnger(15,16,17,A0);

byte menuUsedCode=0;
// Display somthing on line 1 and 2 of the lcd screen
void DisplayText(String line1,String line2){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
// Display somthing on line 1 and 2 of the lcd screen
void DisplayValues(float value1,float value2, byte precision=3){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(value1,precision);
  lcd.setCursor(0, 1);
  lcd.print(value2,precision);
}
// displaying something with line & text on a specific lcd line
void DisplayTextfloat(String text,float value, byte precision=3, byte line=0){
  text+=String(value,precision);
  lcd.clear();
  lcd.setCursor(0, line);
  lcd.print(text);
}

void DisplayTextint(String text1,String text2,int value1,long int value2){

  text1+=String(value1);
  text2+=String(value2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
}
byte getmenuUsed() {
  return menuUsedCode;
}
void setmenuUsed(byte n) {
  menuUsedCode=n;
}
void menuSetup()
{
  Serial.println("Setting up menu...");
  //add the file menu to the menu root
  menu.getRoot().add(Battery);
  Battery.addRight(Iteneraire).addRight(GPSData ).addRight(Filemnger);
  Iteneraire.add(Start).addRight(Stop).addRight(FileOpn).addRight(PtOpn);
  GPSData.add(Coord).addRight(Time).addRight(Status).addRight(altitude);
  FileOpn.add(NewFile).addRight(OverWr);
  PtOpn.add(Seconde_1).addRight(Secondes_15).addRight(Minute_1);
}


//  This is where you define a behaviour for a menu item

void DisplayUsedEvent(byte usedEventNumber ){


}



void menuUseEvent(MenuUseEvent used)
{
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
  else if (used.item.isEqual(altitude)) {
    //Serial.println(used.item.getName());
    menuUsedCode=UAltitude;
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

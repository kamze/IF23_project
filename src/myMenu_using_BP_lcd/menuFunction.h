
/**
 * This is the structure of the modelled menu
 *
 * Batterie ok ? if used return 1 " L1: Batterie; L2 e %"
 * Iteneraire
 *      Court: ok?
 *      Moyen ok?
 *      Tour3 ok ? we write gps data in it
 *      Compagne ok ? we write gps data in it
 *      Batiment ok ? we write gps data in it
 * GPSData
 *      Coord ok? "L1: latitude;L2 longitude"
 *      Time ok? "L1:date  ; L2:time"
 *      Status ok? "L1: sat nomber;L2 Hdop"
 *      SendFile
 *          Tour3 ok ? serial print Tour3
 *          Compagne ok ? serial print Compagne
 *          Batiment ok ? serial print Batiment
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

MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent);
//beneath is the list of menu items needed to build the menu
MenuItem Battery     = MenuItem(menu, "Battery ", 1);//----usable
MenuItem OnOff       = MenuItem(menu, "OnOff   ", 1);//----usable
MenuItem Court       = MenuItem(menu, "Court   ", 1);//----usable
MenuItem Moyen       = MenuItem(menu, "Moyen   ", 1);//----usable
MenuItem Tour3       = MenuItem(menu, "Tour3   ", 1);//----usable
MenuItem Compagne    = MenuItem(menu, "Compagne", 1);//----usable
MenuItem Batiment    = MenuItem(menu, "Batiment", 1);//----usable
MenuItem Coord       = MenuItem(menu, "Coord   ", 1);//----usable
MenuItem Time        = MenuItem(menu, "Time    ", 1);//----usable
MenuItem Status      = MenuItem(menu, "Status  ", 1);//----usable


LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
InputManager BP_mnger(15,16,17,A0);

byte menuUsedCode=0;
// Display somthing on line 1 and 2 of the lcd screen

void menuSetup()
{
  menu.getRoot().add(Battery);
  Battery.addRight(OnOff).addRight(Court).addRight(Moyen);
  Moyen.addRight(Tour3).addRight(Compagne).addRight(Batiment);
  Batiment.addRight(Coord).addRight(Time).addRight(Status);
}


/*Here we get a notification whenever the user changes the menu
 That is, when the menu is navigated*/

void menuChangeEvent(MenuChangeEvent changed){
 // to save memory we use the 4 files in 2 different submenu
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


// when a usable icone is pressed thats where we set values to deal with it later
void menuUseEvent(MenuUseEvent used){
  if(used.item.isEqual(Battery)){
    menuUsedCode=UBattery;
  }
  // ------Iteneraire------------
  else if (used.item.isEqual(OnOff)) {
    menuUsedCode=UonOff ;
  }

  else if (used.item.isEqual(Court)) {
    menuUsedCode=UCourt;
  }
  else if(used.item.isEqual(Moyen)){
    menuUsedCode=UMoyen;
  }

  else if(used.item.isEqual(Tour3) && used.item.getBefore()==NULL) {
    menuUsedCode=UTour3;
  }
  else if (used.item.isEqual(Compagne) && used.item.getBefore()==NULL) {
    menuUsedCode=UCompagne;
  }
  else if (used.item.isEqual(Batiment) && used.item.getBefore()==NULL) {
    menuUsedCode=UBatiment;
  }

  // ------GPSdata------------
  else if(used.item.isEqual(Coord)){
    menuUsedCode=UCoord;
  }
  else if (used.item.isEqual(Time)) {
    menuUsedCode=UTime;
  }
  else if (used.item.isEqual(Status)) {
    menuUsedCode=UStatus;
  }

}

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

void DisplayTextint(String text1,String text2,unsigned int value1,long int value2){

  text1+=String(value1);
  text2+=String(value2);

  Serial.println(text1);
  Serial.println(text2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
}

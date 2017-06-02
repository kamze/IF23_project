#include "Arduino.h"
#include <MenuBackend.h>    //MenuBackend library - copyright by Alexander Brevig
#include <LiquidCrystal.h>  //this library is included in the Arduino IDE
#include "GPSMenu.h"  //this library is included in the Arduino IDE

GPSMenu::GPSMenu(LiquidCrystal* lcd){
 _lcd = lcd;
 _lcd->begin(8, 2);
 _lcd->clear();

  menu =  MenuBackend(menuUseEvent,menuChangeEvent);
  Battery     = MenuItem(menu, "Battery ", 1);//----usable
  Iteneraire  = MenuItem(menu, "Itener  ", 1);
  Start       = MenuItem(menu, "Start   ", 2);//----usable
  Stop        = MenuItem(menu, "Stop    ", 2);//----usable
  FileOpn     = MenuItem(menu, "FileOpn ", 2);
  NewFile     = MenuItem(menu, "NewFile ", 3);//----usable
  OverWr      = MenuItem(menu, "OverWr  ", 3);//----usable
  PtOpn       = MenuItem(menu, "PtOpn   ", 2);
  Seconde_1   = MenuItem(menu, "Court   ", 3);//----usable
  Secondes_15 = MenuItem(menu, "Moyen   ", 3);//----usable
  Minute_1    = MenuItem(menu, "Long    ", 3);//----usable
  GPSData     = MenuItem(menu, "GPSData ", 1);
  Coord       = MenuItem(menu, "Coord   ", 2);//----usable
  Time        = MenuItem(menu, "Time    ", 2);//----usable
  Status      = MenuItem(menu, "Status  ", 2);//----usable
  SpdAlti     = MenuItem(menu, "SpdAlti ", 2);//----usable
  Filemnger   = MenuItem(menu, "Filemngr", 1);//----usable

  GPSMenu::menuSetup();
}

//this function builds the menu and connects the correct items together
void GPSMenu::menuSetup()
{
  //add the file menu to the menu root
  menu.getRoot().add(Battery);
  Battery.addRight(Iteneraire).addRight(GPSData ).addRight(Filemnger);
  Iteneraire.add(Start ).addRight(Stop).addRight(FileOpn).addRight(PtOpn);
  GPSData.add(Coord).addRight(Time).addRight(Status).addRight(SpdAlti);
  FileOpn.add(NewFile).addRight(OverWr);
  PtOpn.add(Seconde_1).addRight(Secondes_15).addRight(Minute_1);
}

//  This is where you define a behaviour for a menu item

void GPSMenu::menuUseEvent(MenuUseEvent used)
 {
   _lcd->setCursor(0, 0);
   _lcd->print(used.item.getName());
   _lcd->setCursor(0, 1);
   _lcd->print("Used    ");
}
/*
  Here we get a notification whenever the user changes the menu
  That is, when the menu is navigated
*/
void GPSMenu::menuChangeEvent(MenuChangeEvent changed)
{
  _lcd->setCursor(0, 0);
  _lcd->print(changed.from.getName());
  _lcd->setCursor(0, 1);
  _lcd->print(changed.to.getName());
}

void GPSMenu::navigateMenus( byte read) {
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
    menu.moveUp();
    break;
  }
}

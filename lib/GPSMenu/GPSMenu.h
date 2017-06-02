#ifndef GPSMENU_h
#define GPSMENU_h

#include "Arduino.h"
#include <MenuBackend.h>    //MenuBackend library - copyright by Alexander Brevig
#include <LiquidCrystal.h>  //this library is included in the Arduino IDE
class GPSMenu
{
  public:
    GPSMenu(LiquidCrystal* lcd);
    void navigateMenus( byte read);
    MenuBackend menu;
    MenuItem Battery;
    MenuItem Iteneraire;
    MenuItem Start;
    MenuItem Stop;
    MenuItem FileOpn;
    MenuItem NewFile;
    MenuItem OverWr;
    MenuItem PtOpn;
    MenuItem Seconde_1;
    MenuItem Secondes_15;
    MenuItem Minute_1;
    MenuItem GPSData;
    MenuItem Coord;
    MenuItem Time;
    MenuItem Status;
    MenuItem SpdAlti;
    MenuItem Filemnger;


    private:
    void menuChangeEvent(MenuChangeEvent changed);
    void menuUseEvent(MenuUseEvent used);
    void menuSetup();
    LiquidCrystal *_lcd;


};

#endif

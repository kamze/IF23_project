/**
 *
 * This is the structure of the modelled menu
 *
 * Batterie ok ?" L1: Batterie; L2 e %"
 * Location
 *   Coord ok? "L1: latitude;L2 longitude"
 *   Time ok? "L1:date  ; L2:time"
 * Iteneraire
 *   Defaut ok? L1: newfile; L2: deltaT=2h"
 *   Options file
 *      new file: ok? e
 *      overwrite ok? e
 *   Option points
 *      30min: ok? e
 *      1heur ok? e
 *      3heur ok? e
 * Filemnger ok? "L1: Taille available ; L2: nombre fichier"
 *
 *CE QUI MANQUE: retour depuis n'importe quelle item vers son pere
 *               ajouter des option pour les delai & et fichiers
 *
 */

#include <MenuBackend.h>

void handleInvalidMove(MenuMoveEvent menu);
void menuChangeEvent(MenuChangeEvent changed);
void menuUseEvent(MenuUseEvent used);
void navigateMenus( byte read);
//this controls the menu backend and the event generation
int DelayMinutes=180;

MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent);
  //beneath is list of menu items needed to build the menu
  MenuItem Battery   = MenuItem(menu, "Battery", 1);
  MenuItem Location    = MenuItem(menu, "Location", 1);
    MenuItem Coord = MenuItem(menu, "Coord", 2);
    MenuItem Time = MenuItem(menu, "Time", 2);
  MenuItem Iteneraire    = MenuItem(menu, "Itener", 1);
    MenuItem Defaut = MenuItem(menu, "Default", 2).getName();
    MenuItem FileOpn = MenuItem(menu, "FileOpn", 2);
      MenuItem NewFile   = MenuItem(menu, "NewFile", 3);
      MenuItem OverWr   = MenuItem(menu, "OverWr", 3);
    MenuItem PtOpn = MenuItem(menu, "PtOpn", 2);
      MenuItem min30   = MenuItem(menu, "30 minutes", 3);
      MenuItem heure_1   = MenuItem(menu, "1 heure", 3);
      MenuItem heure_3   = MenuItem(menu, "3 heure", 3);
  MenuItem Filemnger    = MenuItem(menu, "Filemnger", 1);

//this function builds the menu and connects the correct items together
void menuSetup()
{
  Serial.println("Setting up menu...");
  //add the file menu to the menu root

  menu.getRoot().add(Battery);
  Battery.addRight(Location).addRight(Iteneraire).addRight(Filemnger);
  Location.add(Coord).addRight(Time);
  Iteneraire.add(Defaut).addRight(FileOpn).addRight(PtOpn);
    FileOpn.add(NewFile).addRight(OverWr);
    PtOpn.add(min30).addRight(heure_1).addRight(heure_3);
}

//  This is where you define a behaviour for a menu item

void menuUseEvent(MenuUseEvent used)
 {
  Serial.print("Menu use ");
  if(used.item.getName()==min30.getName()){
  Serial.println(used.item.getName());
  DelayMinutes=30;

}
else if (used.item.getName()==heure_1.getName()) {
  Serial.println(used.item.getName());
  DelayMinutes=60;

}
 else if (used.item.getName()==heure_3.getName()) {
  Serial.println(used.item.getName());
  DelayMinutes=120;

}

}
/*
  Here we get a notification whenever the user changes the menu
  That is, when the menu is navigated
*/
void menuChangeEvent(MenuChangeEvent changed)
{
  Serial.print("Menu change ");
  Serial.print(changed.from.getName());
  Serial.print(" ");
  Serial.println(changed.to.getName());
}

void setup()
{
  Serial.begin(9600);
  menuSetup();
  Serial.println("Starting navigation:\r\nOK: s   Down: s   Left: q   Right: d   z: esp");
}

void navigateMenus( byte read) {
  MenuItem currentMenu=menu.getCurrent();
  switch (read){
  case 's':
    if(!(currentMenu.hasAfterChildren())){  //if the current menu has a child and has been pressed enter then menu navigate to item below
      menu.use();
    }
    else{  //otherwise, if menu has no child and has been pressed enter the current menu is used
      menu.moveDown();
    }
  break;

  case 'd':
    menu.moveRight();

  break;
  case 'q':
    menu.moveLeft();
    break;
  case 'z':
      //menu.toRoot();  //back to main
      menu.moveUp();

  break;
  }
}


void loop()
{
  if (Serial.available())
  {
    byte read = Serial.read();
    navigateMenus(read);
  }
}

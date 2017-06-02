#include <MenuBackend.h>    //MenuBackend library - copyright by Alexander Brevig
#include <LiquidCrystal.h>  //this library is included in the Arduino IDE
#include "InputManager.h"

void menuChanged(MenuChangeEvent changed);
void menuUsed(MenuUseEvent used);
void navigateMenus();

const int buttonPinEnter = 1;   // pin for the Enter button
const int buttonPinLeft = 2;      // pin for the Up button
const int buttonPinRight = 3;    // pin for the Down button
const int buttonPinEsc = 4;     // pin for the Esc button

int lastButtonPushed = 0;

InputManager BP_mnger(15,16,17,A0);
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//Menu variables
MenuBackend menu = MenuBackend(menuUsed,menuChanged);
//initialize menuitems
MenuItem menu1Item1 = MenuItem("Item1");
MenuItem menuItem1SubItem1 = MenuItem("It1Sub1");
MenuItem menuItem1SubItem2 = MenuItem("It1Sub2");
MenuItem menu1Item2 = MenuItem("Item2");
MenuItem menuItem2SubItem1 = MenuItem("It2Sub1");
MenuItem menuItem2SubItem2 = MenuItem("It2Sub2");
MenuItem menuItem3SubItem3 = MenuItem("It2Sub3");
MenuItem menu1Item3 = MenuItem("Item3");

void setup()
{
Serial.begin(9600);
  lcd.begin(8, 2);
  //configure menu
  menu.getRoot().add(menu1Item1);
  menu1Item1.addRight(menu1Item2).addRight(menu1Item3);
  menu1Item1.add(menuItem1SubItem1).addRight(menuItem1SubItem2);
  menu1Item2.add(menuItem2SubItem1).addRight(menuItem2SubItem2).addRight(menuItem3SubItem3);
  menu.toRoot();
  lcd.setCursor(0,0);

}

void loop()
{
  lastButtonPushed=BP_mnger.pressedButton();
  Serial.print("last bp pressed");Serial.println(lastButtonPushed);
  navigateMenus();

}

//on affiche le menu au quelle on est partie
void menuChanged(MenuChangeEvent changed){

  MenuItem newMenuItem=changed.to; //get the destination menu

  lcd.setCursor(0,1); //set the start position for lcd printing to the second row

  if(newMenuItem.getName()==menu.getRoot()){
    lcd.print("Main Menu       ");
  }
  else if(newMenuItem.getName()=="Item1"){
    lcd.print("Item1           ");
  }
  else if(newMenuItem.getName()=="Item1SubItem1"){
    lcd.print("Item1SubItem1");
  }
  else if(newMenuItem.getName()=="Item1SubItem2"){
    lcd.print("Item1SubItem2   ");
  }
  else if(newMenuItem.getName()=="Item2"){
    lcd.print("Item2           ");
  }
  else if(newMenuItem.getName()=="Item2SubItem1"){
    lcd.print("Item2SubItem1   ");
  }
  else if(newMenuItem.getName()=="Item2SubItem2"){
    lcd.print("Item2SubItem2   ");
  }
  else if(newMenuItem.getName()=="Item2SubItem3"){
    lcd.print("Item2SubItem3   ");
  }
  else if(newMenuItem.getName()=="Item3"){
    lcd.print("Item3           ");
  }
}

void menuUsed(MenuUseEvent used){
  lcd.setCursor(0,0);
  lcd.print("You used        ");
  lcd.setCursor(0,1);
  //l'item dans le structure
  lcd.print(used.item.getName());
  //delay(3000);  //delay to allow message reading
  lcd.setCursor(0,0);
//  menu.toRoot();  //back to Main
}

void navigateMenus() {
  MenuItem currentMenu=menu.getCurrent();
  switch (lastButtonPushed){
  case buttonPinEnter:
    if(!(currentMenu.moveDown())){  //if the current menu has a child and has been pressed enter then menu navigate to item below
      menu.use();
    }
    else{  //otherwise, if menu has no child and has been pressed enter the current menu is used
      menu.moveDown();
    }
    break;

  case buttonPinRight:
    menu.moveRight();
    Serial.println("right");

    break;
  case buttonPinLeft:
    menu.moveLeft();
    Serial.println("left");
    break;
    case buttonPinEsc:
      menu.toRoot();  //back to main
      break;
  }

  //lastButtonPushed=0; //reset the lastButtonPushed variable
}

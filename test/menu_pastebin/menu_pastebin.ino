

#include <LiquidCrystal.h>
#include <Bounce2.h>
#include "InputManager.h"
#include <LiquidCrystal.h> // on importe la bibliothèque pour LCD


//-----------Headers---------------
void MenuA();
void MenuB();
void MenuC();
void MenuD();
void MainMenuDisplay();
void MainMenuBtn();
char ReadKeypad();

//-----------End Headers---------------

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
InputManager BP_mnger(15,16,17,A0);

int keypad_pin = A0;
int keypad_value = 0;
int keypad_value_old = 0;

char btn_push;

byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 4;

void setup()
{
    lcd.begin(8,2);  //Initialize a 2x16 type LCD
    Serial.begin(9600);  //Initialize a 2x16 type LCD

    MainMenuDisplay();
    delay(1000);
}
void loop()
{
  /*keypad_value = BP_mnger.pressedButton();
    Serial.println("keypad_value");
    Serial.print(keypad_value);*/

    btn_push = ReadKeypad();

    MainMenuBtn();

    if(btn_push == 'S')//enter selected menu
    {
        switch (mainMenuPage)
        {
            case 1:
              MenuA();
              break;
            case 2:
              MenuB();
              break;
            case 3:
              MenuC();
              break;
            case 4:
              MenuD();
              break;
        }

      //    MainMenuDisplay();
    }



    delay(10);

}//--------------- End of loop() loop ---------------------
void MenuA()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Inside A");


}
void MenuB()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Inside B");

}
void MenuC()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Inside C");


}
void MenuD()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Inside D");


}

void MainMenuDisplay()
{
    lcd.clear();
    lcd.setCursor(0,0);
    switch (mainMenuPage)
    {
        case 1:
          lcd.print("1. Menu A");
          break;
        case 2:
          lcd.print("2. Menu B");
          break;
        case 3:
          lcd.print("3. Menu C");
          break;
        case 4:
          lcd.print("4. Menu D");
          break;
    }
}

void MainMenuBtn()
{
    if(btn_push == 'R')
    {
        mainMenuPage++;
        if(mainMenuPage > mainMenuTotal)
          mainMenuPage = 1;
    }
    else if(btn_push == 'L')
    {
        mainMenuPage--;
        if(mainMenuPage == 0)
          mainMenuPage = mainMenuTotal;
    }

    if(mainMenuPage != mainMenuPageOld) //only update display when page change
    {
      Serial.println("mainMenuPage != mainMenuPageOld");
        MainMenuDisplay();
        mainMenuPageOld = mainMenuPage;
    }
}

char ReadKeypad()
{
  keypad_value = BP_mnger.pressedButton();
  if(keypad_value == 1)
   return 'S'; // Select
  else if(keypad_value==2)
   return 'L'; // left
  else if(keypad_value==3)
    return 'R'; // right
  else if(keypad_value==4)
    return 'A'; // shortcut to activate GPS
  else
    return 'N';

}

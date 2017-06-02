#include "Arduino.h"
#include "GPSMenu.h"  //this library is included in the Arduino IDE

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

GPSMenu menu(&lcd);
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting navigation:\r\nOK: s   Down: s   Left: q   Right: d   z: esp");
}


void loop()
{
  if (Serial.available())
  {
    byte read = Serial.read();
    menu.navigateMenus(read);
  }
}

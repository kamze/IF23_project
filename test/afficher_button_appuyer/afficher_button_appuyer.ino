#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

int BP1=15;
int BP0=16;
int BPEN=17;
// par defaut 011 = aucune bouton
byte donnee_bouton=3;
int bouton_appuye =0;

void setup() {
  lcd.begin(8, 2);
  Serial.begin(9600);
  pinMode(BP1, INPUT);
  pinMode(BP0, INPUT);
  pinMode(BPEN, INPUT);


}

void loop() {
  // read the value from the sensor:
//BPEN BP1 BP0
//BP0
donnee_bouton=0;
donnee_bouton += digitalRead(BP0);
//BP1
  donnee_bouton += digitalRead(BP1)<<1;
//BPEN
  donnee_bouton +=  digitalRead(BPEN)<<2;
Serial.println(donnee_bouton);

  switch(donnee_bouton){
    case 3 :
      bouton_appuye=0;
      break;
    case 4 :
      bouton_appuye=1;
      break;
    case 5 :
      bouton_appuye=2;
      break;
    case 6 :
      bouton_appuye=3;
      break;
    case 7 :
      bouton_appuye=4;
      break;
  }

  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  lcd.print("SW BP");
  lcd.setCursor(0,1);
  lcd.print("sw");
  lcd.setCursor(2,1);
  lcd.print(bouton_appuye);


}

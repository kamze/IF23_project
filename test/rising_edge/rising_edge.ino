#include <Bounce2.h>

Bounce debouncer_BP1 = Bounce();
Bounce debouncer_BP0 = Bounce();
Bounce debouncer_BPEN = Bounce();
int BP1=15;
int BP0=16;
int BPEN=17;

int bouton_appuye=0;
void setup() {
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  debouncer_BP1.attach(BP1);
  debouncer_BP1.interval(5); // interval in ms

  debouncer_BP0.attach(BP0);
  debouncer_BP0.interval(5); // interval in ms

  debouncer_BPEN.attach(BPEN);
  debouncer_BPEN.interval(5); // interval in ms
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  bouton_appuye=0;

  debouncer_BPEN.update();
  debouncer_BP0.update();
  debouncer_BP1.update();
  bool IS_BPEN_rose=debouncer_BPEN.rose();
  bool IS_BP0_high=debouncer_BP0.read();
  bool IS_BP1_high=debouncer_BP1.read();

  if(IS_BPEN_rose){
    if (IS_BP0_high) {
      if (IS_BP1_high) {
        bouton_appuye=4; // bp4 ->111

      }
      else{
        bouton_appuye=2;//BP2 : ->101

      }

    }
    else{
      if (IS_BP1_high) {
        bouton_appuye=3;

      }
      else{
        bouton_appuye=1;

      }

    }

    Serial.print("bouton_appuye: ");
    Serial.println(bouton_appuye);
    Serial.print("IS_BPEN_rose: ");
    Serial.println(IS_BPEN_rose);
    Serial.print("IS_BP0_high: ");
    Serial.println(IS_BP0_high);
    Serial.print("IS_BP1_high: ");
    Serial.println(IS_BP1_high);
    Serial.println("------------------ ");
  }
}

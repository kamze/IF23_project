#include <Bounce2.h>
#include "Arduino.h"
#include "InputManager.h"

InputManager::InputManager(int BP1, int BP0, int BPEN, int tensionPin)
{
  pinMode(BP1, INPUT);
  pinMode(BP0, INPUT);
  pinMode(BPEN, INPUT);
  pinMode(tensionPin, INPUT);

  _BP1 = BP1;
  _BP0 = BP0;
  _BPEN = BPEN;
  _tensionPin=tensionPin;

  debouncer_BP1 = Bounce();
  debouncer_BP0 = Bounce();
  debouncer_BPEN = Bounce();

  debouncer_BP1.attach(BP1);
  debouncer_BP1.interval(5); // interval in ms

  debouncer_BP0.attach(BP0);
  debouncer_BP0.interval(5); // interval in ms

  debouncer_BPEN.attach(BPEN);
  debouncer_BPEN.interval(5); // interval in ms
}

// which button was pressed last
int InputManager::pressedButton()
{
  int bouton_appuye=0;

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
  }
    return bouton_appuye;
  //return IS_BPEN_rose;
}

// acquire the voltage

float InputManager::gettension(){
  int sensorValue;
  float volt_value;
  sensorValue = analogRead(_tensionPin);
  volt_value = map(sensorValue, 0, 1023, 0,7);
return volt_value;
}
